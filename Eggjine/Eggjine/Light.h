#ifndef __LIGHT_H_
#define __LIGHT_H_

#include"ext.hpp"

struct Light
{
	glm::vec3 direction;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

#endif