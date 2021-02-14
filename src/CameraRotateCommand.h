#pragma once
#ifndef CAMERAROTATECOMMAND_H
#define CAMERAROTATECOMMAND_H
#include "Command.h"

class CameraRotateCommand : public Command {
public:
	explicit CameraRotateCommand(int id, glm::vec3 point, float radian);
	void update(std::shared_ptr<Particle>& particle, ofEasyCam& easyCam, float deltaTime) override;
	bool isFinished() override;
	glm::vec3 point;
	float radian;
private:
};
#endif