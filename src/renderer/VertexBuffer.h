#pragma once

#include <stddef.h>

class VertexBuffer
{
private:
    unsigned int m_RendererID;//this number is the ID of the buffer. 
    void* m_MappedBuffer;
    unsigned int m_Count;
    const void* m_Data;
public:
    VertexBuffer(const void* data= nullptr, unsigned int size= 0);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

    void MapBuffer();
    void UnmapBuffer();
    unsigned int GetSize() const { return m_Count; }

    const float* GetData() const;
};
