#include "game.hpp"
#include "glm/trigonometric.hpp"


namespace game {

    namespace entity {
        namespace paddle {
            namespace player1 {
                void ControlledEntityBehavior::ready() {
                    tran = &entity->transform;
                }
                
                void ControlledEntityBehavior::update(float delta) {
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

                void ControlledEntityBehavior::release() {
                    tran = nullptr;
                    entity = nullptr;
                }

            }
            // Player2Controlled

            namespace player2 {
                void ControlledEntityBehavior::ready() {
                    tran = &entity->transform;
                }

                void ControlledEntityBehavior::update(float delta) {
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

                void ControlledEntityBehavior::release() {
                    tran = nullptr;
                    entity = nullptr;
                }

            }
        }

        // BallEntityBehavior
        void BallEntityBehavior::ready() {
            this->tran = &this->entity->transform;
            this->reset();
        }

        void BallEntityBehavior::update(float delta) {

        }

        void BallEntityBehavior::release() {
            this->tran = nullptr;
        }

        void BallEntityBehavior::reset() {
            // Position
            this->tran->position = glm::vec3(
                app::getWidthFloat() * 0.5f,
                app::getHeightFloat() * 0.5f,
                0.0f
            );
        }
    }

    namespace scene {
    }

    namespace global {
    }

}