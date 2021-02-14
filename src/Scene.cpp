#include "Scene.h"
#include <ofFileUtils.h>
#include "PutCommand.h"
#include "PositionCommand.h"
#include "ScaleCommand.h"
#include "ColorCommand.h"

Scene::Scene(const std::string& filename) :
	m_filename(filename),
	m_text(),
	m_commandQueueVec()
{

}
void Scene::rehash() {
	ofFile file(m_filename);
	if (!file.exists()) {
		return;
	}
	std::vector<std::string> linesOfTheFile;
	ofBuffer buffer = ofBufferFromFile(file);
	std::string newText = buffer;
	if (m_text == newText) {
		return;
	}
	ofJson json = ofJson::parse(newText);
	m_commandQueueVec.clear();
	if (json.find("queues") == json.end()) {
		return;
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
			auto cmdInst = parseCommand(cmd);
			if (cmdInst) {
				cmdQueue.submit(cmdInst);
			}
		}
		m_commandQueueVec.emplace_back(cmdQueue);
	}
	this->m_text = newText;
}

void Scene::update(std::shared_ptr<Particle> particle, float deltaTime) {
	for (auto& cmdQueue : m_commandQueueVec) {
		cmdQueue.update(particle, deltaTime);
	}
}
// private
std::shared_ptr<Command> Scene::parseCommand(ofJson& json) {
	if (!json.contains("name") || !json.contains("id")) {
		return nullptr;
	}
	std::string name = json["name"].get<std::string>();
	std::string targetName = name;
	if (name[0] == '!') {
		targetName = name.substr(1);
	}
	std::shared_ptr<Command> ret = nullptr;
	int id = json["id"].get<int>();
	if (id < 0) {
		return nullptr;
	}
	id++;
	glm::vec3 pos = parseVec3(json["position"], "x", "y", "z");
	glm::vec3 scale = parseVec3(json["scale"], "x", "y", "z");
	glm::vec3 color = parseVec3(json["color"], "r", "g", "b");
	if (targetName == "put") {
		ret = std::make_shared<PutCommand>(id,pos,scale,color);
	} else if (targetName == "position") {
		ret = std::make_shared<PositionCommand>(id, pos);
	} else if (targetName == "scale") {
		ret = std::make_shared<ScaleCommand>(id, scale);
	} else if (targetName == "color") {
		ret = std::make_shared<ColorCommand>(id, color);
	}
	if (name[0] == '!') {

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