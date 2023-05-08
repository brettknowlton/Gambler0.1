#pragma once
class IndexBuffer
{
private:
    unsigned int m_RendererID;//this number is the ID of the buffer.
    void* m_MappedBuffer;
    unsigned int m_Count;
public:
    IndexBuffer(const void* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_Count; }

    void MapBuffer();
    void UnmapBuffer();

    const unsigned int* GetData() const;
};
