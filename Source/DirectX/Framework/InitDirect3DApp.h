#pragma once

#include "../../DirectX/Common/d3dApp.h"
#include <DirectXColors.h>
#include <Windows.h>
#include <WinBase.h>
#include <conio.h>
#include <string>

using namespace DirectX;

class InitDirect3DApp : public D3DApp
{
public:
	InitDirect3DApp(HINSTANCE hInstance);
	~InitDirect3DApp();

	//virtual bool Initialize()override;
	virtual bool Initialize();
private:
	virtual void OnResize()override;
	virtual void Update(const GameTimer& gt)override;
	virtual void Draw(const GameTimer& gt)override;

};
