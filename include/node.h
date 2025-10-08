#ifndef NODE_H
#define NODE_H

struct Node {
    double x;
    double y;
    double velocity;

    Node (double x_pos = 0.0, double y_pos = 0.0, double vel = 0.0)
        : x(x_pos), y(y_pos), velocity(vel) {}
};

#endif
