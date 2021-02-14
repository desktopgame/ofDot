#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
	ofGLFWWindowSettings setting;
	setting.setSize(1024, 768);
	setting.setGLVersion(4, 5);

	auto app = std::make_shared<ofApp>();
	ofRunApp(ofCreateWindow(setting), app);
	ofRunMainLoop();
}
