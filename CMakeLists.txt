cmake_minimum_required(VERSION 3.25.2)
project(FinalYearProject)
set(CMAKE_CXX_STANDARD 17)
find_package(OpenGL REQUIRED)
add_subdirectory(third_party/glad)
add_subdirectory(third_party/dependencies)

include(FetchContent)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        bf71a834948186f4097caa076cd2663c69a10e1e
)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        7482de6071d21db77a7236155da44c172a7f6c9e
)
FetchContent_MakeAvailable(glm glfw)

add_executable(FinalYearProject main.cpp)
target_link_libraries(FinalYearProject ${OPENGL_LIBRARIES} glm glfw glad imgui)