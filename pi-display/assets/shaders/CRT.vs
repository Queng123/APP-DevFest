#version 330 core

layout (location = 0) in vec3 inPosition; // Input vertex position

uniform mat4 modelviewProjection; // Model-view-projection matrix

void main()
{
    gl_Position = modelviewProjection * vec4(inPosition, 1.0);
}
