#include"ErrorLogger.h"
#include<comdef.h> // For COM Error-Data type
void ErrorLogger::Log( std::string message )
{
	std::string error_message = "Error: " + message;
	MessageBoxA( NULL, error_message.c_str(), "Error", MB_ICONERROR );

}
void ErrorLogger::Log( HRESULT hr, std::string message )
{
	_com_error error( hr ); // to convert HRESULT to _com_error type class instance
	std::wstring error_message = L"Error: " + StringConverter::StringToWide( message ) + L"\n" + error.ErrorMessage();
	MessageBoxW( NULL, error_message.c_str(), L"Error", MB_ICONERROR );
}

void ErrorLogger::Log(HRESULT hr, std::wstring message)
{
	_com_error error(hr); // to convert HRESULT to _com_error type class instance
	std::wstring error_message = L"Error: " + message + L"\n" + error.ErrorMessage();
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}
