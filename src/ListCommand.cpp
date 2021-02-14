#include "ListCommand.h"


ListCommand::ListCommand(int id, std::vector<std::shared_ptr<Command>> commands) :
	Command(id),
	m_index(0),
	m_commands(commands)
{
}
void ListCommand::reset() {
	this->m_index = 0;
}
void ListCommand::update(std::shared_ptr<Particle>& particle, ofEasyCam& easyCam, float deltaTime) {
	while (m_index < m_commands.size()) {
		m_commands.at(m_index)->update(particle, easyCam, deltaTime);
		if (m_commands.at(m_index)->isFinished()) {
			m_index++;
			deltaTime = 0;
		} else {
			break;
		}
	}
}
bool ListCommand::isFinished() {
	return m_index >= m_commands.size();
}