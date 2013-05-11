#ifndef _CUJSON_HPP_
#define _CUJSON_HPP_

#include <string>
#include <vector>
#include <deque>
#include <istream>
#include <ostream>
#include <iostream>

namespace json
{
	//! Warning codes
	enum WarningCode
	{
		WC_MultiplePairsOneName	//!< Multiple pairs, which are direct children of the same object, have the same name.
	};

	//! Behaviour of the parser when a warning is reported.
	enum WarningPolicy
	{
		WP_Ignore,			//!< Ignore the warning.
		WP_TreatAsError		//!< Report an error and quit.
	};

	//! Error codes
	enum ErrorCode
	{
		EC_EOF,							//!< Unexpected end-of-file.
		EC_ExpectedPair,				//!< Expected a pair.
		EC_ExpectedValue,				//!< Expected a value.
		EC_ExpectedObjectDelimiter,		//!< Expected left curly brace, or a comma.
		EC_MissingRootObject,			//!< The document doesn't have the root object.
		/*!
		 * If the parser encounters two pairs with the same name, which have the same parent,
		 * it calls IErrorCallback::onWarning. When this method returns WP_TreadAsError, IErrorCallback::onError is called
		 * with this value.
		 */
		EC_MultiplePairsOneName
	};

	//! JSON value types
	enum ValueType
	{
		VT_Object,		//!< Object is a collection of name-value pairs.
		VT_Array,		//!< Array is an ordered collection of values.
		VT_String,		//!< String is a sequence of UTF-8 characters.
		VT_Number,		//!< Number is a floating-point, 64 bit numerical value.
		VT_Boolean,		//!< True or false.
		VT_Null			//!< null. Also used by ValueHandle for nonexistent values.
	};

	//! Returns textual description of a warning.
	const std::string& warningToString(WarningCode wc);
	//! Returns textual description of an error.
	const std::string& errorToString(ErrorCode ec);

	//! The base class for all values.
	class Value
	{
	public:
		const ValueType type;	//!< Type of the value.

		/*! \brief Constructor.
		 * \param type Type of the value.
		 */
		Value(ValueType type);
		//! Destructor.
		virtual ~Value();

		/*! \brief Converts the value to std::string.
		 * If type of the value is VT_String, then returns std::string value stored in it.
		 * Othrewise returns defValue.
		 * \param defValue A value which is returned in case the value isn't a string value.
		 */
		std::string string(const std::string& defValue = std::string()) const;
		/*! \brief Converts the value to int.
		 * If type of the value is VT_Number, then returns int value stored in it.
		 * Othrewise returns defValue. Returns rounded value.
		 * \param defValue A value which is returned in case the value isn't a numerical value.
		 */
		int integer(int defValue = 0) const;
		/*! \brief Converts the value to double.
		 * If type of the value is VT_Number, then returns double value stored in it.
		 * Othrewise returns defValue.
		 * \param defValue A value which is returned in case the value isn't a numerical value.
		 */
		double number(double defValue = 0) const;
		/*! \brief Converts the value to bool.
		 * If type of the value is VT_Boolean, then returns bool value stored in it.
		 * Othrewise returns defValue.
		 * \param defValue A value which is returned in case the value isn't a boolean value.
		 */
		bool boolean(bool defValue = false) const;

		//! Converts Value to ObjectValue
		class ObjectValue* toObject();
		//! Converts Value to ObjectValue
		const class ObjectValue* toObject() const;
		//! Converts Value to ArrayValue
		class ArrayValue* toArray();
		//! Converts Value to ArrayValue
		const class ArrayValue* toArray() const;
		//! Converts Value to StringValue
		class StringValue* toString();
		//! Converts Value to StringValue
		const class StringValue* toString() const;
		//! Converts Value to NumberValue
		class NumberValue* toNumber();
		//! Converts Value to NumberValue
		const class NumberValue* toNumber() const;
		//! Converts Value to BoolValue
		class BoolValue* toBool();
		//! Converts Value to BoolValue
		const class BoolValue* toBool() const;
		//! Converts Value to NullValue
		class NullValue* toNull();
		//! Converts Value to NullValue
		const class NullValue* toNull() const;
	};

