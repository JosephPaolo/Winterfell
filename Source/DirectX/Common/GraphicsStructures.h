#pragma once

#include "../../DirectX/Common/d3dUtil.h"
//#include "../../DirectX/Common/MathHelper.h"
#include "../../DirectX/Common/UploadBuffer.h"

//using Microsoft::WRL::ComPtr;
using namespace DirectX;
//using namespace DirectX::PackedVector;

namespace BRGraphicType {

	////Function by Frank Luna
	struct RenderItem{
		RenderItem() = default;
	
		// World matrix of the shape that describes the object's local space
		// relative to the world space, which defines the position, orientation,
		// and scale of the object in the world.
		XMFLOAT4X4 World = MathHelper::Identity4x4();
	
		XMFLOAT4X4 TexTransform = MathHelper::Identity4x4();
	
		// Dirty flag indicating the object data has changed and we need to update the constant buffer.
		// Because we have an object cbuffer for each FrameResource, we have to apply the
		// update to each FrameResource.  Thus, when we modify obect data we should set 
		// NumFramesDirty = gNumFrameResources so that each frame resource gets the update.
		int NumFramesDirty = gNumFrameResources;
	
		// Index into GPU constant buffer corresponding to the ObjectCB for this render item.
		UINT ObjCBIndex = -1;
	
		Material* Mat = nullptr;
		MeshGeometry* Geo = nullptr;
	
		// Primitive topology.
		D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	
		// DrawIndexedInstanced parameters.
		UINT IndexCount = 0;
		UINT StartIndexLocation = 0;
		int BaseVertexLocation = 0;
	};

	//Function by Frank Luna
	/*struct ObjectConstants
	{
		DirectX::XMFLOAT4X4 World = MathHelper::Identity4x4();
		DirectX::XMFLOAT4X4 TexTransform = MathHelper::Identity4x4();
	};*/

	//Function by Frank Luna
	//struct PassConstants
	//{
	//	DirectX::XMFLOAT4X4 View = MathHelper::Identity4x4();
	//	DirectX::XMFLOAT4X4 InvView = MathHelper::Identity4x4();
	//	DirectX::XMFLOAT4X4 Proj = MathHelper::Identity4x4();
	//	DirectX::XMFLOAT4X4 InvProj = MathHelper::Identity4x4();
	//	DirectX::XMFLOAT4X4 ViewProj = MathHelper::Identity4x4();
	//	DirectX::XMFLOAT4X4 InvViewProj = MathHelper::Identity4x4();
	//	DirectX::XMFLOAT3 EyePosW = { 0.0f, 0.0f, 0.0f };
	//	float cbPerObjectPad1 = 0.0f;
	//	DirectX::XMFLOAT2 RenderTargetSize = { 0.0f, 0.0f };
	//	DirectX::XMFLOAT2 InvRenderTargetSize = { 0.0f, 0.0f };
	//	float NearZ = 0.0f;
	//	float FarZ = 0.0f;
	//	float TotalTime = 0.0f;
	//	float DeltaTime = 0.0f;

	//	DirectX::XMFLOAT4 AmbientLight = { 0.0f, 0.0f, 0.0f, 1.0f };

	//	// Indices [0, NUM_DIR_LIGHTS) are directional lights;
	//	// indices [NUM_DIR_LIGHTS, NUM_DIR_LIGHTS+NUM_POINT_LIGHTS) are point lights;
	//	// indices [NUM_DIR_LIGHTS+NUM_POINT_LIGHTS, NUM_DIR_LIGHTS+NUM_POINT_LIGHT+NUM_SPOT_LIGHTS)
	//	// are spot lights for a maximum of MaxLights per object.
	//	Light Lights[MaxLights];
	//};

	//Function by Frank Luna
	/*struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT3 Normal;
	};*/
}
