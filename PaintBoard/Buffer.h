#pragma once

class Buffer
{
public:
	Buffer();
	Buffer(const Buffer&) = delete;
	Buffer(Buffer&&) = delete;
	virtual ~Buffer() = default;

public:
	void Initialize(void* pData, UINT numOfElement, UINT elementSize);
	void Update(void* pData, UINT numOfElement, UINT elementSize);

public:

	ID3D11Buffer* GetBuffer() { return m_mainBuffer.Get(); }
	ID3D11Buffer** GetBufferAddress() { return m_mainBuffer.GetAddressOf(); }
protected:
	ComPtr<ID3D11Buffer> m_mainBuffer;
	ComPtr<ID3D11Buffer> m_stagingBuffer;
	D3D11_BIND_FLAG m_bindFlag;
};
