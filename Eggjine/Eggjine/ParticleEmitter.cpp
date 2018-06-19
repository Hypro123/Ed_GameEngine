#include "ParticleEmitter.h"



ParticleEmitter::ParticleEmitter() :
	m_particles(nullptr),
	m_firstDead(0),
	m_maxParticles(0),
	m_position(0, 0, 0),
	m_vao(0), m_vbo(0), m_ibo(0),
	m_vertexData(nullptr)
{


}


ParticleEmitter::~ParticleEmitter()
{
	delete[] m_particles;
	delete[] m_vertexData;

	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
}

void ParticleEmitter::initialise(unsigned int a_maxParticles,
	unsigned int a_emitRate,
	float a_lifetimeMin, float a_lifetimeMax,
	float a_velocityMin, float a_velocityMax,
	float a_startSize, float a_endSize,
	const glm::vec4& a_startColour, const glm::vec4& a_endColour)
{
		// set up emit timers
		m_emitTimer = 0;
		m_emitRate = 1.0f / a_emitRate;
		// store all variables passed in
		m_startColour = a_startColour;
		m_endColour = a_endColour;
		m_startSize = a_startSize;
		m_endSize = a_endSize;
		m_velocityMin = a_velocityMin;
		m_velocityMax = a_velocityMax;
		m_lifespanMin = a_lifetimeMin;
		m_lifespanMax = a_lifetimeMax;
		m_maxParticles = a_maxParticles;
		// create particle array
		m_particles = new Particle[m_maxParticles];
		m_firstDead = 0;
		// create the array of vertices for the particles
		// 4 vertices per particle for a quad.
		// will be filled during update
		m_vertexData = new ParticleVertex[m_maxParticles * 4];
		// continued next page...
		// create the index buffeer data for the particles
		// 6 indices per quad of 2 triangles
		// fill it now as it never changes
		unsigned int* indexData = new unsigned int[m_maxParticles * 6];
		for (unsigned int i = 0; i < m_maxParticles; ++i) {
			indexData[i * 6 + 0] = i * 4 + 0;
			indexData[i * 6 + 1] = i * 4 + 1;
			indexData[i * 6 + 2] = i * 4 + 2;
			indexData[i * 6 + 3] = i * 4 + 0;
			indexData[i * 6 + 4] = i * 4 + 2;
			indexData[i * 6 + 5] = i * 4 + 3;
		}
		// create opengl buffers
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ibo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_maxParticles * 4 *
			sizeof(ParticleVertex), m_vertexData,
			GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_maxParticles * 6 *
			sizeof(unsigned int), indexData, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0); // position
		glEnableVertexAttribArray(1); // colour
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
			sizeof(ParticleVertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
			sizeof(ParticleVertex), ((char*)0) + 16);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		delete[] indexData;

}

void ParticleEmitter::emit() {
	// only emit if there is a dead particle to use
	if (m_firstDead >= m_maxParticles)
		return;
	// resurrect the first dead particle
	Particle& particle = m_particles[m_firstDead++];
	// assign its starting position
	particle.position = m_position;
	// randomise its lifespan
	particle.lifetime = 0;
	particle.lifespan = (rand() / (float)RAND_MAX) *
		(m_lifespanMax - m_lifespanMin) + m_lifespanMin;
	// set starting size and colour
	particle.colour = m_startColour;
	particle.size = m_startSize;
	// randomise velocity direction and strength
	float velocity = (rand() / (float)RAND_MAX) *
		(m_velocityMax - m_velocityMin) + m_velocityMin;
	particle.velocity.x = (rand() / (float)RAND_MAX) * 2 - 1;
	particle.velocity.y = (rand() / (float)RAND_MAX) * 2 - 1;
	particle.velocity.z = (rand() / (float)RAND_MAX) * 2 - 1;
	particle.velocity = glm::normalize(particle.velocity) *
		velocity;
}