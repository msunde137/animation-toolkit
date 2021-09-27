#version 400

layout (location = 0) in vec3 vPos;

uniform vec3 uColor;
uniform mat4 uMat;
out vec3 color;

void main()
{
   color = uColor;
   gl_Position = uMat * vec4(vPos, 1.0);
}


