#ifndef PATH_H
#define PATH_H

#include <vector>
#include <string>
#include "node.h"

/**
 * A data structure that holds an ordered collection of nodes
 */
class Path {
    public:
        Path();
        explicit Path(const std::vector<Node>& nodes);
        explicit Path(const std::string filepath);
        void addNode(const Node& node);
        void addNode(double x, double y, double velocity = 0.0);

        const Node& getNode(size_t index) const;
        Node* getNodePtr(size_t index);

        size_t size() const;
        bool empty() const;
        void clear();

    private:
        std::vector<Node> nodes_;
};

#endif
