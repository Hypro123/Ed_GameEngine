#include "Mesh.h"
#include<glCore\gl_core_4_5.h>

Mesh* Mesh::m_singleton = nullptr;

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::Create()
{
	if(m_singleton == nullptr)
		m_singleton = new Mesh();
}

void Mesh::Destroy()
{
	delete m_singleton;
	m_singleton = nullptr;
}

void Mesh::initialise(unsigned int vertexCount, const Vertex* verticies, unsigned int indexCount, unsigned int* indicies)
{
	assert(vao == 0);

	//gen buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	//bind vertex array, mesh wrapper
	glBindVertexArray(vao);

	//bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), verticies, GL_STATIC_DRAW);

	//enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// enable second element as normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)16);

	// enable third element as texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

	//bind indicies if there are any
	if (indexCount != 0)
	{
		glGenBuffers(1, &ibo);

		//bind vertex buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		//fill vertex buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indicies, GL_STATIC_DRAW);

		//divide by 3 in order to get triangle amount
		triCount = indexCount / 3;
	}
	else
	{
		triCount = vertexCount / 3;
	}
	//unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::initialiseFullscreenQuad()
{
	assert(vao == 0);
	// generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	// bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);
	// bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// define vertices
	float vertices[] = {
		-1,1, // left top
		-1,-1, // left bottom
		1,1, // right top
		-1,-1, // left bottom
		1,-1, // right bottom
		1, 1 // right top
	};
	// fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices,
		GL_STATIC_DRAW);
	// enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, 0);
	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// quad has 2 triangles
	triCount = 2;
}

void Mesh::draw()
{
	glBindVertexArray(vao);
	//indicies or vertiicies
	if (ibo != 0)
		glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
}

void Mesh::initialiseQuad()
{
	// check that the mesh is not initialized already
	assert(vao == 0);
	// generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	// bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);
	// bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// define 6 vertices for 2 triangles
	Vertex vertices[6];
	vertices[0].Position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].Position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].Position = { -0.5f, 0, -0.5f, 1 };
	vertices[3].Position = { -0.5f, 0, -0.5f, 1 };
	vertices[4].Position = { 0.5f, 0, 0.5f, 1 };
	vertices[5].Position = { 0.5f, 0, -0.5f, 1 };
	
	vertices[0].Normal = {0, 1, 0, 0};
	vertices[1].Normal = { 0, 1, 0, 0 };
	vertices[2].Normal = { 0, 1, 0, 0 };
	vertices[3].Normal = { 0, 1, 0, 0 };
	vertices[4].Normal = { 0, 1, 0, 0 };
	vertices[5].Normal = { 0, 1, 0, 0 };

	vertices[0].TexCoord = { 0, 1 }; // bottom left
	vertices[1].TexCoord = { 1, 1 }; // bottom right
	vertices[2].TexCoord = { 0, 0 }; // top left
	vertices[3].TexCoord = { 0, 0 }; // top left
	vertices[4].TexCoord = { 1, 1 }; // bottom right
	vertices[5].TexCoord = { 1, 0 }; // top right

	// fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex),
		vertices, GL_STATIC_DRAW);
	// enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	
	// enable second element as normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)16);

	// enable third element as texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);
	
	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// quad has 2 triangles
	triCount = 2;
}

