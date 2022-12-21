#ifndef WINDOW_CONTAINER_H
#define WINDOW_CONTAINER_H
#include "RenderWindow.h"
#include"Keyboard/KeyboardClass.h"
#include"Mouse/MouseClass.h"
#include"Graphics/Graphics.h"
class WindowContainer // Base class to be inherited by other class that have window tied to them e.g. Engine class or any other class
{
public:
	WindowContainer(); // will register Raw input devices
	
	// WindowProc func
	LRESULT WindowProc( HWND hWnd, UINT uMsg, WPARAM wPram, LPARAM lPram );
	// mouse class
	// keyboard class
protected:
	RenderWindow renderWindow {};
	KeyboardClass keyboard;
	MouseClass mouse;
	Graphics gfx;
private:

};


#endif
