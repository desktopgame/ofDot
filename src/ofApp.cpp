#include "ofApp.h"
#include <vector>
#include <ctime>

ofApp::ofApp() :
	m_sphereMesh(ofMesh::sphere(0.1f, 12, ofPrimitiveMode::OF_PRIMITIVE_TRIANGLES)),
	m_sphereParticle(),
	m_scene("dots.json"),
	m_easyCam(),
	m_shader(),
	m_frames(0),
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
	m_sphereParticle = std::make_shared<Particle>(m_sphereMesh, GL_TRIANGLES);
	m_scene.refresh();
	if (!m_shader.load("dots.vert", "dots.frag")) {
		::abort();
	}
	m_easyCam.setPosition(glm::vec3(0, 0, -10));
	m_easyCam.lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	this->m_init = true;
}

//--------------------------------------------------------------
void ofApp::update() {
	if (m_frames++ >= 60) {
		if (m_scene.refresh()) {
			m_sphereParticle->clear();
		}
		m_frames = 0;
	}
	m_scene.update(m_sphereParticle, static_cast<float>(ofGetLastFrameTime()));
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