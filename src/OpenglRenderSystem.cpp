#include "OpenglRenderSystem.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace
{
    GLenum getLightEnum(uint32_t index)
    {
        static const GLenum lights[] = {
            GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3,
            GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7
        };

        if (index < 8)
            return lights[index];

        return GL_LIGHT0;
    }
}

void OpenglRenderSystem::init()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_NORMALIZE);
}

void OpenglRenderSystem::clearDisplay(float r, float g, float b)
{
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenglRenderSystem::setViewport(double x, double y, double width, double height)
{
    glViewport(
        static_cast<GLint>(x),
        static_cast<GLint>(y),
        static_cast<GLsizei>(width),
        static_cast<GLsizei>(height)
    );
}

void OpenglRenderSystem::renderTriangleSoup(const std::vector<Vertex>& vertices)
{
    renderData(vertices, RenderDataType::Triangles);
}

void OpenglRenderSystem::renderLines(const std::vector<Vertex>& vertices)
{
    renderData(vertices, RenderDataType::Lines);
}

void OpenglRenderSystem::setupLight(
    uint32_t index,
    glm::vec3 position,
    glm::vec3 Ia,
    glm::vec3 Id,
    glm::vec3 Is
)
{
    GLenum light = getLightEnum(index);

    glm::vec4 ambient (Ia, 1.0f);
    glm::vec4 diffuse (Id, 1.0f);
    glm::vec4 specular(Is, 1.0f);
    glm::vec4 pos     (position, 1.0f);

    glLightfv(light, GL_AMBIENT,  glm::value_ptr(ambient));
    glLightfv(light, GL_DIFFUSE,  glm::value_ptr(diffuse));
    glLightfv(light, GL_SPECULAR, glm::value_ptr(specular));
    glLightfv(light, GL_POSITION, glm::value_ptr(pos));

    if (!glIsEnabled(GL_LIGHTING))
        glEnable(GL_LIGHTING);
}

void OpenglRenderSystem::turnLight(uint32_t index, bool enable)
{
    GLenum light = getLightEnum(index);

    if (enable)
        glEnable(light);
    else
        glDisable(light);
}

void OpenglRenderSystem::setWorldMatrix(const glm::mat4& matrix)
{
    worldMatrix = matrix;
}

const glm::mat4& OpenglRenderSystem::getWorldMatrix() const
{
    return worldMatrix;
}

void OpenglRenderSystem::setViewMatrix(const glm::mat4& matrix)
{
    viewMatrix = matrix;
}

const glm::mat4& OpenglRenderSystem::getViewMatrix() const
{
    return viewMatrix;
}

void OpenglRenderSystem::setProjectionMatrix(const glm::mat4& matrix)
{
    projMatrix = matrix;
}

const glm::mat4& OpenglRenderSystem::getProjMatrix() const
{
    return projMatrix;
}

void OpenglRenderSystem::renderData(
    const std::vector<Vertex>& vertices,
    RenderDataType type
)
{
    glm::mat4 modelView = viewMatrix * worldMatrix;

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(modelView));

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projMatrix));

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    if (!glIsEnabled(GL_COLOR_MATERIAL))
        glEnable(GL_COLOR_MATERIAL);

    if (type == RenderDataType::Triangles)
    {
        glDepthRange(0.01, 1.0);
        glBegin(GL_TRIANGLES);
    }
    else
    {
        glLineWidth(1.0f);
        glBegin(GL_LINES);
    }

    for (const auto& v : vertices)
    {
        glNormal3f(v.normal.x,  v.normal.y,  v.normal.z);
        glColor3f (v.color.r,   v.color.g,   v.color.b);
        glVertex3f(v.position.x, v.position.y, v.position.z);
    }

    glEnd();
}
