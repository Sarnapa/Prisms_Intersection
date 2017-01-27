
	//Micha� Piotrak
	//numer albumu: 269336
	//Przeci�cie graniastos�up�w

#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * vec4(position, 1.0f);
}