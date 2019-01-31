//***************************************************************************************
// Init Direct3D.cpp by Frank Luna (C) 2015 All Rights Reserved.
//
// Demonstrates the sample framework by initializing Direct3D, clearing 
// the screen, and displaying frame stats.
//
//***************************************************************************************

#include "../../DirectX/Framework/InitDirect3DApp.h"
#include "../../DirectX/Common/d3dApp.h"

InitDirect3DApp::InitDirect3DApp(HINSTANCE hInstance): D3DApp(hInstance) {

}

InitDirect3DApp::~InitDirect3DApp()
{
}

bool InitDirect3DApp::Initialize()
{
    if(!D3DApp::Initialize())
		return false;
		
	return true;
}

void InitDirect3DApp::OnResize()
{
	D3DApp::OnResize();
}

//This function is called repeatedly within a loop
void InitDirect3DApp::Update(const GameTimer& gt){

	/*
	char key = ' ';
	std::wstring msg;
	
	//OutputDebugString(L"This message appears repeatedly.\n");

	//TODO properly handle input
	if (_kbhit()) { //If keyboard is pressed
		OutputDebugString(L"This message does not appear.\n");
		key = _getch();
		msg = L"Button Pressed: " + key;
		OutputDebugString(msg.c_str()); //This message does not appear
	}
	*/
}

void InitDirect3DApp::Draw(const GameTimer& gt)
{
    // Reuse the memory associated with command recording.
    // We can only reset when the associated command lists have finished execution on the GPU.
	ThrowIfFailed(mDirectCmdListAlloc->Reset());

	// A command list can be reset after it has been added to the command queue via ExecuteCommandList.
    // Reusing the command list reuses memory.
    ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr));

	// Indicate a state transition on the resource usage.
	mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

<<<<<<< HEAD
	// Clear the back buffer and depth buffer.

	if (inMainLoop) {
		mCommandList->ClearRenderTargetView(CurrentBackBufferView(), Colors::LightSteelBlue, 0, nullptr);
	}
	else {
		mCommandList->ClearRenderTargetView(CurrentBackBufferView(), Colors::Black, 0, nullptr);
	}
	mCommandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);
=======
    // Set the viewport and scissor rect.  This needs to be reset whenever the command list is reset.
    mCommandList->RSSetViewports(1, &mScreenViewport);
    mCommandList->RSSetScissorRects(1, &mScissorRect);
>>>>>>> parent of 2219bf3... Added 3D rendering and texturing to DirectX

    // Clear the back buffer and depth buffer.
	mCommandList->ClearRenderTargetView(CurrentBackBufferView(), Colors::Black, 0, nullptr);
	mCommandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);
	
    // Specify the buffers we are going to render to.
	mCommandList->OMSetRenderTargets(1, &CurrentBackBufferView(), true, &DepthStencilView());
	
    // Indicate a state transition on the resource usage.
	mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

    // Done recording commands.
	ThrowIfFailed(mCommandList->Close());
 
    // Add the command list to the queue for execution.
	ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
	mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
	
	// swap the back and front buffers
	ThrowIfFailed(mSwapChain->Present(0, 0));
	mCurrBackBuffer = (mCurrBackBuffer + 1) % SwapChainBufferCount;

<<<<<<< HEAD
	// Advance the fence value to mark commands up to this fence point.
	mCurrFrameResource->Fence = ++mCurrentFence;

	// Add an instruction to the command queue to set a new fence point. 
	// Because we are on the GPU timeline, the new fence point won't be 
	// set until the GPU finishes processing all the commands prior to this Signal().
	mCommandQueue->Signal(mFence.Get(), mCurrentFence);
}

void InitDirect3DApp::OnMouseDown(WPARAM btnState, int x, int y)
{
	mLastMousePos.x = x;
	mLastMousePos.y = y;

	SetCapture(mhMainWnd);
}

void InitDirect3DApp::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}

