#include "Particle.h"

const int Particle::k_positionIndex = 5;
const int Particle::k_scaleIndex = 6;
const int Particle::k_colorIndex = 7;

Particle::Particle(ofMesh& mesh, int drawMode) :
	m_mesh(mesh),
	m_drawMode(drawMode),
	m_vbo(),
	m_positionBO(),
	m_scaleBO(),
	m_colorBO(),
	m_positionVec(),
	m_scaleVec(),
	m_colorVec(),
	m_amt(),
	m_dirty(false),
	m_bufferAssigned(false)
{
	auto& vb = m_mesh.getVertices();
	auto& ib = m_mesh.getIndices();
	m_amt = ib.size();
	m_vbo.setVertexData(vb.data(), vb.size(), GL_STATIC_DRAW);
	m_vbo.setAttributeDivisor(0, 0);
	m_vbo.setIndexData(ib.data(), ib.size(), GL_STATIC_DRAW);
}

void Particle::emit(glm::vec3 position, glm::vec3 scale, glm::vec3 color) {
	m_positionVec.emplace_back(position);
	m_scaleVec.emplace_back(scale);
	m_colorVec.emplace_back(color);
	this->m_dirty = true;
}

void Particle::update(int i, glm::vec3 position, glm::vec3 scale, glm::vec3 color) {
	bufferAssign();
	m_positionVec[i] = position;
	m_scaleVec[i] = scale;
	m_colorVec[i] = color;
	m_vbo.getAttributeBuffer(5).updateData(sizeof(glm::vec3) * i, sizeof(glm::vec3), &position.x);
	m_vbo.getAttributeBuffer(6).updateData(sizeof(glm::vec3) * i, sizeof(glm::vec3), &scale.x);
	m_vbo.getAttributeBuffer(7).updateData(sizeof(glm::vec3) * i, sizeof(glm::vec3), &color.x);
}

void Particle::position(int i, glm::vec3 position) {
	bufferAssign();
	m_positionVec[i] = position;
	m_vbo.getAttributeBuffer(5).updateData(sizeof(glm::vec3) * i, sizeof(glm::vec3), &position.x);
}

void Particle::scale(int i, glm::vec3 scale) {
	bufferAssign();
	m_scaleVec[i] = scale;
	m_vbo.getAttributeBuffer(6).updateData(sizeof(glm::vec3) * i, sizeof(glm::vec3), &scale.x);
}

void Particle::color(int i, glm::vec3 color) {
	bufferAssign();
	m_colorVec[i] = color;
	m_vbo.getAttributeBuffer(7).updateData(sizeof(glm::vec3) * i, sizeof(glm::vec3), &color.x);
}

void Particle::reserve(int size) {
	if (size < m_positionVec.size()) {
		return;
	}
	while (m_positionVec.size() < size) {
		m_positionVec.emplace_back(glm::vec3(0, 0, 0));
	}
	while (m_scaleVec.size() < size) {
		m_scaleVec.emplace_back(glm::vec3(0, 0, 0));
	}
	while (m_colorVec.size() < size) {
		m_colorVec.emplace_back(glm::vec3(0, 0, 0));
	}
	this->m_dirty = true;
}

void Particle::flush() {
	this->m_dirty = false;
}

void Particle::compile() {
	if (!this->m_dirty) {
		return;
	}
	this->m_dirty = false;
	// バッファの更新
	if (!m_positionBO.isAllocated()) {
		m_positionBO.allocate();
	}
	if (!m_scaleBO.isAllocated()) {
		m_scaleBO.allocate();
	}
	if (!m_colorBO.isAllocated()) {
		m_colorBO.allocate();
	}
	m_positionBO.setData(m_positionVec, GL_STATIC_DRAW);
	m_scaleBO.setData(m_scaleVec, GL_STATIC_DRAW);
	m_colorBO.setData(m_colorVec, GL_STATIC_DRAW);
	// バッファの割り当て
	m_bufferAssigned = true;
	const float stride = sizeof(float) * 3;
	m_vbo.setAttributeBuffer(k_positionIndex, m_positionBO, 3, stride);
	m_vbo.setAttributeDivisor(k_positionIndex, 1);

	m_vbo.setAttributeBuffer(k_scaleIndex, m_scaleBO, 3, stride);
	m_vbo.setAttributeDivisor(k_scaleIndex, 1);

	m_vbo.setAttributeBuffer(k_colorIndex, m_colorBO, 3, stride);
	m_vbo.setAttributeDivisor(k_colorIndex, 1);
}

void Particle::clear() {
	m_positionVec.clear();
	m_scaleVec.clear();
	m_colorVec.clear();
	this->m_dirty = true;
}

void Particle::draw() {
	compile();
	m_vbo.drawElementsInstanced(GL_TRIANGLES, m_amt, m_positionVec.size());
}
// private
void Particle::bufferAssign() {
	if (m_bufferAssigned) {
		return;
	}
	m_bufferAssigned = true;
	// バッファの割り当て
	const float stride = sizeof(float) * 3;
	m_vbo.setAttributeBuffer(k_positionIndex, m_positionBO, 3, stride);
	m_vbo.setAttributeDivisor(k_positionIndex, 1);

	m_vbo.setAttributeBuffer(k_scaleIndex, m_scaleBO, 3, stride);
	m_vbo.setAttributeDivisor(k_scaleIndex, 1);

	m_vbo.setAttributeBuffer(k_colorIndex, m_colorBO, 3, stride);
	m_vbo.setAttributeDivisor(k_colorIndex, 1);
}