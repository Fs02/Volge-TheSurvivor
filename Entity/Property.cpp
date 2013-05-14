#include "Property.hpp"

/*
 * _IPropData
 */

struct _IPropData
{
	bool isMutable;

	_IPropData(bool isMutable)
		:isMutable(isMutable)
	{
	}
	virtual ~_IPropData(){}
	virtual _IPropData* copy() const=0;
};

template<class T>
struct TPropData : public _IPropData
{
	T value;

	TPropData(const T& val, bool isMutable=false)
		:_IPropData(isMutable), value(val)
	{
	}

	_IPropData* copy() const
	{
		return new TPropData(value, isMutable);
	}
};

template<>
struct TPropData<std::string> : public _IPropData
{
	std::string value;
	bool isPath;

	TPropData(const std::string& val, bool isPath, bool isMutable=false)
		:_IPropData(isMutable), value(val), isPath(isPath)
	{
	}

	_IPropData* copy() const
	{
		return new TPropData(value, isPath, isMutable);
	}
};

/*
 * Property
 */

Property::Property()
	:m_Data(nullptr)
{
}

Property::Property(const Property& cp)
	:m_Data(nullptr)
{
	if(cp.m_Data)
		m_Data=cp.m_Data->copy();
}

Property::~Property()
{
	delete m_Data;
}

void Property::reset()
{
	delete m_Data;
	m_Data=nullptr;
	m_Name.clear();
}

void Property::setName(const std::string& name)
{
	m_Name=name;
}

const std::string& Property::getName() const
{
	return m_Name;
}

void Property::setBool(bool val)
{
	delete m_Data;
	m_Data=new TPropData<bool>(val);
}

bool Property::getBool() const
{
	TPropData<bool>* pd=dynamic_cast<TPropData<bool>*>(m_Data);
	if(pd)
		return pd->value;
	return false;
}

bool Property::isBool() const
{
	TPropData<bool>* pd=dynamic_cast<TPropData<bool>*>(m_Data);
	return (pd != nullptr);
}

void Property::setFloat(float val)
{
	delete m_Data;
	m_Data=new TPropData<float>(val);
}

float Property::getFloat() const
{
	TPropData<float>* pd=dynamic_cast<TPropData<float>*>(m_Data);
	if(pd)
		return pd->value;
	return 0;
}

bool Property::isFloat() const
{
	TPropData<float>* pd=dynamic_cast<TPropData<float>*>(m_Data);
	return (pd != nullptr);
}

void Property::setVec2(const b2Vec2& val)
{
	delete m_Data;
	m_Data=new TPropData<b2Vec2>(val);
}

b2Vec2 Property::getVec2() const
{
	TPropData<b2Vec2>* pd=dynamic_cast<TPropData<b2Vec2>*>(m_Data);
	if(pd)
		return pd->value;
	return b2Vec2();
}

bool Property::isVec2() const
{
	TPropData<b2Vec2>* pd=dynamic_cast<TPropData<b2Vec2>*>(m_Data);
	return (pd != nullptr);
}

void Property::setString(const std::string& val)
{
	delete m_Data;
	m_Data=new TPropData<std::string>(val, false);
}

std::string Property::getString() const
{
	TPropData<std::string>* pd=dynamic_cast<TPropData<std::string>*>(m_Data);
	if(pd && !pd->isPath)
		return pd->value;
	return std::string();
}

bool Property::isString() const
{
	TPropData<std::string>* pd=dynamic_cast<TPropData<std::string>*>(m_Data);
	return (pd != nullptr) && (!pd->isPath);
}

void Property::setPath(const std::string& val)
{
	delete m_Data;
	m_Data=new TPropData<std::string>(val, true);
}

std::string Property::getPath() const
{
	TPropData<std::string>* pd=dynamic_cast<TPropData<std::string>*>(m_Data);
	if(pd && pd->isPath)
		return pd->value;
	return std::string();
}

bool Property::isPath() const
{
	TPropData<std::string>* pd=dynamic_cast<TPropData<std::string>*>(m_Data);
	return (pd != nullptr) && (pd->isPath);
}

void Property::setAsMutable(bool isMutable)
{
	if(m_Data)
		m_Data->isMutable=isMutable;
}

bool Property::isMutable() const
{
	if(m_Data)
		return m_Data->isMutable;
	return false;
}
