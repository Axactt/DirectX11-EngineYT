#pragma once
#include"AdapterReader.h"
#include "Shaders.h"
#include "Vertex.h"
#include<SpriteBatch.h>
#include<SpriteFont.h>
class Graphics
{
public:
	bool Initialize( HWND hWnd, int width, int height );
	void RenderFrame();
private:
	bool InitializeDirectX( HWND hWnd, int width, int height );
	bool InitializeShaders();
	bool InitializeScene(); //Initilaize vertex buffers etc

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;

	
	VertexShader vertexshader;
	PixelShader pixelshader;

	Microsoft::WRL::ComPtr<ID3D11Buffer>vertexBuffer; // create a vertex buffer
	Microsoft::WRL::ComPtr<ID3D11Buffer>vertexBuffer2; // vertex buffer 2nd triangle
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>depthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState;

	Microsoft::WRL::ComPtr<ID3D11RasterizerState>rasterizerState;
	
	std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> spriteFont;
}; 