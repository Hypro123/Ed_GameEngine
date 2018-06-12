#version 410

in vec2 vTexCoord;

uniform sampler2D colourTarget;

out vec4 FragColour;

//output colour
vec4 Default(vec2 texCoord)
{
	return texture(colourTarget, texCoord);
}

void main()
{
	//size
	vec2 texSize = textureSize(colourTarget, 0);
	vec2 texelSize = 1.0f/texSize;

	//adjust coordinates
	vec2 scale = (texSize - texelSize)/texSize;
	vec2 texCoord = vTexCoord/scale + texelSize * 0.5f;

	//sample post effect
	FragColour = Default(texCoord);
}