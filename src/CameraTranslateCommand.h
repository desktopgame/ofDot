#pragma once
#ifndef CAMERATRANSLATENCOMMAND_H
#define CAMERATRANSLATENCOMMAND_H
#include "Command.h"

class CameraTranslateCommand : public Command {
public:
	explicit CameraTranslateCommand(int id, glm::vec3 offset);
	void update(std::shared_ptr<Particle>& particle, ofEasyCam& easyCam, float deltaTime) override;
	bool isFinished() override;
	glm::vec3 offset;
private:
};
#endif