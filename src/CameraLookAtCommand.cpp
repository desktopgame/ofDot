#include "CameraLookAtCommand.h"

CameraLookAtCommand::CameraLookAtCommand(int id, glm::vec3 position) :
	Command(id), position(position)
{
}

void CameraLookAtCommand::update(std::shared_ptr<Particle>& particle, ofEasyCam& easyCam, float deltaTime) {
	easyCam.lookAt(position);
}

bool CameraLookAtCommand::isFinished() {
	return true;
}