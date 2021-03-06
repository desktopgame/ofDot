#pragma once
#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H
#include <memory>
#include <vector>
#include <ofEasyCam.h>

class Command;
class Particle;
class CommandQueue {
public:
	explicit CommandQueue();
	void submit(std::shared_ptr<Command>& cmd);
	void update(std::shared_ptr<Particle>& particle, ofEasyCam& easyCam, float deltaTime);

private:
	std::vector<std::shared_ptr<Command>> m_commands;
	int m_offset;
	int m_maxId;
};
#endif