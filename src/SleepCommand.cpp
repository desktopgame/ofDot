#include "SleepCommand.h"

SleepCommand::SleepCommand(int id, float s) : Command(id), s(s), m_elapsed(0) {

}

void SleepCommand::update(std::shared_ptr<Particle>& particle, float deltaTime) {
	m_elapsed += deltaTime;
}
bool SleepCommand::isFinished() {
	return m_elapsed >= s;
}