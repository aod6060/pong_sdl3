#include "engine/sys.hpp"
#include "game/game.hpp"


int main(int argc, char** argv) {
    game::GameApp gameApp;
    app::Config config;
    game::setup(&config, &gameApp); 
    app::init(&config);
    app::update();
    app::release();
    return 0;
}