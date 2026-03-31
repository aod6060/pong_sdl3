#include "SDL3/SDL_events.h"
#include "sys.hpp"
#include <vector>


namespace input {

    static std::vector<InputState> keys;

    void init() {
        keys.resize(Keyboard::KEYBOARD_MAX_SIZE);
        std::for_each(keys.begin(), keys.end(), [](InputState& state) {
            state = InputState::IS_RELAESED;
        });
    }

    void handleEvent(SDL_Event* e) {
        if(e->type == SDL_EVENT_KEY_DOWN) {
            if(keys[e->key.scancode] == InputState::IS_RELAESED) {
                keys[e->key.scancode] = InputState::IS_PRESSED_ONCE;
            }
        } else if(e->type == SDL_EVENT_KEY_UP) {
            if(keys[e->key.scancode] == InputState::IS_PRESSED) {
                keys[e->key.scancode] = InputState::IS_RELEASED_ONCE;
            }
        }
    }

    // This is the last thing that needs to be called in the update method
    void update() {
        std::for_each(keys.begin(), keys.end(), [](InputState& state) {
            if(state == InputState::IS_PRESSED_ONCE) {
                state = InputState::IS_PRESSED;
            }

            if(state == InputState::IS_RELEASED_ONCE) {
                state = InputState::IS_RELAESED;
            }
        });
    }

    void release() {
        keys.clear();
    }

    bool isKeyReleased(Keyboard k) {
        return keys[k] == InputState::IS_RELEASED_ONCE || keys[k] == InputState::IS_RELAESED;
    }

    bool isKeyPressedOnce(Keyboard k) {
        return keys[k] == InputState::IS_PRESSED_ONCE;
    }

    bool isKeyPressed(Keyboard k) {
        return keys[k] == InputState::IS_PRESSED_ONCE || keys[k] == InputState::IS_PRESSED;
    }

    bool isKeyReleasedOnce(Keyboard k) {
        return keys[k] == InputState::IS_RELEASED_ONCE;
    }


}