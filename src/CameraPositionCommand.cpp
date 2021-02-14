#include "CameraPositionCommand.h"

CameraPositionCommand::CameraPositionCommand(int id, glm::vec3 position) :
	Command(id), position(position)
{
}

void CameraPositionCommand::update(std::shared_ptr<Particle>& particle, ofEasyCam& easyCam, float deltaTime) {
	easyCam.setPosition(position);
}

bool CameraPositionCommand::isFinished() {
	return true;
}