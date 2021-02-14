#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H
#include <ofMesh.h>
#include <ofVbo.h>
#include <ofBufferObject.h>
#include <vector>

class Particle {
public:
	static const int k_positionIndex;
	static const int k_scaleIndex;
	static const int k_colorIndex;
	explicit Particle(ofMesh& mesh, int drawMode);

	void emit(glm::vec3 position, glm::vec3 scale, glm::vec3 color);
	void compile();
	void clear();
	void draw();
private:
	ofMesh& m_mesh;
	int m_drawMode;
	ofVbo m_vbo;
	ofBufferObject m_positionBO;
	ofBufferObject m_scaleBO;
	ofBufferObject m_colorBO;
	std::vector<glm::vec3> m_positionVec;
	std::vector<glm::vec3> m_scaleVec;
	std::vector<glm::vec3> m_colorVec;
	int m_amt;
	bool m_dirty;
};
#endif