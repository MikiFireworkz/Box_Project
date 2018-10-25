#version 400 core

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

out vec4 color;

//Texture
uniform sampler2D Texture;

//Time
//uniform float Time;

void main()
{
	//Normal
	//color = vec4(Normal, 1.0f);    

	//Texture
    color = texture(Texture, TexCoord);
}