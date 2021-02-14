#include "ColorCommand.h"

ColorCommand::ColorCommand(int id, glm::vec3 color) : Command(id), color(color) {

}

void ColorCommand::update(std::shared_ptr<Particle>& particle, float deltaTime) {
	particle->color(id, color);
}

bool ColorCommand::isFinished() {
	return true;
}