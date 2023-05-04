#define GLEW_STATIC

//DEFINE EDITOR MODE HERE!


//OpenGL includes
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

//Standard includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

//Custom includes
#include "GLMacros.h"

//Renderer Classes (probably not going to stay here)
#include "renderer/VertexBuffer.cpp"
#include "renderer/IndexBuffer.cpp"
#include "renderer/VertexArray.cpp"
#include "renderer/Shader.cpp"
#include "renderer/Renderer.cpp"
#include "renderer/Texture.cpp"

//Math includes
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

//imgui includes
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"


int main(void)
{
//////////////////////////////////////////////////////////////
////////////////////////// GL SETUP //////////////////////////
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Gambler0.2", NULL, NULL);
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
////////////////////////// END OF GL SETUP //////////////////////////
/////////////////////////////////////////////////////////////////////

    {//TODO: figure out how to get rid of this gross scoping issue...
        float positions[] = {
            -50.0f, -50.0f, 0.0f, 0.0f,
            50.0f, -50.0f, 1.0f, 0.0f,
            50.0f, 50.0f, 1.0f, 1.0f,
            -50.0f, 50.0f, 0.0f, 1.0f,
        };

        unsigned int indecies[]{
            0,1,2,
            2,3,0,
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        //extra spacing added for readability, this is important to understand.
        
        //index buffers and vertex buffers are stored in the GPU's memory, so we need to tell the GPU what the data is and where it is
        //we do this by creating a vertex-array object, which will store the data and tell the GPU what it is and where it is
        //vertex buffers specifically are used to store the data 
        //index buffers specifically are used to tell the GPU what order to draw the data in
        //There is a 3rd object called a vertex array object.
        //vertex arrays have the ability to store both vertex buffers and index buffers, and tell the GPU what the data is and where it is

        VertexArray va; 

        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        va.AddBuffer(vb, layout);

        IndexBuffer ib(indecies, 6);

        //projection matrix converts from world coordinates to screen coordinates, in this case from pixel space to NDC space
        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        
        //view matrix converts from world coordinates to camera coordinates. note: translating the "camera" is actually translating the world in the OPPOSITE direction
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        Shader shader = Shader("../../res/shaders/basic.shader");
        shader.Bind();
        
        //shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        Texture texture("../../res/textures/test.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);
    
        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;


        //imgui setup
        //IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows


        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
        ImGui::StyleColorsDark();

        glm::vec3 translation(200,200,0);


        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);



        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            
            /* Poll for and process events */
            glfwPollEvents();
            
            //tick or update
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            

            /* Render here */
            renderer.Clear();

            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);

            glm::mat4 mvp = proj * view * model;


            shader.Bind();
            
            shader.SetUniformMat4f("u_MVP", mvp);
            
            //this is the draw call. 
            //the vertex array object is bound, the index buffer object is bound, and the shader program is bound
            renderer.Draw(va, ib, shader);

            static float f = 0.0f;
            static int counter = 0;

            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Gambler Level Editor");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");

                ImGui::SliderFloat2("Translation", &translation.x, 0.0f, 960.0f);
                ImGui::End();
            }


            // Rendering
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

        }
        //last , after game loop
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    glfwTerminate();
    return 0;
}