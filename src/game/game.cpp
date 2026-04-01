#include "game.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"


namespace game {

    int test = 0;

    void GameApp::init() {
        input::init();
        render::init();
    }

    void GameApp::handleEvent(SDL_Event* e) {
        input::handleEvent(e);
    }

    void GameApp::update(float delta) {
        
        input::update();
    }

    void GameApp::render() {
        render::clear(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
        render::setProjection(glm::ortho(0.0f, app::getWidthFloat(), app::getHeightFloat(), 0.0f));
        render::setModel(
            glm::translate(glm::mat4(1.0f), glm::vec3(32.0f, 32.0f, 0.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(32.0f, 32.0, 0.0f))
        );

        render::draw();
    }

    void GameApp::release() {
        render::release();
        input::release();
    }

    void setup(app::Config* config, GameApp* app) {
        config->caption = "Pong SDL3";
        config->width = 640;
        config->height = 480;
        config->app = app;
    }
}