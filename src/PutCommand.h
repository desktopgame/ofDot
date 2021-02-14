#pragma once
#ifndef PUTCOMMAND_H
#define PUTCOMMAND_H
#include "Command.h"
#include <ofVec3f.h>

class PutCommand : public Command {
public:
	explicit PutCommand(int id, glm::vec3 position, glm::vec3 scale, glm::vec3 color);

	void update(std::shared_ptr<Particle>& particle, float deltaTime) override;
	bool isFinished() override;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 color;
private:
};
#endif