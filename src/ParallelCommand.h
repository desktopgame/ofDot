#pragma once
#ifndef PARALLELCOMMAND_H
#define PARALLELCOMMAND_H
#include "Command.h"
#include <memory>
#include <vector>

class ParallelCommand : public Command {
public:
	explicit ParallelCommand(int id, std::vector<std::shared_ptr<Command>> commands);
	void reset() override;
	void update(std::shared_ptr<Particle>& particle, ofEasyCam& easyCam, float deltaTime) override;
	bool isFinished() override;
private:
	std::vector<std::shared_ptr<Command>> m_commands;
};
#endif