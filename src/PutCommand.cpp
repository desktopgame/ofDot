#include "PutCommand.h"

PutCommand::PutCommand(int id, glm::vec3 position, glm::vec3 scale, glm::vec3 color)
:
	Command(id),
	position(position),
	scale(scale),
	color(color)
{
}

void PutCommand::update(std::shared_ptr<Particle>& particle, ofEasyCam& easyCam, float deltaTime) {
	particle->update(id, position, scale, color);
}

bool PutCommand::isFinished() {
	return true;
}