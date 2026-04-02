#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/trigonometric.hpp"
#include "sys.hpp"
#include "json/value.h"
#include <fstream>
#include <functional>
#include <map>
#include <string>
#include <vector>


#define SCENE_TYPE "scene"
#define SCENE_VERSION 1

namespace manager {
    // Global
    void init() {
        components::init();
    }

    void release() {
        behavior::release();
        components::release();
    }


    void Global::init() {
        if(scene) {
            scene->init(this);
        }
    }

    void Global::handleEvent(SDL_Event* e) {
        if(scene) {
            scene->handleEvent(e);
        }
    }

    void Global::update(float delta) {
        if(scene) {
            scene->update(delta);
        }
    }

    void Global::render() {
        if(scene) {
            scene->render();
        }
    }

    void Global::release() {
        if(scene) {
            scene->release();
        }
    }

    void Global::loadScene(std::string path) {
        this->scenePath = path;

        std::ifstream in(path);
        Json::Value root;
        in >> root;
        std::string type = root["type"].asString();
        uint32_t version = root["version"].asUInt();

        if(type != SCENE_TYPE) {
            std::cout << path << "> File type isn't a scene. Will try to load!\n";
        }

        if(version != SCENE_VERSION) {
            std::cout << path << "> File version isn't corrected which is " << SCENE_VERSION << ". Will try to load\n";
        }

        this->scene = new Scene();
        this->scene->load(root);
    }

    void Global::changeScene(std::string path) {
        if(this->scene) {
            // To make sure the scene is a new pointer
            this->scene->release();
            delete scene;
            scene = nullptr;
        }
        this->loadScene(path);
        if(this->scene) {
            this->scene->init(this);
        }
    }

    void Global::reloadScene() {
        this->changeScene(this->scenePath);
    }

    void Global::setDefaultScenePath(std::string path) {
        this->defaultScenePath = path;
    }

    void Global::startGame() {
        this->loadScene(this->defaultScenePath);
    }

    // Scene
    void Scene::init(Global* global) {
        this->global = global;

        for(int i = 0; i < this->entities.size(); i++) {
            this->entities[i]->init(this);
        }

        if(this->behavior) {
            this->behavior->init(this);
        }
    }

    void Scene::handleEvent(SDL_Event* e) {
        for(int i = 0; i < this->entities.size(); i++) {
            this->entities[i]->handleEvent(e);
        }
    }

    void Scene::update(float delta) {
        std::vector<Entity*>::iterator it = this->entities.begin();

        while(it != this->entities.end()) {
            if((*it)->needRemoval) {
                (*it)->release();
                delete (*it);
                entities.erase(it);
                continue;
            } else {
                (*it)->update(delta);
                it++;
            }
        }

        if(this->behavior) {
            this->behavior->update(delta);
        }
    }

