#ifndef _PROPERTY_HPP_
#define _PROPERTY_HPP_

#include "stdafx.h"

struct _IPropData;

class Property
{
public:
	Property();
	explicit Property(const Property& cp);
	~Property();

	void reset();

	void setName(const std::string& name);
	const std::string& getName() const;

	void setBool(bool val);
	bool getBool() const;
	bool isBool() const;

	void setFloat(float val);
	float getFloat() const;
	bool isFloat() const;

	void setVec2(const b2Vec2& val);
	b2Vec2 getVec2() const;
	bool isVec2() const;

	void setString(const std::string& val);
	std::string getString() const;
	bool isString() const;

	void setPath(const std::string& val);
	std::string getPath() const;
	bool isPath() const;

	// by default properties are immutable
	void setAsMutable(bool isMutable);
	bool isMutable() const;

private:
	std::string m_Name;
	_IPropData* m_Data;
};

#endif /* _PROPERTY_HPP_ */
