#pragma once
#ifndef SCENE_H
#define SCENE_H
#include <memory>
#include <vector>
#include <string>
#include <ofJson.h>
#include "CommandQueue.h"

class Particle;
class Scene {
public:
	explicit Scene(const std::string& filename);

	void rehash();
	void update(std::shared_ptr<Particle> particle, float deltaTime);
private:
	static std::shared_ptr<Command> parseCommand(ofJson& json);
	static glm::vec3 parseVec3(ofJson& json, std::string xKey, std::string yKey, std::string zKey);
	std::string m_filename;
	std::string m_text;
	std::vector<CommandQueue> m_commandQueueVec;
};
#endif