#pragma once
#ifndef COMMANDCOMMAND_H
#define COMMANDCOMMAND_H
#include "Command.h"

class ColorCommand : public Command {
public:
	explicit ColorCommand(int id, glm::vec3 color);
	void update(std::shared_ptr<Particle>& particle, ofEasyCam& easyCam, float deltaTime) override;
	bool isFinished() override;

	glm::vec3 color;

private:
};
#endif