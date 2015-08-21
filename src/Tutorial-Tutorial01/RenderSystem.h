#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <windows.h>
#include <d3d11.h>
#include <DirectXColors.h>
#include "d3d/App.h"

using namespace DirectX;

namespace byhj
{

class RenderSystem : public byhj::d3d::App
{

public:
	void v_Init()     override;
	void v_Update()   override;
	void v_Render()   override;
	void v_Shutdown() override;

private:

};


}

#endif