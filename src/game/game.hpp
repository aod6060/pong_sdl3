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

    namespace scene {
        struct GameScene;
    }

    namespace entity {
        struct MoveEntityBehavior : public manager::behavior::EntityBehavior {
            manager::Transform* tran = nullptr;
            float speed = 64.0f;

            virtual void ready();
            virtual void update(float delta);
            virtual void release();
        };

        struct TankControlsEntity : public manager::behavior::EntityBehavior {
            manager::Transform* tran = nullptr;
            float rotSpeed = 64.0f;
            float speed = 64.0f;

            virtual void ready();
            virtual void update(float delta);
            virtual void release();

        };

        struct ExitGameEntity : public manager::behavior::EntityBehavior {
            scene::GameScene* gameScene = nullptr;

            virtual void ready();
            virtual void update(float delta);
            virtual void release();
        };
    }

    namespace scene {
        struct GameScene : public manager::behavior::SceneBehavior {
            //entity::TankControlsEntity* player = nullptr;
            manager::Entity* player = nullptr;

            virtual void ready();
            virtual void update(float delta);
            virtual void release();
        };
    }

    namespace global {

    }
}
#endif