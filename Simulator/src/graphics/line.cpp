#include "graphics/line.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

Line::Line(){}
Line::Line(glm::vec3 p0, glm::vec3 p1)
{
    float buffer[] = {p0.x, p0.y, p0.z, p1.x, p1.y, p1.z};
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, buffer, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    glBindVertexArray(0);
}

Line::Line(const void* data, unsigned int size)
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    glBindVertexArray(0);
}

void Line::SetData(const void* data, unsigned int size) const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void Line::Draw() const
{
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_LINES, 0, 4);
    glBindVertexArray(0);
}
