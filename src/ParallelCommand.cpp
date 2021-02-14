#include "ParallelCommand.h"


ParallelCommand::ParallelCommand(int id, std::vector<std::shared_ptr<Command>> commands)
	: Command(id), m_commands(commands)
{
}
void ParallelCommand::reset() {
	for (auto cmd : m_commands) {
		cmd->reset();
	}
}
void ParallelCommand::update(std::shared_ptr<Particle>& particle, ofEasyCam& easyCam, float deltaTime) {
	for (auto cmd : m_commands) {
		if (!cmd->isFinished()) {
			cmd->update(particle, easyCam, deltaTime);
		}
	}
}
bool ParallelCommand::isFinished() {
	for (auto cmd : m_commands) {
		if (!cmd->isFinished()) {
			return false;
		}
	}
	return true;
}