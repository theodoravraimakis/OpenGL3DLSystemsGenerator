cmake_minimum_required(VERSION 3.18)
project(FinalYearProject)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(ThirdParty/glad)
add_subdirectory(ThirdParty/imgui)
add_subdirectory(ThirdParty/stb)

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
FetchContent_Declare(
    rapidobj
    GIT_REPOSITORY https://github.com/guybrush77/rapidobj.git
    GIT_TAG        bce0b3677c2f64002cc0aa3cd10b3bf5960f885b
)

FetchContent_MakeAvailable(glm glfw rapidobj) # can only use once


add_executable(FinalYearProject main.cpp
                                UI/UI.cpp
                                Window/Window.cpp
                                Shader/Shader.cpp
                                Error/Error.cpp
                                Checkpoint/Checkpoint.cpp
                                Render/Render.cpp
                                Camera/Camera.cpp
                                Shapes/Mesh.cpp
                                Shapes/Cylinder.cpp
                                Shapes/Cone.cpp
                                L-System/LSystem.cpp
                                L-System/OutputElement.cpp
                                L-System/Output.cpp
                                Export/OBJExport.cpp
                )

target_link_libraries(FinalYearProject glm glfw glad imgui rapidobj stb)
