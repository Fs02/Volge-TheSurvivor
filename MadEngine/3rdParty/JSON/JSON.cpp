#include "JSON.hpp"
#include <cassert>
#include <cstring>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace json;

/*
 * Private API
 */

namespace _cu
{
	namespace json
	{
		enum ParseRes
		{
			PR_Ok,
			PR_NoMatch,
			PR_Error
		};

		ParseRes parseObject(::json::ITokenStream* ts, ::json::Value*& v, ::json::IErrorCallback* ec);
		ParseRes parseArray(::json::ITokenStream* ts, ::json::Value*& v, ::json::IErrorCallback* ec);
		ParseRes parseString(::json::ITokenStream* ts, ::json::Value*& v, ::json::IErrorCallback* ec);
		ParseRes parseNumber(::json::ITokenStream* ts, ::json::Value*& v, ::json::IErrorCallback* ec);
		ParseRes parseBool(::json::ITokenStream* ts, ::json::Value*& v, ::json::IErrorCallback* ec);
		ParseRes parseNull(::json::ITokenStream* ts, ::json::Value*& v, ::json::IErrorCallback* ec);
		ParseRes parsePair(::json::ITokenStream* ts, ::json::Pair*& pair, ::json::IErrorCallback* ec);

		bool isWhitespace(char c);
		bool isSpecial(char c);
		bool isNumber(const std::string& tk);
		double strToNumber(const std::string& tk);

		int round(double n)
		{
			double fr = n - std::floor(n);
			if (fr >= 0.5)
				return (int)std::ceil(n);
			return (int)std::floor(n);
		}

		ParseRes parseObject(::json::ITokenStream* ts, ::json::Value*& v, ::json::IErrorCallback* ec)
		{
			std::string token;

			if (!ts->peek(0, token))
			{
				if (ec)
					ec->onError(ts->lineNum(0), EC_EOF, std::string());
				return PR_Error;
			}
			if (token != "{")
				return PR_NoMatch;
			ts->pop();

			::json::ObjectValue* obj = new ::json::ObjectValue();

			if (!ts->peek(0, token))
			{
				if (ec)
					ec->onError(ts->lineNum(0), EC_EOF, std::string());
				return PR_Error;
			}
			if (token == "}")
			{
				v = obj;
				ts->pop();
				return PR_Ok;
			}

			while (true)
			{
				ParseRes res;
				::json::Pair* pr = 0;

				if ((res = parsePair(ts, pr, ec)) != PR_NoMatch)
				{
					if (res == PR_Error)
					{
						delete obj;
						return PR_Error;
					} else if (obj->addChild(pr))
					{
						if (ec)
						{
							if(ec->onWarning(ts->lineNum(0), WC_MultiplePairsOneName)==WP_TreatAsError)
							{
								std::string tk;
								ts->peek(0, tk);
								ec->onError(ts->lineNum(0), EC_MultiplePairsOneName, tk);
								return PR_Error;
							}
						}
					}
				} else
				{
					std::string tk;
					ts->peek(0, tk);
					if (ec)
						ec->onError(ts->lineNum(0), EC_ExpectedPair, tk);
					return PR_Error;
				}

				if (!ts->peek(0, token))
				{
					if (ec)
						ec->onError(ts->lineNum(0), EC_EOF, std::string());
					return PR_Error;
				}

				if (token == "}")
				{
					v = obj;
					ts->pop();
					return PR_Ok;
				} else if (token == ",")
				{
					ts->pop();
					continue;
				} else
				{
					delete obj;
					std::string tk;
					ts->peek(0, tk);
					if (ec)
						ec->onError(ts->lineNum(0), EC_ExpectedObjectDelimiter, tk);
					return PR_Error;
				}
			}

			delete obj;
			return PR_NoMatch;
		}

