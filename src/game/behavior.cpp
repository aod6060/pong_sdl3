#include "game.hpp"
#include "glm/trigonometric.hpp"


namespace game {

    namespace entity {

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
            this->tran = nullptr;
        }


        // TankControlsEntityBehavior
        void TankControlsEntity::ready() {
            this->tran = &this->entity->transform;
        }

        void TankControlsEntity::update(float delta) {

            if(input::isKeyPressed(input::Keyboard::KEYS_LEFT)) {
                this->tran->rotation -= this->rotSpeed * delta;
            } else if(input::isKeyPressed(input::Keyboard::KEYS_RIGHT)) {
                this->tran->rotation += this->rotSpeed * delta;
            }


            float rrot = glm::radians(this->tran->rotation);

            if(input::isKeyPressed(input::Keyboard::KEYS_UP)) {
                this->tran->position.x += glm::sin(rrot) * speed * delta;
                this->tran->position.y -= glm::cos(rrot) * speed * delta;
            } else if(input::isKeyPressed(input::Keyboard::KEYS_DOWN)) {
                this->tran->position.x -= glm::sin(rrot) * speed * delta;
                this->tran->position.y += glm::cos(rrot) * speed * delta;
            }
        }

        void TankControlsEntity::release() {
            this->tran = nullptr;
            this->scene = nullptr;
            this->entity = nullptr;
        }

            
    }

    namespace scene {

    }

    namespace global {

    }

}