void InitDirect3DApp::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON) != 0)
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = XMConvertToRadians(0.25f*static_cast<float>(x - mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f*static_cast<float>(y - mLastMousePos.y));

		// Update angles based on input to orbit camera around box.
		mTheta += dx;
		mPhi += dy;

		// Restrict the angle mPhi.
		mPhi = MathHelper::Clamp(mPhi, 0.1f, MathHelper::Pi - 0.1f);
	}
	else if ((btnState & MK_RBUTTON) != 0)
	{
		// Make each pixel correspond to 0.2 unit in the scene.
		float dx = 0.05f*static_cast<float>(x - mLastMousePos.x);
		float dy = 0.05f*static_cast<float>(y - mLastMousePos.y);

		// Update the camera radius based on input.
		mRadius += dx - dy;

		// Restrict the radius.
		mRadius = MathHelper::Clamp(mRadius, 5.0f, 150.0f);
	}

	mLastMousePos.x = x;
	mLastMousePos.y = y;
}

void InitDirect3DApp::OnKeyboardInput(const GameTimer& gt)
{
}

void InitDirect3DApp::UpdateCamera(const GameTimer& gt)
{
	if (inMainLoop) { //Dont process during initialization phase
		// Convert Spherical to Cartesian coordinates.
		mEyePos.x = mRadius * sinf(mPhi)*cosf(mTheta);
		mEyePos.z = mRadius * sinf(mPhi)*sinf(mTheta);
		mEyePos.y = mRadius * cosf(mPhi);

		// Build the view matrix.
		XMVECTOR pos = XMVectorSet(mEyePos.x, mEyePos.y, mEyePos.z, 1.0f);
		XMVECTOR target = XMVectorZero();
		XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
		XMStoreFloat4x4(&mView, view);
	}
=======
	// Wait until frame commands are complete.  This waiting is inefficient and is
	// done for simplicity.  Later we will show how to organize our rendering code
	// so we do not have to wait per frame.
	FlushCommandQueue();
>>>>>>> parent of 2219bf3... Added 3D rendering and texturing to DirectX
}

void InitDirect3DApp::LoadTextures() {
	auto blueRapsolSplash = std::make_unique<Texture>();
	blueRapsolSplash->Name = "blueRapsolSplash";
	blueRapsolSplash->Filename = L"../Assets/blueRapsolSplashTex.DDS";
	ThrowIfFailed(DirectX::CreateDDSTextureFromFile12(md3dDevice.Get(),
		mCommandList.Get(), blueRapsolSplash->Filename.c_str(),
		blueRapsolSplash->Resource, blueRapsolSplash->UploadHeap));

	mTextures[blueRapsolSplash->Name] = std::move(blueRapsolSplash);
}

void InitDirect3DApp::UpdateObjectCBs(const GameTimer& gt)
{
	auto currObjectCB = mCurrFrameResource->ObjectCB.get();
	for (auto& e : mAllRitems)
	{
		// Only update the cbuffer data if the constants have changed.  
		// This needs to be tracked per frame resource.
		if (e->NumFramesDirty > 0)
		{
			XMMATRIX world = XMLoadFloat4x4(&e->World);
			XMMATRIX texTransform = XMLoadFloat4x4(&e->TexTransform);

			ObjectConstants objConstants;
			XMStoreFloat4x4(&objConstants.World, XMMatrixTranspose(world));
			XMStoreFloat4x4(&objConstants.TexTransform, XMMatrixTranspose(texTransform));

			currObjectCB->CopyData(e->ObjCBIndex, objConstants);

			// Next FrameResource need to be updated too.
			e->NumFramesDirty--;
		}
	}
}

void InitDirect3DApp::BuildRootSignature()
{
	// Root parameter can be a table, root descriptor or root constants.
	CD3DX12_ROOT_PARAMETER slotRootParameter[3];

	// Create root CBV.
	slotRootParameter[0].InitAsConstantBufferView(0);
	slotRootParameter[1].InitAsConstantBufferView(1);
	slotRootParameter[2].InitAsConstantBufferView(2);

	// A root signature is an array of root parameters.
	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(3, slotRootParameter, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	// create a root signature with a single slot which points to a descriptor range consisting of a single constant buffer
	ComPtr<ID3DBlob> serializedRootSig = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1,
		serializedRootSig.GetAddressOf(), errorBlob.GetAddressOf());

	if (errorBlob != nullptr)
	{
		::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
	}
	ThrowIfFailed(hr);

	ThrowIfFailed(md3dDevice->CreateRootSignature(
		0,
		serializedRootSig->GetBufferPointer(),
		serializedRootSig->GetBufferSize(),
		IID_PPV_ARGS(mRootSignature.GetAddressOf())));
}

