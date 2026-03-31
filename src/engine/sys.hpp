#ifndef SYS_HPP
#define SYS_HPP



#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <random>
#include <chrono>
#include <filesystem>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <json/json.h>


namespace app {
    struct IApp {
        virtual void init() = 0;
        virtual void handleEvent(SDL_Event* e) = 0;
        virtual void update(float delta) = 0;
        virtual void render() = 0;
        virtual void release() = 0;
    };

    struct Config {
        std::string caption;
        uint32_t width;
        uint32_t height;
        IApp* app = nullptr;
    };

    void init(Config* config);
    void update();
    void release();

    
}
#endif