	//! \brief JSON pair.
	/*!
	 * Pair represents string-value pair.
	 * E. g.:
	 * "numbers" : [ 0, 34, 54]
	 * is a pair named "numbers" of value being an array.
	 */
	class Pair
	{
	public:
		const std::string name;	//!< Name of the pair. Read-only.
		Value* value;			//!< Value of the pair.

		//! Constructor.
		Pair(const std::string& name);
		//! Destructor.
		~Pair();
	};

	/*! \brief JSON object.
	 * An object is a collection of name-value pairs.
	 * E.g.:
	 * {
	 * 		"one" : 1,
	 * 		"two" : 2
	 * }
	 * is an object with two name-value pairs.
	 * Child pairs aren't stored in the original order.
	 */
	class ObjectValue: public Value
	{
	public:
		//! Constructor.
		ObjectValue();
		//! Destructor.
		~ObjectValue();

		//! Returns number of child pairs.
		unsigned int numChildren() const;
		//! Returns a pointer to a child at the specified index.
		Pair* child(unsigned int index);
		//! Returns a pointer to a child at the specified index.
		const Pair* child(unsigned int index) const;
		//! Returns a pointer to a child with the specified name.
		Pair* child(const std::string& name);
		//! Returns a pointer to a child with the specified name.
		const Pair* child(const std::string& name) const;
		/*! \brief Adds a child pair.
		 * If a pair with specified name already exists, it is deleted and replaced with pr.
		 * \param pr A pair to be added.
		 * \return True if pr replaced another pair, false otherwise.
		 */
		bool addChild(Pair* pr); // returns true if there was a pair with the same name

	private:
		std::vector<Pair*> m_children;
	};

	/*! \brief JSON array.
	 * A collection of JSON values.
	 * Values are in the same order as in the input file.
	 * Example:
	 * [ 32, 45, 12 ]
	 */
	class ArrayValue: public Value
	{
	public:
		//! Constructor.
		ArrayValue();
		//! Destructor.
		~ArrayValue();

		//! Returns number of child values.
		unsigned int numChildren() const;
		//! Returns a pointer to a child at the specified index.
		Value* child(unsigned int index);
		//! Returns a pointer to a child at the specified index.
		const Value* child(unsigned int index) const;
		//! Adds the value at the specified index.
		void addChild(unsigned int index, Value* value);
		//! Appends the value at the end of the array.
		void appendChild(Value* value);
		//! Removes a value at the specified index.
		void removeChild(unsigned int index);

	private:
		std::vector<Value*> m_values;
	};

	//! JSON string.
	class StringValue: public Value
	{
	public:
		std::string value;	//!< The value.

		//! Constructor.
		StringValue();
	};

	//! JSON number.
	class NumberValue: public Value
	{
	public:
		double value;	//!< The value.

		//! Constructor.
		NumberValue();
	};

	//! JSON boolean value.
	class BoolValue: public Value
	{
	public:
		bool value;	//!< The value.

		//! Constructor.
		BoolValue();
	};

	//! JSON null value.
	class NullValue: public Value
	{
	public:
		//! Constructor.
		NullValue();
	};

	/*! \brief Error callback.
	 * A pointer to its subclass is passed to Document::load.
	 * Its methods are called to signal occurrences of warnings and errors.
	 */
	class IErrorCallback
	{
	public:
		//! Destructor.
		virtual ~IErrorCallback();
		/*! \brief Called to report a warning.
		 * As for now, warning is reported only when an object has two, or more, pairs with the same name.
		 * \return The return value specifies whether the warning should be treated as error (if so, onError will be called to).
		 */
		virtual WarningPolicy onWarning(int line, WarningCode code)=0;
		/*! \brief Called to report an error.
		 * Possible errors:
		 * 	-unexpected end-of-file
		 * 	-occurrence of an unexpected sequence instead of a pair
		 * 	-occurrence of an unexpected sequence instead of a value
		 * 	-occurence of a character different than a comma or }
		 * 	-inability to parse the root object
		 */
		virtual void onError(int line, ErrorCode code, const std::string& readToken)=0;
	};

