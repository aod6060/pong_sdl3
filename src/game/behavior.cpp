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
            this->entity = nullptr;
        }

        // ExitGameEntity
        void ExitGameEntity::ready() {
            this->gameScene = (scene::GameScene*)this->entity->scene->behavior;
        }

        void ExitGameEntity::update(float delta) {
            manager::components::collision::BoxComponent* box = (manager::components::collision::BoxComponent*)this->entity->components.at("box");
            manager::components::collision::BoxComponent* pbox = (manager::components::collision::BoxComponent*)this->gameScene->player->components.at("box");

            if(box->box.collide(pbox->box)) {
                std::cout << "Collide with!\n";
            }
        }

        void ExitGameEntity::release() {

        }

        
    }

    namespace scene {
        void GameScene::ready() {
            this->player = scene->entities[0];
        }

        void GameScene::update(float delta) {

        }

        void GameScene::release() {

        }
    }

    namespace global {

    }

}