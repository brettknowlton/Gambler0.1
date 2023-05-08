#pragma once

class Texture
{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int mWidth, mHeight, m_BPP;
public:
    Texture(const std::string& path, unsigned int slot=0);
    ~Texture();

    void Bind(unsigned int slot= 0) const;//There are typically up to 32 texture slots on modern GPUs
    void Unbind() const;

    inline unsigned int GetWidth() const { return mWidth; }
    inline unsigned int GetHeight() const { return mHeight; }
};