#ifndef __PLANETOID_H_
#define __PLANETOID_H_

#include<ext.hpp>
#include"Gizmos.h"
#include"Entity.h"

//Class made for easy creation of planetoid objects
class Planetoid : public Entity
{
public:
	Planetoid(glm::mat4 mat, glm::vec4 c, float rad);
	~Planetoid();

	glm::mat4 getTransform() { return globalMatrix; }
	void setTransformData(glm::mat4 m4) { globalMatrix = m4; }

	void setColour(glm::vec4 c) { colour = c; }
	glm::vec4 getColour() { return colour; }

	glm::vec3 getPosition()
	{
		return globalMatrix[3];
	}
	void setPosition(glm::vec3 p)
	{
		localMatrix[3][0] = p.x;
		localMatrix[3][1] = p.y;
		localMatrix[3][2] = p.z;
	}

	float getSize() { return mSize; }
	void setSize(float s) { mSize = s; }

	void drawPlanetoid();
	void updatePlanetoid(float deltaTime);

protected:
	glm::vec4 colour;
	float mSize;
};

#endif