void InitDirect3DApp::UpdateMaterialCBs(const GameTimer& gt)
{
	auto currMaterialCB = mCurrFrameResource->MaterialCB.get();
	for (auto& e : mMaterials)
	{
		// Only update the cbuffer data if the constants have changed.  If the cbuffer
		// data changes, it needs to be updated for each FrameResource.
		Material* mat = e.second.get();
		if (mat->NumFramesDirty > 0)
		{
			XMMATRIX matTransform = XMLoadFloat4x4(&mat->MatTransform);

			MaterialConstants matConstants;
			matConstants.DiffuseAlbedo = mat->DiffuseAlbedo;
			matConstants.FresnelR0 = mat->FresnelR0;
			matConstants.Roughness = mat->Roughness;
			XMStoreFloat4x4(&matConstants.MatTransform, XMMatrixTranspose(matTransform));

			currMaterialCB->CopyData(mat->MatCBIndex, matConstants);

			// Next FrameResource need to be updated too.
			mat->NumFramesDirty--;
		}
	}
}

void InitDirect3DApp::UpdateMainPassCB(const GameTimer& gt)
{
	XMMATRIX view = XMLoadFloat4x4(&mView);
	XMMATRIX proj = XMLoadFloat4x4(&mProj);

	XMMATRIX viewProj = XMMatrixMultiply(view, proj);
	XMMATRIX invView = XMMatrixInverse(&XMMatrixDeterminant(view), view);
	XMMATRIX invProj = XMMatrixInverse(&XMMatrixDeterminant(proj), proj);
	XMMATRIX invViewProj = XMMatrixInverse(&XMMatrixDeterminant(viewProj), viewProj);

	XMStoreFloat4x4(&mMainPassCB.View, XMMatrixTranspose(view));
	XMStoreFloat4x4(&mMainPassCB.InvView, XMMatrixTranspose(invView));
	XMStoreFloat4x4(&mMainPassCB.Proj, XMMatrixTranspose(proj));
	XMStoreFloat4x4(&mMainPassCB.InvProj, XMMatrixTranspose(invProj));
	XMStoreFloat4x4(&mMainPassCB.ViewProj, XMMatrixTranspose(viewProj));
	XMStoreFloat4x4(&mMainPassCB.InvViewProj, XMMatrixTranspose(invViewProj));
	mMainPassCB.EyePosW = mEyePos;
	mMainPassCB.RenderTargetSize = XMFLOAT2((float)mClientWidth, (float)mClientHeight);
	mMainPassCB.InvRenderTargetSize = XMFLOAT2(1.0f / mClientWidth, 1.0f / mClientHeight);
	mMainPassCB.NearZ = 1.0f;
	mMainPassCB.FarZ = 1000.0f;
	mMainPassCB.TotalTime = gt.TotalTime();
	mMainPassCB.DeltaTime = gt.DeltaTime();
	mMainPassCB.AmbientLight = { 0.25f, 0.25f, 0.35f, 1.0f };
	mMainPassCB.Lights[0].Direction = { 0.57735f, -0.57735f, 0.57735f };
	mMainPassCB.Lights[0].Strength = { 0.6f, 0.6f, 0.6f };
	mMainPassCB.Lights[1].Direction = { -0.57735f, -0.57735f, 0.57735f };
	mMainPassCB.Lights[1].Strength = { 0.3f, 0.3f, 0.3f };
	mMainPassCB.Lights[2].Direction = { 0.0f, -0.707f, -0.707f };
	mMainPassCB.Lights[2].Strength = { 0.15f, 0.15f, 0.15f };

	auto currPassCB = mCurrFrameResource->PassCB.get();
	currPassCB->CopyData(0, mMainPassCB);
}

<<<<<<< HEAD
void InitDirect3DApp::LoadTextures()
{
	auto splashArtTex = std::make_unique<Texture>();
	splashArtTex->Name = "splashArtTex";
	splashArtTex->Filename = L"../../../Assets/splashTex4.DDS";
	ThrowIfFailed(DirectX::CreateDDSTextureFromFile12(md3dDevice.Get(),
		mCommandList.Get(), splashArtTex->Filename.c_str(),
		splashArtTex->Resource, splashArtTex->UploadHeap));

	mTextures[splashArtTex->Name] = std::move(splashArtTex);
}

