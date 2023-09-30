﻿// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "__others/targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>

using namespace std;


#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

using namespace DirectX;

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#pragma comment(lib, "ImGui.lib")

#include "DirectXTex.h"
#include "DirectXTex.inl"

#pragma comment(lib, "DirectXTex.lib")

#include <shlwapi.h>

#pragma comment(lib, "shlwapi.lib")

#define	WIN_WIDTH		1920.f
#define	WIN_HEIGHT		1080.f

#define WIN_CENTER		Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f)
#define WIN_SIZE		Vector2(WIN_WIDTH, WIN_HEIGHT)

#define DEVICE			Device::GetInstance()->GetDevice()
#define DC				Device::GetInstance()->GetDC()
#define CAMERA			Camera::GetInstance()

#define KEY_UP(p)		Keyboard::GetInstance()->Up(p)
#define KEY_DOWN(p)		Keyboard::GetInstance()->Down(p)
#define KEY_PRESS(p)	Keyboard::GetInstance()->Press(p)

#define MAP_ROW			13
#define MAP_COL			15

#define TEX_WORLD_SIZE	Vector2(WIN_WIDTH / MAP_COL, WIN_HEIGHT / MAP_ROW)

#define GM				GameManager::GetInst()

typedef XMFLOAT3 Vector3;
typedef XMFLOAT4 Vector4;
typedef XMMATRIX Matrix;


#include "Utility/Singleton.h"
#include "Utility/Keyboard.h"
#include "Utility/Time.h"
#include "Utility/Vector2.h"

#include "Manager/GameManager.h"

#include "Object/Transform.h"

#include "Renderer.h"

#include "Utility/Util.h"

#include "Utility/BinaryWriter.h"
#include "Utility/BinaryReader.h"

#include "System/Device.h"

#include "Render/Buffer/VertexLayout.h"
#include "Render/Buffer/VertexBuffer.h"
#include "Render/Buffer/IndexBuffer.h"
#include "Render/Buffer/ConstantBuffer.h"
#include "Render/Buffer/GlobalBuffer.h"


#include "Render/Texture/Texture.h"
#include "Render/Texture/Frame.h"
#include "Render/Texture/Animation.h"

#include "Render/Shader/VertexShader.h"
#include "Render/Shader/PixelShader.h"


#include "System/Environment.h"
#include "System/Camera.h"

#include "Object/Basic/Object.h"
#include "Object/Basic/Polygons.h"
#include "Object/SolarSystem/Planet.h"

#include "Object/Collision/Collider.h"
#include "Object/Collision/ColliderRect.h"
#include "Object/Collision/ColliderCircle.h"

#include "GameMap/TileManager.h"
#include "GameMap/Block.h"
#include "GameMap/BlockManager.h"

#include "GameMap/MapEditor.h"



#include "Object/Game/Character.h"
#include "Object/Game/Knight.h"

#include "Scene/Scene.h"
#include "Scene/TutorialScene.h"
#include "Scene/SRTScene.h"
#include "Scene/SolarScene.h"
#include "Scene/TextureScene.h"
#include "Scene/CollisionScene.h"

#include "Scene/GameScene.h"

#include "MainGame.h"


extern HWND hWnd;
extern Vector2 mousePos;