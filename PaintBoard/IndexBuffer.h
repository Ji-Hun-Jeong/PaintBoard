#pragma once
#include "Buffer.h"
class IndexBuffer :
    public Buffer
{
public:
    IndexBuffer();
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer(IndexBuffer&&) = delete;
    ~IndexBuffer() = default;

private:

};

