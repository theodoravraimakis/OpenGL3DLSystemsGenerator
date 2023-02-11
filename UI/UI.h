//
// Created by Theodora Vraimakis on 07/02/2023.
//

#ifndef FINALYEARPROJECT_UI_H
#define FINALYEARPROJECT_UI_H


#include "../Render/Render.h"

class UI {

public:
    UI(
            const std::shared_ptr<Window> &window
    );

    ~UI();



//void imguiInitialisation (GLFWwindow* window);
void imguiDisplay();
void imguiDestroy();
//void rot(ArcballCamera* arcCamera);
void imguiDraw();
};

#endif //FINALYEARPROJECT_UI_H