	class StdErrorCallback : public IErrorCallback
	{
	public:
		std::ostream& stream;	//!< Stream.
		std::string fileName;	//!< File name of parsed JSON document.

		/*! \brief Contructor
		 * \param stream Reference to a stream to which messages will be written.
		 * \param fileName Name of parsed file, used to build messages. Can be empty.
		 */
		StdErrorCallback(std::ostream& stream, const std::string& fileName);
		//! Destructor
		~StdErrorCallback();

		//! Writes warning message to stream.
		WarningPolicy onWarning(int line, WarningCode wc);
		//! Writes error message to stream.
		void onError(int line, ErrorCode ec, const std::string& readToken);
	};

	/*! \brief Represents a stream of tokens.
	 * ITokenStream decouples I/O operations from parsing.
	 * ITokenStream's subclasses don't have to load all tokens at once, loading can be done progressively.
	 */
	class ITokenStream
	{
	public:
		//! Destructor.
		virtual ~ITokenStream();
		/*! \brief Peeks a token at the specified index from the current position in the stream.
		 * This method should not pop peeked token from memory.
		 * \param index Offset from the current position in the stream.
		 * \param token  The token.
		 * \return Returns true on success, or false if an error has occurred
		 * (all errors are interpreted as end-of-file).
		 */
		virtual bool peek(unsigned int index, std::string& token)=0;
		/*! Notifes the stream, that token at index 0 is no longer needed, and that the position in the stream has
		 * to be increased by one.
		 */
		virtual void pop()=0;
		//! Returns line number at the specified index.
		virtual int lineNum(unsigned int index)=0;
	};

	/*! \brief Helper class for creating token streams.
	 * It encasulates extraction of tokens from a stream.
	 */
	class TokenStreamHelper: public ITokenStream
	{
	public:
		//! Constructor.
		TokenStreamHelper();

	protected:
		//! Token.
		struct Token
		{
			int lineNum;		//!< Line in which the token begins.
			std::string value;	//!< Token.

			//! Constructor.
			Token(int lineNum = -1, const std::string& value = std::string());
		};

		int m_lineNum;				//!< Number of the current line.
		std::deque<Token> m_tokens;	//!< The tokens.
		Token m_currToken;	//!< The current token.

		/*! \brief Parses a character.
		 * Subclasses have to call this method to build tokens.
		 * \param c The character to be parsed.
		 */
		void m_feed(char c);
		//! Adds m_currToken to m_tokens. Should be called when end-of-file is reached.
		virtual void m_flush();
	};

	//! Token stream using std::istream
	class StdTokenStream: public TokenStreamHelper
	{
	public:
		//! Constructor.
		StdTokenStream(std::istream& str);

		//! Peeks a token.
		bool peek(unsigned int index, std::string& token);
		//! Removes a token.
		void pop();
		//! Returns line number for the specified token.
		int lineNum(unsigned int index);

	private:
		std::istream& m_str;
	};

	/*! \brief JSON document.
	 * Holds pointer to the root object. Manages the whole JSON file.
	 */
	class Document
	{
	public:
		//! Constructor.
		Document();
		//! Destructor.
		~Document();

		/*! \brief Parses a file.
		 * \param ts Token stream.
		 * \param ec Error callback.
		 * \return Returns True on success, false otherwise.
		 */
		bool load(ITokenStream* ts, IErrorCallback* ec);

		//! Returns the root object.
		ObjectValue* root();

	private:
		ObjectValue* m_root;
	};

	/*
	 * Path
	 */

