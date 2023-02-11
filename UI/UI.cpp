//
// Created by Theodora Vraimakis on 07/02/2023.
//

#include "UI.h"
//#include "ArcballCamera.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

UI::UI(
        const std::shared_ptr<Window>& window
)
{

};
UI::~UI() {}

//void imguiInitialisation (GLFWwindow* window) {
//// imgui initialisation
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO &io = ImGui::GetIO();
//    (void) io;
//
//    ImGui::StyleColorsDark();
//
//    ImGui_ImplGlfw_InitForOpenGL(window, true);
////    ImGui_ImplGlfw_InitForOpenGL(window, false);
//    ImGui_ImplOpenGL3_Init();
//}
void UI::imguiDisplay()
{
    // temporary imgui vars
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }

}
void UI::imguiDraw()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void imguiDestroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

//void imguiCamera(ArcballCamera* camera)
//{
//    ImGui_ImplOpenGL3_NewFrame();
//    ImGui_ImplGlfw_NewFrame();
//    ImGui::NewFrame();
////
////    glm::vec3 pos = camera->getPositionV();
////
////    const std::string& name = "haha";
////    const std::vector<std::string> sliderNames =
////            {
////                    "X##TRANSLATION::" + name,
////                    "Y##TRANSLATION::" + name,
////                    "Z##TRANSLATION::" + name
////            };
////    std::vector<float*> values =
////            {
////                    &pos.x,
////                    &pos.y,
////                    &pos.z
////            };
////    for (size_t i = 0; i < sliderNames.size(); i++)
////    {
////    ImGui::SliderFloat(
////            sliderNames[i].c_str(),
////            values[i],
////            -10.0f,
////            10.0f
////    );}
////    camera->setPos(pos);
//
//    float f = arcCamera.FOV;
//    ImGui::SliderFloat(
//            "dis",
//            &f,
//            -100.0f,
//            100.0f
//    );
//    arcCamera.setFOV(f);
//
//    ImGui::Render();
//    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//}