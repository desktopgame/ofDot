#pragma once
#ifndef LISTCOMMAND_H
#define LISTCOMMAND_H
#include "Command.h"
#include <vector>
#include <memory>

class ListCommand : public Command {
public:
	explicit ListCommand(int id, std::vector<std::shared_ptr<Command>> commands);

	void reset() override;
	void update(std::shared_ptr<Particle>& particle, float deltaTime) override;
	bool isFinished() override;
private:
	int m_index;
	std::vector<std::shared_ptr<Command>> m_commands;
};
#endif