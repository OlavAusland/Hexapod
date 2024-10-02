#pragma once
#include <math.h>

constexpr float PI = 3.14159265358979323846;

struct InverseKinematicResult
{
    float theta_1;
    float theta_2;
    float theta_3;
};

InverseKinematicResult CalculateInverseKinematic(float x, float y, float z, float l1, float l2);
