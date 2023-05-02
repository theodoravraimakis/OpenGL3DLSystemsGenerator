//
// Created by Theodora Vraimakis on 07/02/2023.
//

#include "UI.h"

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

UI::UI(
        const std::shared_ptr<Window>& window,
        const std::shared_ptr<Camera>& camera,
        const std::shared_ptr<Light> &light,
        const std::shared_ptr<AllShapes> &allShapes,
        const std::shared_ptr<Shape> &shape,
        const std::shared_ptr<LSystem> &lsys
) :
        m_allShapes(allShapes)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    ImFont* font = io.Fonts->AddFontDefault();
    ImFontConfig config;
    config.MergeMode = true;
    io.Fonts->AddFontFromFileTTF("../ThirdParty/font/NotoSans-Medium.ttf", 18.0f, &config, io.Fonts->GetGlyphRangesGreek());
    io.Fonts->Build();

    assert(font != nullptr && "Font failed to load!");

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window->get(), true);
    ImGui_ImplOpenGL3_Init();

    setPopUp(false);
    setOkButton(false);
    setPressedOk(false);
    isBackgroundBlack = true;
    displayReminder = false;

    shapes =
            {
                    "HELLO!",
                    "Hilbert Curve",
                    "Gosper Curve",
                    "E-Curve",
                    "Gosper Island",
                    "Lévy C Curve",
                    "Sierpinski Curve",
                    "Diamond (Edge Rewrite)",
                    "Dragon Curve (Edge Rewrite)",
                    "Sierpinski Gasket (Edge Rewrite)",
                    "Quadratic Koch (Edge Rewrite)",
                    "Quadratic Snowflake (Edge Rewrite)",
                    "Koch Curve a (Edge Rewrite)",
                    "Koch Curve b (Edge Rewrite)",
                    "Koch Curve c (Edge Rewrite)",
                    "Koch Curve d (Edge Rewrite)",
                    "Koch Curve e (Edge Rewrite)",
                    "Koch Curve f (Edge Rewrite)",

                    "Hilbert Curve (3D Fractal)",
                    "Hilbert Curve Version 2 (3D Fractal)",
                    "Sierpinski Carpet (3D Fractal)",

                    "Bush (3D Plant)",
                    "Flower (3D Plant)",
                    "Flower Version 2 (3D Plant)",
                    "Flowering Tree (3D Plant)",

                    "Branching Structure A",
                    "Branching Structure B",
                    "Branching Structure C",
                    "Branching Structure D",
                    "Branching Structure E",
                    "Branching Structure F",
                    "Branching Structure Fa",
                    "Branching Structure Fb",
                    "Branching Structure Fc",
                    "Branching Structure Fd",
                    "Branching Structure Fe",
                    "Branching Structure G (Context-sensitive)",
                    "Branching Structure H (Context-sensitive)",
                    "Branching Structure I (Context-sensitive)",
                    "Branching Structure J (Context-sensitive)",
                    "Branching Structure K (Context-sensitive)",
                    "Branching Structure L (Context-sensitive)",

                    "Four Spirals",
                    "Leaf",
                    "Bushy Branching",
                    "Weed",
                    "Pentaplexity",
                    "Krishna Anklets",
                    "Kolam",
                    "Checkerboard"

            };

};
UI::~UI() {}

void UI::imguiDraw(const std::shared_ptr<Window> &window,
                   const std::shared_ptr<Camera> &camera,
                   std::shared_ptr<Shape> &shape,
                   const std::shared_ptr<Light> &light,
                   const std::shared_ptr<AllShapes> &allShapes,
                   std::shared_ptr<LSystem>& lsys
)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::GetStyle().WindowRounding = 6.0f;
    ImGui::GetStyle().FrameRounding = 6.0f;
    ImGui::GetStyle().ScrollbarRounding = 6.0f;
    ImGui::GetStyle().GrabRounding = 6.0f;

    if (getColorPopUp())
        colorChangePopUp(selectedRule);
    if (getPopUp())
        ruleExistsPopUp(errorMessage);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
    if (ImGui::Begin("My Menu"))
    {

        x(lsys, lsys->m_output, shape, allShapes);

        if(ImGui::TreeNode("Cylinder")) {
//            shapeCap(
//                    shape,
//                    allShapes
//            );
            changeColor(allShapes->m_cylinder);
            ImGui::TreePop();
            ImGui::Separator();
        }

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
        ImGui::Begin("Application Settings");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::Checkbox("Show User Manual", &showManual);
        if (showManual)
        {
            ImGui::Begin("User Manual", &showManual);
            userManual();
            if (ImGui::Button("Close Me"))
                showManual = false;
            ImGui::End();
        }
        if (ImGui::Checkbox("Dark Mode", &isBackgroundBlack)) {
            window->setBackground(isBackgroundBlack);
        }
        float buttonWidth = ImGui::GetContentRegionAvail().x + (ImGui::GetStyle().FramePadding.x * 2);

        ImGui::PushItemWidth(buttonWidth);
        if (ImGui::Button("Center Object"))
        {
            if(m_loadedMesh.positions.empty())
                camera->setObjectPos(glm::vec4(lsys->m_output->center, 1.0f));
            else {
                auto center = glm::vec3(0.0f);
                for (auto const &pos: m_loadedMesh.positions) {
                    center += pos;
                }
                center /= static_cast<float>(m_loadedMesh.positions.size());
                camera->setObjectPos(glm::vec4(center, 1.0f));

                auto min = glm::vec3(std::numeric_limits<float>::max());
                auto max = glm::vec3(-std::numeric_limits<float>::max());
                for (auto const &pos: m_loadedMesh.positions) {
                    min = glm::min(min, pos);
                    max = glm::max(max, pos);
                }
                glm::vec3 size = max - min;
                float diagonalLength = glm::length(size);
                float distance = 2.0f * diagonalLength; // twice the diagonal length
                glm::vec3 cameraPosition = center + glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f)) * distance;
                camera->setPos(glm::vec4(cameraPosition, 1.0f));
            }
        }
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::PushItemWidth(buttonWidth);
        if (ImGui::Button("Take Screenshot"))
            window->takeScreenshot();
        ImGui::PopItemWidth();

        imguiCamera(camera, lsys);
        changeLight(light);

        ImGui::PopStyleColor();
        ImGui::End();

        save(window, lsys, camera, allShapes);
        ImGui::End();
        ImGui::PopStyleColor();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::imguiDestroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

bool UI::isCursorOnUI()
{
    ImGuiIO& io = ImGui::GetIO();

    if (io.WantCaptureMouse)
        return true;

    return false;
}

void UI::imguiCamera(const std::shared_ptr<Camera> &camera,
                     const std::shared_ptr<LSystem> &lsys
)
{
    if (ImGui::TreeNode("Camera")) {
        glm::vec4 targetPos = camera->getObjectPos();
        glm::vec4 pos = camera->getPos();
        const std::vector<std::string> slidersTarget =
                {
                        "##XTargetPos",
                        "##YTargetPos",
                        "##ZTargetPos"
                };
        std::vector<float*> values =
                {
                        &targetPos.x,
                        &targetPos.y,
                        &targetPos.z
                };
        ImGui::Text("Target Position:");
        for (size_t i = 0; i < slidersTarget.size(); i++)
        {
            ImGui::SliderFloat(
                    slidersTarget[i].c_str(),
                    values[i],
                    -10.0f,
                    10.0f
            );
        }

        const std::vector<std::string> slidersCamera =
                {
                        "##XCameraPos",
                        "##YCameraPos",
                        "##ZCameraPos"
                };

        std::vector<float*> position = {
                &pos.x,
                &pos.y,
                &pos.z
        };
        ImGui::Text("Camera Position:");
        for (size_t i = 0; i < slidersCamera.size(); i++)
        {
            ImGui::SliderFloat(
                    slidersCamera[i].c_str(),
                    position[i],
                    -10.0f,
                    10.0f
            );
        }
        camera->setPos(pos);
        camera->setObjectPos(targetPos);

        ImGui::TreePop();
        ImGui::Separator();
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
        *shape->m_useTexture = false;
        shape->setColor(c);
    }
}