    void Scene::render() {
        render::clear(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
        render::setProjection(glm::ortho(0.0f, app::getWidthFloat(), app::getHeightFloat(), 0.0f));

        for(int i = 0; i < this->entities.size(); i++) {
            this->entities[i]->render();
        }
    }

    void Scene::release() {
        for(int i = 0; i < this->entities.size(); i++) {
            this->entities[i]->release();
            delete this->entities[i];
            this->entities[i] = nullptr;
        }
        this->entities.clear();

        if(this->behavior) {
            this->behavior->release();
            delete this->behavior;
            this->behavior = nullptr;
        }

        this->global = nullptr;
    }

    void Scene::load(Json::Value value) {
        if(!value["behavior"].isNull()) {
            std::string name = value["behavior"].asString();
            this->behavior = manager::behavior::create(name);
        }

        // Entities
        Json::Value entities = value["entities"];
        for(int i = 0; i < entities.size(); i++) {
            Json::Value obj = entities[i];
            Entity* temp = new Entity();
            temp->load(obj);
            this->entities.push_back(temp);
        }
    }

    void Scene::addEntity(Entity* entity) {
        entity->init(this);
        this->entities.push_back(entity);
    }

    void Scene::removeEntity(Entity* entity) {
        entity->needRemoval = true;
    }

    // Transform

    void Transform::init(Entity* entity) {
        this->entity = entity;
    }

    void Transform::release() {
        this->entity = nullptr;
    }


    glm::mat4 Transform::toModel() {
        return 
            glm::translate(glm::mat4(1.0f), this->position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
            glm::scale(glm::mat4(1.0f), this->scale);
    }

    void Transform::load(Json::Value value) {
        this->position = glm::vec3(
            value["position"]["x"].asFloat(),
            value["position"]["y"].asFloat(),
            value["position"]["z"].asFloat()
        );
        this->rotation = value["rotation"].asFloat();
        this->scale = glm::vec3(
            value["scale"]["x"].asFloat(),
            value["scale"]["y"].asFloat(),
            value["scale"]["z"].asFloat()
        );
    }

    // Entity
    void Entity::init(Scene* scene) {
        this->scene = scene;

        this->transform.init(this);

        this->componentIterator([&](IComponent* comp) {
            comp->init(this);
        });

        if(this->behavior) {
            this->behavior->init(this);
        }
    }

    void Entity::handleEvent(SDL_Event* e) {
        this->componentIterator([&](IComponent* comp) {
            comp->handleEvent(e);
        });
    }

    void Entity::update(float delta) {
        this->componentIterator([&](IComponent* comp) {
            comp->update(delta);
        });

        if(this->behavior) {
            this->behavior->update(delta);
        }
    }

    void Entity::render() {
        this->componentIterator([&](IComponent* comp) {
            comp->render();
        });
    }

    void Entity::release() {
        this->componentIterator([&](IComponent* comp) {
            comp->release();
            delete comp;
            comp = nullptr;
        });
        components.clear();
        if(this->behavior) {
            this->behavior->ready();
            delete behavior;
            behavior = nullptr;
        }
        transform.release();
        this->scene = nullptr;
    }

    void Entity::load(Json::Value value) {
        if(!value["name"].empty()) {
            this->name = value["name"].asString();
        }

        if(!value["behavior"].empty() && !value["behavior"].isNull()) {
            std::string name = value["behavior"].asString();
            this->behavior = manager::behavior::create(name);
        }

        if(!value["transform"].empty()) {
            transform.load(value["transform"]);
        }

        if(!value["components"].empty()) {
            Json::Value components = value["components"];
            for(int i = 0; i < components.size(); i++) {
                Json::Value comp = components[i];
                std::string type = comp["type"].asString();
                components::createFactory(this, type, comp);
            }
        }
    }

    void Entity::componentIterator(std::function<void(IComponent* comp)> callback) {
        for(std::map<std::string, IComponent*>::iterator it = this->components.begin(); it != this->components.end(); it++) {
            callback(it->second);
        }
    }

    // Components
    namespace components {
        namespace render {
            // SpriteComponent
            void SpriteComponent::init(Entity* entity) {
                this->entity = entity;
            }

            void SpriteComponent::handleEvent(SDL_Event* e) {

            }

            void SpriteComponent::update(float delta) {

            }

            void SpriteComponent::render() {
                ::render::setModel(entity->transform.toModel());
                ::render::draw();
            }

            void SpriteComponent::release() {
                this->entity = nullptr;
            }

            void SpriteComponent::load(Json::Value value) {

            }

        }

        // Functions
        static std::map<std::string, std::function<IComponent*()>> _compFactory;

        void init() {
            registerComponent("sprite", []() { return new render::SpriteComponent();});
        }

        void release() {
            _compFactory.clear();
        }

        void registerComponent(std::string name, std::function<IComponent*()> functoryFunction) {
            _compFactory[name] = functoryFunction;
        }

        IComponent* create(std::string name) {
            return _compFactory.at(name)();
        }

        void createFactory(manager::Entity* entity, std::string type, Json::Value value) {
            if(_compFactory.find(type) != _compFactory.end()) {
                entity->components[type] = create(type);
                entity->components.at(type)->load(value);
                return;
            } else {
                std::cout << "\"\" isn't a component type!\n";
                return;
            }
        }
    }

    namespace behavior {
        // Behavior
        void Behavior::init(Scene* scene) {
            this->scene = scene;
            this->ready();
        }

        void Behavior::init(Entity* entity) {
            this->entity = entity;
            this->ready();
        }

        // Functions
        std::map<std::string, std::function<IBehavior*()>> _behaviorFactory;

        void release() {
            _behaviorFactory.clear();
        }
        
        void registerBehavior(std::string name, std::function<IBehavior*()> fuctoryFunction) {
            _behaviorFactory[name] = fuctoryFunction;
        }
        
        IBehavior* create(std::string name) {
            //return nullptr;
            if(_behaviorFactory.find(name) != _behaviorFactory.end()) {
                return _behaviorFactory.at(name)();
            } else {
                std::cout << name << " isn't a behavior!\n";
                return nullptr;
            }
        }
        

    }
}