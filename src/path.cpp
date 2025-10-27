#include "path.h"

#include "utils.h"

Path::Path() {}

Path::Path(const std::vector<Node> &nodes) : nodes_(nodes) {}

Path::Path(const std::string filepath) {
	std::string file_contents = readFile(filepath, 1000);
	if (file_contents == "") {
		std::cout << "bad filename, creating empty path object" << std::endl;
		return;
	}

	std::istringstream stream(file_contents);
	std::string line;

	while (std::getline(stream, line)) {
		// Skip empty lines and lines starting with # (comments/metadata)
		if (line.empty() || line[0] == '#') continue;

		// Parse comma-separated values
		std::istringstream line_stream(line);
		std::string token;
		std::vector<float> values;

		// Try to parse all comma-separated values as floats
		while (std::getline(line_stream, token, ',')) {
			if (!token.empty()) {
				try {
					values.push_back(std::stof(token));
				} catch (const std::invalid_argument &) {
					// Skip lines that contain non-numeric data
					values.clear();
					break;
				} catch (const std::out_of_range &) {
					// Skip lines with out-of-range numbers
					values.clear();
					break;
				}
			}
		}

		// Create node if we have at least 2 valid numeric values
		// Use first 3 values: x, y, velocity (velocity defaults to 0 if not
		// present)
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
