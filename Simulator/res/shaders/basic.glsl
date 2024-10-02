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
    float distance = 1.0 - (abs(pos.x) + abs(pos.y)) / 50.0;
    //color = vec4(distance, distance, distance, 1.0);
    color = vec4((pos.x / 10.0), 1.0, (pos.z / 10.0) + 0.1, 1.0);
}
