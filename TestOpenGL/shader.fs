#version 330 core
out vec4 FragColor;
in vec3 vertexColor;
in vec2 TexCoord;
uniform vec4 outColor;

uniform sampler2D ourTexture;
void main()
{
	//FragColor = vec4(1.0, 0.0,0.0, 1.0f);
	FragColor = texture(ourTexture, TexCoord);
}
