#pragma once
#ifndef SLEEPCOMMAND_H
#define SLEEPCOMMAND_H
#include "Command.h"

class SleepCommand : public Command {
public:
	explicit SleepCommand(int id, float s);
	void update(std::shared_ptr<Particle>& particle, ofEasyCam& easyCam, float deltaTime) override;
	bool isFinished() override;
	float s;
private:
	float m_elapsed;
};
#endif