// Created by: Andrew Steven Michel
// Date Created: May 2018
#include "FileOperationException.h"

namespace Drewski
{
	FileOperationException::FileOperationException(std::string messageIn) : exceptionMessage(messageIn)
	{
	}

	FileOperationException::~FileOperationException()
	{
	}

	const char* FileOperationException::what() const throw()
	{
		return exceptionMessage.c_str();
	}
}