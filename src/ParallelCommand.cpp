#include "ParallelCommand.h"


ParallelCommand::ParallelCommand(int id, std::vector<std::shared_ptr<Command>> commands)
	: Command(id), m_commands(commands)
{
}
void ParallelCommand::update(std::shared_ptr<Particle>& particle, float deltaTime) {
	for (auto cmd : m_commands) {
		if (!cmd->isFinished()) {
			cmd->update(particle, deltaTime);
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