#version 400

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

struct FogInfo
{
   vec3 color;
   float minDist;
   float maxDist;
};

uniform LightInfo uLight;
uniform Material uMaterial;
uniform FogInfo uFog;
uniform float uGamma;
uniform sampler2D uTexture;
uniform sampler2D uDetail;

in vec4 position;
in vec3 normal;
in vec2 uv;

vec3 phongModel(in vec3 ePos, in vec3 eNormal)
{
   float w = uLight.position.w; // 0 => directional light; 1 => point light
   vec3 s = normalize(uLight.position.xyz - w * ePos);
   vec3 v = normalize(-ePos);
   vec3 h = normalize(v + s);

   vec3 ambient = uLight.La * uMaterial.Ka;

   float angle = max( dot(s,eNormal), 0.0 ); 
   vec3 diffuse = angle * uLight.Ld * uMaterial.Kd;

   float base = max(dot(h, eNormal), 0.0);
   vec3 spec = uLight.Ls * uMaterial.Ks * pow(base, uMaterial.shininess);

   vec4 mainColor = texture(uTexture, uv);
   vec4 detailColor = texture(uDetail, uv);
   vec4 texColor = mix(mainColor, detailColor, detailColor.a);

   // texture test: 
   //return (ambient + diffuse) * texColor.xyz + spec;
   return ambient + diffuse + spec;
}

void main()
{
   vec3 color = phongModel(position.xyz, gl_FrontFacing? normal : -normal);

   // apply linear fog
   float d = length(position.xyz);
   float factor = clamp((d - uFog.minDist)/(uFog.maxDist - uFog.minDist), 0.0, 1.0);
   color = mix(color, uFog.color, factor);

   // apply gamma
   color = pow(color, vec3(uGamma));

   gl_FragColor = vec4(color, 1.0);
}

