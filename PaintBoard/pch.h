// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include "framework.h"
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxtk/SimpleMath.h>
#include <directxtk/DDSTextureLoader.h>
#include <wrl.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Define.h"

using std::cout;
using std::endl;
using std::string;
using std::wstring;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::unique_ptr;
using std::make_unique;
using DirectX::XM_PI;

#endif //PCH_H
