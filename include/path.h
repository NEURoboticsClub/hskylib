#ifndef PATH_H
#define PATH_H

#include <vector>
#include "node.h"

class Path {
    public:
        Path();
        explicit Path(const std::vector<Node>& nodes);
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
