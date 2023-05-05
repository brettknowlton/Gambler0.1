cmake_minimum_required(VERSION 3.5)
project(Gambler0.1)

# Change working directory to be the same as the project directory so relative paths work
set(CMAKE_VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

# Set the path to the Dependencies directory
set(DEPENDENCIES_DIR "${CMAKE_SOURCE_DIR}/Dependencies")

# Add GLFW
set(GLFW_DIR "${DEPENDENCIES_DIR}/GLFW")
include_directories(${GLFW_DIR}/include)
set(LIBS ${LIBS} ${GLFW_DIR}/lib-vc2022/glfw3.lib)

# Add GLUT
set(GLUT_DIR "${DEPENDENCIES_DIR}/GLUT")
include_directories(${GLUT_DIR}/include)
set(LIBS ${LIBS} ${GLUT_DIR}/lib/glut32.lib)

# Add GLEW
set(GLEW_DIR "${DEPENDENCIES_DIR}/GLEW")
include_directories(${GLEW_DIR}/include)
set(LIBS ${LIBS} ${GLEW_DIR}/lib/Release/Win32/glew32s.lib)

# Add misc libraries
include_directories(${CMAKE_SOURCE_DIR}/src)

# Add imgui source files
include_directories(${CMAKE_SOURCE_DIR}/src/vendor)
file(GLOB IMGUI_SOURCES ${CMAKE_SOURCE_DIR}/src/vendor/imgui/*.cpp)
file(GLOB IMGUI_HEADERS ${CMAKE_SOURCE_DIR}/src/vendor/imgui/*.h)

# Add your project source files
add_executable(Gambler0.1 src/main.cpp ${IMGUI_SOURCES})

# Link libraries
target_link_libraries(Gambler0.1 ${LIBS})

# Set the C++ standard to the latest release
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)