		ParseRes parseArray(::json::ITokenStream* ts, ::json::Value*& v, ::json::IErrorCallback* ec)
		{
			std::string token;

			if (!ts->peek(0, token))
			{
				if (ec)
					ec->onError(ts->lineNum(0), EC_EOF, std::string());
				return PR_Error;
			}

			if (token != "[")
				return PR_NoMatch;
			ts->pop();

			::json::ArrayValue* arr = new ::json::ArrayValue();

			if (!ts->peek(0, token))
			{
				delete arr;
				if (ec)
					ec->onError(ts->lineNum(0), EC_EOF, std::string());
				return PR_Error;
			}
			if (token == "]")
			{
				ts->pop();
				v = arr;
				return PR_Ok;
			}

			while (true)
			{
				ParseRes res;
				::json::Value* val;

				if ((res = parseObject(ts, val, ec)) != PR_NoMatch)
				{
					if (res == PR_Error)
					{
						delete arr;
						return PR_Error;
					}
				} else if ((res = parseArray(ts, val, ec)) != PR_NoMatch)
				{
					if (res == PR_Error)
					{
						delete arr;
						return PR_Error;
					}
				} else if ((res = parseString(ts, val, ec)) != PR_NoMatch)
				{
					if (res == PR_Error)
					{
						delete arr;
						return PR_Error;
					}
				} else if ((res = parseNumber(ts, val, ec)) != PR_NoMatch)
				{
					if (res == PR_Error)
					{
						delete arr;
						return PR_Error;
					}
				} else if ((res = parseBool(ts, val, ec)) != PR_NoMatch)
				{
					if (res == PR_Error)
					{
						delete arr;
						return PR_Error;
					}
				} else if ((res = parseNull(ts, val, ec)) != PR_NoMatch)
				{
					if (res == PR_Error)
					{
						delete arr;
						return PR_Error;
					}
				} else
				{
					std::string tk;
					ts->peek(0, tk);
					if (ec)
						ec->onError(ts->lineNum(0), EC_ExpectedValue, tk);
					delete arr;
					return PR_Error;
				}

				arr->appendChild(val);

				if (!ts->peek(0, token))
				{
					if (ec)
						ec->onError(ts->lineNum(0), EC_EOF, std::string());
					return PR_Error;
				}

				if (token == ",")
				{
					ts->pop();
					continue;
				} else if (token == "]")
				{
					ts->pop();
					v = arr;
					return PR_Ok;
				}
			}

			return PR_Error;
		}

		ParseRes parseString(::json::ITokenStream* ts, ::json::Value*& v, ::json::IErrorCallback* ec)
		{
			std::string token;

			if (!ts->peek(0, token))
			{
				if (ec)
					ec->onError(ts->lineNum(0), EC_EOF, std::string());
				return PR_Error;
			}

			if (token[0] == '\"' && token[token.size() - 1] == '\"')
			{
				ts->pop();
				::json::StringValue* str = new ::json::StringValue();
				str->value = token.substr(1, token.size() - 2);
				v = str;
				return PR_Ok;
			}

			return PR_NoMatch;
		}

		ParseRes parseNumber(::json::ITokenStream* ts, ::json::Value*& v, ::json::IErrorCallback* ec)
		{
			std::string token;

			if (!ts->peek(0, token))
			{
				if (ec)
					ec->onError(ts->lineNum(0), EC_EOF, std::string());
				return PR_Error;
			}

			if (isNumber(token))
			{
				ts->pop();
				::json::NumberValue* num = new ::json::NumberValue();
				num->value = strToNumber(token);
				v = num;
				return PR_Ok;
			}

			return PR_NoMatch;
		}

		ParseRes parseBool(::json::ITokenStream* ts, ::json::Value*& v, ::json::IErrorCallback* ec)
		{
			std::string token;

			if (!ts->peek(0, token))
			{
				if (ec)
					ec->onError(ts->lineNum(0), EC_EOF, std::string());
				return PR_Error;
			}

			if (token == "true" || token == "false")
			{
				ts->pop();
				::json::BoolValue* bv = new ::json::BoolValue();
				bv->value = (token == "true");
				v = bv;
				return PR_Ok;
			}

			return PR_NoMatch;
		}