void UI::changeLight(const std::shared_ptr<Light> &light)
{
    if (ImGui::TreeNode("Light")) {

        ImGui::Text("Color: ");
        ImGui::ColorEdit3(
                "##lightColor",
                (float *) &light->m_lcolor
        );

        float availableWidthLight = ImGui::GetContentRegionAvail().x;
        float buttonWidth = ImGui::CalcTextSize("Strength: ").x + ImGui::GetStyle().FramePadding.x;

        ImGui::Text("Strength: ");
        ImGui::SameLine();
        ImGui::PushItemWidth(availableWidthLight - buttonWidth);
        ImGui::SliderFloat("##lightStrength", &light->m_lambient, 0.0f, 1.0f);
        ImGui::PopItemWidth();

        const std::string& name = "Light";
        const std::vector<std::string> sliders =
                {
                        "##X POSITION of " + name,
                        "##Y POSITION of " + name,
                        "##Z POSITION of " + name
                };

        glm::vec3 pos = light->m_lpos;

        std::vector<float*> position = {
                &pos.x,
                &pos.y,
                &pos.z
        };
        ImGui::Text("Position:");
        for (size_t i = 0; i < sliders.size(); i++)
        {
            ImGui::SliderFloat(
                    sliders[i].c_str(),
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

void UI::x(std::shared_ptr<LSystem>& lsys,
           std::shared_ptr<Output>& segments,
           std::shared_ptr<Shape>& shape,
           const std::shared_ptr<AllShapes> &allShapes
)
{
    lsys->m_axiomBuffer = commandsToString(&(*lsys), (*lsys).getAxiom());

    std::vector<Rule> rules = lsys->m_rules;
    ImGui::SetNextItemOpen(true);
    ImGui::SetNextItemOpen(true);
    if (ImGui::TreeNode("L-System")) {

        availableWidth = ImGui::GetContentRegionAvail().x;
        float buttonWidth = ImGui::CalcTextSize("Clear\nL-system").x + ImGui::GetStyle().FramePadding.x * 4;

        if(getReminder()) {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f));
            ImGui::Text("Press ENTER to update the L-system!");
            ImGui::PopStyleColor();
        }
        ImGui::PushItemWidth(availableWidth - buttonWidth);
        ImGui::InputText("##Axiom", &lsys->m_axiomBuffer);
        if (ImGui::IsItemEdited())
            displayReminder = true;
        else
            displayReminder = false;
        if (ImGui::IsKeyPressed(ImGuiKey_Enter)) {
            displayReminder = false;
            lsys->updateAxiom();
        }
        ImGui::PopItemWidth();

        ImGui::SameLine();

        if (ImGui::Button("Clear\nL-system"))
        {
            lsys->clear();

        }
        changeGenerations(lsys);

        if(ImGui::TreeNode("Edit Rules")) {
            if(!lsys->m_rules.empty())
                ImGui::Text("Rules:");
            for (auto& rule: lsys->m_rules)
            {
                displayRule(&rule, lsys, shape);
            }

            ImVec2 letterSize = ImGui::CalcTextSize("A");
            ImGui::Text("Add Rule:");

            if(lsys->contextSensitive)
            {
                ImGui::PushItemWidth(letterSize.x * 2);
                ImGui::InputText("##Left", &nLeft);
                ImGui::SameLine();
                ImGui::Text("<");
                ImGui::SameLine();
                ImGui::PopItemWidth();
                ImGui::SameLine();
            }

            ImGui::SetNextItemWidth(letterSize.x * 2);
            ImGui::InputText("##Rule", &nR);
            ImGui::SameLine();

            if(lsys->contextSensitive)
            {
                ImGui::SameLine();
                ImGui::Text(">");
                ImGui::SameLine();
                ImGui::PushItemWidth(letterSize.x * 2);
                ImGui::InputText("##Right", &nRight);
                ImGui::PopItemWidth();
                ImGui::SameLine();
            }

            if(lsys->parametric)
            {
                ImGui::Text("(");
                ImGui::SameLine();
                ImGui::PushItemWidth(availableWidth * 0.05f);
                ImGui::InputText("##Variable", &nV);
                ImGui::PopItemWidth();
                ImGui::SameLine();
                ImGui::Text(")");
                ImGui::SameLine();
                ImGui::Text(":");
                ImGui::SameLine();
                ImGui::PushItemWidth(availableWidth * 0.15f);
                ImGui::InputText("##Condition", &nCnd);
                ImGui::PopItemWidth();
                ImGui::SameLine();
            }

            ImGui::Text("->");
            ImGui::SameLine();

            if (!lsys->parametric) {
                ImGui::SetNextItemWidth(availableWidth * 0.8f);
            } else {
                ImGui::SetNextItemWidth(availableWidth * 0.25f);
            }

            ImGui::InputText("##Commands", &nC);


            if (ImGui::Button("Add Rule")) {
                if (strcmp(nC.c_str(), "") == 0)
                {
                    setPopUp(true);
                    errorMessage = "Commands argument cannot be empty.";
                }
                else if (lsys->ruleExists(*nR.c_str()) && !(lsys->parametric || lsys->contextSensitive))
                {
                    setPopUp(true);
                    errorMessage = std::string("Rule ") + std::string(nR) + std::string(" already exists, \ncannot have duplicated in context-free L-systems");
                }
                else
                {
                    if(lsys->parametric || lsys->contextSensitive)
                        lsys->addRule(&(*nR.c_str()),
                                      &(*nC.c_str()),
                                      &(*nV.c_str()),
                                      &(*nCnd.c_str()),
                                      &(*nLeft.c_str()),
                                      &(*nRight.c_str())
                        );
                    else
                        lsys->addRule(&(*nR.c_str()), &(*nC.c_str()));

                    nR.clear();
                    nC.clear();
                    nV.clear();
                    nCnd.clear();
                    nLeft.clear();
                    nRight.clear();
                }

            }
            if (ImGui::Checkbox("Parametric L-System", &lsys->parametric)) {

                if (lsys->parametric) {
                    lsys->contextSensitive = false;
                }
            }
            if (ImGui::Checkbox("Context-Sensitive L-System", &lsys->contextSensitive)) {

                if (lsys->contextSensitive) {
                    lsys->parametric = false;
                }
            }
            ImGui::TreePop();
            ImGui::Separator();
        }

        if(ImGui::TreeNode("L-system parameters")) {
            changeAngle(lsys);
            changeLength(lsys, segments, shape, allShapes);
            ImGui::TreePop();
            ImGui::Separator();
        }

        if(ImGui::TreeNode("Pre-loaded L-systems")) {
            defaultSettings(lsys);
            ImGui::TreePop();
            ImGui::Separator();
        }

        ImGui::TreePop();
        ImGui::Separator();
    }
}

void UI::displayRule(Rule* rule,
                     std::shared_ptr<LSystem>& lsys,
                     std::shared_ptr<Shape> &shape) {
    ImVec2 letterSize = ImGui::CalcTextSize("A");

    if(lsys->contextSensitive)
    {
        ImGui::PushItemWidth(letterSize.x * 2);
        ImGui::InputText(std::string("##LeftDisplay").append(rule->m_left).append(rule->m_name).append(rule->m_right).c_str(), &rule->m_left);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::Text("<");
        ImGui::SameLine();
    }

    rule->m_ruleBuffer = commandsToString(&(*lsys), rule->m_commands);
    ImGui::Text("%s", rule->m_name.c_str());
    ImGui::SameLine();

    if(lsys->contextSensitive)
    {
        ImGui::SameLine();
        ImGui::Text(">");
        ImGui::SameLine();
        ImGui::PushItemWidth(letterSize.x * 2);
        ImGui::InputText(std::string("##RightDisplay").append(rule->m_left).append(rule->m_name).append(rule->m_right).c_str(), &rule->m_right);
        ImGui::PopItemWidth();
        ImGui::SameLine();
    }

    if(lsys->parametric)
    {
        ImGui::Text("(");
        ImGui::SameLine();
        ImGui::PushItemWidth(availableWidth * 0.1f);
        ImGui::InputText(std::string("##VariableDisplay").append(rule->m_left).append(rule->m_name).append(rule->m_right).c_str(), &rule->m_variables);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        ImGui::Text(")");
        ImGui::SameLine();
        ImGui::Text(":");
        ImGui::SameLine();
        ImGui::PushItemWidth(availableWidth * 0.1f);
        ImGui::InputText(std::string("##ConditionDisplay").append(rule->m_left).append(rule->m_name).append(rule->m_right).c_str(), &rule->m_condition);
        ImGui::PopItemWidth();
        ImGui::SameLine();
    }

    ImGui::Text("->");
    ImGui::SameLine();

    availableWidth = ImGui::GetContentRegionAvail().x;
    float buttonWidth = ImGui::CalcTextSize(std::string("Delete").append("##" + rule->m_name).c_str()).x + ImGui::GetStyle().FramePadding.x * 4;

    ImGui::PushItemWidth(availableWidth - buttonWidth);

    ImGui::InputText(std::string("##").append(rule->m_left).append(rule->m_name).append(rule->m_right).c_str(), &rule->m_ruleBuffer);

    if (ImGui::IsItemEdited())
        setReminder(true);
    else
        setReminder(false);
    if (ImGui::IsKeyPressed(ImGuiKey_Enter)) {
        lsys->updateRule(rule);
        setReminder(false);
    }
    ImGui::PopItemWidth();

    ImGui::SameLine();
    if (ImGui::Button(std::string("Delete").append("##" + rule->m_name).c_str())) {
        lsys->deleteRule(rule);
    }

    glm::vec3 c = rule->m_shape->getColor();
    auto t = ImVec4(c.x, c.y, c.z, 1.0);

    if(ImGui::ColorButton(std::string(rule->m_name).append("c").c_str(), t, 0, ImVec2(32.0f, 32.0f))) {
        setColorPopUp(true);
        *rule->m_useTexture = false;
        selectedRule = std::make_shared<Rule>(*rule);
    }
    ImGui::SameLine();

    for (auto texture: lsys->m_textures->textures) {
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

        if (*rule->m_polygon || lsys->contextSensitive) {
            ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
        }
        if (ImGui::ImageButton((rule->m_name + texture.name).c_str(), (void *) (intptr_t) texture.location,
                               ImVec2(32.0f, 32.0f))) {

            auto r = std::make_shared<Rule>(*rule);
            lsys->setTexture(r, texture.location);
        }
        if (*rule->m_polygon || lsys->contextSensitive) {
            ImGui::PopStyleVar();
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                (*rule->m_polygon) ? ImGui::SetTooltip("Textures Unavailable with Polygon Rules!") : ImGui::SetTooltip("Textures Unavailable with Context Sensitive Grammars!");
            ImGui::PopItemFlag();

        }
        ImGui::PopStyleVar();
        ImGui::SameLine();

    }

    ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    ImGui::Button("Add\ntexture", ImVec2(60.0f, 32.0f));
    ImGui::PopStyleVar();
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
        ImGui::SetTooltip("Texture Loading is Currently not Implemented!");
    ImGui::PopItemFlag();

}

void UI::changeAngle(std::shared_ptr<LSystem>& lsys) {
    auto angleChange =  *lsys->m_angle;
    ImGui::Text("Angle:");
    ImGui::SameLine();
    ImGui::SliderFloat("##angle", (float*)&angleChange, 0.0f, 180.0f, "%.2f", 0);
    if(ImGui::IsItemEdited())
    {
        lsys->m_angle = std::make_shared<float>(angleChange);
        lsys->run();
    }
}

void UI::changeLength(
        std::shared_ptr<LSystem>& lsys,
        std::shared_ptr<Output>& output,
        std::shared_ptr<Shape> &shape,
        const std::shared_ptr<AllShapes> &allShapes
) {
    ImGui::SetNextItemOpen(true);
    if(ImGui::TreeNode("Shape")) {
        ImGui::Text("Length:");
        ImGui::SameLine();
        auto lengthChangeCyl = allShapes->m_cylinder->getLength();
        ImGui::SliderFloat("##Length cyl", &lengthChangeCyl, 0.0001f, 0.5f, "%.5f", 0);
        if (allShapes->m_cylinder->getLength() != lengthChangeCyl) {
            allShapes->m_cylinder->setLength(lengthChangeCyl);
            lsys->run();
        }
        ImGui::Text("Width:");
        ImGui::SameLine();
        auto widthChangeCyl = allShapes->m_cylinder->getWidth();
        ImGui::SliderFloat("##Width cyl", &widthChangeCyl, 0.0001f, 0.2f, "%.5f", 0);
        if(ImGui::IsItemEdited())
        {
            if (allShapes->m_cylinder->getWidth() != widthChangeCyl) {
                allShapes->m_cylinder->setWidth(widthChangeCyl);
                lsys->run();
            }
        }
        ImGui::TreePop();
        ImGui::Separator();
    }

    for(const auto& rule: lsys->m_rules) {
        if (*rule.m_polygon) {
            ImGui::Text("Rule %c Shape Length", rule.m_name[0]);
            ImGui::SameLine();
            auto lengthChangePoly = rule.m_shape->getPolygonLength();
            ImGui::SliderFloat(std::string("##Poly length").append(rule.m_name).c_str(), &lengthChangePoly, 0.0f, 0.5f, "%.5f", 0);
            if (ImGui::IsItemEdited()) {
                rule.m_shape->m_polyLength = lengthChangePoly;
                rule.m_shape->makePolygon(rule.m_commands);
                rule.m_shape->createVAO();
            }
            ImGui::Text("Rule %c Shape Angle", rule.m_name[0]);
            ImGui::SameLine();
            auto angleChangePoly = rule.m_shape->getPolygonAngle();
            ImGui::SliderFloat(std::string("##Poly angle").append(rule.m_name).c_str(), (float *) &angleChangePoly, 0.0f, 90.0f, "%.2f", 0);
            if (ImGui::IsItemEdited()) {
                rule.m_shape->m_polyAngle = angleChangePoly;
                rule.m_shape->makePolygon(rule.m_commands);
                rule.m_shape->createVAO();
            }
        }
    }

}

void UI::changeGenerations(
        std::shared_ptr<LSystem>& lsys
) {
    ImGui::Text("Generations: ");
    ImGui::SameLine();
    auto generationChange = lsys->getGenerations();
    ImGui::PushItemWidth(ImGui::GetFontSize() * 3);
    if (ImGui::Button("-"))
        generationChange -= 1;
    ImGui::SameLine();
    if (ImGui::SliderInt("##Generations", &generationChange, 0, 30, "%d", ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_NoRoundToFormat))
        generationChange = std::clamp(generationChange, 0, 30);
    ImGui::SameLine();
    if (ImGui::Button("+"))
        generationChange += 1;
    ImGui::PopItemWidth();
    if(lsys->getGenerations() != generationChange) {
        lsys->setGenerations(generationChange);
        lsys->run();
    }
}

void UI::save(
        const std::shared_ptr<Window> &window,
        std::shared_ptr<LSystem>& lsys,
        const std::shared_ptr<Camera> &camera,
        const std::shared_ptr<AllShapes> &allShapes
) {

    availableWidth = ImGui::GetContentRegionAvail().x;

    float buttonWidth = ImGui::CalcTextSize("Export to OBJ").x + ImGui::GetStyle().FramePadding.x * 4;

    ImGui::PushItemWidth(availableWidth - buttonWidth);
    ImGui::InputText("##saveFile", &saveFile);
    ImGui::PopItemWidth();

    ImGui::SameLine();
    if (ImGui::Button("Export to OBJ")) {

        std::filesystem::path filePath("../objects/" + saveFile + ".obj");
        if (std::filesystem::exists(filePath))
        {
            errorMessage = "File \'" + saveFile + ".obj\' already exists.\n"
                                                  "Press \'OK\' to overwrite it";
            setOkButton(true);
            setPopUp(true);
        }
        else {
            lsys->m_output->concatenate(allShapes);
            OBJExport::exportToOBJ(lsys->m_output->concatenatedMesh, saveFile);
        }

    }

    if (getPressedOk()) {
        lsys->m_output->concatenate(allShapes);
        OBJExport::exportToOBJ(lsys->m_output->concatenatedMesh, saveFile);
        setOkButton(false);
        setPressedOk(false);
        saveFile.clear();
    }

    buttonWidth = ImGui::CalcTextSize("Import Mesh from OBJ").x + ImGui::GetStyle().FramePadding.x * 4;

    ImGui::PushItemWidth(availableWidth - buttonWidth);
    ImGui::InputText("##openFile", &openFile);
    ImGui::PopItemWidth();

    ImGui::SameLine();
    if (ImGui::Button("Import Mesh from OBJ")) {

        try {
            if (!m_loadedMesh.positions.empty())
                Mesh::clearMesh(m_loadedMesh);
            m_loadedMesh = OBJExport::loadOBJ(std::string("../objects/").append(openFile));
            m_loadedMeshVAO = Mesh::createVAO(m_loadedMesh, false);
            m_loadedMeshName = openFile + ".obj";
            auto center = glm::vec3(0.0f);
            for (auto const &pos: m_loadedMesh.positions) {
                center += pos;
            }
            center /= static_cast<float>(m_loadedMesh.positions.size());
            camera->setObjectPos(glm::vec4(center, 1.0f));

            auto min = glm::vec3(std::numeric_limits<float>::max());
            auto max = glm::vec3(-std::numeric_limits<float>::max());
            for (auto const &pos: m_loadedMesh.positions) {
                min = glm::min(min, pos);
                max = glm::max(max, pos);
            }
            glm::vec3 size = max - min;
            float diagonalLength = glm::length(size);
            float distance = 2.0f * diagonalLength;
            glm::vec3 cameraPosition = center + glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f)) * distance;
            camera->setPos(glm::vec4(cameraPosition, 1.0f));
        } catch (const std::runtime_error& e) {
            std::cerr << "Error loading mesh: " << openFile << std::endl << e.what() << ".\n" << std::endl;
            setPopUp(true);
            errorMessage = std::string("Error loading mesh: \'" + openFile + "\'\n" + e.what() + ".");
        }

    }
    if (!m_loadedMesh.positions.empty()) {
        ImGui::Text("Displaying mesh from: %s", m_loadedMeshName.c_str());
        if (ImGui::Button("Remove Loaded Mesh")) {
            Mesh::clearMesh(m_loadedMesh);
            camera->setObjectPos(glm::vec4(lsys->m_output->center, 1.0f));
        }
    }

}

