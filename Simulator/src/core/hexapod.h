#pragma once
#include <vector>
#include "core/leg.h"
#include "graphics/line.h"
#include "glm/glm.hpp"

#include <unordered_map>

class Hexapod
{
public:
    enum WalkCycle
    {
        Default,
        Improved
    };
public:
    std::unordered_map<WalkCycle, void (*)(Hexapod&)> walkCycles;
    glm::vec3 origo{0, 0, 0}; 

    float baseRadius = 10;

    glm::vec3 direction{0, 0, 0};
public:
    std::vector<Leg> legs;
public:
    Hexapod(glm::vec3 origo);

    void Draw() const;

    void SetWalkCycle(WalkCycle, void (*)(Hexapod&));

    void SetOrigo(const glm::vec3& position);
    glm::vec3 GetOrigo() const;

    void SetDirection(glm::vec3 dir);
    glm::vec3 GetDirection() const;
};
