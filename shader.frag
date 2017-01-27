
	//Micha³ Piotrak
	//numer albumu: 269336
	//Przeciêcie graniastos³upów


#version 330 core

out vec4 color;

uniform vec3 ourColor;

void main()
{
	color = vec4(ourColor, 0.7f);
	//color = vec4(0.2f, 0.3f, 0.5f, 1.0f);
}