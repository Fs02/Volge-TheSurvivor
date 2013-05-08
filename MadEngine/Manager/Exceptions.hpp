#pragma once

#include "..\..\stdafx.h"

namespace Mad
{
	namespace Manager
	{
		namespace Exceptions
		{
			class FileNotFound
				: public std::runtime_error
			{
			public:
				FileNotFound(const std::string& message = "The specified file not found or corrupt !")
					: runtime_error(message) {}
			};
			
			class ResourceNotFound
				: public std::runtime_error
			{
			public:
				ResourceNotFound(const std::string& message = "The Specified resource not found in resource index !")
					: runtime_error(message) {}
			};

			class BadMemoryAllocation
				: public std::runtime_error
			{
			public:
				BadMemoryAllocation(const std::string& message = "Failed to Allocate memory !")
					: runtime_error(message) {}
			};

			class InvalidKey
				: public std::runtime_error
			{
			public:
				InvalidKey(const std::string& location = "index !", const std::string& message = "the specified key not found in ")
					: runtime_error(message + location) {}
			};

			class DuplicateKey
				: public std::runtime_error
			{
			public:
				DuplicateKey(const std::string& location = "index !", const std::string& message = "Duplicate key in ")
					: runtime_error(message + location) {}
			};
		}
	}
}