		ParseRes parseNull(::json::ITokenStream* ts, ::json::Value*& v, ::json::IErrorCallback* ec)
		{
			std::string token;

			if (!ts->peek(0, token))
			{
				if (ec)
					ec->onError(ts->lineNum(0), EC_EOF, std::string());
				return PR_Error;
			}

			if (token == "null")
			{
				ts->pop();
				v = new ::json::NullValue();
				return PR_Ok;
			}

			return PR_NoMatch;
		}

		ParseRes parsePair(::json::ITokenStream* ts, ::json::Pair*& pr, ::json::IErrorCallback* ec)
		{
			std::string token;
			std::string name;

			if (!ts->peek(0, token))
			{
				if (ec)
					ec->onError(ts->lineNum(0), EC_EOF, std::string());
				return PR_Error;
			}

			if (token[0] == '\"' && token[token.size() - 1] == '\"')
			{
				name = token.substr(1, token.size() - 2);
			} else
				return PR_NoMatch;

			if (!ts->peek(1, token))
			{
				if (ec)
					ec->onError(ts->lineNum(1), EC_EOF, std::string());
				return PR_Error;
			}
			if (token != ":")
				return PR_NoMatch;

			ts->pop();
			ts->pop();

			pr = new ::json::Pair(name);
			ParseRes res;

			if ((res = parseObject(ts, pr->value, ec)) != PR_NoMatch)
			{
				if (res == PR_Error)
				{
					delete pr;
					return PR_Error;
				}
			} else if ((res = parseArray(ts, pr->value, ec)) != PR_NoMatch)
			{
				if (res == PR_Error)
				{
					delete pr;
					return PR_Error;
				}
			} else if ((res = parseString(ts, pr->value, ec)) != PR_NoMatch)
			{
				if (res == PR_Error)
				{
					delete pr;
					return PR_Error;
				}
			} else if ((res = parseNumber(ts, pr->value, ec)) != PR_NoMatch)
			{
				if (res == PR_Error)
				{
					delete pr;
					return PR_Error;
				}
			} else if ((res = parseBool(ts, pr->value, ec)) != PR_NoMatch)
			{
				if (res == PR_Error)
				{
					delete pr;
					return PR_Error;
				}
			} else if ((res = parseNull(ts, pr->value, ec)) != PR_NoMatch)
			{
				if (res == PR_Error)
				{
					delete pr;
					return PR_Error;
				}
			} else
			{
				std::string tk;
				ts->peek(0, tk);
				if (ec)
					ec->onError(ts->lineNum(0), EC_ExpectedValue, tk);
				delete pr;
				return PR_Error;
			}

			return PR_Ok;
		}

		bool isWhitespace(char c)
		{
			switch (c)
			{
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				return true;
			default:
				return false;
			}
		}

		bool isSpecial(char c)
		{
			switch (c)
			{
			case '{':
			case '}':
			case '[':
			case ']':
			case ':':
			case ',':
				return true;
			default:
				return false;
			}
		}

		bool isNumber(const std::string& tk)
		{
			bool gotComma = false;
			for (unsigned int i = 0; i < tk.size(); ++i)
			{
				char c = tk[i];
				if (c == '-')
				{
					if (i != 0)
						return false;
				} else if (c == '.')
				{
					if (gotComma)
						return false;
					gotComma = true;
				} else if (c < '0' || c > '9')
					return false;

			}

			return true;
		}

		double strToNumber(const std::string& tk)
		{
			std::stringstream str(tk);
			double n;
			str >> n;
			return n;
		}

		bool comparePairString(const ::json::Pair* pr, const std::string& str)
		{
			return std::strcmp(pr->name.c_str(), str.c_str()) < 0;
		}

		bool comparePairPair(const ::json::Pair* a, const ::json::Pair* b)
		{
			return std::strcmp(a->name.c_str(), b->name.c_str()) < 0;
		}
	}
}

/*
 * Public API
 */

