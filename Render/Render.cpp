//
// Created by Theodora Vraimakis on 10/02/2023.
//

#include "Render.h"



void Render::run()
{
    m_window = std::make_shared<Window>();

    auto pos = glm::vec4(1.0f);
    auto tar = glm::vec4(0.0f);

    m_camera = std::make_shared<Camera>(
            m_window->get(),
            pos,
            tar,
            10.0f,
            ((float)m_window->nwidth / (float) m_window->nheight)

    );

    std::vector<Shader::ShaderSource> s = {
            { GL_VERTEX_SHADER, "../Shader/camera.vert" },
            { GL_FRAGMENT_SHADER, "../Shader/camera.frag" }
    };

    m_shader = std::make_shared<Shader>(s);

    m_light = std::make_shared<Light>();
    m_allShapes = std::make_shared<AllShapes>();
    m_shape =  m_allShapes->m_cylinder;
    configureCallbacks();

    fov = m_camera->getFOV();

    std::vector<Command> c1 = {};
    std::vector<Rule> r = {};
    m_rules = r;

    m_lsys = std::make_shared<LSystem>(
            std::vector<Command>(std::move(c1)),
            3.0,
            m_rules,
            std::make_shared<float>(90.0f),
            m_shape->getLength(),
            m_shape,
            m_allShapes,
            m_camera
    );
    m_lsys->m_setting = "HELLO!";

    m_lsys->m_axiomBuffer.clear();
    m_lsys->m_axiomBuffer = "H+f+E-ff-ff|L-ff-ff|L-fff-ff|Of+!";
    m_lsys->m_rules.clear();

    m_lsys->addRule("H", "F+f+F[F]+F-F");
    m_lsys->m_rules.back().m_shape->m_color = glm::vec3(255, 87, 51) / 255.0f;
    m_lsys->m_rules.back().m_shape->updateShape();
    m_lsys->addRule("E", "[-F]F[-F]F[-F]");
    m_lsys->m_rules.back().m_shape->m_color = glm::vec3(255, 189, 51) / 255.0f;
    m_lsys->m_rules.back().m_shape->updateShape();
    m_lsys->addRule("L", "[-F]FF");
    m_lsys->m_rules.back().m_shape->m_color = glm::vec3(219, 255, 51) / 255.0f;
    m_lsys->m_rules.back().m_shape->updateShape();
    m_lsys->addRule("O", "FF+F+FF+F");
    m_lsys->m_rules.back().m_shape->m_color = glm::vec3(117, 255, 51) / 255.0f;
    m_lsys->m_rules.back().m_shape->updateShape();
    m_lsys->addRule("!", "[\"(0.3)F][\"(0.5)f\"(1.7)FF]");
    m_lsys->m_rules.back().m_shape->m_color = glm::vec3(51, 255, 87) / 255.0f;
    m_lsys->m_rules.back().m_shape->updateShape();


    m_lsys->m_angle = std::make_shared<float>(90);
    m_lsys->updateAxiom();

    m_UI = std::make_unique<UI>(
            m_window,
            m_camera,
            m_light,
            m_allShapes,
            m_shape,
            m_lsys
    );

    mainLoop();
    destroy();
}

void Render::configureCallbacks() {
    m_isMouseInMotion = false;
    isOnUI = std::make_shared<bool>(false);

    glfwSetWindowUserPointer(m_window->get(), m_camera.get());
    glfwSetWindowUserPointer(m_window->get(), m_shader.get());
    glfwSetScrollCallback(m_window->get(), scrollCallback);
    glfwGetFramebufferSize(m_window->get(), &m_window->nwidth, &m_window->nheight);
}

void Render::scrollCallback(
        GLFWwindow* window,
        double xoffset,
        double yoffset
) {
    if(*isOnUI)
        return;
    float actualFOV = fov;
    float newFOV = actualFOV - yoffset;
    if (newFOV < 1.0f)
        newFOV = 1.0f;
    if (newFOV > 100.0f)
        newFOV = 100.0f;

//    camera->setFOV(newFOV);
    fov = newFOV;
}

void Render::handleInput() {
    m_window->pollEvents();
    if (m_UI->isCursorOnUI()) {
        return;
    }
    if (glfwGetMouseButton(m_window->get(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

        auto cameraPointer = std::dynamic_pointer_cast<Camera>(m_camera);
        if (!m_isMouseInMotion)
        {
            cameraPointer->saveCursor();
            m_isMouseInMotion = true;
        }
        else
        {
            cameraPointer->update();
        }

    }
    else
        m_isMouseInMotion = false;
}

void Render::mainLoop()
{

    m_shape->make();
    m_shape->createVAO();

    GLuint grassTexture = OBJExport::loadTexture("../textures/treeTexture.jpeg", 4);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, grassTexture);
    GLuint textureLocation = glGetUniformLocation(m_shader->programId(), "textureSampler");
    glUniform1i(textureLocation, 0);

    m_allShapes->m_cylinder->getMesh().texture = grassTexture;
    while (!m_window->isWindowClosed()) {

        isOnUI = std::make_shared<bool>(m_UI->isCursorOnUI());


        m_window->processInput();
        m_window->clearScreen();
        m_window->resize();

        handleInput();

        glUseProgram(m_shader->programId());

        m_camera->setFOV(fov);

        glm::mat4 projection = m_camera->getProjectionM();
        m_shader->setMat4("projection", projection);

        glm::mat4 view = m_camera->getViewMat();
        m_shader->setMat4("view", view);


        m_shader->setVec3("lightColor", m_light->m_lcolor);
        m_shader->setVec3("lightPos", m_light->m_lpos);
        m_shader->setFloat("ambientStrength", m_light->m_lambient);
        m_shader->setFloat("specularStrength", m_light->m_specular);
        m_shader->setFloat("shininess", 0.5);

        if (!m_UI->m_loadedMesh.positions.empty()) {
            glBindVertexArray(m_UI->m_loadedMeshVAO);
            m_shader->setMat4("model", glm::mat4(1.0f));
            glDrawArrays(GL_TRIANGLES, 0, m_UI->m_loadedMesh.positions.size());

        }
        else
        {
            m_lsys->m_output->draw(m_shader, m_shape, m_allShapes, m_camera, m_lsys->m_textures);
        }
        m_UI->imguiDraw(m_window,
                        m_camera,
                        m_shape,
                        m_light,
                        m_allShapes,
                        m_lsys
        );


        m_window->swapBuffers();

    }
    auto g = m_shape->getPointerVAO();
    glDeleteVertexArrays(GL_ARRAY_BUFFER, g);

    m_UI->imguiDestroy();
}
void Render::destroy()
{}