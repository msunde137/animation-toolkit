#version 400

layout (location = 0) in vec3 vPositions;
layout (location = 1) in vec3 vNormals;
layout (location = 2) in vec2 vTextureCoords;
layout (location = 3) in vec4 vJoints;
layout (location = 4) in vec4 vWeights;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform mat4 JointMats[100];

out vec4 position;
out vec3 normal;
out vec2 uv;

void main()
{
  vec4 pos = vec4(0,0,0,0);
  vec4 nor = vec4(0,0,0,0);
  for (int i = 0; i < 4; i++) {
    pos += vWeights[i] * (JointMats[int(vJoints[i])] * vec4(vPositions, 1)); 
    nor += vWeights[i] * (JointMats[int(vJoints[i])] * vec4(vNormals, 0)); 
  }

  position = ModelViewMatrix * pos;
  normal = normalize( NormalMatrix * normalize(nor.xyz));
  uv = vTextureCoords;
  gl_Position = MVP * pos;
}


