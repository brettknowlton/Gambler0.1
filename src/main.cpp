// Define editor mode here!
#define GAMBLER_DEBUG

// OpenGL includes
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

// Standard includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Custom includes
#include "GLMacros.h"
#include "KeyListener.cpp"

// Renderer Classes (probably not going to stay here)
#include "renderer/VertexBuffer.cpp"
#include "renderer/IndexBuffer.cpp"
#include "renderer/VertexArray.cpp"
#include "renderer/Shader.cpp"
#include "renderer/Renderer.cpp"
#include "renderer/Texture.cpp"
#include "renderer/BatchRenderer.cpp"

// Math includes
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

// ImGui includes
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"

// Test classes
#include "tests/Test.cpp"
#include "tests/TestClearColor.cpp"
#include "tests/TestBatchedRendering.cpp"
#include "tests/TestRenderWorld.cpp"
#include "tests/TestPlayer.cpp"

// Game classes
#include "game/World.cpp"
#include "game/Zone.cpp"
#include "game/Collider.cpp"
#include "game/Tile.cpp"
#include "game/Camera.cpp"
//#include "game/Player.cpp"

// ECS classes
#include "game/ecs/Entity.cpp"
#include "game/ecs/Componenets/Component.cpp"
#include "game/ecs/Componenets/CMP_Transform.cpp"

#include <memory>

// Function prototypes
void InitializeGLFW();
GLFWwindow* CreateGLFWWindow();
void InitializeGLEW();
void InitializeImGui(GLFWwindow* window);
void ShutdownImGui();
void RunApplicationLoop(GLFWwindow* window, test::Test*& currentTest, test::TestMenu* testMenu);
void RenderImGui(test::Test*& currentTest, test::TestMenu* testMenu, Renderer& renderer);

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    /*
    * Inputs:
    * GLFWwindow* window: A pointer to the GLFW window that the callback is being called from.
    * int key: The key that was pressed.
    * int scancode: The system-specific scancode of the key.
    * int action: The action that was performed on the key.
    * int mods: Bit field describing which modifier keys were held down.
    *
    * Functionality:
    * Handles key presses and releases.
    *
    * Returns: None
    */
    KeyListener::GetInstance().SetKeyState(key, action);
}

int main(void)
{
    
    InitializeGLFW();

    GLFWwindow* window = CreateGLFWWindow();
    if (!window) {
        glfwTerminate();
        return -1;
    }

    InitializeGLEW();

    // Initialize ImGui and set up styles
    InitializeImGui(window);

    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;

    // Register tests here
    testMenu->RegisterTest<test::TestClearColor>("Clear Color");
    testMenu->RegisterTest<test::TestBatchedRendering>("Batched Rendering");
    testMenu->RegisterTest<test::TestRenderWorld>("Render World");
    testMenu->RegisterTest<test::TestPlayer>("Player");

    glfwSetKeyCallback(window, KeyCallback);

    RunApplicationLoop(window, currentTest, testMenu);

    ShutdownImGui();

    glfwTerminate();
    return 0;
}

void InitializeGLFW() {
    /*
    * Inputs: None
    *
    * Functionality:
    * Initializes the GLFW library and sets window hints for the OpenGL context.
    *
    * Returns: None
    */
    if (!glfwInit()) {
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* CreateGLFWWindow() {
    /*
    * Inputs: None
    *
    * Functionality:
    * Creates a GLFW window with a specified width, height, and title.
    * Sets the window's context current and syncs the framerate with the monitor's refresh rate.
    *
    * Returns GLFWwindow*: A pointer to the created GLFW window.
    */
    GLFWwindow* window = glfwCreateWindow(960, 540, "Gambler0.2", NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Set framerate to sync with monitor's refresh rate

    return window;
}

void InitializeGLEW() {
    /*
    * Inputs: None
    *
    * Functionality:
    * Initializes the GLEW library and prints the OpenGL version to the console.
    *
    * Returns: None
    */
    if (glewInit() != GLEW_OK) {
        std::cout << "Error initializing GLEW" << std::endl;
        exit(-1);
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
}

void InitializeImGui(GLFWwindow* window) {
    /*
    * Inputs:
    * GLFWwindow* window : A pointer to the GLFW window for which ImGui is to be initialized.
    *
    * Functionality:
    * Initializes ImGui for the given GLFW window and sets ImGui configurations and styles.
    *
    * Returns: None
    */
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();
}

void ShutdownImGui() {
    /*
    * Inputs: None
    *
    * Functionality:
    * Shuts down ImGui, releasing its resources.
    *
    * Returns: None
    */
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void RunApplicationLoop(GLFWwindow* window, test::Test*& currentTest, test::TestMenu* testMenu) {
    /*
    * Inputs:
    * GLFWwindow* window         : A pointer to the GLFW window.
    * test::Test*& currentTest   : A reference to a pointer to the current test being executed.
    * test::TestMenu* testMenu   : A pointer to the test menu.
    *
    * Functionality:
    * Runs the main application loop, updating and rendering ImGui and handling test execution.
    *
    * Returns: None
    */
    Renderer renderer;

    // Enable blending
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Render
        GLCall(glClearColor(0.3f, 0.3f, 0.5f, 1.0f));
        renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        RenderImGui(currentTest, testMenu, renderer);

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }

    delete currentTest;
    if (currentTest != testMenu) {
        delete testMenu;
    }
}

void RenderImGui(test::Test*& currentTest, test::TestMenu* testMenu, Renderer& renderer) {
    /*
    * Inputs:
    * test::Test*& currentTest   : A reference to a pointer to the current test being executed.
    * test::TestMenu* testMenu   : A pointer to the test menu.
    * Renderer& renderer         : A reference to the Renderer object being used.
    *
    * Functionality:
    * Renders ImGui components and updates the current test's ImGui components.
    *
    * Returns: None
    */
    if (currentTest) {
        currentTest->OnUpdate(0.0f);
        currentTest->OnRender();
        currentTest->OnRender(renderer);
        ImGui::Begin("Test");
        if (currentTest != testMenu && ImGui::Button("<-")) {
            delete currentTest;
            currentTest = testMenu;
        }
        currentTest->OnImGuiRender();
        ImGui::End();
    }
}