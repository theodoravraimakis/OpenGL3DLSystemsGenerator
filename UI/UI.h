//
// Created by Theodora Vraimakis on 07/02/2023.
//

#ifndef FINALYEARPROJECT_UI_H
#define FINALYEARPROJECT_UI_H


#include <iostream>
#include "../Window/Window.h"
#include "../Camera/Camera.h"
#include "../Shapes/Cylinder.h"
#include "../Shader/Shader.h"
#include "../Config/Config.h"
#include "../L-System/LSystem.h"
#include "../Export/OBJExport.h"
#include "imgui.h"
#include <memory>
#include "imgui_internal.h"



class UI {

public:
    UI(
            const std::shared_ptr<Window>& window,
            const std::shared_ptr<Camera>& camera,
            const std::shared_ptr<Light> &light,
            const std::shared_ptr<AllShapes> &allShapes,
            const std::shared_ptr<Shape> &shape,
            const std::shared_ptr<LSystem> &lsys
    );

    ~UI();

    static bool isCursorOnUI();
    void userManual();
    static void imguiDestroy();
    void imguiDraw(const std::shared_ptr<Window> &window,
                    const std::shared_ptr<Camera> &camera,
                   std::shared_ptr<Shape> &shape,
                   const std::shared_ptr<Light> &light,
                   const std::shared_ptr<AllShapes> &allShapes,
                   std::shared_ptr<LSystem>& lsys
                    );
    static void imguiCamera(const std::shared_ptr<Camera> &camera,
                            const std::shared_ptr<LSystem> &lsys);
    void shapeCap(std::shared_ptr<Shape>& shape,
                  const std::shared_ptr<AllShapes> &allShapes);
    static void changeColor(const std::shared_ptr<Shape> &shape);
    static void changeLight(const std::shared_ptr<Light> &light);

    void x(std::shared_ptr<LSystem>& lsys,
           std::shared_ptr<Output>& segments,
           std::shared_ptr<Shape>& shape,
           const std::shared_ptr<AllShapes> &allShapes
           );

    std::shared_ptr<std::string> str = std::make_shared<std::string>("");
    std::shared_ptr<std::string> axiomString = std::make_shared<std::string>("");
    std::string y;
    static int filter(ImGuiInputTextCallbackData* data);

    void displayRule(Rule* rule,
                     std::shared_ptr<LSystem>& lsys,
                     std::shared_ptr<Shape> &shape);
    void ruleShape(Rule* rule, std::shared_ptr<AllShapes>& allShapes);
    void defaultSettings(std::shared_ptr<LSystem>& lsys);

    void changeAngle(std::shared_ptr<LSystem>& lsys);
    void changeLength(
            std::shared_ptr<LSystem>& lsys,
            std::shared_ptr<Output>& segments,
            std::shared_ptr<Shape> &shape,
            const std::shared_ptr<AllShapes> &allShapes
            );

    void changeGenerations(
            std::shared_ptr<LSystem>& lsys
    );
    void save(
            const std::shared_ptr<Window> &window,
            std::shared_ptr<LSystem>& lsys,
            const std::shared_ptr<Camera> &camera,
            const std::shared_ptr<AllShapes> &allShapes
            );

    bool& getPopUp()
    {
        return popUp;
    }
    bool& getColorPopUp()
    {
        return colorPopUp;
    }
    bool& getPressedOk()
    {
        return pressedOK;
    }
    bool& getOkButton()
    {
        return okButton;
    }

    void setPopUp(bool newPopUp)
    {
        if (popUp != newPopUp)
        {
            popUp = newPopUp;
        }
    }
    void setColorPopUp(bool newPopUp)
    {
        if (colorPopUp != newPopUp)
        {
            colorPopUp = newPopUp;
        }
    }
    void setOkButton(bool newOk)
    {
        if (okButton != newOk)
        {
            okButton = newOk;
        }
    }
    void setPressedOk(bool newOk)
    {
        if (pressedOK != newOk)
        {
            pressedOK = newOk;
        }
    }
    void setReminder(bool newReminder)
    {
        if (displayReminder != newReminder)
        {
            displayReminder = newReminder;
        }
    }
    bool& getReminder()
    {
        return displayReminder;
    }

    std::string nR;
    std::string nC;
    std::string nCnd;
    std::string nV;
    std::string nLeft;
    std::string nRight;
    std::string errorMessage;

    std::string saveFile;
    std::string openFile;


    void ruleExistsPopUp(std::string message);
    void colorChangePopUp(std::shared_ptr<Rule>& rule);
   std::shared_ptr<Rule> selectedRule;
    bool popUp;
    bool colorPopUp;
    bool okButton;
    bool pressedOK;
    bool isBackgroundBlack;
    bool displayReminder;
    bool showManual;
    float availableWidth;
    std::shared_ptr<AllShapes>                      m_allShapes;
    MeshData                                        m_loadedMesh;
    GLuint                                        m_loadedMeshVAO;
    std::string                                        m_loadedMeshName;
    std::string current_item;
    std::vector<std::string> shapes;
    ImFont* font;
};


#endif //FINALYEARPROJECT_UI_H
