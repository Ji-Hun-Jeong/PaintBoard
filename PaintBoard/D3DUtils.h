#pragma once
// SingleTon은 하드웨어에 한해서만

class D3DUtils
{
public:
	D3DUtils(const D3DUtils&) = delete;
	D3DUtils(D3DUtils&&) = delete;
private:
	D3DUtils() = default;
	~D3DUtils() = default;
public:
	void CreateVertexShaderAndInputLayout(const wstring& vsPrefixPath, ComPtr<ID3D11VertexShader>& vs,
		const vector<D3D11_INPUT_ELEMENT_DESC>& desc, ComPtr<ID3D11InputLayout>& inputLayout);

	void CreatePixelShader(const wstring& psPrefixPath, ComPtr<ID3D11PixelShader>& ps);

	void CreateBuffer(UINT numOfElement, UINT elementSize, D3D11_BIND_FLAG bindFlag
		, ComPtr<ID3D11Buffer>& buffer);

	void CreateStagingBuffer(void* initData, UINT numOfElement, UINT elementSize
		, ComPtr<ID3D11Buffer>& stagingBuffer);

	void UpdateBuffer(void* pData, UINT numOfElement, UINT elementSize
		, ComPtr<ID3D11Buffer>& buffer, ComPtr<ID3D11Buffer>& stagingBuffer);
public:
	void CreateVertexBuffer(UINT numOfElement, UINT elementSize, ComPtr<ID3D11Buffer>& buffer);

	void CreateIndexBuffer(UINT numOfElement, UINT elementSize, ComPtr<ID3D11Buffer>& buffer);
public:
	void Initialize(HWND hWnd, UINT screenWidth, UINT screenHeight);

	static D3DUtils& GetInst();
	ComPtr<ID3D11Device>& GetDevice() { return m_device; }
	ComPtr<ID3D11DeviceContext>& GetContext() { return m_context; }
	ComPtr< IDXGISwapChain>& GetSwapChain() { return m_swapChain; }
	UINT GetMSAALevel() { return m_msaaLevel; }

private:
	ComPtr<ID3D11Device> m_device;
	ComPtr<ID3D11DeviceContext> m_context;
	ComPtr<IDXGISwapChain> m_swapChain;

	UINT m_screenWidth = 0;
	UINT m_screenHeight = 0;
	UINT m_msaaLevel = 0;
};

