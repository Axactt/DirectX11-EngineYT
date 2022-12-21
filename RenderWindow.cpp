#include"WindowContainer.h"

bool RenderWindow::Initialize(WindowContainer* pWindowContainer, HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height )
{
	this->hInstance = hInstance;
	this->width = width;
	this->height = height;
	this->window_title = window_title;
	this->window_title_wide = StringConverter::StringToWide( this->window_title );// wide string representation of window title
	this->window_class = window_class;
	this->window_class_wide = StringConverter::StringToWide( this->window_class );// wide string representation of class

	this->RegisterWindowClass(); // register the window class struct
	this->hWnd = CreateWindowEx( 0,//Extended windws style
								   this->window_class_wide.c_str(),//window class name
								   this->window_title_wide.c_str(),//window title
								   WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,//Windows style
								   0,// window x position
								   0,// window y position
								   this->width,
								   this->height,
								   NULL,//Handle to parent of this wind,first win no parent
								   NULL,//Handle to menu or child window identifier
								   this->hInstance,//Handle to the instance of module to be used with this window
								   pWindowContainer );// pointer to a value to be passed to window through CREATESTRUCT structure using WM_NCCREATE message(windowcntnr*)
	if (this->hWnd == NULL)
	{
		ErrorLogger::Log( GetLastError(), "CreateWindowEx failed for Window: " + this->window_title );
		return false;
	}
	// Bring the window up on screen and set it as main focus
	ShowWindow( this->hWnd, SW_SHOW );
	SetForegroundWindow( this->hWnd );
	SetFocus( this->hWnd );

	return true;
}

bool RenderWindow::ProcessMessages()
{
	//Handle the window messages, Main message loop
	MSG msg {}; // Message structure
	SecureZeroMemory( &msg, sizeof( MSG ) );// initialize the message structure
while (PeekMessage( &msg,// output poiter to store message to MSG struct
		 this->hWnd, //handle to window we are checking messages for 
		 0, // Minimum filter message value
		 0, // Maximum filter message value
		 PM_REMOVE )) // Remove message after capturing it via PeekMessages
	{
		TranslateMessage( &msg );// Tranlate messages from virtual key messages into character messages so we 
		DispatchMessage( &msg );//Dispatch message to our Window Proc for this Window
	}
	//Check if the window is closed
	if (msg.message == WM_NULL)
	{
		// when the message becomes Null, we check for IsWindow(hWnd)!=Null
		if (!IsWindow( this->hWnd ))
		{
			this->hWnd = NULL;
			UnregisterClass( this->window_class_wide.c_str(), this->hInstance );
			return false;
		}

	}
	return true;
}

HWND RenderWindow::GetHWND() const
{
	return this->hWnd;
}

// Destructor unregisters the classs and destroys window
RenderWindow::~RenderWindow()
{
	if (this->hWnd != NULL)
	{
		UnregisterClass( this->window_class_wide.c_str(), this->hInstance );
		DestroyWindow( hWnd );

	}
}

LRESULT CALLBACK HandleMsgRedirect( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch (uMsg)
	{
		case WM_CLOSE:
		{
			DestroyWindow( hWnd );
			return 0;
		}
		default:
		{
			//retrieve pointer to window class
			WindowContainer* const pWindow =
				reinterpret_cast<WindowContainer*>(GetWindowLongPtr( hWnd, GWLP_USERDATA ));
			//forward message to window class handler
			return pWindow->WindowProc( hWnd, uMsg, wParam, lParam );
		}

	}

}


// Window proc function setup WNDPROC function pointer
LRESULT CALLBACK HandleMessageSetup( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch (uMsg)
	{
		// WM_NCCREATE triggered when window is created
		// this message will be used  pass param to our createwindowex()
		//Passing in pointer to object that inherits windowcontainer
		case WM_NCCREATE:
		{
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			WindowContainer* pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
			if (pWindow == nullptr)// Sanity check
			{
				ErrorLogger::Log( "Critical Error: pointer to window container is null during WM_NCCREATE. " );
				exit( -1 );
			}
			SetWindowLongPtr( hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow) );
			SetWindowLongPtr( hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect) );
			return pWindow->WindowProc( hWnd, uMsg, wParam, lParam );
			// return DefWindowProc( hWnd, uMsg, wParam, lParam );
		}
		
		default:

		return DefWindowProc( hWnd, uMsg, wParam, lParam );

	}
}


void RenderWindow::RegisterWindowClass()
{
	WNDCLASSEX wc;// Our window-class struct for creating new windowCls
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;//Flags[Redraw on width/height change from resize/movemnet]
	wc.lpfnWndProc = HandleMessageSetup;//Pointer to our aplication specific window-proc function for handling messages to this window
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = this->hInstance;//Handle to instance that contains the window procedure
	wc.hIcon = NULL;//handle to the class icon.Must be a handle to an icon resource.We are not curently assigning this
	wc.hIconSm = NULL;// handle to small icon for this class
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );//Default cursor
	wc.hbrBackground = NULL;//Handle to class background brush for window's background color
	wc.lpszMenuName = NULL;//Pointer to a null terminated string for the menu
	wc.lpszClassName = this->window_class_wide.c_str();// Pointer to null terminated string of our class name for the window
	wc.cbSize = sizeof( WNDCLASSEX );// Need to fill in the size of our struct for cbSize
	RegisterClassEx( &wc );//Register the class so that it is usable.

}