	/* \brief Path to an element.
	 * Describes a location of an element in a tree.
	 * Allows for quick access to specific element.
	 */
	class Path
	{
	public:
		//! Constructor.
		Path();
		/* \brief Constructor.
		 * Constructs a path from the given string.
		 * \param elems A string containing elements separated using '/'.
		 */
		Path(const std::string& elems);
		/* \brief Contructor.
		 * Copies contents of elems to m_elems.
		 * Useful when names of the elements contain '/'.
		 * \param elems A vector containing elements.
		 */
		Path(const std::vector<std::string>& elems);

		//! Appends single element to the path.
		void append(const std::string& elem);
		//! Converts the path to a string.
		std::string toString() const;

		//! Returns number of path's elements.
		size_t numElements() const;
		//! Returns element with the specified index, or asserts.
		const std::string& element(size_t index) const;

	private:
		std::vector<std::string> m_elems;
	};

	/*
	 * Handles
	 */

	//! JSON element handle.
	template<class T>
	class Handle
	{
	};

	//! JSON pair handle.
	template<>
	class Handle<Pair>
	{
		friend class Handle<Value>;

	public:
		//! Contructor.
		Handle(const Pair* pr = 0);

		//! Assignment operator.
		Handle<Pair>& operator =(const Handle<Pair>& h);

		//! Retrives pointer to the pair.
		const Pair* pointer() const;

		//! Returns name of the pair.
		std::string name() const;
		//! Returns handle of the value.
		Handle<Value> value() const;
		//! Finds value specified by p.
		Handle<Value> findValue(const Path& p) const;

		//! Returns true, if the pair is not null.
		operator bool() const;

	private:
		const Pair* m_pair;

		Handle<Value> m_findVal(const Path& p, size_t i) const;
	};

	//! JSON value handle.
	template<>
	class Handle<Value>
	{
		friend class Handle<Pair>;

	public:
		//! Constructor.
		Handle<Value>(const Value* v = 0);

		//! Assignment operator.
		Handle<Value>& operator =(const Handle<Value>& h);

		/*! \brief Returns type of the value.
		 * If the value is null, returns VT_Null.
		 */
		ValueType type() const;
		//! Returns pointer to the value.
		const Value* pointer() const;

		//! Tries to convert the value to a string. If fails, returns defVal.
		std::string string(const std::string& defVal = std::string()) const;
		//! Tries to convert the value to a integer. If fails, returns defVal.
		int integer(int defVal = 0) const;
		//! Tries to convert the value to a floating point number. If fails, returns defVal.
		double number(double defVal = 0) const;
		//! Tries to convert the value to a bool. If fails, returns defVal.
		bool boolean(bool defVal = false) const;
		//! Returns true if the value is null, or its type is VT_Null.
		bool isNull() const;

		//! For array and object values returns number of children, for other types returns 0.
		unsigned int numChildren() const;
		//! For objects returns a pair with the specified name (or 0), for other types returns 0.
		Handle<Pair> childPair(const std::string& name) const;
		//! For objects returns a pair at the specified index (or 0), for other types returns 0.
		Handle<Pair> childPair(unsigned int index) const;
		//! Returns child at the given index for arrays, 0 for other values.
		Handle<Value> childValue(unsigned int index) const;
		//! Finds value specified by p.
		Handle<Value> findValue(const Path& p) const;

		//! Returns true, if the value if null.
		operator bool() const;

	private:
		const Value* m_value;

		Handle<Value> m_findVal(const Path& p, size_t i) const;
	};

	typedef Handle<Pair> PairHandle;
	typedef Handle<Value> ValueHandle;

	/*
	 * Implementation
	 */

	// miJSON::Handle<Pair>
	inline Handle<Pair>::Handle(const Pair* pr)
			: m_pair(pr)
	{
	}

	inline Handle<Pair>& Handle<Pair>::operator =(const Handle<Pair>& h)
	{
		m_pair = h.m_pair;
		return (*this);
	}

	inline const Pair* Handle<Pair>::pointer() const
	{
		return m_pair;
	}

