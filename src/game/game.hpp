#ifndef GAME_HPP
#define GAME_HPP

#include "../engine/sys.hpp"


namespace game {


    struct GameApp : public app::IApp {
        manager::Global global;

        virtual void init();
        virtual void handleEvent(SDL_Event* e);
        virtual void update(float delta);
        virtual void render();
        virtual void release();

        void initBehaviors();
    };

    void setup(app::Config* config, GameApp* app);

    namespace entity {
        namespace paddle {
            namespace player1 {
                struct ControlledEntityBehavior : public manager::behavior::EntityBehavior {
                    float speed = 64.0f;
                    float direction = 0.0f;
                    manager::Transform* tran = nullptr;

                    virtual void ready();
                    virtual void update(float delta);
                    virtual void release();
                };
            }

            namespace player2 {
                struct ControlledEntityBehavior : public manager::behavior::EntityBehavior {
                    float speed = 64.0f;
                    float direction = 0.0f;
                    manager::Transform* tran = nullptr;

                    virtual void ready();
                    virtual void update(float delta);
                    virtual void release();
                };
            }
        }

        struct BallEntityBehavior : public manager::behavior::EntityBehavior {

            glm::vec2 velocity = glm::vec2(0.0f);

            virtual void ready();
            virtual void update(float delta);
            virtual void release(); 
            
        };
    }

    namespace scene {
    }

    namespace global {

    }
}
#endif