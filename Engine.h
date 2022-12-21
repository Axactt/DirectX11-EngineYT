#ifndef ENGINE_H
#define ENGINE_h
#include"WindowContainer.h"
class Engine: WindowContainer // Inherits from windowcontainer
{
public:
	bool Initialize( HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height );
	bool ProcessMessages();
	void Update();
	void RenderFrame();
};
#endif