void InitDirect3DApp::BuildRootSignature()
=======
void InitDirect3DApp::BuildShadersAndInputLayout()
>>>>>>> parent of 2219bf3... Added 3D rendering and texturing to DirectX
{
	const D3D_SHADER_MACRO alphaTestDefines[] =
	{
<<<<<<< HEAD
		::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
	}
	ThrowIfFailed(hr);

	ThrowIfFailed(md3dDevice->CreateRootSignature(
		0,
		serializedRootSig->GetBufferPointer(),
		serializedRootSig->GetBufferSize(),
		IID_PPV_ARGS(mRootSignature.GetAddressOf())));
}

void InitDirect3DApp::BuildDescriptorHeaps()
{
	//
	// Create the SRV heap.
	//
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.NumDescriptors = 1;
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	ThrowIfFailed(md3dDevice->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&mSrvDescriptorHeap)));

	//
	// Fill out the heap with actual descriptors.
	//
	CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(mSrvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

	auto splashArtTex = mTextures["splashArtTex"]->Resource;

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = splashArtTex->GetDesc().Format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = splashArtTex->GetDesc().MipLevels;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

	md3dDevice->CreateShaderResourceView(splashArtTex.Get(), &srvDesc, hDescriptor);
}
=======
		"ALPHA_TEST", "1",
		NULL, NULL
	};
>>>>>>> parent of 2219bf3... Added 3D rendering and texturing to DirectX

	mShaders["standardVS"] = d3dUtil::CompileShader(L"Shaders\\Default.hlsl", nullptr, "VS", "vs_5_1");
	mShaders["opaquePS"] = d3dUtil::CompileShader(L"Shaders\\Default.hlsl", nullptr, "PS", "ps_5_1");

	mInputLayout =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};
}

