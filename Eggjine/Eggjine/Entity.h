#ifndef _ENTITY_H_
#define _ENTITY_H_

#include<ext.hpp>
#include<vector>

class Entity
{
public:
	Entity();
	~Entity();

	void UpdateGlobalTransforms();

	void setParent(Entity* sParent) { m_parent = sParent; }
	void setChild(Entity* sChild) { m_children.push_back(sChild); }

	glm::mat4 localMatrix;
	glm::mat4 globalMatrix;
protected:
	Entity * m_parent;
	std::vector<Entity*> m_children;
};

#endif