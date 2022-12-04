#include"WindowContainer.h"
LRESULT WindowContainer::WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	OutputDebugStringA( "WINDOW PROC FROM WINDOW CONTAINER " );
	return DefWindowProc( hWnd, uMsg, wParam, lParam );

}