void InitDirect3DApp::BuildShapeGeometry()
{
	GeometryGenerator geoGen;
<<<<<<< HEAD
	//GeometryGenerator::MeshData box = geoGen.CreateSixTexBox(1.0f, 1.0f, 1.0f, 3);
	//GeometryGenerator::MeshData broken = geoGen.CreateBox(1.0f, 1.0f, 1.0f, 3);
	//GeometryGenerator::MeshData box = geoGen.CreateSixTexBox(1.0f, 1.0f, 1.0f, 3);
	GeometryGenerator::MeshData box = geoGen.CreateBox(1.0f, 1.0f, 1.0f, 3);
	GeometryGenerator::MeshData splashArt = geoGen.CreateQuad(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
=======
	GeometryGenerator::MeshData box = geoGen.CreateBox(1.5f, 0.5f, 1.5f, 3);
>>>>>>> parent of 2219bf3... Added 3D rendering and texturing to DirectX

	//
	// We are concatenating all the geometry into one big vertex/index buffer.  So
	// define the regions in the buffer each submesh covers.
	//

	// Cache the vertex offsets to each object in the concatenated vertex buffer.
	UINT boxVertexOffset = 0;
<<<<<<< HEAD
	UINT splashArtVertexOffset = (UINT)box.Vertices.size();

	// Cache the starting index for each object in the concatenated index buffer.
	UINT boxIndexOffset = 0;
	UINT splashArtIndexOffset = (UINT)box.Indices32.size();
=======
	UINT gridVertexOffset = (UINT)box.Vertices.size();
	//UINT sphereVertexOffset = gridVertexOffset + (UINT)grid.Vertices.size();
	//UINT cylinderVertexOffset = sphereVertexOffset + (UINT)sphere.Vertices.size();

	// Cache the starting index for each object in the concatenated index buffer.
	UINT boxIndexOffset = 0;
	UINT gridIndexOffset = (UINT)box.Indices32.size();
	//UINT sphereIndexOffset = gridIndexOffset + (UINT)grid.Indices32.size();
	//UINT cylinderIndexOffset = sphereIndexOffset + (UINT)sphere.Indices32.size();
>>>>>>> parent of 2219bf3... Added 3D rendering and texturing to DirectX

	SubmeshGeometry boxSubmesh;
	boxSubmesh.IndexCount = (UINT)box.Indices32.size();
	boxSubmesh.StartIndexLocation = boxIndexOffset;
	boxSubmesh.BaseVertexLocation = boxVertexOffset;

<<<<<<< HEAD
	SubmeshGeometry splashArtSubmesh;
	splashArtSubmesh.IndexCount = (UINT)splashArt.Indices32.size();
	splashArtSubmesh.StartIndexLocation = splashArtIndexOffset;
	splashArtSubmesh.BaseVertexLocation = splashArtVertexOffset;
=======
	//SubmeshGeometry gridSubmesh;
	//gridSubmesh.IndexCount = (UINT)grid.Indices32.size();
	//gridSubmesh.StartIndexLocation = gridIndexOffset;
	//gridSubmesh.BaseVertexLocation = gridVertexOffset;
>>>>>>> parent of 2219bf3... Added 3D rendering and texturing to DirectX

	//
	// Extract the vertex elements we are interested in and pack the
	// vertices of all the meshes into one vertex buffer.
	//

	auto totalVertexCount =
<<<<<<< HEAD
		box.Vertices.size() +
		splashArt.Vertices.size();
=======
		box.Vertices.size();
		//grid.Vertices.size() +
		//sphere.Vertices.size() +
		//cylinder.Vertices.size();
>>>>>>> parent of 2219bf3... Added 3D rendering and texturing to DirectX

	std::vector<Vertex> vertices(totalVertexCount);

	UINT k = 0;
	for (size_t i = 0; i < box.Vertices.size(); ++i, ++k)
	{
		vertices[k].Pos = box.Vertices[i].Position;
		vertices[k].Normal = box.Vertices[i].Normal;
<<<<<<< HEAD
		vertices[k].TexC = box.Vertices[i].TexC;
	}

	for (size_t i = 0; i < splashArt.Vertices.size(); ++i, ++k)
	{
		vertices[k].Pos = splashArt.Vertices[i].Position;
		vertices[k].Normal = splashArt.Vertices[i].Normal;
		vertices[k].TexC = splashArt.Vertices[i].TexC;
=======
>>>>>>> parent of 2219bf3... Added 3D rendering and texturing to DirectX
	}


	std::vector<std::uint16_t> indices;
	indices.insert(indices.end(), std::begin(box.GetIndices16()), std::end(box.GetIndices16()));
<<<<<<< HEAD
	indices.insert(indices.end(), std::begin(splashArt.GetIndices16()), std::end(splashArt.GetIndices16()));
=======
>>>>>>> parent of 2219bf3... Added 3D rendering and texturing to DirectX

	const UINT vbByteSize = (UINT)vertices.size() * sizeof(Vertex);
	const UINT ibByteSize = (UINT)indices.size() * sizeof(std::uint16_t);

	auto geo = std::make_unique<MeshGeometry>();
	geo->Name = "shapeGeo";

	ThrowIfFailed(D3DCreateBlob(vbByteSize, &geo->VertexBufferCPU));
	CopyMemory(geo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

	ThrowIfFailed(D3DCreateBlob(ibByteSize, &geo->IndexBufferCPU));
	CopyMemory(geo->IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);

	geo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(),
		mCommandList.Get(), vertices.data(), vbByteSize, geo->VertexBufferUploader);

	geo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(),
		mCommandList.Get(), indices.data(), ibByteSize, geo->IndexBufferUploader);

	geo->VertexByteStride = sizeof(Vertex);
	geo->VertexBufferByteSize = vbByteSize;
	geo->IndexFormat = DXGI_FORMAT_R16_UINT;
	geo->IndexBufferByteSize = ibByteSize;

	geo->DrawArgs["box"] = boxSubmesh;
<<<<<<< HEAD
	geo->DrawArgs["splashArt"] = splashArtSubmesh;
=======
>>>>>>> parent of 2219bf3... Added 3D rendering and texturing to DirectX

	mGeometries[geo->Name] = std::move(geo);
}

void InitDirect3DApp::BuildPSOs()
{
	D3D12_GRAPHICS_PIPELINE_STATE_DESC opaquePsoDesc;

	//
	// PSO for opaque objects.
	//
	ZeroMemory(&opaquePsoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	opaquePsoDesc.InputLayout = { mInputLayout.data(), (UINT)mInputLayout.size() };
	opaquePsoDesc.pRootSignature = mRootSignature.Get();
	opaquePsoDesc.VS =
	{
		reinterpret_cast<BYTE*>(mShaders["standardVS"]->GetBufferPointer()),
		mShaders["standardVS"]->GetBufferSize()
	};
	opaquePsoDesc.PS =
	{
		reinterpret_cast<BYTE*>(mShaders["opaquePS"]->GetBufferPointer()),
		mShaders["opaquePS"]->GetBufferSize()
	};
	opaquePsoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	opaquePsoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	opaquePsoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	opaquePsoDesc.SampleMask = UINT_MAX;
	opaquePsoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	opaquePsoDesc.NumRenderTargets = 1;
	opaquePsoDesc.RTVFormats[0] = mBackBufferFormat;
	opaquePsoDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	opaquePsoDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	opaquePsoDesc.DSVFormat = mDepthStencilFormat;
	ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(&opaquePsoDesc, IID_PPV_ARGS(&mOpaquePSO)));
}

