#include "game.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"


namespace game {

    int test = 0;

    void GameApp::init() {
        this->initBehaviors();
        input::init();
        render::init();
        manager::init();
        global.loadGlobalConfig();
        global.startGame();
        global.init();
    }

    void GameApp::handleEvent(SDL_Event* e) {
        input::handleEvent(e);
        global.handleEvent(e);
    }

    void GameApp::update(float delta) {
        global.update(delta);
        input::update();
    }

    void GameApp::render() {
        global.render();
    }

    void GameApp::release() {
        global.release();

        manager::release();
        render::release();
        input::release();
    }

    void GameApp::initBehaviors() {
        manager::behavior::registerBehavior("Entity.Player1Controlled", [](){return new entity::paddle::Player1Controlled();});
        manager::behavior::registerBehavior("Entity.Player2Controlled", [](){return new entity::paddle::Player2Controlled();});
    }

    void setup(app::Config* config, GameApp* app) {
        config->caption = "Pong SDL3";
        config->width = 640;
        config->height = 480;
        config->app = app;
    }
}