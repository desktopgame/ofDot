#pragma once
#ifndef CAMERALOOKATCOMMAND_H
#define CAMERALOOKATCOMMAND_H
#include "Command.h"

class CameraLookAtCommand : public Command {
public:
	explicit CameraLookAtCommand(int id, glm::vec3 position);
	void update(std::shared_ptr<Particle>& particle, ofEasyCam& easyCam, float deltaTime) override;
	bool isFinished() override;
	glm::vec3 position;
private:
};
#endif