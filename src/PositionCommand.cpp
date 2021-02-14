#include "PositionCommand.h"

PositionCommand::PositionCommand(int id, glm::vec3 position) : Command(id), position(position) {

}

void PositionCommand::update(std::shared_ptr<Particle>& particle, ofEasyCam& easyCam, float deltaTime) {
	particle->position(id, position);
}

bool PositionCommand::isFinished() {
	return true;
}