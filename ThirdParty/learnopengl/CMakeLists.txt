cmake_minimum_required(VERSION 3.20)
project(learnopengl)

include(FetchContent)
FetchContent_Declare(
    learnopengl
    GIT_REPOSITORY https://github.com/JoeyDeVries/LearnOpenGL.git
    GIT_TAG        eb05991135a6e7084357530e8c39e2e5143dc1df
    SOURCE_SUBDIR includes
)
FetchContent_Populate(learnopengl)

add_library(learnopengl
INTERFACE
        ${learnopengl_SOURCE_DIR}/src/1.getting_started/7.4.camera_class/camera_class.cpp
#        ${learnopengl_SOURCE_DIR}/includes/learnopengl/shader.h
        )

target_link_libraries(learnopengl
INTERFACE
            glad
            glm)

target_include_directories(learnopengl INTERFACE ${learnopengl_SOURCE_DIR}/includes/
        ${learnopengl_SOURCE_DIR}/src/1.getting_started/7.4.camera_class/
        )

#file(COPY ${learnopengl_SOURCE_DIR}/src/1.getting_started/7.4.camera_class/7.4.camera.vs DESTINATION ${CMAKE_BINARY_DIR}/shaders/)
#file(COPY ${learnopengl_SOURCE_DIR}/src/1.getting_started/7.4.camera_class/7.4.camera.fs DESTINATION ${CMAKE_BINARY_DIR}/shaders/)