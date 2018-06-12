#ifndef __MESH_H_
#define __MESH_H_
#include<ext.hpp>

struct Vertex
{
	glm::vec4 Position;
	glm::vec4 Normal;
	glm::vec2 TexCoord;
};

struct meshData
{
	Vertex* v;
	int vertAmount;
 	unsigned int * indicies;
	int indiciCount;
};

class Mesh
{
public:
	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) { m_singleton = nullptr; }
	virtual ~Mesh();

	static void Create();
	static void Destroy();

	void initialise(unsigned int vertexCount, const Vertex* verticies, unsigned int indexCount = 0, unsigned int* indicies = nullptr);
	void initialiseFullscreenQuad();
	void initialiseQuad();

	void draw();

	void drawBox(glm::vec3 center, glm::vec3 extents, glm::vec4 colour, glm::mat4* m = nullptr);
	void drawCylinder(glm::vec3 center, float radius, float height, int segments, glm::vec4 colour, glm::mat4* m = nullptr);
	void drawPyramid();
	void drawSphere();
	void drawCone();
	void drawGrid();

	//circle
	meshData getCircleStruct(glm::vec3 center, float radius, int segments, glm::vec4 colour);

protected:
	unsigned int triCount;
	unsigned int vao, vbo, ibo;

	static Mesh* m_singleton;
};

#endif