#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
uniform mat4 u_MVP;

out vec4 pos;

void main()
{
    pos = position;
    gl_Position = u_MVP * position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 pos;

void main()
{
    float dist = 1 - (sqrt(pos.x * pos.x + pos.z * pos.z) / 50.0);
    color = vec4(dist, dist, dist, 1.0);
}
