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
#include <glm/gtc/type_ptr.hpp>

class UI {

public:
    UI(
            const std::shared_ptr<Window>& window,
            const std::shared_ptr<ArcballCamera>& camera,
            const std::shared_ptr<Light> &light
    );

    ~UI();

static void imguiDemo();
static bool isCursorPositionInGUI() ;
static bool isClicked();
static bool clicked();
static void imguiDestroy();
void imguiDraw(const std::shared_ptr<ArcballCamera> &camera,
                const std::shared_ptr<Shape> &shape,
                const std::shared_ptr<Light> &light
                );
static void imguiCamera(const std::shared_ptr<ArcballCamera> &camera);
static void shapeCap(
        const std::shared_ptr<Shape> &shape
        );
static void changeColor(const std::shared_ptr<Shape> &shape);
static void changeLight(const std::shared_ptr<Light> &light);

};

#endif //FINALYEARPROJECT_UI_H
