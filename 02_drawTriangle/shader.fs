#version 330 core

out vec4 fragColor;
in vec3 toFragmentColor;

void main()
{
	fragColor = vec4(toFragmentColor, 1.0f);
}
