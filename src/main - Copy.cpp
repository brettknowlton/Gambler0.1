#define GLEW_STATIC

//DEFINE EDITOR MODE HERE!

//DEFINE EDITOR MODE HERE!
#define GAMBLER_DEBUG




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
#include "renderer/BatchRenderer.cpp"

//Math includes
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

//imgui includes
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"

//tests
#include "tests/Test.cpp"
#include "tests/TestClearColor.cpp"
#include "tests/TestTexture2D.cpp"
#include "tests/TestBatchedRendering.cpp"
#include "tests/TestRenderWorld.cpp"

//game
#include "World.cpp"
#include "Zone.cpp"
#include "Collider.cpp"
#include "Tile.cpp"
#include "Camera.cpp"


#include <memory>


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
        //enable blending
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

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

        test::Test* currentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestTexture2D>("Texture 2D");
        testMenu->RegisterTest<test::TestBatchedRendering>("Batched Rendering");
        testMenu->RegisterTest<test::TestRenderWorld>("Render World");



        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            
            /* Poll for and process events */
            glfwPollEvents();
            

            // Render
            GLCall(glClearColor(0.7f, 0.5f, 0.0f, 1.0f));
            renderer.Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            
            if (currentTest)
            {
                currentTest->OnUpdate(0.0f);

                currentTest->OnRender(renderer);
                ImGui::Begin("Test");
                if (currentTest != testMenu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->OnImGuiRender();
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

        delete currentTest;
        if(currentTest != testMenu)
            delete testMenu;
        //last , after game loop
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }


    glfwTerminate();
    return 0;
}