void InitDirect3DApp::BuildFrameResources()
{
	for (int i = 0; i < gNumFrameResources; ++i)
	{
		mFrameResources.push_back(std::make_unique<FrameResource>(md3dDevice.Get(),
			1, (UINT)mAllRitems.size(), (UINT)mMaterials.size()));
	}
}

<<<<<<< HEAD
void InitDirect3DApp::BuildMaterials(){

	auto splashMat = std::make_unique<Material>();
	splashMat->Name = "splashMat";
	splashMat->MatCBIndex = 0;
	splashMat->DiffuseSrvHeapIndex = 0;
	splashMat->DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	splashMat->FresnelR0 = XMFLOAT3(0.05f, 0.05f, 0.05f);
	splashMat->Roughness = 0.2f;
	
	auto grayMat = std::make_unique<Material>();
	grayMat->Name = "grayMat";
	grayMat->MatCBIndex = 1;
	grayMat->DiffuseSrvHeapIndex = 1;
	grayMat->DiffuseAlbedo = XMFLOAT4(Colors::LightGray);
	grayMat->FresnelR0 = XMFLOAT3(0.02f, 0.02f, 0.02f);
	grayMat->Roughness = 0.2f;

	auto darkGrayMat = std::make_unique<Material>();
	darkGrayMat->Name = "darkGrayMat";
	darkGrayMat->MatCBIndex = 2;
	darkGrayMat->DiffuseSrvHeapIndex = 2;
	darkGrayMat->DiffuseAlbedo = XMFLOAT4(Colors::DarkGray);
	darkGrayMat->FresnelR0 = XMFLOAT3(0.02f, 0.02f, 0.02f);
	darkGrayMat->Roughness = 0.2f;

	auto yellowMat = std::make_unique<Material>();
	yellowMat->Name = "yellowMat";
	yellowMat->MatCBIndex = 3;
	yellowMat->DiffuseSrvHeapIndex = 3;
	yellowMat->DiffuseAlbedo = XMFLOAT4(Colors::Yellow);
	yellowMat->FresnelR0 = XMFLOAT3(0.02f, 0.02f, 0.02f);
	yellowMat->Roughness = 0.2f;

	auto orangeMat = std::make_unique<Material>();
	orangeMat->Name = "orangeMat";
	orangeMat->MatCBIndex = 4;
	orangeMat->DiffuseSrvHeapIndex = 4;
	orangeMat->DiffuseAlbedo = XMFLOAT4(Colors::Orange);
	orangeMat->FresnelR0 = XMFLOAT3(0.02f, 0.02f, 0.02f);
	orangeMat->Roughness = 0.2f;

	auto redMat = std::make_unique<Material>();
	redMat->Name = "redMat";
	redMat->MatCBIndex = 5;
	redMat->DiffuseSrvHeapIndex = 6;
	redMat->DiffuseAlbedo = XMFLOAT4(Colors::Red);
	redMat->FresnelR0 = XMFLOAT3(0.02f, 0.02f, 0.02f);
	redMat->Roughness = 0.2f;

	auto purpleMat = std::make_unique<Material>();
	purpleMat->Name = "purpleMat";
	purpleMat->MatCBIndex = 6;
	purpleMat->DiffuseSrvHeapIndex = 6;
	purpleMat->DiffuseAlbedo = XMFLOAT4(Colors::Purple);
	purpleMat->FresnelR0 = XMFLOAT3(0.02f, 0.02f, 0.02f);
	purpleMat->Roughness = 0.2f;

	auto blueMat = std::make_unique<Material>();
	blueMat->Name = "blueMat";
	blueMat->MatCBIndex = 7;
	blueMat->DiffuseSrvHeapIndex = 7;
	blueMat->DiffuseAlbedo = XMFLOAT4(Colors::Blue);
	blueMat->FresnelR0 = XMFLOAT3(0.02f, 0.02f, 0.02f);
	blueMat->Roughness = 0.2f;

	auto greenMat = std::make_unique<Material>();
	greenMat->Name = "greenMat";
	greenMat->MatCBIndex = 8;
	greenMat->DiffuseSrvHeapIndex = 8;
	greenMat->DiffuseAlbedo = XMFLOAT4(Colors::Green);
	greenMat->FresnelR0 = XMFLOAT3(0.02f, 0.02f, 0.02f);
	greenMat->Roughness = 0.2f;

	auto invisMat = std::make_unique<Material>();
	invisMat->Name = "invisMat";
	invisMat->MatCBIndex = 9;
	invisMat->DiffuseSrvHeapIndex = 9;
	invisMat->DiffuseAlbedo = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	invisMat->FresnelR0 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	invisMat->Roughness = 0.0f;

	mMaterials["splashMat"] = std::move(splashMat);
	mMaterials["grayMat"] = std::move(grayMat);
	mMaterials["darkGrayMat"] = std::move(darkGrayMat);
	mMaterials["yellowMat"] = std::move(yellowMat);
	mMaterials["orangeMat"] = std::move(orangeMat);
	mMaterials["redMat"] = std::move(redMat);
	mMaterials["purpleMat"] = std::move(purpleMat);
	mMaterials["blueMat"] = std::move(blueMat);
	mMaterials["greenMat"] = std::move(greenMat);
	mMaterials["invisMat"] = std::move(invisMat);
=======
void InitDirect3DApp::BuildMaterials()
{
	auto bricks0 = std::make_unique<Material>();
	bricks0->Name = "bricks0";
	bricks0->MatCBIndex = 0;
	bricks0->DiffuseSrvHeapIndex = 0;
	bricks0->DiffuseAlbedo = XMFLOAT4(Colors::ForestGreen);
	bricks0->FresnelR0 = XMFLOAT3(0.02f, 0.02f, 0.02f);
	bricks0->Roughness = 0.1f;

	auto stone0 = std::make_unique<Material>();
	stone0->Name = "stone0";
	stone0->MatCBIndex = 1;
	stone0->DiffuseSrvHeapIndex = 1;
	stone0->DiffuseAlbedo = XMFLOAT4(Colors::LightSteelBlue);
	stone0->FresnelR0 = XMFLOAT3(0.05f, 0.05f, 0.05f);
	stone0->Roughness = 0.3f;

	auto tile0 = std::make_unique<Material>();
	tile0->Name = "tile0";
	tile0->MatCBIndex = 2;
	tile0->DiffuseSrvHeapIndex = 2;
	tile0->DiffuseAlbedo = XMFLOAT4(Colors::LightGray);
	tile0->FresnelR0 = XMFLOAT3(0.02f, 0.02f, 0.02f);
	tile0->Roughness = 0.2f;

	auto skullMat = std::make_unique<Material>();
	skullMat->Name = "skullMat";
	skullMat->MatCBIndex = 3;
	skullMat->DiffuseSrvHeapIndex = 3;
	skullMat->DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	skullMat->FresnelR0 = XMFLOAT3(0.05f, 0.05f, 0.05);
	skullMat->Roughness = 0.3f;

	mMaterials["bricks0"] = std::move(bricks0);
	mMaterials["stone0"] = std::move(stone0);
	mMaterials["tile0"] = std::move(tile0);
	mMaterials["skullMat"] = std::move(skullMat);
>>>>>>> parent of 2219bf3... Added 3D rendering and texturing to DirectX
}

void InitDirect3DApp::BuildRenderItems()
{
<<<<<<< HEAD
	std::unique_ptr<RenderItem> shapeHolder;
	int index = 0;

	shapeHolder = std::make_unique<RenderItem>();
	XMStoreFloat4x4(&shapeHolder->World, XMMatrixScaling(8.0f, 8.0f, 8.0f)*XMMatrixTranslation(-12.0f, -4.0f, 0.0f));
	//XMStoreFloat4x4(&cubeHolder->TexTransform, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	shapeHolder->ObjCBIndex = index;
	shapeHolder->Mat = mMaterials["splashMat"].get();
	shapeHolder->Geo = mGeometries["shapeGeo"].get();
	shapeHolder->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	shapeHolder->IndexCount = shapeHolder->Geo->DrawArgs["splashArt"].IndexCount;
	shapeHolder->StartIndexLocation = shapeHolder->Geo->DrawArgs["splashArt"].StartIndexLocation;
	shapeHolder->BaseVertexLocation = shapeHolder->Geo->DrawArgs["splashArt"].BaseVertexLocation;
	mAllRitems.push_back(std::move(shapeHolder));
	index++;

	shapeHolder = std::make_unique<RenderItem>();
	XMStoreFloat4x4(&shapeHolder->World, XMMatrixScaling(1.0f, 1.0f, 1.0f)*XMMatrixTranslation(0.0f, 0.0f, 0.0f));
	//XMStoreFloat4x4(&cubeHolder->TexTransform, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	shapeHolder->ObjCBIndex = index;
	shapeHolder->Mat = mMaterials["orangeMat"].get();
	shapeHolder->Geo = mGeometries["shapeGeo"].get();
	shapeHolder->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	shapeHolder->IndexCount = shapeHolder->Geo->DrawArgs["box"].IndexCount;
	shapeHolder->StartIndexLocation = shapeHolder->Geo->DrawArgs["box"].StartIndexLocation;
	shapeHolder->BaseVertexLocation = shapeHolder->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(shapeHolder));
	index++;
=======
	/*
	auto boxRitem = std::make_unique<RenderItem>();
	XMStoreFloat4x4(&boxRitem->World, XMMatrixScaling(2.0f, 2.0f, 2.0f)*XMMatrixTranslation(0.0f, 0.5f, 0.0f));
	XMStoreFloat4x4(&boxRitem->TexTransform, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	boxRitem->ObjCBIndex = 0;
	boxRitem->Mat = mMaterials["stone0"].get();
	boxRitem->Geo = mGeometries["shapeGeo"].get();
	boxRitem->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	boxRitem->IndexCount = boxRitem->Geo->DrawArgs["box"].IndexCount;
	boxRitem->StartIndexLocation = boxRitem->Geo->DrawArgs["box"].StartIndexLocation;
	boxRitem->BaseVertexLocation = boxRitem->Geo->DrawArgs["box"].BaseVertexLocation;
	mAllRitems.push_back(std::move(boxRitem));
	*/
>>>>>>> parent of 2219bf3... Added 3D rendering and texturing to DirectX

	// All the render items are opaque.
	for (auto& e : mAllRitems)
		mOpaqueRitems.push_back(e.get());
}