void Mesh::drawBox(glm::vec3 center, glm::vec3 extents, glm::vec4 colour, glm::mat4* m)
{
	Vertex verts[8];
	glm::vec3 c = center;
	
	//extents
	glm::vec3 vX(extents.x, 0, 0);
	glm::vec3 vY(0, extents.y, 0);
	glm::vec3 vZ(0, 0, extents.z);

	if (m != nullptr)
	{
		vX = glm::vec3((*m * glm::vec4(vX, 0)));
		vY = glm::vec3((*m * glm::vec4(vX, 0)));
		vZ = glm::vec3((*m * glm::vec4(vX, 0)));
		c = glm::vec3(glm::vec3((*m)[3]) + c);
	}

	verts[0].Position = glm::vec4(glm::vec3(extents.x / 2, -extents.y / 2, extents.z / 2), 1);
	verts[1].Position = glm::vec4(glm::vec3(extents.x / 2, -extents.y / 2, -extents.z / 2), 1);
	verts[2].Position = glm::vec4(glm::vec3(-extents.x / 2, -extents.y / 2, -extents.z / 2), 1);
	verts[3].Position = glm::vec4(glm::vec3(-extents.x / 2, -extents.y / 2, extents.z / 2), 1);
	verts[4].Position = glm::vec4(glm::vec3(extents.x / 2, extents.y / 2, extents.z / 2), 1);
	verts[5].Position = glm::vec4(glm::vec3(extents.x / 2, extents.y / 2, -extents.z / 2), 1);
	verts[6].Position = glm::vec4(glm::vec3(-extents.x / 2, extents.y / 2, -extents.z / 2), 1);
	verts[7].Position = glm::vec4(glm::vec3(-extents.x / 2, extents.y / 2, extents.z / 2), 1);

	unsigned int indicies[36] = { 
		0, 1, 2, 2, 0, 3,
		0, 3, 7, 7, 0, 4,
		7, 6, 5, 5, 7, 4,
		3, 7, 2, 2, 7, 6,
		0, 1, 5, 5, 0, 4,
		6, 5, 1, 1, 6, 2
	};
	initialise(8, verts, 36, indicies);
}

//incomplete
void Mesh::drawCylinder(glm::vec3 center, float radius, float height, int segments, glm::vec4 colour, glm::mat4* m)
{
	meshData retdat1 = getCircleStruct(glm::vec4(center.x, center.y + height/2, center.z, 1), radius, segments, colour);
	meshData retdat2 = getCircleStruct(glm::vec4(center.x, center.y + -height/2, center.z, 1), radius, segments, colour);

	unsigned int* indicies = new unsigned int[retdat1.indiciCount + retdat2.indiciCount];
	unsigned int indCount = retdat1.indiciCount + retdat2.indiciCount ;
	

	Vertex* verts = new Vertex[retdat1.vertAmount + retdat2.vertAmount];
	unsigned int vertCount = retdat1.vertAmount + retdat2.vertAmount;

	//indicies
	for(int i = 0; i < retdat1.indiciCount; i++)
	{
		indicies[i] = retdat1.indicies[i];
	}
	for(int i = (retdat1.indiciCount); i < indCount; i++)
	{
		indicies[i] = retdat2.indicies[i - retdat2.indiciCount] + segments + 1;
	}

	//verticies
	for(int i = 0; i < retdat1.vertAmount; i++)
	{
		verts[i] = retdat1.v[i];
	}
	for(int i = retdat1.vertAmount; i < vertCount; i++)
	{
		verts[i] = retdat2.v[i - retdat2.vertAmount];
	}

	initialise(vertCount, verts, indCount, indicies);
}

meshData Mesh::getCircleStruct(glm::vec3 center, float radius, int segments, glm::vec4 colour)
{
	int vertAmount = segments + 1;
	Vertex* verts = new Vertex[vertAmount];

	unsigned int* indicies;

	int count = segments * 3 + 1;
	indicies = new unsigned int[count];

	int tempValue = 0;
	


	for (int i = 0; i < vertAmount; i++)
	{
		verts[i].Position = glm::vec4(center, 1);
		verts[i].Normal = glm::vec4(0.0f, 0.0f, 0.0f, 1);
		verts[i].TexCoord = glm::vec2(0.0f, 0.0f);
	}


	//initialisation
	for (int i = 0; i < count; ++i)
	{
		indicies[i] = 0;
	}

	for (int i = 1; i < vertAmount; i++)
	{
		verts[i].Position = glm::vec4(sinf((2 * glm::pi<float>()) / segments * i) * radius, center.y, cosf((2 * glm::pi<float>()) / segments * i) * radius, 1);
	}

	//segments(works)
	for (int i = 1; i < count; i++)
	{
		if ((i % 3) == 0)
		{
			indicies[i] = 0;
			tempValue += 2;
		}
		else
		{
			indicies[i] = (i - tempValue);
			indicies[i + 1] = indicies[i] + 1;
		}

		if (indicies[i] > segments)
			indicies[i] = indicies[1];
	}

	count--;

	meshData retData;
	retData.indiciCount = count;
	retData.indicies = indicies;
	retData.v = verts;
	retData.vertAmount = vertAmount;

	return retData;
}