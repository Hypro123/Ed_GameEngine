#version 410

in vec4 vPosition;
in vec3 vNormal;

out vec4 FragColor;

uniform sampler2D diffuseTexture; //sampled colour

uniform vec3 Ia; //ambient light

//main light
uniform vec3 Id; //diffuse
uniform vec3 Is; //specular
uniform vec3 lightDirection; //direction

//secondary light
uniform vec3 Id1; //diffuse
uniform vec3 Is1; //specular
uniform vec3 lightDirection1; //direction

uniform vec3 Ka; //ambient material colour
uniform vec3 Kd; //diffuse material colour
uniform vec3 Ks; //speculat material Colour
uniform float specularPower; //Material specular power

uniform vec3 cameraPosition;

void main()
{
	vec3 N = normalize(vNormal);
	vec3 L = normalize(lightDirection);
	vec3 L1 = normalize(lightDirection1);

	//calculate lambert term
	float lambertTerm = max(0, min(1, dot(N, -L)));

	// calculate view vector and reflection vector
	vec3 V = normalize(cameraPosition - vPosition.xyz);
	vec3 R = reflect( L, N );
	// calculate specular term
	float specularTerm = pow( max( 0, dot( R, V ) ), specularPower );

	vec3 ambient = Ia * Ka;
	vec3 diffuse = Id * Kd * lambertTerm;
	vec3 specular = Is * Ks * specularTerm;

	//output lambert as greyscale
	FragColor = vec4(ambient + diffuse + specular, 1);
}