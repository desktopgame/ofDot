#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "Scene.h"

class ofApp : public ofBaseApp{

	public:
		explicit ofApp();
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	private:
		ofMesh m_sphereMesh;
		std::shared_ptr<Particle> m_sphereParticle;
		Scene m_scene;

		ofEasyCam m_easyCam;
		ofShader m_shader;
		bool m_init;
		int m_frames;
};

void onError(unsigned int source, unsigned int type,
	unsigned int id, unsigned int severity,
	int length, const char* message,
	const void* userParam);