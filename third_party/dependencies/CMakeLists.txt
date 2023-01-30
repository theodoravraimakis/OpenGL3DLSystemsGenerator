include(FetchContent)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        d7c8516a4b848c0291e3d75b627c0843f515f591
)
FetchContent_MakeAvailable(imgui)
# FetchContent_GetProperties(imgui)
# if(NOT imgui_POPULATED)
#   FetchContent_Populate(imgui)

#   add_library(imgui ${imgui_SOURCE_DIR}/imgui.cpp ${imgui_SOURCE_DIR}/imgui_draw.cpp ${imgui_SOURCE_DIR}/imgui_widgets.cpp)
#   target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})

# endif()
# https://github.com/MalteQuandt/physicsrenderer/blob/9d985799ba1298e622c3811c1492efff2bb9a8e0/lib/external/CMakeLists.txt
add_library(imgui
        STATIC
        )
target_sources(imgui
        PUBLIC
            # Top-Level files
            ${imgui_SOURCE_DIR}/imgui.cpp
            ${imgui_SOURCE_DIR}/imgui_demo.cpp
            ${imgui_SOURCE_DIR}/imgui_tables.cpp
            ${imgui_SOURCE_DIR}/imgui_widgets.cpp
            ${imgui_SOURCE_DIR}/imgui_draw.cpp

            # Backend-Specific code
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)

target_link_libraries(imgui
        PUBLIC
            glad
            glfw)

target_include_directories(imgui
        PUBLIC
            # Top-Level Includes
            ${imgui_SOURCE_DIR}/
            # Backend-specific includes
            ${imgui_SOURCE_DIR}/backends/
        )
