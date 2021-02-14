#include "ScaleCommand.h"

ScaleCommand::ScaleCommand(int id, glm::vec3 scale) : Command(id), scale(scale) {

}

void ScaleCommand::update(std::shared_ptr<Particle>& particle, ofEasyCam& easyCam, float deltaTime) {
	particle->scale(id, scale);
}

bool ScaleCommand::isFinished() {
	return true;
}