const std::string& json::warningToString(WarningCode wc)
{
	static const std::string messages[]=
	{
			"an object has multiple pairs with the same name"
	};

	return messages[wc];
}

const std::string& json::errorToString(ErrorCode ec)
{
	static const std::string messages[]=
	{
			"unexpected end-of-file",
			"expected a pair",
			"expected a value",
			"expected } or comma",
			"the document doesn't have the root object",
			"an object has multiple pairs with the same name"
	};

	return messages[ec];
}

json::Value::Value(ValueType type)
		: type(type)
{
}

json::Value::~Value()
{
}

std::string json::Value::string(const std::string& defValue) const
{
	if (type == VT_String)
		return ((const StringValue*) this)->value;
	return defValue;
}

int json::Value::integer(int defValue) const
{
	if (type == VT_Number)
		return _cu::json::round(((const NumberValue*) this)->value);
	return defValue;
}

double json::Value::number(double defValue) const
{
	if (type == VT_Number)
		return ((const NumberValue*) this)->value;
	return defValue;
}

bool json::Value::boolean(bool defValue) const
{
	if (type == VT_Boolean)
		return ((const BoolValue*) this)->value;
	return defValue;
}

json::ObjectValue* json::Value::toObject()
{
	if (type == VT_Object)
		return (ObjectValue*) this;
	return 0;
}

const json::ObjectValue* json::Value::toObject() const
{
	if (type == VT_Object)
		return (const ObjectValue*) this;
	return 0;
}

json::ArrayValue* json::Value::toArray()
{
	if (type == VT_Array)
		return (ArrayValue*) this;
	return 0;
}

const json::ArrayValue* json::Value::toArray() const
{
	if (type == VT_Array)
		return (const ArrayValue*) this;
	return 0;
}

json::StringValue* json::Value::toString()
{
	if (type == VT_String)
		return (StringValue*) this;
	return 0;
}

const json::StringValue* json::Value::toString() const
{
	if (type == VT_String)
		return (const StringValue*) this;
	return 0;
}

json::NumberValue* json::Value::toNumber()
{
	if (type == VT_Number)
		return (NumberValue*) this;
	return 0;
}

const json::NumberValue* json::Value::toNumber() const
{
	if (type == VT_Number)
		return (const NumberValue*) this;
	return 0;
}

json::BoolValue* json::Value::toBool()
{
	if (type == VT_Boolean)
		return (BoolValue*) this;
	return 0;
}

const json::BoolValue* json::Value::toBool() const
{
	if (type == VT_Boolean)
		return (const BoolValue*) this;
	return 0;
}

json::NullValue* json::Value::toNull()
{
	if (type == VT_Null)
		return (NullValue*) this;
	return 0;
}

const json::NullValue* json::Value::toNull() const
{
	if (type == VT_Null)
		return (const NullValue*) this;
	return 0;
}

json::Pair::Pair(const std::string& name)
		: name(name), value(0)
{
}

json::Pair::~Pair()
{
	delete value;
}

json::ObjectValue::ObjectValue()
		: Value(VT_Object)
{
}

json::ObjectValue::~ObjectValue()
{
	for (unsigned int i = 0; i < m_children.size(); ++i)
		delete m_children[i];
}

unsigned int json::ObjectValue::numChildren() const
{
	return m_children.size();
}

json::Pair* json::ObjectValue::child(unsigned int index)
{
	assert(index < m_children.size());
	return m_children[index];
}

const json::Pair* json::ObjectValue::child(unsigned int index) const
{
	assert(index < m_children.size());
	return m_children[index];
}

json::Pair* json::ObjectValue::child(const std::string& name)
{
#ifdef _MSC_VER
	Pair ref(name);
	std::vector<Pair*>::iterator iter = std::lower_bound(m_children.begin(), m_children.end(), &ref, &_cu::json::comparePairPair);
#else
	std::vector<Pair*>::iterator iter = std::lower_bound(m_children.begin(), m_children.end(), name, &_cu::json::comparePairString);
#endif
	if (iter != m_children.end() && (*iter)->name == name)
		return (*iter);
	return NULL;
}

