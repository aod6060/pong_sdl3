#include "game.hpp"
#include "glm/trigonometric.hpp"


namespace game {

    namespace entity {
        namespace paddle {
            void Player1Controlled::ready() {
                tran = &entity->transform;
            }

            void Player1Controlled::update(float delta) {
                if(input::isKeyPressed(input::Keyboard::KEYS_W)) {
                    if(tran->position.y - (tran->scale.y * 0.5f) > 0.0f) {
                        direction = -1.0f;
                    } else {
                        direction = 0.0f;
                    }
                } else if(input::isKeyPressed(input::Keyboard::KEYS_S)) {
                    if(tran->position.y + (tran->scale.y * 0.5f) < app::getHeightFloat()) {
                        direction = 1.0f;
                    } else {
                        direction = 0.0f;
                    }
                } else {
                    direction = 0.0f;
                }

                tran->position.y += direction * speed * delta;
            }

            void Player1Controlled::release() {
                tran = nullptr;
                entity = nullptr;
            }


            // Player2Controlled
            void Player2Controlled::ready() {
                tran = &entity->transform;
            }

            void Player2Controlled::update(float delta) {
                if(input::isKeyPressed(input::Keyboard::KEYS_I)) {
                    if(tran->position.y - (tran->scale.y * 0.5f) > 0.0f) {
                        direction = -1.0f;
                    } else {
                        direction = 0.0f;
                    }
                } else if(input::isKeyPressed(input::Keyboard::KEYS_K)) {
                    if(tran->position.y + (tran->scale.y * 0.5f) < app::getHeightFloat()) {
                        direction = 1.0f;
                    } else {
                        direction = 0.0f;
                    }
                } else {
                    direction = 0.0f;
                }

                tran->position.y += direction * speed * delta;
            }

            void Player2Controlled::release() {
                tran = nullptr;
                entity = nullptr;
            }

        }
    }

    namespace scene {
    }

    namespace global {
    }

}