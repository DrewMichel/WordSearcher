// Created by: Andrew Steven Michel
// Date Created: May 2018
#include <iostream>
#include <string>

namespace Drewski
{
	class FileOperationException
	{
		private:
			std::string exceptionMessage;

		public:
			FileOperationException(std::string messageIn = "FILE OPERATION EXCEPTION");

			~FileOperationException();

			const char* what() const throw();
	};
}