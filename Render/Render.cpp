//
// Created by Theodora Vraimakis on 10/02/2023.
//

#include "Render.h"



void Render::run()
{
    m_window = std::make_shared<Window>(
//            Config::SCR_WIDTH,
//            Config::SCR_HEIGHT,
//            Config::TITLE
    );
    m_camera = std::make_shared<ArcballCamera>(
            m_window->get(),
            glm::fvec4(0.0f, 0.0f, 5.0f, 1.0f),
            glm::fvec4(0.0f),
            45.0f
    );
    std::vector<Shader::ShaderSource> s = {
            { GL_VERTEX_SHADER, "../Shaders/camera.vert" },
            { GL_FRAGMENT_SHADER, "../Shaders/camera.frag" }
    };
    m_shader = std::make_shared<Shader>(s);
    m_cylinder = std::make_shared<Cylinder>();

    m_UI = std::make_unique<UI>(
            m_window,
            m_camera,
            m_cylinder
//            m_shader
    );

    configureCallbacks();

    mainLoop();
    destroy();
}

//void Render::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
//    //action == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
//    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
//
////        double startXPos, startYPos; //screen coordinates when mouse clicks.
////        glfwGetCursorPos(window, &startXPos, &startYPos);
////        m_camera->startPos.x = ((startXPos - (SCR_WIDTH/2) ) / (SCR_WIDTH/2)) * RADIUS; //convert to NDC, then assign to startPos.
////        m_camera->startPos.y = (((SCR_HEIGHT/2) - startYPos) / (SCR_HEIGHT/2)) * RADIUS;// ..same for y coordinate.
////        m_camera->startPos.z = m_camera->z_axis(m_camera->startPos.x, m_camera->startPos.y);
////        flag = true;
//    }
//    else if(action == GLFW_RELEASE){
////        m_camera->replace();
////        flag = false;
//    }
//}
//void Render::mousePositionCallback(GLFWwindow* window, double xpos, double ypos){
////    if(flag == true){
////        //Get the screen coordinates when mouse clicks.
////        m_camera->currentPos.x = ((xpos - (SCR_WIDTH/2) ) / (SCR_WIDTH/2)) * RADIUS;
////        m_camera->currentPos.y = (((SCR_HEIGHT/2) - ypos) / (SCR_HEIGHT/2)) * RADIUS;
////        m_camera->currentPos.z = m_camera->z_axis(m_camera->currentPos.x, m_camera->currentPos.y);
////        m_camera->rotation();
////    }
////}
void Render::configureCallbacks() {
    m_isMouseInMotion = false;

    glfwSetWindowUserPointer(m_window->get(), m_camera.get());
    glfwSetWindowUserPointer(m_window->get(), m_shader.get());
//    glfwSetMouseButtonCallback(m_window->get(), mouseButtonCallback);
//    glfwSetCursorPosCallback(m_window->get(), mousePositionCallback);
    glfwSetScrollCallback(m_window->get(), scrollCallback);
    glfwSetKeyCallback(m_window->get(), r);
}

void Render::scrollCallback(
        GLFWwindow* window,
        double xoffset,
        double yoffset
) {
    ArcballCamera* camera = static_cast<ArcballCamera*>(
            glfwGetWindowUserPointer(window)
    );

    float actualFOV = camera->getFOV();
    float newFOV = actualFOV + yoffset * -1.0f;

    camera->setFOV(newFOV);
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
            glm::mat4 newRot = glm::mat4(1.0);

            pCamera->updateCameraPos(newRot);
        }

    } else
    {
        m_isMouseInMotion = false;
    }
}

void Render::mainLoop()
{

//    Shader ourShader({
//                             { GL_VERTEX_SHADER, "../shaders/camera.vert" },
//                             { GL_FRAGMENT_SHADER, "../shaders/camera.frag" }
//                     });


//// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
//    float vertices[] = {
//            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//    };
//// world space positions of our cubes
//    glm::vec3 cubePositions[] = {
//            glm::vec3( 0.0f,  0.0f,  0.0f),
//            glm::vec3( 2.0f,  5.0f, -15.0f),
//            glm::vec3(-1.5f, -2.2f, -2.5f),
//            glm::vec3(-3.8f, -2.0f, -12.3f),
//            glm::vec3( 2.4f, -0.4f, -3.5f),
//            glm::vec3(-1.7f,  3.0f, -7.5f),
//            glm::vec3( 1.3f, -2.0f, -2.5f),
//            glm::vec3( 1.5f,  2.0f, -2.5f),
//            glm::vec3( 1.5f,  0.2f, -1.5f),
//            glm::vec3(-1.3f,  1.0f, -1.5f)
//    };
//
//    unsigned int VBO, VAO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//// position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//// texture coord attribute
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);

    Cylinder he;
    auto rootCylinder = he.getMesh();
//auto rootCylinder = m_cylinder->getMesh();
    size_t vertexCountRootCylinder = he.returnVertexCount();
//    GLuint root = Mesh::createVAO(rootCylinder);
    GLuint root = he.returnVAO();
    glBindVertexArray(root);
    glUseProgram(m_shader->programId());

    while (!m_window->isWindowClosed()) {
        m_window->resize();

        handleInput();

        m_window->processInput();
        m_window->clearScreen();
//        m_UI->reload(m_window, m_shader);
//        glIsProgram(m_shader->getHandle())


        glUseProgram(m_shader->programId());
        glm::mat4 projection = glm::mat4(1.0f);
        projection = m_camera->getProjectionM();
        m_shader->setMat4("projection", projection);
        glm::mat4 view = m_camera->getViewM();
        m_shader->setMat4("view", view);
//                 render boxes
//        for (int i = 0; i < 10; i++)
//        {
//
//            // calculate the model matrix for each object and pass it to shader before drawing
//            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//            model = glm::translate(model, cubePositions[i]);
//            float angle = 20.0f * i;
//            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//            ourShader.setMat4("model", model);
////            ourShader.setVec4("ourColor", glm::vec4(0.88f, 0.33f, 0.25f, 1.0f));
//
//
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }



        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3( 0.0f,  0.0f,  0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        m_shader->setMat4("model", model);
////        glm::mat3 normalMatrix = glm::mat3(inverse(glm::mat4(1.0f)));
////        ourShader.setMat3("normalMatrix", normalMatrix);

//        glDrawArrays(GL_TRIANGLES, 0, 3 * vertexCountRootCylinder);
        glDrawArrays(GL_TRIANGLES, 0, 3 * vertexCountRootCylinder);




        m_UI->imguiDraw(m_camera,
                        m_cylinder
//                        m_shader
                        );

        m_window->swapBuffers();

    }
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
    m_UI->imguiDestroy();
}
void Render::destroy()
{
    m_window->destroy();
}
void Render::r(GLFWwindow* aWindow, int aKey, int, int aAction, int)
{
    auto* sh = static_cast<Shader*>(
            glfwGetWindowUserPointer(aWindow)
    );
//    auto pShader = std::dynamic_pointer_cast<Shader>(m_shader);
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