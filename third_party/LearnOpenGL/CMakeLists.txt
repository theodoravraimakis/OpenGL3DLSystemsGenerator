cmake_minimum_required(VERSION 3.20)
project(LOGL)

include(FetchContent)
FetchContent_Declare(
    logl
    GIT_REPOSITORY https://github.com/JoeyDeVries/LearnOpenGL.git
    GIT_TAG        eb05991135a6e7084357530e8c39e2e5143dc1df
    SOURCE_SUBDIR includes
)
FetchContent_Populate(logl)

add_library(LOGL
INTERFACE
        )

target_link_libraries(LOGL
INTERFACE
            glad
            glm)

target_include_directories(LOGL INTERFACE ${logl_SOURCE_DIR}/includes/
        ${logl_SOURCE_DIR}/src/1.getting_started/7.4.camera_class/
        )

file(COPY ${logl_SOURCE_DIR}/src/1.getting_started/7.4.camera_class/7.4.camera.vs DESTINATION ${CMAKE_BINARY_DIR}/shaders/)
file(COPY ${logl_SOURCE_DIR}/src/1.getting_started/7.4.camera_class/7.4.camera.fs DESTINATION ${CMAKE_BINARY_DIR}/shaders/)