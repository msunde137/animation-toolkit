#version 400

in vec3 frontColor;
in vec3 backColor;

void main()
{
   gl_FragColor = vec4(gl_FrontFacing? frontColor : backColor, 1.0);
}

