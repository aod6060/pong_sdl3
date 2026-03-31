#include "game.hpp"


namespace game {

    void GameApp::init() {
        glDisable(GL_DEPTH_TEST);
    }

    void GameApp::handleEvent(SDL_Event* e) {

    }

    void GameApp::update(float delta) {
        std::cout << "Delta: " << delta << "\n";
    }

    void GameApp::render() {
        glViewport(0, 0, app::getWidth(), app::getHeight());
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Do nothing here for the moment.
    }

    void GameApp::release() {

    }

    void setup(app::Config* config, GameApp* app) {
        config->caption = "Pong SDL3";
        config->width = 640;
        config->height = 480;
        config->app = app;
    }
}