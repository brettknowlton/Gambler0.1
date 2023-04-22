#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Renderer.cpp"

#include "VertexBuffer.cpp"
#include "IndexBuffer.cpp"
#include "VertexArray.cpp"

struct ShaderProgramSource{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string &filepath){
    
    //create a file stream
    std::ifstream stream(filepath);
    std::cout << "Reading: " << filepath << std::endl;

    //create an enum to track what type of shader we are parsing
    enum class ShaderType{
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    //create a string(line) and an array(ss) that we will use to parse through and add lines to one or the other shader
    std::string line;
    std::stringstream ss[2];

    //start with no shader type
    ShaderType type = ShaderType::NONE;

    while(getline(stream, line)){
        if(line.find("#shader") != std::string::npos){
            if (line.find("vertex") != std::string::npos){
                type = ShaderType::VERTEX;

            }
            else if (line.find("fragment") != std::string::npos){
                //fragment mode
                type = ShaderType::FRAGMENT;
            }
        }
        else{
            ss[(int)type] << line << std::endl;
    }
    }
    /*
    * Print shader code:
    * std::cout << "VERTEX" << std::endl;
    * std::cout << ss[0].str() << std::endl;
    * std::cout << "FRAGMENT" << std::endl;
    * std::cout << ss[1].str() << std::endl;
    */

    return { 
        ss[0].str(),
        ss[1].str()
    };
}

static unsigned int compileShader(unsigned int type,const std::string& source){
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile "<< 
        (type==GL_VERTEX_SHADER ? "vertex" : (type == GL_FRAGMENT_SHADER ? "fragment" : "no")) << 
        " shader!" << std::endl;

        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);


    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /*Set framerate to sync with monitor's refresh rate*/
    glfwSwapInterval(1);

    if(glewInit() != GLEW_OK){
        std::cout <<"Error initializing GLEW"<<std::endl;
        return -1;
    }

    //print gl version
    std::cout << glGetString(GL_VERSION) << std::endl;


    {
        float positions[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f,  0.5f,
            -0.5f,  0.5f,
        };

        unsigned int indecies[]{
            0,1,2,
            2,3,0,
        };

        //vertex array object
        unsigned int vao;

        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indecies, 6);

        ShaderProgramSource source = ParseShader("../../res/shaders/basic.shader");
        
        unsigned int shader = createShader(source.VertexSource, source.FragmentSource);
        GLCall(glUseProgram(shader));
        
        GLCall(int location = glGetUniformLocation(shader, "u_Color"));
        ASSERT(location != -1);

        GLCall(glUseProgram(0));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

        float colors[] = {0, 1.0f, 0};
        unsigned int channel = 0;
        unsigned int channel2 = 1;
        float increment = 0.005f;


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            //get input
            /* Poll for and process events */
            glfwPollEvents();



            //tick or update


            /* Render here */
            GLCall(glClear(GL_COLOR_BUFFER_BIT));

            GLCall(glUseProgram(shader));
            GLCall(glUniform4f(location, colors[0], colors[1], colors[2], 1.0f));

            //vb.Bind();//This binds the VERTEX buffer to the currently bound vertex array object in openGL
           
            va.Bind();//This binds the VERTEX ARRAY object to the currently bound vertex array object in openGL

            ib.Bind();//This binds the INDEX buffer to the currently bound vertex array object in openGL
            
            //this is the draw call. More needs to happen to actualy show what is being drawn. It will draw the currently bound buffer
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            if(colors[channel] >= 1.0f){
                channel2 = channel;
                channel = (channel + 1) % 3;
            }
            colors[channel] += increment;
            colors[channel2] -= increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

        }

        glDeleteProgram(shader);
    }
    glfwTerminate();
    return 0;
}