const json::Pair* json::ObjectValue::child(const std::string& name) const
{
#ifdef _MSC_VER
	Pair ref(name);
	std::vector<Pair*>::const_iterator iter = std::lower_bound(m_children.begin(), m_children.end(), &ref, &_cu::json::comparePairPair);
#else
	std::vector<Pair*>::const_iterator iter = std::lower_bound(m_children.begin(), m_children.end(), name, &_cu::json::comparePairString);
#endif
	if (iter != m_children.end() && (*iter)->name == name)
		return (*iter);
	return NULL;
}

bool json::ObjectValue::addChild(Pair* pr)
{
#ifdef _MSC_VER
	std::vector<Pair*>::iterator iter = std::lower_bound(m_children.begin(), m_children.end(), pr, &_cu::json::comparePairPair);
#else
	std::vector<Pair*>::iterator iter = std::lower_bound(m_children.begin(), m_children.end(), pr->name, &_cu::json::comparePairString);
#endif
	if (iter != m_children.end() && (*iter)->name == pr->name)
	{
		delete (*iter);
		(*iter) = pr;
		return true;
	} else
	{
		m_children.insert(iter, pr);
		return false;
	}
}

json::ArrayValue::ArrayValue()
		: Value(VT_Array)
{
}

json::ArrayValue::~ArrayValue()
{
	for (unsigned int i = 0; i < m_values.size(); ++i)
		delete m_values[i];
}

unsigned int json::ArrayValue::numChildren() const
{
	return m_values.size();
}

json::Value* json::ArrayValue::child(unsigned int index)
{
	assert(index < m_values.size());
	return m_values[index];
}

const json::Value* json::ArrayValue::child(unsigned int index) const
{
	assert(index < m_values.size());
	return m_values[index];
}

void json::ArrayValue::addChild(unsigned int index, Value* value)
{
	assert(index <= m_values.size());
	m_values.insert(m_values.begin() + index, value);
}

void json::ArrayValue::appendChild(Value* value)
{
	m_values.push_back(value);
}

void json::ArrayValue::removeChild(unsigned int index)
{
	assert(index < m_values.size());
	m_values.erase(m_values.begin() + index);
}

json::StringValue::StringValue()
		: Value(VT_String)
{
}

json::NumberValue::NumberValue()
		: Value(VT_Number), value(0)
{
}

json::BoolValue::BoolValue()
		: Value(VT_Boolean), value(false)
{
}

json::NullValue::NullValue()
		: Value(VT_Null)
{
}

json::IErrorCallback::~IErrorCallback()
{
}

json::StdErrorCallback::StdErrorCallback(std::ostream& stream, const std::string& fileName)
	:stream(stream), fileName(fileName)
{
}

json::StdErrorCallback::~StdErrorCallback()
{
}

json::WarningPolicy json::StdErrorCallback::onWarning(int line, WarningCode wc)
{
	if(fileName.empty())
		stream<<"JSON warning (line "<<line<<"): ";
	else
		stream<<"JSON warning (file "<<fileName<<", line "<<line<<"): ";
	stream<<warningToString(wc)<<"\n";

	return WP_Ignore;
}

void json::StdErrorCallback::onError(int line, ErrorCode ec, const std::string& readToken)
{
	if(fileName.empty())
		stream<<"JSON error (line "<<line<<"): ";
	else
		stream<<"JSON error (file "<<fileName<<", line "<<line<<"): ";
	stream<<errorToString(ec);
	if(!readToken.empty())
		stream<<" (got: "<<readToken<<")\n";
	else
		stream<<"\n";
}

json::ITokenStream::~ITokenStream()
{
}

json::TokenStreamHelper::TokenStreamHelper()
		: m_lineNum(1)
{
}

json::TokenStreamHelper::Token::Token(int lineNum, const std::string& value)
		: lineNum(lineNum), value(value)
{
}

