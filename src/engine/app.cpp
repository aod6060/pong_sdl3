#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_oldnames.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_video.h"
#include "sys.hpp"


namespace app {

    static Config* _config = nullptr;
    static SDL_Window* _window = nullptr;
    static SDL_GLContext _context = nullptr;
    static bool _is_running = true;

    static float fps_time = 0.0f;
    static float fps_maxTime = 1.0f;
    
    void init(Config* config) {
        _config = config;

        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

        _window = SDL_CreateWindow(getCaption().c_str(), getWidth(), getHeight(), SDL_WINDOW_OPENGL);

        _context = SDL_GL_CreateContext(_window);

        glewInit();

        if(_config->app) {
            _config->app->init();
        }
    }

    void update() {
        SDL_Event e;

        uint32_t pre_time = SDL_GetTicks();
        uint32_t curr_time = 0;
        float delta = 0.0f;

        while(_is_running) {
            curr_time = SDL_GetTicks();
            delta = (curr_time - pre_time) / 1000.0f;
            pre_time = curr_time;

            // Update FPS timer
            if(fps_maxTime <= fps_time) {
                fps_time = 0.0f;
                std::stringstream ss;
                ss << getCaption() << " FPS: ("<< (1.0f / delta) <<")";
                std::string cap = ss.str();
                SDL_SetWindowTitle(_window, cap.c_str());
            } else {
                fps_time += delta;
            }

            while(SDL_PollEvent(&e)) {
                if(e.type == SDL_EVENT_QUIT) {
                    app::exit();
                }

                if(_config->app) {
                    _config->app->handleEvent(&e);
                }
            }

            if(_config->app) {
                _config->app->update(delta);
                _config->app->render();
            }

            SDL_GL_SwapWindow(_window);
        }
    }

    void release() {
        if(_config->app) {
            _config->app->release();
        }

        SDL_GL_DestroyContext(_context);
        SDL_DestroyWindow(_window);
        SDL_Quit();
    }

    std::string getCaption() {
        return _config->caption;
    }

    uint32_t getWidth() {
        return _config->width;
    }

    uint32_t getHeight() {
        return _config->height;
    }

    float getWidthFloat() {
        return (float)getWidth();
    }

    float getHeightFloat() {
        return (float)getHeight();
    }

    float getAspect() {
        return getWidthFloat() / getHeightFloat();
    }

    void exit() {
        _is_running = false;
    }

    SDL_Window* getWindow() {
        return _window;
    }

    SDL_GLContext getContext() {
        return _context;
    }
}