void UI::ruleExistsPopUp(std::string message) {
    ImGui::BeginPopup("Warning");
    ImGui::OpenPopup("Warning");

    if (ImGui::BeginPopupModal("Warning"), true) {
        ImGui::Text("%s", message.c_str());
    }
    if (getOkButton()) {
        if (ImGui::Button("OK")) {
            setPressedOk(true);
            setPopUp(false);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
    }
    if (ImGui::Button("Close")) {
        setOkButton(false);
        setPopUp(false);
        ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
}

void UI::colorChangePopUp(std::shared_ptr<Rule>& rule) {
    ImGui::BeginPopup("Color Change");
    ImGui::OpenPopup("Color Change");

    if (ImGui::BeginPopup("Color Change"), true) {
        glm::vec3 c = rule->m_shape->getColor();
        ImGui::ColorPicker3("pic", glm::value_ptr(c));
        if (rule->m_shape->getColor() != c) {
            if (rule->m_polygon) {
                Mesh::clearMesh(rule->m_shape->getMesh());
                rule->m_shape->makePolygon(rule->m_commands);
            }
            rule->m_shape->setColor(c);
        }

    }
    if (ImGui::Button("Close")) {
        setColorPopUp(false);
        ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();

}

void UI::defaultSettings(std::shared_ptr<LSystem>& lsys)
{
    if (ImGui::BeginCombo((char*)"##Settings: ", lsys->m_setting.empty() ? "Choose setting" : lsys->m_setting.c_str()))
    {
        for (auto & shape : shapes)
        {
            bool is_selected = (lsys->m_setting == shape);
            if (ImGui::Selectable(shape.c_str(), is_selected)) {
                lsys->m_setting = shape;

                if (lsys->m_setting == "Hilbert Curve (3D Fractal)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "A";
                    lsys->m_rules.clear();
                    lsys->addRule("A", "B-F+CFC+F-D&F^D-F+&&CFC+F+B//");
                    lsys->addRule("B", "A&F^CFB^F^D^^-F-D^|F^B|FC^F^A//");
                    lsys->addRule("C", "|D^|F^B-F+C^F^A&&FA&F^C+F+B^F^D//");
                    lsys->addRule("D", "|CFB-F+B|FA&F^A&&FB-F+B|FC//");

                    lsys->m_generations = 4;
                    lsys->m_angle = std::make_shared<float>(90);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Branching Structure A")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "F";
                    lsys->m_rules.clear();
                    lsys->addRule("F", "F[+F]F[-F]F");
                    lsys->m_angle = std::make_shared<float>(25);
                    lsys->m_generations = 2;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Branching Structure C")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "F";
                    lsys->m_rules.clear();
                    lsys->addRule("F", "FF+[+F-F-F]-[-F+F+F]");
                    lsys->m_angle = std::make_shared<float>(22.5);
                    lsys->m_generations = 2;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Branching Structure E")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "X";
                    lsys->m_rules.clear();
                    lsys->addRule("X", "F[+X][-X]FX");
                    lsys->addRule("F", "FF");
                    lsys->m_angle = std::make_shared<float>(35);
                    lsys->m_generations = 4;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Branching Structure F")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "X";
                    lsys->m_rules.clear();
                    lsys->addRule("X", "F-[[X]+X]+F[+FX]-X");
                    lsys->addRule("F", "FF");
                    lsys->m_angle = std::make_shared<float>(22.5);
                    lsys->m_generations = 4;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Branching Structure B")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "F";
                    lsys->m_rules.clear();
                    lsys->addRule("F", "F[+FF][-FF]F[-F][+F]F");
                    lsys->m_angle = std::make_shared<float>(35);
                    lsys->m_generations = 2;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Branching Structure D")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "VZFFF";
                    lsys->m_rules.clear();
                    lsys->addRule("V", "[+++W][---W]YV");
                    lsys->addRule("W", "+X[-W]Z");
                    lsys->addRule("X", "-W[+X]Z");
                    lsys->addRule("Y", "YZ");
                    lsys->addRule("Z", "[-FFF][+FFF]F");
                    lsys->m_angle = std::make_shared<float>(20);
                    lsys->m_generations = 5;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Branching Structure Fc")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "FX";
                    lsys->m_rules.clear();
                    lsys->addRule("X", "[\"(0.7)-FX]+FX");
                    lsys->m_angle = std::make_shared<float>(40);
                    lsys->m_generations = 4;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Branching Structure Fd")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "aF";
                    lsys->m_rules.clear();
                    lsys->addRule("a", "FFFFFv[+++h][---q]fb");
                    lsys->addRule("b", "FFFFFv[+++h][---q]fc");
                    lsys->addRule("c", "FFFFFv[+++fa]fd");
                    lsys->addRule("d", "FFFFFv[+++h][---q]fe");
                    lsys->addRule("e", "FFFFFv[+++h][---q]fg");
                    lsys->addRule("g", "FFFFFv[---fa]fa");
                    lsys->addRule("h", "ifFF");
                    lsys->addRule("i", "fFFF[--m]j");
                    lsys->addRule("j", "fFFF[--n]k");
                    lsys->addRule("k", "fFFF[--o]l");
                    lsys->addRule("l", "fFFF[--p]");
                    lsys->addRule("m", "fFn");
                    lsys->addRule("n", "fFo");
                    lsys->addRule("o", "fFp");
                    lsys->addRule("p", "fF");
                    lsys->addRule("q", "rfF");
                    lsys->addRule("r", "fFFF[++m]s");
                    lsys->addRule("s", "fFFF[++n]t");
                    lsys->addRule("t", "fFFF[++o]u");
                    lsys->addRule("u", "fFFF[++p]");
                    lsys->addRule("v", "Fv");
                    lsys->m_angle = std::make_shared<float>(12);
                    lsys->m_generations = 20;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Branching Structure Fe")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "aF";
                    lsys->m_rules.clear();
                    lsys->addRule("a", "FFFFFy[++++n][----t]fb");
                    lsys->addRule("b", "+FFFFFy[++++n][----t]fc");
                    lsys->addRule("c", "FFFFFy[++++n][----t]fd");
                    lsys->addRule("d", "-FFFFFy[++++n][----t]fe");
                    lsys->addRule("e", "FFFFFy[++++n][----t]fg");
                    lsys->addRule("g", "FFFFFy[+++fa]fh");
                    lsys->addRule("h", "FFFFFy[++++n][----t]fi");
                    lsys->addRule("i", "+FFFFFy[++++n][----t]fj");
                    lsys->addRule("j", "FFFFFy[++++n][----t]fk");
                    lsys->addRule("k", "-FFFFFy[++++n][----t]fl");
                    lsys->addRule("l", "FFFFFy[++++n][----t]fm");
                    lsys->addRule("m", "FFFFFy[---fa]fa");
                    lsys->addRule("n", "ofFFF");
                    lsys->addRule("o", "fFFFp");
                    lsys->addRule("p", "fFFF[-s]q");
                    lsys->addRule("q", "fFFF[-s]r");
                    lsys->addRule("r", "fFFF[-s]");
                    lsys->addRule("s", "fFfF");
                    lsys->addRule("t", "ufFFF");
                    lsys->addRule("u", "fFFFv");
                    lsys->addRule("v", "fFFF[+s]w");
                    lsys->addRule("w", "fFFF[+s]x");
                    lsys->addRule("x", "fFFF[+s]");
                    lsys->addRule("y", "Fy");
                    lsys->m_angle = std::make_shared<float>(12);
                    lsys->m_generations = 30;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Branching Structure G (Context-sensitive)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "FBFBFB";
                    lsys->m_rules.clear();
                    lsys->contextSensitive = true;

                    lsys->addRule("A", "A", "A", "A");
                    lsys->addRule("A", "B[+FBFB]", "A", "B");
                    lsys->addRule("B", "B", "A", "A");
                    lsys->addRule("B", "B", "A", "B");
                    lsys->addRule("A", "A", "B", "A");
                    lsys->addRule("A", "BFB", "B", "B");
                    lsys->addRule("B", "A", "B", "A");
                    lsys->addRule("B", "A", "B", "B");
                    lsys->addRule("-", "");
                    lsys->m_rules.back().m_commands.emplace_back("+", CommandType::RIGHT);
                    lsys->addRule("+", "");
                    lsys->m_rules.back().m_commands.emplace_back("-", CommandType::LEFT);

                    lsys->m_angle = std::make_shared<float>(22.5);
                    lsys->m_generations = 30;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Branching Structure H (Context-sensitive)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "FBFBFB";
                    lsys->m_rules.clear();
                    lsys->contextSensitive = true;

                    lsys->addRule("A", "B", "A", "A");
                    lsys->addRule("A", "B[-FBFB]", "A", "B");
                    lsys->addRule("B", "B", "A", "A");
                    lsys->addRule("B", "B", "A", "B");
                    lsys->addRule("A", "A", "B", "A");
                    lsys->addRule("A", "BFB", "B", "B");
                    lsys->addRule("B", "B", "B", "A");
                    lsys->addRule("B", "A", "B", "B");
                    lsys->addRule("-", "");
                    lsys->m_rules.back().m_commands.emplace_back("+", CommandType::RIGHT);
                    lsys->addRule("+", "");
                    lsys->m_rules.back().m_commands.emplace_back("-", CommandType::LEFT);

                    lsys->m_angle = std::make_shared<float>(22.5);
                    lsys->m_generations = 30;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Branching Structure I (Context-sensitive)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "FBFBFB";
                    lsys->m_rules.clear();
                    lsys->contextSensitive = true;

                    lsys->addRule("A", "A", "A", "A");
                    lsys->addRule("A", "B", "A", "B");
                    lsys->addRule("B", "A", "A", "A");
                    lsys->addRule("B", "B[+FBFB]", "A", "B");
                    lsys->addRule("A", "A", "B", "A");
                    lsys->addRule("A", "BFB", "B", "B");
                    lsys->addRule("B", "A", "B", "A");
                    lsys->addRule("B", "A", "B", "B");
                    lsys->addRule("-", "");
                    lsys->m_rules.back().m_commands.emplace_back("+", CommandType::RIGHT);
                    lsys->addRule("+", "");
                    lsys->m_rules.back().m_commands.emplace_back("-", CommandType::LEFT);

                    lsys->m_angle = std::make_shared<float>(25.75);
                    lsys->m_generations = 30;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Branching Structure J (Context-sensitive)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "FAFBFB";
                    lsys->m_rules.clear();
                    lsys->contextSensitive = true;

                    lsys->addRule("A", "B", "A", "A");
                    lsys->addRule("A", "A", "A", "B");
                    lsys->addRule("B", "A", "A", "A");
                    lsys->addRule("B", "BFB", "A", "B");
                    lsys->addRule("A", "B", "B", "A");
                    lsys->addRule("A", "B[+FBFB]", "B", "B");
                    lsys->addRule("B", "B", "B", "A");
                    lsys->addRule("B", "A", "B", "B");
                    lsys->addRule("-", "");
                    lsys->m_rules.back().m_commands.emplace_back("+", CommandType::RIGHT);
                    lsys->addRule("+", "");
                    lsys->m_rules.back().m_commands.emplace_back("-", CommandType::LEFT);

                    lsys->m_angle = std::make_shared<float>(25.75);
                    lsys->m_generations = 17;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Branching Structure K (Context-sensitive)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "FAFAFA";
                    lsys->m_rules.clear();
                    lsys->contextSensitive = true;

                    lsys->addRule("B", "B", "B", "B");
                    lsys->addRule("B", "A[-FAFA]", "B", "A");
                    lsys->addRule("A", "A", "B", "B");
                    lsys->addRule("A", "A", "B", "A");
                    lsys->addRule("B", "B", "A", "B");
                    lsys->addRule("B", "AFA", "A", "A");
                    lsys->addRule("A", "A", "A", "B");
                    lsys->addRule("A", "B", "A", "A");
                    lsys->addRule("-", "");
                    lsys->m_rules.back().m_commands.emplace_back("+", CommandType::RIGHT);
                    lsys->addRule("+", "");
                    lsys->m_rules.back().m_commands.emplace_back("-", CommandType::LEFT);

                    lsys->m_angle = std::make_shared<float>(22.5);
                    lsys->m_generations = 30;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Branching Structure L (Context-sensitive)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "xD";
                    lsys->m_rules.clear();
                    lsys->contextSensitive = true;

                    lsys->addRule("B", "HEHE");
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Sierpinski Carpet (3D Fractal)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "H";
                    lsys->m_rules.clear();

                    lsys->addRule("H", "[S-1+s-1+S]");
                    lsys->addRule("S", "[R2r2R]");
                    lsys->addRule("s", "[r22r]");
                    lsys->addRule("R", "[H^3&H^3&H]");
                    lsys->addRule("r", "[H^33&H]");
                    lsys->addRule("1", "2");
                    lsys->addRule("2", "3");
                    lsys->addRule("3", "111");
                    lsys->addRule("c", "{F+F+F+F+}");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(0.2f, 0.6f, 1.0f); //blue
                    lsys->m_rules.back().m_shape->setPolyLength(0.1f);
                    lsys->m_rules.back().m_shape->setPolyAngle(90.0f);
                    lsys->m_rules.back().m_shape->updatePolygon(lsys->m_rules.back().m_commands);

                    lsys->m_angle = std::make_shared<float>(90.0f);
                    lsys->m_generations = 5;
                    lsys->updateAxiom();

                    lsys->m_camera->setObjectPos(glm::vec4(lsys->m_output->center, 1.0f));
                }
                if (lsys->m_setting == "Bush (3D Plant)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "A";
                    lsys->m_rules.clear();

                    lsys->addRule("A", "[B//////B///////B]");
                    lsys->addRule("B", "[&SLA]");
                    lsys->addRule("S", "FL");
                    lsys->addRule("F", "F/////L");
//                    lsys->addRule("L", "[^^u]"); //OG
                    lsys->addRule("L", "[^^++++u]");
                    lsys->addRule("u", "{-F+F+F-|-F+F+F}");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(0.2f, 0.6f, 0.2f); //green
                    lsys->m_rules.back().m_shape->setPolyLength(0.06f);
                    lsys->m_rules.back().m_shape->setPolyAngle(22.5f);
                    lsys->m_rules.back().m_shape->updatePolygon(lsys->m_rules.back().m_commands);

                    lsys->m_angle = std::make_shared<float>(22.5f);
                    lsys->m_generations = 10;
                    lsys->updateAxiom();

                }
                if (lsys->m_setting == "Flower (3D Plant)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "P";
                    lsys->m_rules.clear();

                    lsys->addRule("P", "X+[P+]--////[--J]X[++J]-[P]++PK");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(0.4f, 0.3f, 0.0f);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("X", "FY[//&&J]FY");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(0.4f, 0.3f, 0.0f);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("Y", "YFY");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(0.4f, 0.3f, 0.0f);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("u", "{+F-FF-F+|+F-FF-F}");
                    lsys->m_rules.back().m_shape->m_polyAngle = 18.0f;
                    lsys->m_rules.back().m_shape->m_polyLength = 0.06f;
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(0.2f, 0.6f, 0.2f); //green
                    lsys->m_rules.back().m_shape->updatePolygon(lsys->m_rules.back().m_commands);
                    lsys->addRule("J", "[u]");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(0.4f, 0.3f, 0.0f);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("K", "[&&&p/W////W////W////W////W]");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(0.4f, 0.3f, 0.0f);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("p", "FF");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(0.4f, 0.3f, 0.0f);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("w", "{&&&&-F+F|-F+F}");
                    lsys->m_rules.back().m_shape->m_polyAngle = 18.0f;
                    lsys->m_rules.back().m_shape->m_polyLength = 0.145f;
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1.0f, 0.5f, 0.5f); //pink
                    lsys->m_rules.back().m_shape->updatePolygon(lsys->m_rules.back().m_commands);
                    lsys->addRule("W", "[^F][w]");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1.0f, 0.8f, 0.2f); //yellow
                    lsys->m_rules.back().m_shape->updateShape();

                    lsys->m_angle = std::make_shared<float>(18.0f);
                    lsys->m_generations = 3;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Flower Version 2 (3D Plant)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "P";
                    lsys->m_rules.clear();

                    lsys->addRule("P", "S+[P+O]--//[--L]S[++L]-[PO]++PO");
                    lsys->addRule("S", "Fs[//&&L][//^^L]Fs");
                    lsys->addRule("s", "sFs");
                    lsys->addRule("u", "{+F-FF-F+|+F-FF-F}");
                    lsys->m_rules.back().m_shape->makePolygon(lsys->m_rules.back().m_commands);
                    lsys->m_rules.back().m_shape->m_polyAngle = 18.0f;
                    lsys->m_rules.back().m_shape->m_polyLength = 0.06f;
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(0.2f, 0.6f, 0.2f); //green
                    lsys->m_rules.back().m_shape->updatePolygon(lsys->m_rules.back().m_commands);
//                    lsys->addRule("L", "[u]"); //OG
                    lsys->addRule("L", "[++u]");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(0.1451f, 0.25098f, 0.07451f); //dark green-brown
                    lsys->m_rules.back().m_shape->updateShape();
//                    lsys->addRule("O", "[&&&p/W////W////W////W////W]"); //OG
                    lsys->addRule("O", "[&&&p/W///W///W///W///W///W]");
                    lsys->addRule("p", "FF");
                    lsys->addRule("w", "{&&&&-F+F|-F+F}");
                    lsys->m_rules.back().m_shape->makePolygon(lsys->m_rules.back().m_commands);
                    lsys->m_rules.back().m_shape->m_polyAngle = 18.0f;
                    lsys->m_rules.back().m_shape->m_polyLength = 0.145f;
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(0.68235f, 0.18039f, 0.44314f); //pink-purple
                    lsys->m_rules.back().m_shape->updatePolygon(lsys->m_rules.back().m_commands);
//                    lsys->addRule("W", "[^F][w]"); //OG
                    lsys->addRule("W", "[^F][&&&&w]");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1.0f, 0.8f, 0.2f); //yellow
                    lsys->m_rules.back().m_shape->updateShape();

                    lsys->m_angle = std::make_shared<float>(18.0f);
                    lsys->m_generations = 3;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Flowering Tree (3D Plant)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "FFFA";
                    lsys->m_rules.clear();

                    lsys->addRule("A", "![&&++J][B]////[&&++J][B]////[&&++J]B");
                    lsys->addRule("B", "@(0.9)&FFFAO");
                    lsys->addRule("J", "{+F-FF-F+|+F-FF-F}");
                    lsys->m_rules.back().m_shape->makePolygon(lsys->m_rules.back().m_commands);
                    lsys->m_rules.back().m_shape->m_polyAngle = 30.0f;
                    lsys->m_rules.back().m_shape->m_polyLength = 0.04f;
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(0.2f, 0.6f, 0.2f); //green
                    lsys->m_rules.back().m_shape->updatePolygon(lsys->m_rules.back().m_commands);
                    lsys->addRule("w", "{&&&&-F+F|-F+F}");
                    lsys->m_rules.back().m_shape->m_polyAngle = 30.0f;
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(0.68235f, 0.18039f, 0.44314f);
                    lsys->m_rules.back().m_shape->updatePolygon(lsys->m_rules.back().m_commands);
                    lsys->addRule("W", "[^E][&&&&w]");
                    lsys->addRule("O", "[W///W///W///W///W///W]");
                    lsys->addRule("E", "@(0.5)F");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1.0f, 0.85f, 0.0f);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("F", "F");

                    lsys->m_angle = std::make_shared<float>(28.0f);
                    lsys->m_generations = 11;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Gosper Island")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "F";
                    lsys->m_rules.clear();

                    lsys->addRule("F", "F+F-F-F+F-F-F+F-F-F+F-F");

                    lsys->m_angle = std::make_shared<float>(60.0f);
                    lsys->m_generations = 2;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Sierpinski Curve") // https://math.stackexchange.com/questions/3393187/does-there-exist-an-l-system-for-the-sierpiński-curve
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "F--XF--F--XF";
                    lsys->m_rules.clear();

                    lsys->addRule("X", "XF+F+XF--F--XF+F+X");

                    lsys->m_angle = std::make_shared<float>(45.0f);
                    lsys->m_generations = 2;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Four Spirals") // https://www.reddit.com/r/generative/comments/i17hcz/four_spirals_lsystem/
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "[x]+++++++++++[x]+++++++++++[x]+++++++++++[x]";
                    lsys->m_rules.clear();

                    lsys->addRule("x", "[@(0.9)+F+F+F+Fx[++@(0.6)x]]");

                    lsys->m_angle = std::make_shared<float>(8.0f);
                    lsys->m_generations = 4;
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Hilbert Curve Version 2 (3D Fractal)") // https://jsantell.com/l-systems/
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "X";
                    lsys->m_rules.clear();

                    lsys->addRule("X", "^\\XF^\\XFX-F^//XFX&F+//XFX-F/X-/");

                    lsys->m_generations = 2;
                    lsys->m_angle = std::make_shared<float>(90);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Hilbert Curve") // http://algorithmicbotany.org/papers/ffas-synthesis-of-spacing-filling-curves-on-the-square-grid.pdf
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "L";
                    lsys->m_rules.clear();

                    lsys->addRule("L", "+RF-LFL-FR+");
                    lsys->addRule("R", "-LF+RFR+FL-");

                    lsys->m_generations = 2;
                    lsys->m_angle = std::make_shared<float>(90);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Gosper Curve") // http://algorithmicbotany.org/papers/ffas-synthesis-of-spacing-filling-curves-on-the-square-grid.pdf
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "l";
                    lsys->m_rules.clear();

                    lsys->addRule("l", "l-r--r+l++ll+r-");
                    lsys->addRule("r", "+l-rr--r-l++l+r");

                    lsys->m_generations = 2;
                    lsys->m_angle = std::make_shared<float>(60);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "E-Curve")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "-r";
                    lsys->m_rules.clear();

                    lsys->addRule("l", "ll-r-r+l+l-r-rl+r+llr-l+r+ll+r-lr-r-l+l+rr-");
                    lsys->addRule("r", "+ll-r-r+l+lr+l-rr-l-r+lrr-l-rl+l+r-r-l+l+rr");

                    lsys->m_generations = 1;
                    lsys->m_angle = std::make_shared<float>(90);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Lévy C Curve")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "F";
                    lsys->m_rules.clear();

                    lsys->addRule("F", "+F−−F+");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();


                    lsys->m_generations = 9;
                    lsys->m_angle = std::make_shared<float>(45);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "HELLO!")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "H+f+E-ff-ff|L-ff-ff|L-fff-ff|Of+!";
                    lsys->m_rules.clear();

                    lsys->addRule("H", "F+f+F[F]+F-F");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(255, 87, 51) / 255.0f;
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("E", "[-F]F[-F]F[-F]");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(255, 189, 51) / 255.0f;
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("L", "[-F]FF");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(219, 255, 51) / 255.0f;
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("O", "FF+F+FF+F");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(117, 255, 51) / 255.0f;
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("!", "[\"(0.3)F][\"(0.5)f\"(1.7)FF]");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(51, 255, 87) / 255.0f;
                    lsys->m_rules.back().m_shape->updateShape();

                    lsys->m_angle = std::make_shared<float>(90);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Diamond (Edge Rewrite)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "F";
                    lsys->m_rules.clear();

                    lsys->addRule("F", "FF++F++F+F++F-F");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->m_generations = -1;
                    lsys->m_angle = std::make_shared<float>(60);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Dragon Curve (Edge Rewrite)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "l";
                    lsys->m_rules.clear();

                    lsys->addRule("l", "l+r+");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("r", "-l-r");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->m_generations = 8;
                    lsys->m_angle = std::make_shared<float>(90);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Sierpinski Gasket (Edge Rewrite)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "r";
                    lsys->m_rules.clear();

                    lsys->addRule("l", "r+l+r");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("r", "l-r-l");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->m_generations = 5;
                    lsys->m_angle = std::make_shared<float>(60);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Quadratic Koch (Edge Rewrite)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "F-F-F-F";
                    lsys->m_rules.clear();

                    lsys->addRule("F", "F+FF-FF-F-F+F+FF-F-F+F+FF+FF-F");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->m_generations = 0;
                    lsys->m_angle = std::make_shared<float>(90);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Quadratic Snowflake (Edge Rewrite)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "-F";
                    lsys->m_rules.clear();

                    lsys->addRule("F", "F+F-F-F+F");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->m_generations = 1;
                    lsys->m_angle = std::make_shared<float>(90);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Koch Curve a (Edge Rewrite)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "F-F-F-F";
                    lsys->m_rules.clear();

                    lsys->addRule("F", "FF-F-F-F-F-F+F");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->m_generations = 1;
                    lsys->m_angle = std::make_shared<float>(90);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Koch Curve b (Edge Rewrite)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "F-F-F-F";
                    lsys->m_rules.clear();

                    lsys->addRule("F", "FF-F-F-F-FF");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->m_generations = 1;
                    lsys->m_angle = std::make_shared<float>(90);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Koch Curve c (Edge Rewrite)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "F-F-F-F";
                    lsys->m_rules.clear();

                    lsys->addRule("F", "FF-F+F-F-FF");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->m_generations = 0;
                    lsys->m_angle = std::make_shared<float>(90);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Koch Curve d (Edge Rewrite)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "F-F-F-F";
                    lsys->m_rules.clear();

                    lsys->addRule("F", "FF-F--F-F");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->m_generations = 0;
                    lsys->m_angle = std::make_shared<float>(90);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Koch Curve e (Edge Rewrite)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "F-F-F-F";
                    lsys->m_rules.clear();

                    lsys->addRule("F", "F-FF--F-F");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->m_generations = 1;
                    lsys->m_angle = std::make_shared<float>(90);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Koch Curve f (Edge Rewrite)")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "F-F-F-F";
                    lsys->m_rules.clear();

                    lsys->addRule("F", "F-F+F-F-F");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->m_generations = 1;
                    lsys->m_angle = std::make_shared<float>(90);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Leaf")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "a";
                    lsys->m_rules.clear();


                    lsys->addRule("F", "\"(0.9)F\"(0.9)");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("a", "F[+x]Fb");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("b", "F[-y]Fa");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("x", "a");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("y", "b");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->m_generations = 4;
                    lsys->m_angle = std::make_shared<float>(45);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Bushy Branching")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "Y";
                    lsys->m_rules.clear();


                    lsys->addRule("X", "X[-FFF][+FFF]FX");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("Y", "YFX[+Y][-Y]");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->m_generations = 4;
                    lsys->m_angle = std::make_shared<float>(25.7);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Weed")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "F";
                    lsys->m_rules.clear();

                    lsys->addRule("F", "FF-[XY]+[XY]");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("X", "+FY");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("Y", "-FX");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->m_generations = 4;
                    lsys->m_angle = std::make_shared<float>(22.5);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Pentaplexity")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "F++F++F++F++F";
                    lsys->m_rules.clear();


                    lsys->addRule("F", "F++F++F|F-F++F");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->m_generations = 2;
                    lsys->m_angle = std::make_shared<float>(36);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Krishna Anklets")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "-X--X";
                    lsys->m_rules.clear();


                    lsys->addRule("X", "XFX--XFX");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->m_generations = 3;
                    lsys->m_angle = std::make_shared<float>(45);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Kolam")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "-D--D";
                    lsys->m_rules.clear();


                    lsys->addRule("A", "F++FFFF--F--FFFF++F++FFFF--F");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("B", "F--FFFF++F++FFFF--F--FFFF++F");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("C", "BFA--BFA");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->addRule("D", "CFC--CFC");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->m_generations = 4;
                    lsys->m_angle = std::make_shared<float>(45);
                    lsys->updateAxiom();
                }
                if (lsys->m_setting == "Checkerboard")
                {
                    lsys->m_axiomBuffer.clear();
                    lsys->m_axiomBuffer = "F+XF+F+XF";
                    lsys->m_rules.clear();


                    lsys->addRule("e", "{-F-F-F}");
                    lsys->m_rules.back().m_shape->m_polyAngle = 90.0f;
                    lsys->m_rules.back().m_shape->m_polyLength = 0.1f;
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updatePolygon(lsys->m_rules.back().m_commands);
                    lsys->addRule("X", "Xe+XF+F+Xe+X");
                    lsys->m_rules.back().m_shape->m_color = glm::vec3(1);
                    lsys->m_rules.back().m_shape->updateShape();
                    lsys->m_generations = -1;
                    lsys->m_angle = std::make_shared<float>(90);
                    lsys->updateAxiom();
                }
            }
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
}
void UI::userManual() {

    if(ImGui::TreeNode("Line Drawing Commands")) {

        ImGui::BeginTable("Line Drawing Commands", 2);

        ImGui::TableSetupColumn("Symbol", ImGuiTableColumnFlags_WidthFixed, 50.0f);
        ImGui::TableSetupColumn("Interpretation");
        ImGui::TableHeadersRow();

        ImGui::TableNextColumn();
        ImGui::Text("F");
        ImGui::TableNextColumn();
        ImGui::Text("move forward and draw a line");

        ImGui::TableNextColumn();
        ImGui::Text("f");
        ImGui::TableNextColumn();
        ImGui::Text("move forward without drawing a line");

        ImGui::TableNextColumn();
        ImGui::Text("+");
        ImGui::TableNextColumn();
        ImGui::Text(u8"turn left by angle \u03B4");

        ImGui::TableNextColumn();
        ImGui::Text("-");
        ImGui::TableNextColumn();
        ImGui::Text(u8"turn right by angle \u03B4");

        ImGui::TableNextColumn();
        ImGui::Text("&");
        ImGui::TableNextColumn();
        ImGui::Text(u8"pitch down by angle \u03B4");

        ImGui::TableNextColumn();
        ImGui::Text("^");
        ImGui::TableNextColumn();
        ImGui::Text(u8"pitch up by angle \u03B4");

        ImGui::TableNextColumn();
        ImGui::Text("\\");
        ImGui::TableNextColumn();
        ImGui::Text(u8"roll clockwise by angle \u03B4");

        ImGui::TableNextColumn();
        ImGui::Text("/");
        ImGui::TableNextColumn();
        ImGui::Text(u8"roll counter-clockwise by angle \u03B4");

        ImGui::TableNextColumn();
        ImGui::Text("|");
        ImGui::TableNextColumn();
        ImGui::Text("turn around (180°)");

        ImGui::TableNextColumn();
        ImGui::Text("[");
        ImGui::TableNextColumn();
        ImGui::Text("push state");

        ImGui::TableNextColumn();
        ImGui::Text("]");
        ImGui::TableNextColumn();
        ImGui::Text("pop state");

        ImGui::EndTable();
        ImGui::TreePop();
        ImGui::Separator();
    }

    if(ImGui::TreeNode("Incremental Changes Commands")) {

        ImGui::BeginTable("Incremental Changes Commands", 2);  // Begin table with 2 columns

        ImGui::TableSetupColumn("Symbol", ImGuiTableColumnFlags_WidthFixed, 50.0f);
        ImGui::TableSetupColumn("Interpretation");
        ImGui::TableHeadersRow();

        ImGui::TableNextColumn();
        ImGui::Text("\"");
        ImGui::TableNextColumn();
        ImGui::Text("scale length by given size scale");

        ImGui::TableNextColumn();
        ImGui::Text("'");
        ImGui::TableNextColumn();
        ImGui::Text("scale width by given size scale");

        ImGui::TableNextColumn();
        ImGui::Text("@");
        ImGui::TableNextColumn();
        ImGui::Text("scale entire segment");

        ImGui::EndTable();
        ImGui::TreePop();
        ImGui::Separator();
    }
    if(ImGui::TreeNode("Polygon Rules")) {
        ImGui::PushTextWrapPos(ImGui::GetContentRegionAvail().x);
        ImGui::NewLine();
        ImGui::Text("Any rule containing curly brackets ('{' and '}') is interpreted as a polygon and the shape will be assigned to it.");
        ImGui::NewLine();
        ImGui::Text("That is, given a rule:");
        ImGui::Text("c -> {F+F+F+F+}                   taken from 'Sierpinski Carpet (3D Fractal)'");
        ImGui::Text("And considering that the angle of the polygon is set to 90° the output of this command will be a square.");
        ImGui::NewLine();
        ImGui::Text("Similarly:");
        ImGui::Text("u -> {+F-FF-F+|+F-FF-F}           taken from 'Flower Version 2 (3D Plant)'");
        ImGui::Text("With a polygon angle of 18° is a hexagon.");
        ImGui::PopTextWrapPos();
        ImGui::TreePop();
        ImGui::Separator();
    }
    if(ImGui::TreeNode("Using the Application")) {
        ImGui::PushTextWrapPos(ImGui::GetContentRegionAvail().x);
        ImGui::SetNextItemOpen(true);
        if(ImGui::TreeNode("L-SYSTEM")) {
            ImGui::PushTextWrapPos(ImGui::GetContentRegionAvail().x);
            ImGui::Text("To quickly edit any of the slider values CTRL-press the slider, input the desired value and press ENTER.");
            ImGui::Text("To erase all rules and clear the axiom press 'Clear L-system'.");
            ImGui::NewLine();
            ImGui::Text("TEXTURES");
            ImGui::Text("...");
            ImGui::NewLine();
            ImGui::Text("GENERATIONS");
            ImGui::Text("You can evaluate the L-system to a maximum of 30 generations (NOTE: considering how computationally expensive the program is it may crash after few generations.");
            ImGui::PopTextWrapPos();
            ImGui::TreePop();
            ImGui::Separator();
        }
        ImGui::SetNextItemOpen(true);
        if(ImGui::TreeNode("EXPORT & IMPORT FEATURE")) {
            ImGui::PushTextWrapPos(ImGui::GetContentRegionAvail().x);
            ImGui::Text("EXPORT");
            ImGui::Text("To export a mesh as OBJ file input the desired name into the input box located next to the 'Export to OBJ' button and press the button.");
            ImGui::Text("You only need to specify the name of the file (without extension type), as the export type will be automatically set to .obj and an accompanying .mtl file will be created together with it.");
            ImGui::Text("All files are being saved in the 'objects' folder located in the main directory of the project.");
            ImGui::Text("IMPORT");
            ImGui::Text("To import a mesh");
            ImGui::PopTextWrapPos();
            ImGui::TreePop();
            ImGui::Separator();
        }
        ImGui::SetNextItemOpen(true);
        if(ImGui::TreeNode("TAKING SCREENSHOTS")) {
            ImGui::PushTextWrapPos(ImGui::GetContentRegionAvail().x);
            ImGui::Text("To take a screenshot press the 'Take Screenshot' button located in the 'Application Settings' window.");
            ImGui::Text("The screenshot will be saved in the 'screenshots' folder located in the main directory of the project.");
            ImGui::Text("The screenshots names are being saved with the following name format:");
            ImGui::Text("'Screenshot yyyy-mm-dd at HH.MM.SS'");
            ImGui::PopTextWrapPos();
            ImGui::TreePop();
            ImGui::Separator();
        }
        if(ImGui::TreeNode("CAMERA")) {
            ImGui::PushTextWrapPos(ImGui::GetContentRegionAvail().x);
            ImGui::Text("it is possible that the object will be not in the centre of the camera, to re-centre it, press the 'Centre Object' button in the 'Application Settings' window.");
            ImGui::Text("To change the target/camera positions open the 'Camera' node in the 'Application Settings' window.");
            ImGui::PopTextWrapPos();
            ImGui::TreePop();
            ImGui::Separator();
        }
        if(ImGui::TreeNode("LIGHT")) {
            ImGui::PushTextWrapPos(ImGui::GetContentRegionAvail().x);
            ImGui::Text("To change the light color, position or strength open the 'Light' node in the 'Application Settings' window.");
            ImGui::PopTextWrapPos();
            ImGui::TreePop();
            ImGui::Separator();
        }
        ImGui::PopTextWrapPos();
        ImGui::TreePop();
        ImGui::Separator();
    }

}