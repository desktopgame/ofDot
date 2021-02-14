#pragma once
#ifndef CAMERAPOSITIONCOMMAND_H
#define CAMERAPOSITIONCOMMAND_H
#include "Command.h"

class CameraPositionCommand : public Command {
public:
	explicit CameraPositionCommand(int id, glm::vec3 position);
	void update(std::shared_ptr<Particle>& particle, ofEasyCam& easyCam, float deltaTime) override;
	bool isFinished() override;
	glm::vec3 position;
private:
};
#endif