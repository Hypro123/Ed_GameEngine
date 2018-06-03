#include "Planetoid.h"

Planetoid::Planetoid(glm::mat4 myData, glm::vec4 c, float rad)
{
	globalMatrix = myData;
	colour = c;
	mSize = rad;
	
}


Planetoid::~Planetoid()
{
}

void Planetoid::updatePlanetoid(float deltaTime)
{
	UpdateGlobalTransforms();
}

void Planetoid::drawPlanetoid()
{
	aie::Gizmos::addSphere(glm::vec3(0), mSize, 10, 10, colour, &globalMatrix);
}