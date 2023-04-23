#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

//#include "GLMacros.h"

#include "VertexBuffer.cpp"
#include "IndexBuffer.cpp"
#include "VertexArray.cpp"
#include "Shader.cpp"
#include "Renderer.cpp"



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
    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
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


    {//TODO: figure out how to get rid of this scoping issue...
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

        //extra spacing added for readability, this is important to understand.
        
        //index buffers and vertex buffers are stored in the GPU's memory, so we need to tell the GPU what the data is and where it is
        //we do this by creating a vertex-array object, which will store the data and tell the GPU what it is and where it is
        //vertex buffers specifically are used to store the data 
        //index buffers specifically are used to tell the GPU what order to draw the data in
        //There is a 3rd object called a vertex array object.
        //vertex arrays have the ability to store both vertex buffers and index buffers, and tell the GPU what the data is and where it is

        VertexArray va; //create a vertex-array object, this will partially be the VBO, but it will also tell the GPU what type the data is and where it is


        VertexBuffer vb(positions, 4 * 2 * sizeof(float));//create a vertex-buffer object aka VBO, veretx-buffer takes in a pointer to the data and the size of the data you want to store in it


        VertexBufferLayout layout;//also create a vertex-buffer-layout object to tell the vertex buffer what the data is


        layout.Push<float>(2);//tell the layout that the data is a float and that there are 2 of them


        va.AddBuffer(vb, layout);//add the vertex-buffer and the vertex-buffer-layout to the vertex-array object


        IndexBuffer ib(indecies, 6);//create an index-buffer object aka IBO, this will represent the order that the data in the vertex-buffer object should be drawn in


        Shader shader = Shader("../../res/shaders/basic.shader");//create a shader object, this will represent the shader program that will be used to draw the data in the vertex-buffer object
        shader.Bind();
        
        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);//set the uniform variable u_Color

        va.Unbind();//unbind the vertex array object
        vb.Unbind();//unbind the vertex buffer object
        ib.Unbind();//unbind the index buffer object
        shader.Unbind();//unbind the shader program

        Renderer renderer;

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
            
            if(colors[channel] >= 1.0f){
                channel2 = channel;
                channel = (channel + 1) % 3;
            }
            colors[channel] += increment;
            colors[channel2] -= increment;

            


            /* Render here */
            renderer.Clear();
            shader.Bind();
            shader.SetUniform4f("u_Color", colors[0], colors[1], colors[2], 1.0f);
            
            //this is the draw call. 
            //the vertex array object is bound, the index buffer object is bound, and the shader program is bound
            renderer.Draw(va, ib, shader);


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

        }
    }
    glfwTerminate();
    return 0;
}