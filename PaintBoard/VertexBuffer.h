#pragma once
#include "Buffer.h"
class VertexBuffer :
    public Buffer
{
public:
    VertexBuffer();
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&&) = delete;
    ~VertexBuffer() = default;

private:

};

