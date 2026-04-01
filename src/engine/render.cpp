#include "sys.hpp"


namespace render {
    // Shaders
    glw::Shader vertexShader;
    glw::Shader fragmentShader;

    // Program
    glw::Program program;

    // Buffers
    glw::VertexBuffer vertices;
    glw::IndexBuffer indices;

    // Matrix
    static glm::mat4 proj;
    static glm::mat4 model;

    void init() {
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

        vertices.init();
        vertices.add3(-0.5f, -0.5f, 0.0f);
        vertices.add3(0.5f, -0.5f, 0.0f);
        vertices.add3(-0.5f, 0.5f, 0.0f);
        vertices.add3(0.5f, 0.5f, 0.0f);
        vertices.update();

        indices.init();
        indices.add3(0, 1, 2);
        indices.add3(2, 1, 3);
        indices.update();
    }

    void release() {
        indices.release();
        vertices.release();
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

}