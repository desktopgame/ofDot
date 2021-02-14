#include "CameraRotateCommand.h"

CameraRotateCommand::CameraRotateCommand(int id, glm::vec3 point, float radian) :
	Command(id), point(point), radian(radian)
{
}

void CameraRotateCommand::update(std::shared_ptr<Particle>& particle, ofEasyCam& easyCam, float deltaTime) {
	easyCam.rotateRad(radian, point);
}

bool CameraRotateCommand::isFinished() {
	return true;
}