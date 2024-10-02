#include "core/hexapod.h"
#include "core/IK.h"

Hexapod::Hexapod(glm::vec3 origo)
    : origo(origo)
{
    for(float angle = 0.0f; angle < 360.0f; angle += 60.0f)
    {
        float x = origo.x + cos(glm::radians(angle)) * this->baseRadius;
        float z = origo.z + sin(glm::radians(angle)) * this->baseRadius;
        legs.push_back({glm::vec3(x, origo.y, z), 10.0, 16.0, glm::radians(0.0)});
    }
}

void Hexapod::Draw() const
{
    for(auto leg : legs)
    {
        leg.Draw();

        glm::vec3 endEffector{glm::normalize(leg.base)};
        endEffector *= 10.0;
        
        auto angles = CalculateInverseKinematic(endEffector.x, endEffector.y - 10, -endEffector.z, 10.0f, 16.0f);
        leg.Rotate(angles.theta_1, angles.theta_2, angles.theta_3);
    }
}


void Hexapod::SetOrigo(const glm::vec3& position)
{
    origo = position;
}

glm::vec3 Hexapod::GetOrigo() const { return origo; }

void Hexapod::SetDirection(glm::vec3 dir)
{
    direction = glm::normalize(dir);
}

glm::vec3 Hexapod::GetDirection() const { return direction; }

void Hexapod::SetWalkCycle(Hexapod::WalkCycle cycle, void (*ptr)(Hexapod&)){ this->walkCycles[cycle] = ptr; }
