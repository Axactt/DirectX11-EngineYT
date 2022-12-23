#include"Engine.h"


int APIENTRY wWinMain( _In_ HINSTANCE hInstance,
					  _In_opt_  HINSTANCE hPrevInstance,
					  _In_ LPWSTR  lpCmdLine,
					  _In_ int lpCmdShow )
{
	Engine engine {}; // Renderwindow class instance object
	if (engine.Initialize(hInstance, "Title", "MyWindow Class", 800, 600))
	{
		while (engine.ProcessMessages() == true)// To keep window open
		{
			engine.Update();
			engine.RenderFrame();
		}
	}
	return 0;
}

//INPUT ASSEMBLER - COMPLETED
//VERTEX SHADER  - COMPLETED
//RASTERIZER  - COMPLETED
//PIXeL SHADER - COMPLETED
//OUTPUT MERGER - COMPLETED

// Create our vertex buffer
//Draw