#include "core/leg.h"

#include <glm/glm.hpp>

Leg::Leg(glm::vec3 base, float l1, float l2, float rotationOffset = 0.0)
{
    this->base = base;
    this->femur = glm::vec3(l1, 0, 0);
    this->tibia = glm::vec3(l2, 0, 0);

    this->base = glm::rotate(glm::mat4(1.0f), rotationOffset, glm::vec3(0, 1, 0)) * glm::vec4(this->base, 1.0f);
    
    vertices = (float*)malloc(sizeof(float) * 12);
    Rotate(0, 0, 0);

    graphics = Line(vertices, 12 * sizeof(vertices));
}

void Leg::Rotate(float z, float femur, float tibia)
{
    glm::mat4 zRotMat(1.0f);
    glm::mat4 femurRotMat(1.0f);
    glm::mat4 tibiaRotMat(1.0f);

    zRotMat = glm::rotate(zRotMat, z, glm::vec3(0, 1, 0));
    femurRotMat = glm::rotate(femurRotMat, femur, glm::vec3(0, 0, 1));
    tibiaRotMat = glm::rotate(tibiaRotMat, tibia, glm::vec3(0, 0, 1));
    
    glm::vec3 tmp_femur = zRotMat * femurRotMat * glm::vec4(this->femur, 1.0f);
    glm::vec3 tmp_tibia = zRotMat * femurRotMat * tibiaRotMat * glm::vec4(this->tibia, 1.0f);

    vertices[0] = base.x; vertices[1] = base.y; vertices[2] = base.z;
    vertices[3] = base.x + tmp_femur.x; vertices[4] = base.y + tmp_femur.y; vertices[5] = base.z + tmp_femur.z;
    vertices[6] = base.x + tmp_femur.x; vertices[7] = base.y + tmp_femur.y; vertices[8] = base.z + tmp_femur.z;
    vertices[9] = base.x + tmp_femur.x + tmp_tibia.x; vertices[10] = base.y + tmp_femur.y + tmp_tibia.y; vertices[11] = base.z + tmp_femur.z + tmp_tibia.z;
    
    graphics.SetData(vertices, 12 * sizeof(vertices));
};
