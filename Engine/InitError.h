#pragma once

#include <exception>
#include <string>


class InitError : public std::exception {
public:
	InitError();
	InitError(class OpenALWrapper* alWrapper);
	InitError(const std::string&);
	virtual ~InitError() throw();
	virtual const char* what() const throw();
private:
	std::string msg;
};

