#include "../../stdafx.h"

namespace Mad
{
	namespace Utility
	{
		class ConfigParser
		{
		private:
			std::map<std::string,std::string> m_Cfg;
			std::string m_FileName;

			void removeComment(std::string& line) const;

			bool isOnlyWhiteSpace(const std::string& line) const;
			bool isValidLine(const std::string& line) const;
			
			void extractKey(std::string& key, size_t const &sepPos, const std::string& line) const;
			void extractValue(std::string& value, size_t const &sepPos, const std::string& line) const;

			void extractContents(const std::string& line);
			void parseLine(const std::string &line, size_t const lineNo);
			void extractKeys();

			

		public:
			ConfigParser(const std::string& fileName);
			~ConfigParser();
			void saveChanges();
			void getValue(const std::string &key, std::string& value) const;
			void setValue(const std::string &key, const std::string& value);
			bool isKeyExists(const std::string& key) const;
			
		};
	}
}
