#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>


struct ShaderProgramSource{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string &filepath){
    
    std::ifstream stream(filepath);
    std::cout << filepath << std::endl;
    enum class ShaderType{
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while(getline(stream, line)){
        if(line.find("#shader") != std::string::npos){
            if (line.find("vertex") != std::string::npos){
                type = ShaderType::VERTEX;
                std::cout << "vertex mode";

            }
            else if (line.find("fragment") != std::string::npos){
                //fragment mode
                type = ShaderType::FRAGMENT;
                std::cout << "fragment mode";
            }
        }
        else{
            std::cout << line << std::endl;
            ss[(int)type] << line << std::endl;
    }
    }
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
        (type==GL_VERTEX_SHADER ? "vertex" : "fragment") << 
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

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK){
        std::cout <<"Error initializing GLEW"<<std::endl;
        return -1;
    }

    //print gl version
    std::cout << glGetString(GL_VERSION) << std::endl;

    //define the vertex buffer
    float positions[6] = {
       -0.5f, -0.5f,
        0.0f,  0.5f,
        0.5f, -0.5f
    };

    //create a buffer
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), positions, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);//This explains the layout of the data in the buffer
    glEnableVertexAttribArray(0);

    //std::string workingDir = filesystem::current_path().string();

    //std::cout << workingDir << std::endl;
    //ShaderProgramSource source = ParseShader(workingDir + "..\\res\\shaders\\basic.shader");
    ShaderProgramSource source = ParseShader("C:\\dev\\Gambler0.1\\res\\shaders\\basic.shader");
    std::cout << "VERTEX" << std::endl;
    std::cout << source.VertexSource << std::endl;
    std::cout << "FRAGMENT" << std::endl;
    std::cout << source.FragmentSource << std::endl;

    unsigned int shader = createShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);
    
    


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        //get input
        /* Poll for and process events */
        glfwPollEvents();



        //tick or update


        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        //this is the draw call. More needs to happen to actualy show what is being drawn. It will draw the currently bound buffer
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}