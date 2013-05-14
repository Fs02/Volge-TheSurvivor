#include "ConfigParser.hpp"
#include <fstream>

Mad::Utility::ConfigParser::ConfigParser(const std::string& fileName)
{
	m_FileName	= fileName;
	extractKeys();
}

Mad::Utility::ConfigParser::~ConfigParser()
{
	saveChanges();
}

void Mad::Utility::ConfigParser::removeComment(std::string& line) const
{
	if (line.find('#') != line.npos)
		line.erase(line.find('#'));
}

bool Mad::Utility::ConfigParser::isOnlyWhiteSpace(const std::string& line) const
{
	return (line.find_first_not_of(' ') == line.npos);
}

bool Mad::Utility::ConfigParser::isValidLine(const std::string& line) const
{
	std::string temp	= line;
	temp.erase(0,temp.find_first_not_of("\t "));
	if (temp[0] == '=')	
		return false;

	if (temp.find('=') == temp.npos)
		return false;

	for (size_t i = temp.find('=') + 1; i < temp.length(); i++)
	{
		if (temp[i] != ' ')
			return true;
	}
	return false;
}

void Mad::Utility::ConfigParser::extractKey(std::string& key, size_t const &sepPos, const std::string& line) const
{
	key		= line.substr(0, sepPos);
	if (key.find('\t') != line.npos || key.find(' ') != line.npos)
		key.erase(key.find_first_of("\t "));
}

void Mad::Utility::ConfigParser::extractValue(std::string& value, size_t const &sepPos, const std::string& line) const
{
	value	= line.substr(sepPos + 1);
	value.erase(0, value.find_first_not_of("\t "));
	value.erase(value.find_last_not_of("\t ") + 1);
}

void Mad::Utility::ConfigParser::extractContents(const std::string &line) 
{
	std::string temp = line;
        // Erase leading whitespace from the line.
	temp.erase(0, temp.find_first_not_of("\t "));
	size_t sepPos = temp.find('=');

	std::string key, value;
	extractKey(key, sepPos, temp);
	extractValue(value, sepPos, temp);
	if (!isKeyExists(key))
		m_Cfg.insert(std::pair<std::string, std::string>(key, value));
	else
		std::cout<<"Config Parser Error : Duplicate key name !"<<std::endl;
}

void Mad::Utility::ConfigParser::parseLine(const std::string &line, size_t const lineNo)
{
	if (line.find('=') == line.npos)
		std::cout<<"Config Parser Error : missing '=' on line "<<lineNo<<std::endl;
	if (!isValidLine(line))
		std::cout<<"Config Parser Error : line "<<lineNo<<" not valid !"<<std::endl;

	extractContents(line);
}

void Mad::Utility::ConfigParser::extractKeys()
{
	std::ifstream file;
	file.open(m_FileName.c_str());
	if (!file)
		std::cout<<"Config Parser Error : File not Exist !"<<std::endl;

	std::string line;
	size_t lineNo	= 0;
	while (std::getline(file,line))
	{
		lineNo++;
		std::string temp	= line;

		if(temp.empty())
			continue;

		removeComment(temp);
		if(isOnlyWhiteSpace(temp))
			continue;

		parseLine(temp,lineNo);
	}

	file.close();
}

bool Mad::Utility::ConfigParser::isKeyExists(const std::string& key) const
{
	return (m_Cfg.find(key) != m_Cfg.end());
}

void Mad::Utility::ConfigParser::getValue(const std::string &key, std::string &value) const
{
	if (isKeyExists(key))
		value	= m_Cfg.find(key)->second;
}

void Mad::Utility::ConfigParser::setValue(const std::string &key, const std::string &value)
{
	m_Cfg[key] = value;
}

void Mad::Utility::ConfigParser::saveChanges()
{
	std::ifstream ifile;
	ifile.open(m_FileName.c_str());
	if (!ifile)
		std::cout<<"Config Parser Error : File not Exist !"<<std::endl;

	std::string line;
	std::vector<std::string> tempLines;
	size_t lineNo	= 0;
	/*
	std::map<std::string, std::string> tempContents	= m_Cfg;

	while (std::getline(ifile,line))
	{
		lineNo++;
		
		for (auto i = tempContents.begin(); i != tempContents.end(); i++)
			std::cout<<i->first<<"->"<<i->second<<std::endl;
		std::cout<<lineNo<<std::endl;

		if (isValidLine(line))
		{
			std::string temp = line;
			temp.erase(0, temp.find_first_not_of("\t "));
			size_t sepPos = temp.find('=');

			std::string key, value;
			extractKey(key, sepPos, temp);
			extractValue(value, sepPos, temp);

			if (!isKeyExists(key))
			{
				tempLines.push_back(key+" = "+value);
				tempContents.erase(key);
			}
			else
			{
				tempLines.push_back(key+" = "+m_Contents[key]);
			}
		}
		else
		{
			tempLines.push_back(line);
		}
	}
	ifile.close();
	*/
	for (auto it = m_Cfg.begin(); it != m_Cfg.end(); it++)
		tempLines.push_back(it->first+" = "+it->second);

	std::ofstream ofile;
	ofile.open(m_FileName.c_str());
	for (size_t i = 0; i < tempLines.size(); i++)
		ofile<<tempLines[i]<<"\n";
	ofile.close();
}