void json::TokenStreamHelper::m_feed(char c)
{
	if (m_currToken.value.size() > 0 && m_currToken.value[0] == '\"')
	{
		if (c == '\n')
		{
			++m_lineNum;
			if (!m_currToken.value.empty() && m_currToken.value[m_currToken.value.size() - 1] == '\r')
				m_currToken.value.erase(m_currToken.value.begin() + (m_currToken.value.size() - 1));
			m_currToken.value += c;
		} else if (c == '\"')
		{
			m_currToken.value += c;
			this->m_flush();
		} else
			m_currToken.value += c;
	} else
	{
		if (_cu::json::isSpecial(c))
		{
			this->m_flush();

			m_currToken.lineNum = m_lineNum;
			m_currToken.value = std::string(1, c);
			this->m_flush();

			m_currToken.value.clear();
		} else if (_cu::json::isWhitespace(c))
		{
			this->m_flush();

			if (c == '\n')
				++m_lineNum;
		} else
		{
			if (m_currToken.value.empty())
				m_currToken.lineNum = m_lineNum;
			m_currToken.value += c;
		}
	}
}

void json::TokenStreamHelper::m_flush()
{
	if (m_currToken.value.size() > 0)
	{
		m_tokens.push_back(m_currToken);
		m_currToken.value.clear();
	}
}

json::StdTokenStream::StdTokenStream(std::istream& str)
		: m_str(str)
{
}

bool json::StdTokenStream::peek(unsigned int index, std::string& token)
{
	while (index >= m_tokens.size())
	{
		if (!m_str || m_str.eof())
		{
			this->m_flush();
			break;
		}
		this->m_feed(m_str.get());
	}

	if (index >= m_tokens.size())
		return false;

	token = m_tokens[index].value;
	return true;
}

void json::StdTokenStream::pop()
{
	m_tokens.pop_front();
}

int json::StdTokenStream::lineNum(unsigned int index)
{
	while (index >= m_tokens.size())
	{
		if (!m_str || m_str.eof())
		{
			this->m_flush();
			break;
		}
		this->m_feed(m_str.get());
	}

	if (index >= m_tokens.size())
		return false;

	return m_tokens[index].lineNum;
}

json::Document::Document()
		: m_root(0)
{
}

json::Document::~Document()
{
	delete m_root;
}

bool json::Document::load(ITokenStream* ts, IErrorCallback* ec)
{
	delete m_root;

	json::Value* v = 0;
	_cu::json::ParseRes res = _cu::json::parseObject(ts, v, ec);
	if (res == _cu::json::PR_NoMatch)
	{
		if (ec)
			ec->onError(1, EC_MissingRootObject, std::string());
		delete v;
		return false;
	}

	if (res == _cu::json::PR_Error)
		return false;

	m_root = (ObjectValue*) v;
	return true;
}

json::ObjectValue* json::Document::root()
{
	return m_root;
}

/*
 * json::Path
 */

json::Path::Path()
{
}

json::Path::Path(const std::string& elems)
{
	std::string elem;
	for(size_t i=0; i < elems.size(); ++i)
	{
		if(elems[i] == '/')
		{
			if(!elem.empty())
				m_elems.push_back(elem);
			elem.clear();
		}
		else
			elem+=elems[i];
	}

	if(!elem.empty())
		m_elems.push_back(elem);
}

json::Path::Path(const std::vector<std::string>& elems)
	:m_elems(elems)
{
}

void json::Path::append(const std::string& elem)
{
	m_elems.push_back(elem);
}

std::string json::Path::toString() const
{
	std::string res;
	for(size_t i=0; i < m_elems.size(); ++i)
	{
		if(i != 0)
			res+='/';
		res+=m_elems[i];
	}
	return res;
}

size_t json::Path::numElements() const
{
	return m_elems.size();
}

const std::string& json::Path::element(size_t index) const
{
	assert(index < m_elems.size());
	return m_elems[index];
}
