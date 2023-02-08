#version 330 core
out vec4 FragColor;
in vec3 vertexColor;
in vec2 TexCoord;
uniform vec4 outColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixScale;
void main()
{
	//FragColor = vec4(1.0, 0.0,0.0, 1.0f);
	FragColor = mix(texture(texture1, TexCoord) , texture(texture2, vec2(1.0-TexCoord.x, TexCoord.y)), mixScale);
	//FragColor = texture(texture2, TexCoord);
}
