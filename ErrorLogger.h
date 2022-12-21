#ifndef ERROR_LOGGER_H
#define ERROR_LOGGER_H
#include"StringConverter.h"
#include<Windows.h>
class ErrorLogger // singleton class
{
public:
	static void Log( std::string message );
	static void Log( HRESULT hr, std::string message );
	static void Log(HRESULT hr, std::wstring message);
};

#endif
