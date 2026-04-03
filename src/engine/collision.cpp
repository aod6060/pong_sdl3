#include "sys.hpp"


namespace collision {


    // Box
    void Box::init(glm::vec2 p, glm::vec2 o, glm::vec2 s) {
        this->position = p;
        this->offset = o;
        this->size = s;
    }

    float Box::left() {
        return (position.x + offset.x) - (size.x * 0.5f);
    }

    float Box::right() {
        return (position.x + offset.x) + (size.x * 0.5f);
    }

    float Box::top() {
        return (position.y + offset.y) - (size.y * 0.5f);
    }

    float Box::bottom() {
        return (position.y + offset.y) + (size.y * 0.5f);
    }

    bool Box::collide(Box& other) {
        return 
            left() < other.right() &&
            right() > other.left() &&
            top() < other.bottom() &&
            bottom() > other.top();
    }

    bool Box::collide(glm::vec2 point) {
        return 
            left() < point.x &&
            right() > point.x &&
            top() < point.y &&
            bottom() > point.y;
    }

}