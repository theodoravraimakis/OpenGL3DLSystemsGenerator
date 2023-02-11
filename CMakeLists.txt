cmake_minimum_required(VERSION 3.18)
project(FinalYearProject)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(third_party/glad)
add_subdirectory(third_party/imgui)
add_subdirectory(third_party/learnopengl)

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
        Window/Window.cpp Shader/Shader.cpp Error/Error.cpp Checkpoint/Checkpoint.cpp Render/Render.cpp Camera/ArcballCamera.cpp)

target_link_libraries(FinalYearProject glm glfw glad imgui rapidobj
#learnopengl
)

#file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/shaders) # create a shaders folder
#
## copy shaders
#add_custom_command(TARGET FinalYearProject PRE_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_SOURCE_DIR}/shaders/ ${CMAKE_BINARY_DIR}/shaders)
