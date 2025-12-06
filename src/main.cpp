#include "ViewerWindow.h"
#include "OpenglRenderSystem.h"
#include "GeometryPrimitives.h"

#include <glm/gtc/matrix_transform.hpp>

// Малюємо фігуру (можеш переключати між кубом і пірамідою)
void renderScene(OpenglRenderSystem& rs)
{
    // static, щоб не створювати вершини кожен кадр
    static const auto cubeData    = GeometryPrimitives::createCubeVertices();
    static const auto pyramidData = GeometryPrimitives::createPyramidVertices();

    // РОЗКОМЕНТУЙ, що хочеш показувати:

    // Куб
    rs.renderTriangleSoup(cubeData);

    // Піраміда
    // rs.renderTriangleSoup(pyramidData);
}

void moveCube(OpenglRenderSystem& rs, const glm::vec3& offset)
{
    rs.setViewMatrix(glm::translate(rs.getViewMatrix(), offset));
}

int main()
{
    constexpr int width  = 640;
    constexpr int height = 480;

    OpenglRenderSystem rs;
    ViewerWindow window("myWindow", static_cast<uint32_t>(width), static_cast<uint32_t>(height));

    // Обробка клавіш
    window.setKeyCallback([&rs](KeyCode key, Action action, Modifier mods)
    {
        (void)mods; // поки що не використовуємо

        if (action != Action::Press && action != Action::Repeat)
            return;

        switch (key)
        {
        case KeyCode::UP:    moveCube(rs, { 0.0f,  0.1f, 0.0f }); break;
        case KeyCode::DOWN:  moveCube(rs, { 0.0f, -0.1f, 0.0f }); break;
        case KeyCode::LEFT:  moveCube(rs, { 0.1f,  0.0f, 0.0f }); break;
        case KeyCode::RIGHT: moveCube(rs, {-0.1f,  0.0f, 0.0f }); break;
        default:
            break;
        }
    });

    // Ініціалізація OpenGL і світла
    rs.init();
    rs.setupLight(
        0,
        glm::vec3(0.0f, 5.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );
    rs.turnLight(0, true);

    // Камера
    glm::vec3 cameraPosition(0.0f, 0.0f, -3.0f);
    glm::vec3 lookAtCenter  (0.0f, 0.0f,  0.0f);
    glm::vec3 cameraUpVector(0.0f, 1.0f,  0.0f);

    glm::mat4 viewMatrix = glm::lookAt(cameraPosition, lookAtCenter, cameraUpVector);
    rs.setViewMatrix(viewMatrix);

    glm::mat4 projMatrix = glm::perspective(
        glm::radians(60.0f),
        static_cast<float>(width) / static_cast<float>(height),
        0.1f,
        500.0f
    );
    rs.setProjectionMatrix(projMatrix);

    // Головний цикл
    while (!glfwWindowShouldClose(window.getGLFWHandle()))
    {
        rs.setViewport(0, 0, window.getWidth(), window.getHeight());
        rs.clearDisplay(0.5f, 0.5f, 0.5f);

        renderScene(rs);

        glfwSwapBuffers(window.getGLFWHandle());
        glfwWaitEvents();
    }

    return 0;
}
