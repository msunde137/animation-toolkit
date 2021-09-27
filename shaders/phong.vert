#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNor;
layout (location = 2) in vec2 vUV;

uniform mat3 uNormalMat;
uniform mat4 uModelViewMat;
uniform mat4 uMVPMat;

out vec4 position;
out vec3 normal;
out vec2 uv;

void main()
{
   position = uModelViewMat * vec4( vPos, 1.0);
   normal = normalize( uNormalMat * vNor);
   uv = vUV;

   gl_Position = uMVPMat * vec4(vPos, 1.0);
}


