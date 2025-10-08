#include "path.h"

Path::Path() {}

Path::Path(const std::vector<Node>& nodes) : nodes_(nodes) {}

void Path::addNode(const Node& node) {
    nodes_.push_back(node);
}

void Path::addNode(double x, double y, double veolcity) {
    nodes_.emplace_back(x, y, velocity);
}

const Node& Path::getNode(size_t index) const {
    return nodes_.at(index);
}

size_t Path::size() const {
    return nodes_.size();
}

bool Path::empty() const {
    return nodes_.empty()
}

void Path::clear() {
    nodes_.clear();
}
