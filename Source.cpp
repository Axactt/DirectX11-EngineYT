#include"Engine.h"
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"DirectXTK.lib")

int APIENTRY wWinMain( _In_ HINSTANCE hInstance,
					  _In_opt_  HINSTANCE hPrevInstance,
					  _In_ LPWSTR  lpCmdLine,
					  _In_ int lpCmdShow )
{
	Engine engine {}; // Renderwindow class instance object
	engine.Initialize( hInstance, "Title", "MyWindow Class", 800, 600 );
	while (engine.ProcessMessages()==true)// To keep window open
	{
		Sleep( 50 );
	}
	
	return 0;
}