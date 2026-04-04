#include "game.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"


namespace game {

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
        // Player 1
        manager::behavior::registerBehavior("Entity.Paddle.Player1.Controlled", [](){return new entity::paddle::player1::ControlledEntityBehavior();});
        // Player 2
        manager::behavior::registerBehavior("Entity.Paddle.Player2.Controlled", [](){return new entity::paddle::player2::ControlledEntityBehavior();});
        manager::behavior::registerBehavior("Entity.Paddle.Player2.Impossible", [](){return new entity::paddle::player2::ImpossibleEntityBehavior();});
        manager::behavior::registerBehavior("Entity.Paddle.Player2.Expert", [](){return new entity::paddle::player2::ExpertEntityBehavior();});
        manager::behavior::registerBehavior("Entity.Paddle.Player2.Hard", [](){return new entity::paddle::player2::HardEntityBehavior();});
        manager::behavior::registerBehavior("Entity.Paddle.Player2.Normal", [](){return new entity::paddle::player2::NormalEntityBehavior();});
        manager::behavior::registerBehavior("Entity.paddle.Player2.Easy", [](){return new entity::paddle::player2::EasyEntityBehavior();});
        // Ball
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