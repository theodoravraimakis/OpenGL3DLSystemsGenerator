//
// Created by Theodora Vraimakis on 07/02/2023.
//

#ifndef FINALYEARPROJECT_UI_H
#define FINALYEARPROJECT_UI_H


//#include "../Render/Render.h"
#include <iostream>
#include "../Window/Window.h"
#include "../Camera/ArcballCamera.h"
#include "../Shapes/Cylinder.h"
#include "../Shader/Shader.h"
#include "../Config/Config.h"

class UI {

public:
    UI(
            const std::shared_ptr<Window>& window,
            const std::shared_ptr<ArcballCamera>& camera,
            const std::shared_ptr<Cylinder> &cylinder,
//            const std::shared_ptr<Shader>& shader
            const std::shared_ptr<Light> &light
    );

    ~UI();



//void imguiInitialisation (GLFWwindow* window);
static void imguiDemo();
static bool isCursorPositionInGUI() ;
static bool isClicked();
static bool clicked();
static void imguiDestroy();
//void rot(ArcballCamera* arcCamera);
    void imguiDraw(const std::shared_ptr<ArcballCamera> &camera,
                      const std::shared_ptr<Cylinder> &cylinder,
                      const std::shared_ptr<Light> &light
//                      const std::shared_ptr<Shader> &shader
);
void parametersMenu();
static void imguiCamera(const std::shared_ptr<ArcballCamera> &camera);
static void imguiCylinder(
        const std::shared_ptr<Cylinder> &cylinder
//                          const std::shared_ptr<Shader> &shader
);
static void changeColor(const std::shared_ptr<Cylinder> &cylinder);
//void reload(const std::shared_ptr<Window>& window, const std::shared_ptr<Shader> &shader);
//static bool cap;
//void setImguiVars();
static void changeLight(const std::shared_ptr<Light> &light);
};

#endif //FINALYEARPROJECT_UI_H
