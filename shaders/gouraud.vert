#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNor;

struct LightInfo
{
   vec4 position;
   vec3 La; 
   vec3 Ld; 
   vec3 Ls; 
};

struct Material
{
   vec3 Kd;
   vec3 Ka;
   vec3 Ks;
   float shininess;
};

uniform LightInfo uLight; 
uniform Material uMaterial;
uniform float uGamma;
uniform mat3 uNormalMat;
uniform mat4 uModelViewMat;
uniform mat4 uMVPMat;

out vec3 frontColor;
out vec3 backColor;

vec3 phongModel(in vec3 ePos, in vec3 eNormal)
{
   float w = uLight.position.w; // w == 0 => directional light; w == 1 => point light
   vec3 s = normalize(uLight.position.xyz - w * ePos);
   vec3 v = normalize(-ePos);
   vec3 h = normalize(s + v);

   vec3 ambient = uLight.La * uMaterial.Ka;

   float angle = max( dot(s,eNormal), 0.0 ); 
   vec3 diffuse = angle * uLight.Ld * uMaterial.Kd;

   float base = max(dot(h,eNormal), 0.0);
   vec3 spec = uLight.Ls * uMaterial.Ks * pow(base, uMaterial.shininess);

   return ambient + diffuse + spec;
}

void main()
{
   vec4 ePos = uModelViewMat * vec4( vPos, 1.0);
   vec3 eNormal = normalize( uNormalMat * vNor);

   frontColor = pow(phongModel(ePos.xyz, eNormal), vec3(uGamma));
   backColor = pow(phongModel(ePos.xyz, -eNormal), vec3(uGamma));

   gl_Position = uMVPMat * vec4(vPos, 1.0);
}


