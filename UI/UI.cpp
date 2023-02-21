//
// Created by Theodora Vraimakis on 07/02/2023.
//

#include "UI.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

UI::UI(
        const std::shared_ptr<Window>& window,
        const std::shared_ptr<ArcballCamera>& camera,
//        const std::shared_ptr<Cylinder>& cylinder,
        const std::shared_ptr<Light> &light
)
{

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window->get(), true);
    ImGui_ImplOpenGL3_Init();

};
UI::~UI() {}

void UI::imguiDemo()
{
    // temporary imgui vars
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

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
void UI::imguiDraw(const std::shared_ptr<ArcballCamera> &camera,
                   const std::shared_ptr<Shape> &shape,
                   const std::shared_ptr<Light> &light
)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    imguiCamera(camera);

    if(ImGui::TreeNode("Cylinder")) {
        shapeCap(
                shape
        );
        changeColor(shape);
        ImGui::TreePop();
        ImGui::Separator();
    }
    changeLight(light);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::imguiDestroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

bool UI::isCursorPositionInGUI()
{
    ImGuiIO& io = ImGui::GetIO();

    if (io.WantCaptureMouse)
        return true;

    return false;
}

bool UI::isClicked()
{
    if (ImGui::IsMouseClicked(0, false))
        return true;
    return false;
}

bool UI::clicked()
{
    if (ImGui::GetMouseClickedCount(0) == 1 ||
        ImGui::GetMouseClickedCount(1) == 1 ||
        ImGui::GetMouseClickedCount(2) == 1
    )
        return true;
    return false;

}

void UI::imguiCamera(const std::shared_ptr<ArcballCamera> &camera)
{
    if (ImGui::TreeNode("Camera")) {
//
    glm::vec4 targetPos = camera->getTargetPos();
    glm::vec4 pos = camera->getPos();
    float f = camera->getFOV();
//
    const std::string& name1 = "haha";
    const std::vector<std::string> sliderNames =
            {
                    "X##TRANSLATION::" + name1,
                    "Y##TRANSLATION::" + name1,
                    "Z##TRANSLATION::" + name1
            };
    std::vector<float*> values =
            {
                    &targetPos.x,
                    &targetPos.y,
                    &targetPos.z
            };
    for (size_t i = 0; i < sliderNames.size(); i++)
    {
        ImGui::SliderFloat(
            sliderNames[i].c_str(),
            values[i],
            -100.0f,
            100.0f
    );
    }


        ImGui::SliderFloat(
                "FOV",
                &f,
                0.0f,
                200.0f
        );

        const std::string& name = "Camera";
        const std::vector<std::string> sliderNames1 =
                {
                        "X POSITION of " + name,
                        "Y POSITION of " + name,
                        "Z POSITION of " + name
                };


        std::vector<float*> position = {
                &pos.x,
                &pos.y,
                &pos.z
        };
        for (size_t i = 0; i < sliderNames.size(); i++)
        {
            ImGui::SliderFloat(
                    sliderNames1[i].c_str(),
                    position[i],
                    -100.0f,
                    100.0f
            );
        }
        camera->setPos(pos);
        camera->setTargetPos(targetPos);
        camera->setFOV(f);


        ImGui::TreePop();
        ImGui::Separator();
    }
}

void UI::shapeCap(
        const std::shared_ptr<Shape> &shape
)
{
    bool* change = shape->changeCap();

    ImGui::Checkbox("Cap on", change);
    if (*shape->getCap() != *shape->changeCap()) {
        shape->setCap(*change);
        std::cout << "vio" << std::endl;
    }

//shape->setMesh();

//MeshData h = shape->getMesh();
//    shape->setMesh(h);

    const char* items[] = { "Cylinder", "Cone"};
    static const char* current_item = NULL;

    if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
    {
        for (int n = 0; n < IM_ARRAYSIZE(items); n++)
        {
            bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(items[n], is_selected)) {
                current_item = items[n];
//                shape->changeShape(current_item);
//                shape->getShape();
            }
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
//        if (shape->getShape() == 0) shape->setMesh()
//        if (current_item == items[0])
//            std::cout<<current_item;
        ImGui::EndCombo();
    }

}

void UI::changeColor(const std::shared_ptr<Shape> &shape)
{
    glm::vec3 c = shape->getColor();

    ImGui::ColorEdit3(
            "Color",
            glm::value_ptr(c)
    );

    if (shape->getColor() != c) {
        shape->setColor(c);
        std::cout << "vio" << std::endl;
    }

}

void UI::changeLight(const std::shared_ptr<Light> &light)
{
    if (ImGui::TreeNode("Light")) {
    ImGui::ColorEdit3(
            "color",
            (float *) &light->m_lcolor
    );
    ImGui::SliderFloat("Strength", &light->m_lambient, 0.0f, 1.0f);

    const std::string& name = "Light";
    const std::vector<std::string> sliderNames =
            {
                    "X POSITION of " + name,
                    "Y POSITION of " + name,
                    "Z POSITION of " + name
            };

    glm::vec3 pos = light->m_lpos;

    std::vector<float*> position = {
            &pos.x,
            &pos.y,
            &pos.z
    };
    for (size_t i = 0; i < sliderNames.size(); i++)
    {
        ImGui::SliderFloat(
                sliderNames[i].c_str(),
                position[i],
                -10.0f,
                10.0f
        );
    }
    light->setLightPos(pos);

        ImGui::TreePop();
        ImGui::Separator();
    }
}