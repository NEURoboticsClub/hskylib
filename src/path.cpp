#include "path.h"

#include "utils.h"

Path::Path() {}

Path::Path(const std::vector<Node> &nodes) : nodes_(nodes) {}

Path::Path(const std::string filepath) {
	std::string file_contents = readFile(filepath, 1000);
	if (file_contents == "bad filename") {
		std::cout << "bad filename, creating empty path object" << std::endl;
		return;
	}

	std::istringstream stream(file_contents);
	std::string line;

	while (std::getline(stream, line)) {
		// Skip empty lines
		if (line.empty()) continue;

		// Remove brackets and spaces
		std::string cleaned;
		for (char c : line) {
			if (c != '[' && c != ']' && c != ' ') {
				cleaned += c;
			}
		}

		// Parse comma-separated values
		std::istringstream line_stream(cleaned);
		std::string token;
		std::vector<float> values;

		while (std::getline(line_stream, token, ',')) {
			if (!token.empty()) {
				values.push_back(std::stof(token));
			}
		}

		// Create node based on number of values
		if (values.size() >= 2) {
			float x = values[0];
			float y = values[1];
			float velocity = (values.size() >= 3) ? values[2] : 0.0f;
			nodes_.emplace_back(x, y, velocity);
		}
	}
}

void Path::addNode(const Node &node) { nodes_.push_back(node); }

void Path::addNode(double x, double y, double velocity) {
	nodes_.emplace_back(x, y, velocity);
}

const Node &Path::getNode(size_t index) const { return nodes_.at(index); }

size_t Path::size() const { return nodes_.size(); }

bool Path::empty() const { return nodes_.empty(); }

void Path::clear() { nodes_.clear(); }
