#include "game.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"


namespace game {

    int test = 0;

    void GameApp::init() {
        this->initBehaviors();
        input::init();
        render::init();
        util::init();
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
        util::release();
        render::release();
        input::release();
    }

    void GameApp::initBehaviors() {
        // Entity
        manager::behavior::registerBehavior("Entity.Paddle.Player1.Controlled", [](){return new entity::paddle::player1::ControlledEntityBehavior();});
        manager::behavior::registerBehavior("Entity.Paddle.Player2.Controlled", [](){return new entity::paddle::player2::ControlledEntityBehavior();});
        manager::behavior::registerBehavior("Entity.Ball", [](){return new entity::BallEntityBehavior();});
        // Scene
        manager::behavior::registerBehavior("Scene.GameScene", []() {return new scene::GameSceneBehavior();});
        // Global
    }

    void setup(app::Config* config, GameApp* app) {
        config->caption = "Pong SDL3";
        config->width = 640;
        config->height = 480;
        config->app = app;
    }
}