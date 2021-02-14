#pragma once
#ifndef SCALECOMMAND_H
#define SCALECOMMAND_H
#include "Command.h"

class ScaleCommand : public Command {
public:
	explicit ScaleCommand(int id, glm::vec3 scale);
	void update(std::shared_ptr<Particle>& particle, float deltaTime) override;
	bool isFinished() override;

	glm::vec3 scale;

private:
};
#endif