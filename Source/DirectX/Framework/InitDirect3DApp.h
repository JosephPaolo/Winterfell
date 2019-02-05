#pragma once

#include "../../DirectX/Common/d3dApp.h"
#include "../../DirectX/Common/d3dUtil.h"
#include "../../DirectX/Common/MathHelper.h"
#include "../../DirectX/Common/UploadBuffer.h"
#include "../../DirectX/Common/GraphicsStructures.h"
#include "../../DirectX/Common/ShapeTypes.h"
#include "../../BlueRapsolEngine/BlueRapsolEngine/FrameResource.h"
#include "../../BlueRapsolEngine/BlueRapsolEngine/BRDataTypes.h"
#include "../../DirectX/Common/GeometryGenerator.h"
#include <DirectXColors.h>
#include <Windows.h>
#include <WinBase.h>
#include <conio.h>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace BRGraphicType;

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")

class BlueRapsolEngine;
class InitDirect3DApp : public D3DApp
{
public:
	InitDirect3DApp(HINSTANCE hInstance, BlueRapsolEngine *getEngineRef);
	InitDirect3DApp(const InitDirect3DApp& rhs) = delete;
	InitDirect3DApp& operator=(const InitDirect3DApp& rhs) = delete;
	~InitDirect3DApp();

	virtual bool Initialize()override;

	GameTimer* getTimer();
	int newRenderItem(); //Creates a box at origin, returns mRenderItem index
	//int newRenderItem(ShapeType setType, BRDataType::Vector3 setPosition); //Creates the selected shape at set location, returns mRenderItem index

	void setPosition(int renderItemIndex, BRDataType::Vector3 setPosition); //Warning! This resets rotation and scalar to default values.
	//void setTransform(int renderItemIndex, BRDataType::Vector3 setPosition, BRDataType::Vector3 setEulerAngle, BRDataType::Vector3 setScalar);

	XMFLOAT4X4 getRenderItemTransform(int index);
	void InitDirect3DApp::setMatrix(int renderItemIndex, XMFLOAT4X4 newMatrix);

private:
	virtual void OnResize()override;
	virtual void Update(const GameTimer& gt)override;
	virtual void Draw(const GameTimer& gt)override;

	virtual void OnMouseDown(WPARAM btnState, int x, int y)override;
	virtual void OnMouseUp(WPARAM btnState, int x, int y)override;
	virtual void OnMouseMove(WPARAM btnState, int x, int y)override;

	void OnKeyboardInput(const GameTimer& gt);
	void UpdateCamera(const GameTimer& gt);
	void AnimateMaterials(const GameTimer& gt);
	void UpdateObjectCBs(const GameTimer& gt);
	void UpdateMaterialCBs(const GameTimer& gt);
	void UpdateMainPassCB(const GameTimer& gt);

	void LoadTextures();
	void BuildRootSignature();
	void BuildDescriptorHeaps();
	void BuildShadersAndInputLayout();
	void BuildShapeGeometry();
	void BuildPSOs();
	void BuildFrameResources();
	void BuildMaterials();
	void BuildRenderItems();
	void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);
	void HideSplashArt(); //test

	std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> GetStaticSamplers();


private:

	std::vector<std::unique_ptr<FrameResource>> mFrameResources;
	FrameResource* mCurrFrameResource = nullptr;
	int mCurrFrameResourceIndex = 0;

	UINT mCbvSrvDescriptorSize = 0;

	ComPtr<ID3D12RootSignature> mRootSignature = nullptr;

	ComPtr<ID3D12DescriptorHeap> mSrvDescriptorHeap = nullptr;

	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
	std::unordered_map<std::string, std::unique_ptr<Material>> mMaterials;
	std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;
	std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;

	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

	ComPtr<ID3D12PipelineState> mOpaquePSO = nullptr;

	// List of all the render items.
	std::vector<std::unique_ptr<RenderItem>> mAllRitems;

	// Render items divided by PSO.
	std::vector<RenderItem*> mOpaqueRitems;

	PassConstants mMainPassCB;

	XMFLOAT3 mEyePos = { 0.0f, 0.0f, -10.0f };
	XMFLOAT4X4 mView = MathHelper::Identity4x4();
	XMFLOAT4X4 mProj = MathHelper::Identity4x4();

	float mTheta = 1.3f*XM_PI;
	float mPhi = 0.4f*XM_PI;
	float mRadius = 20.0f;

	POINT mLastMousePos;

	bool awaitingMainLoop = true;

	BlueRapsolEngine* engineRef;
	//std::unique_ptr<RenderItem> objRef[2];
};
