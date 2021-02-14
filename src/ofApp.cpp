#include "ofApp.h"
#include <vector>
#include <ctime>

ofApp::ofApp() :
	m_sphereMesh(ofMesh::sphere(0.1f, 12, ofPrimitiveMode::OF_PRIMITIVE_TRIANGLES)),
	m_easyCam(),
	m_shader(),
	m_init(false)
{
}

//--------------------------------------------------------------
void ofApp::setup() {
#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(reinterpret_cast<GLDEBUGPROC>(onError), 0);
#endif
	::srand((unsigned int)::time(NULL));
	this->m_sphereParticle = std::make_shared<Particle>(m_sphereMesh, GL_TRIANGLES);
	for (int x = -10; x < 10; x++) {
		for (int y = -10; y < 10; y++) {
			for (int z = -10; z < 10; z++) {
				double min = 0.0;
				double max = 1.0;
				float r = static_cast<float>(min + (rand() * (max - min + 1.0) / (1.0 + RAND_MAX)));
				float g = static_cast<float>(min + (rand() * (max - min + 1.0) / (1.0 + RAND_MAX)));
				float b = static_cast<float>(min + (rand() * (max - min + 1.0) / (1.0 + RAND_MAX)));
				if (x == -10 || y == -10 || z == -10 || x == 9 || y == 9 || z == 9) {
					r = g = b = 0.0f;
				}
				m_sphereParticle->emit(
					glm::vec3(x, y, z),
					glm::vec3(1, 1, 1),
					glm::vec3(r, g, b)
				);
			}
		}
	}

	if (!m_shader.load("dots.vert", "dots.frag")) {
		::abort();
	}
	m_easyCam.setPosition(glm::vec3(0, 0, -10));
	m_easyCam.lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	this->m_init = true;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	if (!m_init) {
		return;
	}
	m_shader.begin();
	m_easyCam.begin();
	m_sphereParticle->draw();
	//m_sphereVbo.drawElementsInstanced(GL_TRIANGLES, m_amt, m_xSize * m_ySize);
	m_easyCam.end();
	m_shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void onError(unsigned int source, unsigned int type,
	unsigned int id, unsigned int severity,
	int length, const char* message,
	const void* userParam) {
	std::cerr << message << std::endl;
}