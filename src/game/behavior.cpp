#include "game.hpp"


namespace game {


    // Move Entity Behavior
    void MoveEntityBehavior::ready() {
        this->tran = &this->entity->transform;

    }

    void MoveEntityBehavior::update(float delta) {
        if(input::isKeyPressed(input::Keyboard::KEYS_LEFT)) {
            this->tran->position.x -= speed * delta;
        } else if(input::isKeyPressed(input::Keyboard::KEYS_RIGHT)) {
            this->tran->position.x += speed * delta;
        }

        if(input::isKeyPressed(input::Keyboard::KEYS_UP)) {
            this->tran->position.y -= speed * delta;
        } else if(input::isKeyPressed(input::Keyboard::KEYS_DOWN)) {
            this->tran->position.y += speed * delta;
        }

    }

    void MoveEntityBehavior::release() {
        this->scene = nullptr;
        this->entity = nullptr;
    }

}