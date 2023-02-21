//
// Created by Theodora Vraimakis on 10/02/2023.
//

#include "Render.h"



void Render::run()
{
    m_window = std::make_shared<Window>(
    );

    m_camera = std::make_shared<ArcballCamera>(
            m_window->get(),
            glm::fvec4(1.0f, 1.0f, 30.0f, 1.0f),
            glm::fvec4(1.0f),
            50.0f,
            ((float)m_window->nwidth / (float) m_window->nheight)

    );
    std::vector<Shader::ShaderSource> s = {
            { GL_VERTEX_SHADER, "../Shaders/camera.vert" },
            { GL_FRAGMENT_SHADER, "../Shaders/camera.frag" }
    };
    m_shader = std::make_shared<Shader>(s);
    m_shape = std::make_shared<Cylinder>();
    m_shape =  std::make_shared<Cone>(true, 4, glm::vec3(0.88f, 0.33f, 0.25f),
        glm::rotate(glm::mat4(1.0f), kPi_/2, glm::vec3(0.0f, 0.0f, 1.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(4.f, 0.5f, 0.5f)));\
    m_light = std::make_shared<Light>();
    m_turtle = std::make_shared<Turtle>();
//    m_coordsAxis = std::make_shared<coordinateAxesArrows>();
//    position = m_camera->getPos();
    configureCallbacks();

    fov = m_camera->getFOV();

    m_UI = std::make_unique<UI>(
            m_window,
            m_camera,
            m_light
    );

    mainLoop();
    destroy();
}

void Render::configureCallbacks() {
    m_isMouseInMotion = false;

    glfwSetWindowUserPointer(m_window->get(), m_camera.get());
    glfwSetWindowUserPointer(m_window->get(), m_shader.get());
    glfwSetScrollCallback(m_window->get(), scrollCallback);//
    glfwSetKeyCallback(m_window->get(), reloadShader); //shader reload
    glfwGetFramebufferSize(m_window->get(), &m_window->nwidth, &m_window->nheight);
}

void Render::scrollCallback(
        GLFWwindow* window,
        double xoffset,
        double yoffset
) {
    float actualFOV = fov;
    float newFOV = actualFOV - yoffset
//            * -1.0f
            ;
    if (newFOV < 1.0f)
        newFOV = 1.0f;
    if (newFOV > 100.0f)
        newFOV = 100.0f;

//    camera->setFOV(newFOV);
    fov = newFOV;
}

void Render::handleInput() {
    m_window->pollEvents();

    if (m_UI->isCursorPositionInGUI())
        return;
    if (glfwGetMouseButton(m_window->get(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

        auto pCamera = std::dynamic_pointer_cast<ArcballCamera>(m_camera);

        if (!m_isMouseInMotion)
        {
            pCamera->saveCursorPos();

            m_isMouseInMotion = true;

        } else {

            // TODO: Make it dynamic.
            glm::mat4 newRot = glm::mat4(1.0f);
//            glm::mat4 newRot = m_turtle->finalWorldMatrices[0];

            pCamera->updateCameraPos(newRot);
        }

    } else
    {
        m_isMouseInMotion = false;
    }
}

void Render::mainLoop()
{
    m_turtle->computeFinalWorldM();

    while (!m_window->isWindowClosed()) {

        m_window->processInput();
        m_window->clearScreen();
        m_window->resize();

        handleInput();

        m_camera->processInput(m_window->getDeltaTime());

        glUseProgram(m_shader->programId());


        m_camera->setFOV(fov);

        glm::mat4 projection = m_camera->getProjectionM();
        m_shader->setMat4("projection", projection);

        glm::mat4 view = m_camera->getViewM();
        m_shader->setMat4("view", view);



        m_shader->setVec3("lightColor", m_light->m_lcolor);
        m_shader->setVec3("lightPosition", m_light->m_lpos);
        m_shader->setFloat("ambientStrength", m_light->m_lambient);



        m_turtle->draw(m_shader, m_shape);



        m_UI->imguiDraw(m_camera,
                        m_shape,
                        m_light
        );


        m_window->swapBuffers();

    }

    m_UI->imguiDestroy();
}
void Render::destroy()
{
//    m_window->destroy();
//    m_shader->d
}
void Render::reloadShader(GLFWwindow* aWindow, int aKey, int, int aAction, int)
{
    auto* sh = static_cast<Shader*>(
            glfwGetWindowUserPointer(aWindow)
    );
    if (GLFW_KEY_R == aKey && GLFW_PRESS == aAction)
    {
        try
        {
            sh->reload();
            std::fprintf(stderr, "Shaders reloaded and recompiled.\n");
        }
        catch (std::exception const& eErr)
        {
            std::fprintf(stderr, "Error when reloading shader:\n");
            std::fprintf(stderr, "%s\n", eErr.what());
            std::fprintf(stderr, "Keeping old shader.\n");
        }
    }
}

