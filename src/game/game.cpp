#include "game.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"


namespace game {

    int test = 0;

    void GameApp::init() {
        global.setDefaultScenePath("data/scenes/test.scene.json");

        input::init();
        render::init();
        manager::init();

        this->initBehaviors();

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
        manager::behavior::registerBehavior("Game.MoveEntity", []() {return new MoveEntityBehavior();});
    }

    void setup(app::Config* config, GameApp* app) {
        config->caption = "Pong SDL3";
        config->width = 640;
        config->height = 480;
        config->app = app;
    }
}