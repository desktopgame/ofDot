#pragma once
#ifndef COMMAND_H
#define COMMAND_H
#include <memory>
#include <ofEasyCam.h>
#include "Particle.h"

class Command {
public:
	explicit Command(int id);
	virtual ~Command() = default;

	virtual void reset();
	virtual void update(std::shared_ptr<Particle>& particle, ofEasyCam& easyCam, float deltaTime) = 0;
	virtual bool isFinished() = 0;
	const int id;
private:
};
#endif