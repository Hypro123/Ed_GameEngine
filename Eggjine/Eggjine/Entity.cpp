#include "Entity.h"



Entity::Entity()
{
	m_parent = nullptr;
	
	localMatrix = glm::mat4(1);
	globalMatrix = glm::mat4(1);
}


Entity::~Entity()
{
	if(m_children.size() > 0)
	{
		for(int i = 0; i < m_children.size(); i++)
		{
			delete m_children[i];
		}
	}
}

void Entity::UpdateGlobalTransforms()
{
	if(m_parent != nullptr)
	{
		globalMatrix = m_parent->globalMatrix * localMatrix;
	}
	else
	{
		globalMatrix = localMatrix;
	}
	for(int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->UpdateGlobalTransforms();
	}
}