	inline std::string Handle<Pair>::name() const
	{
		if (m_pair)
			return m_pair->name;
		return std::string();
	}

	inline Handle<Value> Handle<Pair>::value() const
	{
		if (m_pair)
			return ValueHandle(m_pair->value);
		return 0;
	}

	inline Handle<Value> Handle<Pair>::findValue(const Path& p) const
	{
		return this->m_findVal(p, 0);
	}

	inline Handle<Pair>::operator bool() const
	{
		return (m_pair != 0);
	}

	inline Handle<Value> Handle<Pair>::m_findVal(const Path& p, size_t i) const
	{
		if(p.numElements() == 0 || !m_pair)
			return Handle<Value>();

		std::cout<<'/'<<m_pair->name;

		if(p.numElements()-1 == i)
		{
			if(m_pair && m_pair->name == p.element(i))
				return m_pair->value;
			else
				return Handle<Value>();
		}

		if(!m_pair->value)
			return Handle<Value>();
		return this->value().m_findVal(p, i+1);
	}

	inline Handle<Value>::Handle(const Value* v)
			: m_value(v)
	{
	}

	inline Handle<Value>& Handle<Value>::operator =(const Handle<Value>& h)
	{
		m_value = h.m_value;
		return (*this);
	}

	inline ValueType Handle<Value>::type() const
	{
		if (m_value)
			return m_value->type;
		return VT_Null;
	}

	inline const Value* Handle<Value>::pointer() const
	{
		return m_value;
	}

	inline std::string Handle<Value>::string(const std::string& defVal) const
	{
		if (m_value != 0 && m_value->type == VT_String)
			return ((const StringValue*) m_value)->value;
		return defVal;
	}

	inline int Handle<Value>::integer(int defVal) const
	{
		if (m_value != 0 && m_value->type == VT_Number)
			return (int)((const NumberValue*) m_value)->value;
		return defVal;
	}

	inline double Handle<Value>::number(double defVal) const
	{
		if (m_value != 0 && m_value->type == VT_Number)
			return ((const NumberValue*) m_value)->value;
		return defVal;
	}

	inline bool Handle<Value>::boolean(bool defVal) const
	{
		if (m_value != 0 && m_value->type == VT_Boolean)
			return ((const BoolValue*) m_value)->value;
		return defVal;
	}

	inline bool Handle<Value>::isNull() const
	{
		return (m_value == 0 || m_value->type == VT_Null);
	}

	inline unsigned int Handle<Value>::numChildren() const
	{
		if (!m_value)
			return 0;

		if (m_value->type == VT_Object)
			return ((const ObjectValue*) m_value)->numChildren();
		else if (m_value->type == VT_Array)
			return ((const ArrayValue*) m_value)->numChildren();

		return 0;
	}

	inline Handle<Pair> Handle<Value>::childPair(const std::string& name) const
	{
		if (m_value != 0 && m_value->type == VT_Object)
			return PairHandle(((const ObjectValue*) m_value)->child(name));
		return PairHandle(0);
	}

	inline Handle<Pair> Handle<Value>::childPair(unsigned int index) const
	{
		if (m_value != 0 && m_value->type == VT_Object)
			return PairHandle(((const ObjectValue*) m_value)->child(index));
		return PairHandle(0);
	}

	inline Handle<Value> Handle<Value>::childValue(unsigned int index) const
	{
		if (m_value != 0 && m_value->type == VT_Array)
			return ValueHandle(((const ArrayValue*) m_value)->child(index));
		return ValueHandle(0);
	}

	inline Handle<Value> Handle<Value>::findValue(const Path& p) const
	{
		return this->m_findVal(p, 0);
	}

	inline Handle<Value>::operator bool() const
	{
		return (m_value != 0);
	}

	inline Handle<Value> Handle<Value>::m_findVal(const Path& p, size_t i) const
	{
		return this->childPair(p.element(i)).m_findVal(p, i);
	}
}

#endif /* _CUJSON_HPP_ */
