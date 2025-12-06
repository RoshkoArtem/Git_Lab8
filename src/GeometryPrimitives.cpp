#include "GeometryPrimitives.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

using std::vector;

namespace GeometryPrimitives
{
    std::vector<Vertex> createCubeVertices()
    {
        vector<Vertex> cubeVertices;

        // 8 вершин куба
        glm::vec3 positions[] = {
            {-0.5f, -0.5f, -0.5f}, // 0
            { 0.5f, -0.5f, -0.5f}, // 1
            { 0.5f,  0.5f, -0.5f}, // 2
            {-0.5f,  0.5f, -0.5f}, // 3
            {-0.5f, -0.5f,  0.5f}, // 4
            { 0.5f, -0.5f,  0.5f}, // 5
            { 0.5f,  0.5f,  0.5f}, // 6
            {-0.5f,  0.5f,  0.5f}  // 7
        };

        // Нормалі для кожної грані
        glm::vec3 normals[] = {
            { 0.0f,  0.0f, -1.0f}, // front
            { 0.0f,  0.0f,  1.0f}, // back
            {-1.0f,  0.0f,  0.0f}, // left
            { 1.0f,  0.0f,  0.0f}, // right
            { 0.0f, -1.0f,  0.0f}, // bottom
            { 0.0f,  1.0f,  0.0f}  // top
        };

        // Колір для кожної грані
        glm::vec3 colors[] = {
            {1.0f, 0.0f, 0.0f}, // red
            {0.0f, 1.0f, 0.0f}, // green
            {0.0f, 0.0f, 1.0f}, // blue
            {1.0f, 1.0f, 0.0f}, // yellow
            {1.0f, 0.0f, 1.0f}, // magenta
            {0.0f, 1.0f, 1.0f}  // cyan
        };

        // Індекси трикутників (12 трикутників, 36 індексів)
        unsigned int indices[] = {
            0, 1, 2, 2, 3, 0, // front
            4, 5, 6, 6, 7, 4, // back
            0, 3, 7, 7, 4, 0, // left
            1, 5, 6, 6, 2, 1, // right
            0, 1, 5, 5, 4, 0, // bottom
            3, 2, 6, 6, 7, 3  // top
        };

        cubeVertices.reserve(36);

        for (int i = 0; i < 36; ++i)
        {
            unsigned int index = indices[i];
            int face = i / 6; // 6 вершин (2 трикутники) на грань

            Vertex v;
            v.position = positions[index];
            v.normal   = normals[face];
            v.color    = colors[face];

            cubeVertices.push_back(v);
        }

        return cubeVertices;
    }

    std::vector<Vertex> createPyramidVertices()
    {
        vector<Vertex> verts;

        // Квадратна основа
        glm::vec3 A{-0.5f, -0.5f, -0.5f};
        glm::vec3 B{ 0.5f, -0.5f, -0.5f};
        glm::vec3 C{ 0.5f, -0.5f,  0.5f};
        glm::vec3 D{-0.5f, -0.5f,  0.5f};

        // Вершина
        glm::vec3 T{0.0f, 0.5f, 0.0f};

        auto addTri = [&](glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 color)
        {
            glm::vec3 n = glm::normalize(glm::cross(p1 - p0, p2 - p0));
            verts.push_back(Vertex{p0, n, color});
            verts.push_back(Vertex{p1, n, color});
            verts.push_back(Vertex{p2, n, color});
        };

        // Сторони (4 трикутники)
        addTri(T, A, B, {1.0f, 0.0f, 0.0f}); // червона
        addTri(T, B, C, {0.0f, 1.0f, 0.0f}); // зелена
        addTri(T, C, D, {0.0f, 0.0f, 1.0f}); // синя
        addTri(T, D, A, {1.0f, 1.0f, 0.0f}); // жовта

        // Основа (2 трикутники)
        glm::vec3 baseColor{0.7f, 0.7f, 0.7f};
        addTri(A, B, C, baseColor);
        addTri(A, C, D, baseColor);

        return verts;
    }
}
