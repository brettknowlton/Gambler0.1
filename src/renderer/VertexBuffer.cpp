#include "VertexBuffer.h"
#include "GLMacros.cpp"
#include <GL/glew.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererID));//create ONE buffer and store the ID in m_RendererID
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));//make this the currently active buffer
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));//add data to the currently active buffer
}

VertexBuffer:: ~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID))
}
void VertexBuffer::Bind() const
{//make this the currently active buffer
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{//Unbinds all buffers
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void* VertexBuffer::MapBuffer()
{
    Bind();
    GLCall(m_MappedBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
    return m_MappedBuffer;
}

void VertexBuffer::UnmapBuffer()
{
    GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
    Unbind();
}
