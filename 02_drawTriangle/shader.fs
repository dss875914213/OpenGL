#version 330 core

out vec4 fragColor;
in vec2 toFragmentTextureCoord;
uniform sampler2D myTexure1;
uniform sampler2D myTexure2;
uniform float alpha;

void main()
{
	// fragColor = vec4(toFragmentTextureCoord.x, toFragmentTextureCoord.y, 0.0f, 1.0f);
	fragColor = mix(texture(myTexure1, toFragmentTextureCoord), texture(myTexure2, toFragmentTextureCoord), alpha);
}
