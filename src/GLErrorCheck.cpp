//This file is nothing but macros for our openGL calls. Getting them out of the way by putting them here.
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__ ))

static void GLClearError()
{while (glGetError() != GL_NO_ERROR);}

static bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ")" << function <<
         " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}