#include "CameraTranslateCommand.h"

CameraTranslateCommand::CameraTranslateCommand(int id, glm::vec3 offset) :
	Command(id), offset(offset)
{
}

void CameraTranslateCommand::update(std::shared_ptr<Particle>& particle, ofEasyCam& easyCam, float deltaTime) {
	easyCam.move(offset);
}

bool CameraTranslateCommand::isFinished() {
	return true;
}