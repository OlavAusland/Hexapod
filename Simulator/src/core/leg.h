#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "graphics/line.h"

class Leg
{
private:
    Line graphics;
public:
    glm::vec3 base;

    glm::vec3 femur;
    glm::vec3 tibia;
    float* vertices;
    

    Leg(glm::vec3 base, float l1, float l2, float rotationOffset);

    void Rotate(float z, float femur, float tibia);

    inline void Draw() const { graphics.Draw(); }
};
