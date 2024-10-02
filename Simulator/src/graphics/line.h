#pragma once
#include <glm/glm.hpp>

class Line
{
private:
    unsigned int m_RendererID;
    unsigned int m_VAO;
public:
    Line();
    Line(glm::vec3 p0, glm::vec3 p1);
    Line(const void* data, unsigned int size);
    
    void SetData(const void* data, unsigned int size) const;
    void Draw() const;
};
