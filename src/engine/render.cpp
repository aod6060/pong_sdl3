#include "SDL3/SDL_oldnames.h"
#include "SDL3/SDL_video.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "sys.hpp"


namespace render {
    struct TextShader {
    // Shaders
        glw::Shader vertexShader;
        glw::Shader fragmentShader;
        // Program
        glw::Program program;

        void init();
        void release();
    } textShader;

    // Shaders
    glw::Shader vertexShader;
    glw::Shader fragmentShader;

    // Program
    glw::Program program;

    // Buffers
    glw::VertexBuffer vertices;
    glw::VertexBuffer texCoords;
    glw::IndexBuffer indices;

    // Matrix
    static glm::mat4 proj;
    static glm::mat4 model;
    static glm::mat4 offset;

    void init() {

        SDL_GL_SetSwapInterval(1);

        glDisable(GL_DEPTH_TEST);

        vertexShader.init(GL_VERTEX_SHADER, "data/shaders/main.vs.glsl");
        fragmentShader.init(GL_FRAGMENT_SHADER, "data/shaders/main.fs.glsl");

        program.init({&vertexShader, &fragmentShader});

        program.bind();

        program.uniforms.createUniform("proj");
        program.uniforms.createUniform("model");

        program.attributes.createAttribute("vertices", 0);

        program.attributes.bind();
        program.attributes.enableAttribute("vertices");
        program.attributes.unbind();

        program.unbind();

        textShader.init();

        vertices.init();
        vertices.add3(-0.5f, -0.5f, 0.0f);
        vertices.add3(0.5f, -0.5f, 0.0f);
        vertices.add3(-0.5f, 0.5f, 0.0f);
        vertices.add3(0.5f, 0.5f, 0.0f);
        vertices.update();

        texCoords.init();
        texCoords.add2(0.0f, 0.0f);
        texCoords.add2(1.0f, 0.0f);
        texCoords.add2(0.0f, 1.0f);
        texCoords.add2(1.0f, 1.0f);
        texCoords.update();

        indices.init();
        indices.add3(0, 1, 2);
        indices.add3(2, 1, 3);
        indices.update();

        font::init();
    }

    void release() {
        font::release();

        indices.release();
        texCoords.release();
        vertices.release();
        textShader.release();
        program.release();
        vertexShader.release();
        fragmentShader.release();
    }
    
    void clear(glm::vec4 clearColor) {
        glViewport(0, 0, app::getWidth(), app::getHeight());
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void setProjection(glm::mat4 m) {
        proj = m;
    }

    void setModel(glm::mat4 m) {
        model = m;
    }

    void setOffset(glm::mat4 m) {
        offset = m;
    }

    void draw() {
        program.bind();
        program.uniforms.uniformMat4("proj", proj);
        program.uniforms.uniformMat4("model", model);

        program.attributes.bind();
        vertices.bind();
        program.attributes.pointer("vertices", 3, GL_FLOAT);
        vertices.unbind();

        indices.bind();
        glDrawElements(GL_TRIANGLES, indices.count(), GL_UNSIGNED_INT, nullptr);
        indices.unbind();

        program.attributes.unbind();
        
        program.unbind();
    }


    void TextShader::init() {
        this->vertexShader.init(GL_VERTEX_SHADER, "data/shaders/text.vs.glsl");
        this->fragmentShader.init(GL_FRAGMENT_SHADER, "data/shaders/text.fs.glsl");
        this->program.init({&this->vertexShader, &this->fragmentShader});

        this->program.bind();
        this->program.uniforms.createUniform("proj");
        this->program.uniforms.createUniform("model");
        this->program.uniforms.createUniform("tex0");
        this->program.uniforms.uniform1i("tex0", 0);

        this->program.attributes.createAttribute("vertices", 0);
        this->program.attributes.createAttribute("texCoords", 1);

        this->program.attributes.bind();
        this->program.attributes.enableAttribute("vertices");
        this->program.attributes.enableAttribute("texCoords");
        this->program.attributes.unbind();

        this->program.unbind();
    }

    void TextShader::release() {
        this->program.release();
        this->fragmentShader.release();
        this->vertexShader.release();
    }


    namespace font {
        glw::Texture2D text;
        TTF_Font* font24 = nullptr;

        void init() {
            TTF_Init();
            text.init();
            font24 = TTF_OpenFont("data/fonts/Roboto.ttf", 24);;
        }

        void release() {
            TTF_CloseFont(font24);
            text.release();
            TTF_Quit();
        }

        void getSize(std::string text, int* width, int* height) {
            TTF_GetStringSize(font24, text.data(), text.size(), width, height);
        }

        void draw(std::string text) {
            // Update Texture
            SDL_Surface* surf = TTF_RenderText_Blended(font24, text.data(), text.size(), {255, 255, 255, 255});
            font::text.bind(GL_TEXTURE0);
            font::text.texImage2D(0, GL_RGBA, surf->w, surf->h, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);
            font::text.texParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            font::text.texParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            // Draw Texture
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            render::textShader.program.bind();
            render::textShader.program.uniforms.uniformMat4("proj", render::proj);
            render::textShader.program.uniforms.uniformMat4("model", render::model);
            render::textShader.program.attributes.bind();
            
            render::vertices.bind();
            render::textShader.program.attributes.pointer("vertices", 3, GL_FLOAT);
            render::vertices.unbind();

            render::texCoords.bind();
            render::textShader.program.attributes.pointer("texCoords", 2, GL_FLOAT);
            render::texCoords.unbind();

            render::indices.bind();
            glDrawElements(GL_TRIANGLES, render::indices.count(), GL_UNSIGNED_INT, nullptr);
            render::indices.unbind();

            render::textShader.program.attributes.unbind();
            render::textShader.program.unbind();
            glDisable(GL_BLEND);
            font::text.unbind(GL_TEXTURE0);
            SDL_DestroySurface(surf);
        }
    }
}