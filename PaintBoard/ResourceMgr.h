#pragma once

	class ResourceMgr
	{
	public:
		ResourceMgr() = default;
		ResourceMgr(const ResourceMgr&) = default;
		ResourceMgr(ResourceMgr&&) = default;
		~ResourceMgr() = default;

	public:
		static string GetResourceAbsolutePath(string fileName);
		static wstring GetResourceAbsolutePath(wstring fileName);

	private:
		static string m_absolutePath;
		static wstring m_absolutePathW;

	};

