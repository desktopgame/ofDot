#include "Scene.h"
#include <ofFileUtils.h>
#include "PutCommand.h"
#include "PositionCommand.h"
#include "ScaleCommand.h"
#include "ColorCommand.h"
#include "SleepCommand.h"
#include "ListCommand.h"
#include "ParallelCommand.h"
#include "CameraPositionCommand.h"
#include "CameraLookAtCommand.h"

Scene::Scene(const std::string& filename) :
	m_filename(filename),
	m_text(),
	m_commandQueueVec()
{

}
bool Scene::refresh() {
	ofFile file(m_filename);
	if (!file.exists()) {
		return false;
	}
	std::vector<std::string> linesOfTheFile;
	ofBuffer buffer = ofBufferFromFile(file);
	std::string newText = buffer;
	if (m_text == newText) {
		return false;
	}
	ofJson json = ofJson::parse(newText);
	m_commandQueueVec.clear();
	if (json.find("queues") == json.end()) {
		return false;
	}
	ofJson& queues = json["queues"];
	for (int i = 0; i < static_cast<int>(queues.size()); i++) {
		ofJson& queue = queues.at(i);
		if (queue.find("commands") == queue.end()) {
			continue;
		}
		CommandQueue cmdQueue;
		ofJson& commands = queue["commands"];
		for (int j = 0; j < static_cast<int>(commands.size()); j++) {
			ofJson& cmd = commands.at(j);
			cmdQueue.submit(parseCommandRec(cmd));
		}
		m_commandQueueVec.emplace_back(cmdQueue);
	}
	this->m_text = newText;
	std::cout << "reloaded." << std::endl;
	return true;
}

void Scene::update(std::shared_ptr<Particle> particle, ofEasyCam& easyCam, float deltaTime) {
	for (auto& cmdQueue : m_commandQueueVec) {
		cmdQueue.update(particle, easyCam, deltaTime);
	}
}
// private
std::shared_ptr<Command> Scene::parseCommandRec(ofJson& json) {
	if (json.contains("name") && json["name"].get<std::string>() == "list") {
		std::vector<std::shared_ptr<Command>> commands;
		ofJson& list = json["list"];
		for (int k = 0; k < static_cast<int>(list.size()); k++) {
			auto cmdInst = parseCommandRec(list.at(k));
			if (cmdInst) {
				commands.emplace_back(cmdInst);
			}
		}
		return std::make_shared<ListCommand>(0, commands);
	} else if(json.contains("name") && json["name"].get<std::string>() == "parallel") {
		std::vector<std::shared_ptr<Command>> commands;
		ofJson& list = json["list"];
		for (int k = 0; k < static_cast<int>(list.size()); k++) {
			auto cmdInst = parseCommandRec(list.at(k));
			if (cmdInst) {
				commands.emplace_back(cmdInst);
			}
		}
		return std::make_shared<ParallelCommand>(0, commands);
	} else {
		return parseCommand(json);
	}
}
std::shared_ptr<Command> Scene::parseCommand(ofJson& json) {
	if (!json.contains("name")) {
		return nullptr;
	}
	std::string name = json["name"].get<std::string>();
	std::string targetName = name;
	std::shared_ptr<Command> ret = nullptr;
	int id = json.contains("id") ? json["id"].get<int>() : -1;
	id++;
	glm::vec3 pos = parseVec3(json["position"], "x", "y", "z");
	glm::vec3 scale = parseVec3(json["scale"], "x", "y", "z");
	glm::vec3 color = parseVec3(json["color"], "x", "y", "z");
	if (targetName == "dot") {
		ret = std::make_shared<PutCommand>(id,pos,scale,color);
	} else if (targetName == "position") {
		ret = std::make_shared<PositionCommand>(id, pos);
	} else if (targetName == "scale") {
		ret = std::make_shared<ScaleCommand>(id, scale);
	} else if (targetName == "color") {
		ret = std::make_shared<ColorCommand>(id, color);
	} else if (targetName == "sleep") {
		ret = std::make_shared<SleepCommand>(0, json["s"].get<float>());
	} else if (targetName == "cameraPosition") {
		ret = std::make_shared<CameraPositionCommand>(0, pos);
	} else if (targetName == "cameraLookAt") {
		ret = std::make_shared<CameraLookAtCommand>(0, pos);
	}
	return ret;
}
glm::vec3 Scene::parseVec3(ofJson& json, std::string xKey, std::string yKey, std::string zKey) {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	if (json.contains(xKey)) {
		x = json[xKey].get<float>();
	}
	if (json.contains(yKey)) {
		y = json[yKey].get<float>();
	}
	if (json.contains(zKey)) {
		z = json[zKey].get<float>();
	}
	return glm::vec3(x, y, z);
}