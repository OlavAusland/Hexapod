#include "core/IK.h"
#include <glm/ext/scalar_constants.hpp>

InverseKinematicResult CalculateInverseKinematic(float x, float y, float z, float l1, float l2)
{
    float r1 = sqrt(z * z + x * x);
    float r2 = y;
    float r3 = sqrt(r1 * r1 + r2 * r2);

    float phi_1 = acos((r3 * r3 - l2 * l2 - l1 * l1) / (-2.0 * l2 * l1));
    float phi_2 = acos((l2 * l2 - l1 * l1 - r3 * r3) / (-2.0 * l1 * r3));
    float phi_3 = atan2(y, r1);

    float theta_1 = atan2(z, x);
    float theta_2 = phi_3 + phi_2;
    float theta_3 = glm::pi<float>() + phi_1;

    return {theta_1, theta_2, theta_3};
}
