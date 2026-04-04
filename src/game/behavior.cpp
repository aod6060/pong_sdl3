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
                // ControlledEntityBehavior
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


                // ImpossibleEntityBehavior
                void ImpossibleEntityBehavior::ready() {
                    this->tran = &entity->transform;
                    gsBehavior = (scene::GameSceneBehavior*)this->entity->scene->behavior;
                }

                void ImpossibleEntityBehavior::update(float delta) {
                    manager::Transform* ball = &gsBehavior->ball->transform;
                    if(tran->position.y - (tran->scale.y * 0.5) > ball->position.y) {
                        this->direction = -1.0f;
                    } else if(tran->position.y + (tran->scale.y * 0.5) < ball->position.y) {
                        this->direction = 1.0f;
                    } else {
                        this->direction = 0.0f;
                    }
                    this->tran->position.y += this->speed * this->direction * delta;
                    ball = nullptr;
                }

                void ImpossibleEntityBehavior::release() {
                    gsBehavior = nullptr;
                    tran = nullptr;
                    entity = nullptr;
                }

                // ExpertEntityBehavior
                void ExpertEntityBehavior::ready() {
                    this->tran = &entity->transform;
                    gsBehavior = (scene::GameSceneBehavior*)this->entity->scene->behavior;
                }

                void ExpertEntityBehavior::update(float delta) {
                    manager::Transform* ball = &gsBehavior->ball->transform;
                    entity::BallEntityBehavior* ballBehavior = (entity::BallEntityBehavior*)gsBehavior->ball->behavior;

                    if(ballBehavior->velocity.x > 0.0f) {
                        if(tran->position.y - (tran->scale.y * 0.5) > ball->position.y) {
                            this->direction = -1.0f;
                        } else if(tran->position.y + (tran->scale.y * 0.5) < ball->position.y) {
                            this->direction = 1.0f;
                        } else {
                            this->direction = 0.0f;
                        }
                        this->tran->position.y += this->speed * this->direction * delta;
                    }
                    ballBehavior = nullptr;
                    ball = nullptr;
                }

                void ExpertEntityBehavior::release() {
                    this->tran = nullptr;
                    this->gsBehavior = nullptr;
                    this->entity = nullptr;
                }

            }
        }

        // BallEntityBehavior
        void BallEntityBehavior::ready() {
            this->gameScene = (scene::GameSceneBehavior*)this->entity->scene->behavior;
            this->tran = &this->entity->transform;
            this->reset();
        }

        void BallEntityBehavior::update(float delta) {

            if(this->tran->position.y - (this->tran->scale.y * 0.5f) <= 0.0f) {
                this->velocity.y = 1.0f;
            }

            if(this->tran->position.y + (this->tran->scale.y * 0.5f) > app::getHeightFloat()) {
                this->velocity.y = -1.0f;
            }

            if(this->tran->position.x + (this->tran->scale.x * 0.5) < 0.0f) {
                reset();
            }

            if(this->tran->position.x - (this->tran->scale.x * 0.5) > app::getWidthFloat()) {
                reset();
            }

            manager::components::collision::BoxComponent* ballBoxComp = (manager::components::collision::BoxComponent*)this->entity->components.at("box");
            manager::components::collision::BoxComponent* player1BoxComp = (manager::components::collision::BoxComponent*)this->gameScene->player1->components.at("box");
            manager::components::collision::BoxComponent* player2BoxComp = (manager::components::collision::BoxComponent*)this->gameScene->player2->components.at("box");


            if(ballBoxComp->box.collide(player1BoxComp->box)) {
                this->speedX = this->speedX * 2.0f;
                this->velocity.x = this->speedX;
            }

            if(ballBoxComp->box.collide(player2BoxComp->box)) {
                this->speedX = this->speedX * 2.0f;
                this->velocity.x = -this->speedX;
            }

            ballBoxComp = nullptr;
            player1BoxComp = nullptr;
            player2BoxComp = nullptr;
            this->tran->position.x += this->speed * this->velocity.x * delta;
            this->tran->position.y += this->speed * this->velocity.y * delta;
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

            this->velocity.x = (util::nextBool()) ? -1.0 : 1.0;
            this->velocity.y = (util::nextBool()) ? -1.0 : 1.0;

            this->speedX = 1.0f;
        }
    }

    namespace scene {
        void GameSceneBehavior::ready() {
            this->player1 = this->scene->entities[0];
            this->player2 = this->scene->entities[1];
            this->ball = this->scene->entities[2];
        }

        void GameSceneBehavior::update(float delta) {
        }

        void GameSceneBehavior::release() {
        }

    }

    namespace global {
    }

}