void InitDirect3DApp::DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems)
{
	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	UINT matCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(MaterialConstants));

	auto objectCB = mCurrFrameResource->ObjectCB->Resource();
	auto matCB = mCurrFrameResource->MaterialCB->Resource();

	// For each render item...
	for (size_t i = 0; i < ritems.size(); ++i)
	{
		auto ri = ritems[i];

		cmdList->IASetVertexBuffers(0, 1, &ri->Geo->VertexBufferView());
		cmdList->IASetIndexBuffer(&ri->Geo->IndexBufferView());
		cmdList->IASetPrimitiveTopology(ri->PrimitiveType);

		D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + ri->ObjCBIndex*objCBByteSize;
		D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + ri->Mat->MatCBIndex*matCBByteSize;

		cmdList->SetGraphicsRootConstantBufferView(0, objCBAddress);
		cmdList->SetGraphicsRootConstantBufferView(1, matCBAddress);

		cmdList->DrawIndexedInstanced(ri->IndexCount, 1, ri->StartIndexLocation, ri->BaseVertexLocation, 0);
	}
}
<<<<<<< HEAD

std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> InitDirect3DApp::GetStaticSamplers()
{
	// Applications usually only need a handful of samplers.  So just define them all up front
	// and keep them available as part of the root signature.  

	const CD3DX12_STATIC_SAMPLER_DESC pointWrap(
		0, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC pointClamp(
		1, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC linearWrap(
		2, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC linearClamp(
		3, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC anisotropicWrap(
		4, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressW
		0.0f,                             // mipLODBias
		8);                               // maxAnisotropy

	const CD3DX12_STATIC_SAMPLER_DESC anisotropicClamp(
		5, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressW
		0.0f,                              // mipLODBias
		8);                                // maxAnisotropy

	return {
		pointWrap, pointClamp,
		linearWrap, linearClamp,
		anisotropicWrap, anisotropicClamp };
}


=======
>>>>>>> parent of 2219bf3... Added 3D rendering and texturing to DirectX
