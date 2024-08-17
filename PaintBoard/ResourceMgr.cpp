#include "pch.h"
#include "ResourceMgr.h"


string ResourceMgr::m_absolutePath = "E:/source/repos/Base/Resource/";
wstring ResourceMgr::m_absolutePathW = L"E:/source/repos/Base/Resource/";

string ResourceMgr::GetResourceAbsolutePath(string fileName)
{
	return string(m_absolutePath + std::move(fileName));
}
wstring ResourceMgr::GetResourceAbsolutePath(wstring fileName)
{
	return wstring(m_absolutePathW + std::move(fileName));
}
