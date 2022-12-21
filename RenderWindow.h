#ifndef RENDER_WINDOW_H
#define RENDER_WINDOW_H
#include"ErrorLogger.h"
// Cannnot include WindowContainer.h as that will cause circular dependency

//Forward declare WindowContainer class 
class WindowContainer;

class RenderWindow
{
private:
	void RegisterWindowClass();// RegisterWindowClassEx api called by Initialize function
	HWND hWnd { NULL }; //Handle to this window hWnd
	HINSTANCE hInstance { NULL }; // handle to application instance
	std::string window_title { "" };
	std::wstring window_title_wide { L"" };//wide string representation of window title
	std::string window_class { "" };
	std::wstring window_class_wide { L"" };// wide string representtation of window class name or name of application
	int width { 0 };
	int height { 0 };
public:
	//Initialize function changed to have first argument as pointer to windowContainer
	bool Initialize( WindowContainer* pWindowContainer,HINSTANCE hInstance,std::string window_title, std::string window_class, int width, int height );
	bool ProcessMessages(); // WNDPROC wrapper to capture messages/events
	HWND GetHWND()const;
	~RenderWindow();
};

#endif
