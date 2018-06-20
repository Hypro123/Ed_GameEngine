#version 410

in vec2 vTexCoord;

uniform sampler2D colourTarget;

out vec4 FragColour;

//output colour
vec4 Default(vec2 texCoord)
{
	return texture(colourTarget, texCoord);
}

//Blur
vec4 Blur(vec2 texCoord)
{
	vec2 texel = 1.0f/ textureSize(colourTarget, 0);
	
	vec4 colour = texture(colourTarget, texCoord);
	colour += texture(colourTarget, texCoord + texel * vec2(-1,1));
	colour += texture(colourTarget, texCoord + texel * vec2(-1,0));
	colour += texture(colourTarget, texCoord + texel * vec2(-1,-1));
	colour += texture(colourTarget, texCoord + texel * vec2(0,1));
	colour += texture(colourTarget, texCoord + texel * vec2(0,-1));
	colour += texture(colourTarget, texCoord + texel * vec2(1,1));
	colour += texture(colourTarget, texCoord + texel * vec2(1,0));
	colour += texture(colourTarget, texCoord + texel * vec2(1,-1));

	return colour / 9;
}

//Distort
vec4 Distort(vec2 texCoord)
{
	vec2 mid = vec2(0.5f);
	float distanceFromCentre = distance(texCoord, mid);
	vec2 normalizedCoord = normalize(texCoord - mid);
	float bias = distanceFromCentre + sin(distanceFromCentre * 15) * 0.05f;
	vec2 newCoord = mid + bias * normalizedCoord;
	return texture(colourTarget, newCoord);
}

//Distort
vec4 DistortBlur(vec2 texCoord)
{
	vec2 mid = vec2(0.5f);
	float distanceFromCentre = distance(texCoord, mid);
	vec2 normalizedCoord = normalize(texCoord - mid);
	float bias = distanceFromCentre + tan(distanceFromCentre * 15) * 0.05f;
	vec2 newCoord = mid + bias * normalizedCoord;
	
	vec2 texel = 20.0f/ textureSize(colourTarget, 0);
	
	vec4 colour = texture(colourTarget, newCoord);
	colour += texture(colourTarget, newCoord + texel * vec2(-1,1));
	colour += texture(colourTarget, newCoord + texel * vec2(-1,0));
	colour += texture(colourTarget, newCoord + texel * vec2(-1,-1));
	colour += texture(colourTarget, newCoord + texel * vec2(0,1));
	colour += texture(colourTarget, newCoord + texel * vec2(0,-1));
	colour += texture(colourTarget, newCoord + texel * vec2(1,1));
	colour += texture(colourTarget, newCoord + texel * vec2(1,0));
	colour += texture(colourTarget, newCoord + texel * vec2(1,-1));

	return colour / 9;
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
	FragColour = Blur(texCoord);
}