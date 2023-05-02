cmake_minimum_required(VERSION 3.20)
project(stb)

include(FetchContent)
FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
)
FetchContent_Populate(stb)

add_library(stb
        INTERFACE
        ${stb_SOURCE_DIR}/stb_image.h
        ${stb_SOURCE_DIR}/stb_image_write.h
        )
#
target_link_libraries(stb
        INTERFACE
#        glad
#        glm
        )

target_include_directories(
        stb INTERFACE ${stb_SOURCE_DIR}/stb_image.h
        stb INTERFACE ${stb_SOURCE_DIR}/stb_image_write.h
#        ${learnopengl_SOURCE_DIR}/src/1.getting_started/7.4.camera_class/
        )

#file(COPY ${learnopengl_SOURCE_DIR}/src/1.getting_started/7.4.camera_class/7.4.camera.vs DESTINATION ${CMAKE_BINARY_DIR}/shaders/)
#file(COPY ${learnopengl_SOURCE_DIR}/src/1.getting_started/7.4.camera_class/7.4.camera.fs DESTINATION ${CMAKE_BINARY_DIR}/shaders/)