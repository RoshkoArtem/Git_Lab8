#pragma once

#include "Vertex.h"
#include <vector>

namespace GeometryPrimitives
{
    // Куб з методички
    std::vector<Vertex> createCubeVertices();

    // Додатково: 4-х стороння піраміда
    std::vector<Vertex> createPyramidVertices();
}
