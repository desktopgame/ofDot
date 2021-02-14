#include "CommandQueue.h"
#include "Command.h"

CommandQueue::CommandQueue() :
	m_commands(),
	m_offset(0),
	m_maxId(-1)
{
}

void CommandQueue::submit(std::shared_ptr<Command>& cmd) {
	m_commands.emplace_back(cmd);
	if (m_maxId < cmd->id) {
		m_maxId = cmd->id;
	}
}

void CommandQueue::update(std::shared_ptr<Particle>& particle, float deltaTime) {
	if (m_offset >= m_commands.size()) {
		return;
	}
	particle->reserve(m_maxId + 1);
	while (m_offset < m_commands.size()) {
		m_commands.at(m_offset)->update(particle, deltaTime);
		if (m_commands.at(m_offset)->isFinished()) {
			m_offset++;
			deltaTime = 0;
		} else {
			break;
		}
	}
}