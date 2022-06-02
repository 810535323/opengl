#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 texcoord;
uniform sampler2D bearTexture;
uniform sampler2D chickenTexture;
void main()
{
    FragColor = mix(texture(bearTexture,texcoord),texture(chickenTexture,texcoord),0.5);
};
