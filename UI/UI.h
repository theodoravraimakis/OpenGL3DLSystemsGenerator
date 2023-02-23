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
#include <memory>


class Camera {
private:
    Shape* obj;
public:
    Camera (bool flag){
        if (flag) {
            obj = new Cylinder();
        } else {
            obj = new Cone();
        }
    }
};

class UI {

public:
    UI(
            const std::shared_ptr<Window>& window,
            const std::shared_ptr<ArcballCamera>& camera,
            const std::shared_ptr<Light> &light,
            const std::shared_ptr<Shape> &shape
    );

    ~UI();

    static void imguiDemo();
    static bool isCursorPositionInGUI() ;
    static bool isClicked();
    static bool clicked();
    static void imguiDestroy();
    void imguiDraw(const std::shared_ptr<ArcballCamera> &camera,
                   std::shared_ptr<Shape> &shape,
                    const std::shared_ptr<Light> &light
                    );
    static void imguiCamera(const std::shared_ptr<ArcballCamera> &camera);
    void shapeCap(
            std::shared_ptr<Shape>& shape
            );
    static void changeColor(const std::shared_ptr<Shape> &shape);
    static void changeLight(const std::shared_ptr<Light> &light);

    std::shared_ptr<Shape> m_cylinder=std::make_shared<Cylinder>();
    std::shared_ptr<Shape> m_cone=std::make_shared<Cone>();

};


#endif //FINALYEARPROJECT_UI_H
