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


    struct MoveEntityBehavior : public manager::behavior::Behavior {
        manager::Transform* tran = nullptr;
        float speed = 64.0f;

        virtual void ready();
        virtual void update(float delta);
        virtual void release();
    };
}
#endif