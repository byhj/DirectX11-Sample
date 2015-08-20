#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <windows.h>
#include <d3d11.h>
#include <DirectXColors.h>

using namespace DirectX;

namespace byhj
{

class RenderSystem
{

public:
	void Init();
	void Render();
	void Shutdown();

private:
	void init_window();
	void init_device();



};


}

#endif