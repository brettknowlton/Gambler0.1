#include "IndexBuffer.h"
#include "GLMacros.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count)
: m_Count(count)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data,  GL_STATIC_DRAW));
}

IndexBuffer:: ~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID))
}
void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::MapBuffer()
{
    Bind();
    GLCall(m_MappedBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
}

void IndexBuffer::UnmapBuffer()
{
    GLCall(glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER));
    Unbind();
}

const unsigned int* IndexBuffer::GetData() const
{
    return (const unsigned int*)m_MappedBuffer;
}