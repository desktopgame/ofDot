#pragma once
#ifndef POSITIONCOMMAND_H
#define POSITIONCOMMAND_H
#include "Command.h"

class PositionCommand : public Command {
public:
	explicit PositionCommand(int id, glm::vec3 position);
	void update(std::shared_ptr<Particle>& particle, ofEasyCam& easyCam, float deltaTime) override;
	bool isFinished() override;

	glm::vec3 position;

private:
};
#endif