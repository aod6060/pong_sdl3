#include "sys.hpp"
#include <algorithm>
#include <fstream>


namespace render {
    namespace glw {
        // Shader
        void Shader::init(GLenum type, std::string path) {
            this->id = glCreateShader(type);
            // Load Shader
            std::ifstream in(path);
            in.seekg(0, std::ios::end);
            uint32_t shader_size = in.tellg();
            in.seekg(0, std::ios::beg);
            std::string src;
            src.resize(shader_size);
            in.read(src.data(), src.size());

            const char* c_src = src.c_str();
            glShaderSource(this->id, 1, &c_src, nullptr);

            glCompileShader(this->id);

            int err_len = 0;
            glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &err_len);

            if(err_len > 0) {
                std::string log;
                log.resize(err_len);
                glGetShaderInfoLog(this->id, log.size(), nullptr, log.data());
                std::cout << log << "\n";
            }


        }

        void Shader::release() {
            glDeleteShader(this->id);
        }

        // Uniform
        void Uniform::init(Program* program) {
            this->program = program;
        }
        
        void Uniform::release() {
            this->program = nullptr;
        }
        
        void Uniform::createUniform(std::string name) {
            this->uniforms[name] = glGetUniformLocation(this->program->id, name.c_str());
        }
        
        // Integer
        void Uniform::uniform1i(std::string name, int x) {
            glUniform1i(this->uniforms.at(name), x);
        }
        
        void Uniform::uniform2i(std::string name, int x, int y) {
            glUniform2i(this->uniforms.at(name), x, y);
        }
        
        void Uniform::uniform3i(std::string name, int x, int y, int z) {
            glUniform3i(this->uniforms.at(name), x, y, z);
        }
        
        void Uniform::uniform4i(std::string name, int x, int y, int z, int w) {
            glUniform4i(this->uniforms.at(name), x, y, z, w);
        }
        
        // Float
        void Uniform::uniform1f(std::string name, float x) {
            glUniform1f(this->uniforms.at(name), x);
        }
        
        void Uniform::uniform2f(std::string name, float x, float y) {
            glUniform2f(this->uniforms.at(name), x, y);
        }
        
        void Uniform::uniform3f(std::string name, float x, float y, float z) {
            glUniform3f(this->uniforms.at(name), x, y, z);
        }
        
        void Uniform::uniform4f(std::string name, float x, float y, float z, float w) {
            glUniform4f(this->uniforms.at(name), x, y, z, w);
        }
        
        // Matrix
        void Uniform::uniformMat2(std::string name, const glm::mat2& m) {
            glUniformMatrix2fv(this->uniforms.at(name), 1, GL_FALSE, &m[0][0]);
        }
        
        void Uniform::uniformMat3(std::string name, const glm::mat3& m) {
            glUniformMatrix3fv(this->uniforms.at(name), 1, GL_FALSE, &m[0][0]);
        }
        
        void Uniform::uniformMat4(std::string name, const glm::mat4& m) {
            glUniformMatrix4fv(this->uniforms.at(name), 1, GL_FALSE, &m[0][0]);
        }
        
        // Attribute
        void Attribute::init(Program* program) {
            this->program = program;
            glGenVertexArrays(1, &this->id);
        }

        void Attribute::release() {
            glDeleteVertexArrays(1, &this->id);
            this->program = nullptr;
        }

        void Attribute::bind() {
            glBindVertexArray(this->id);
        }

        void Attribute::unbind() {
            glBindVertexArray(0);
        }

        void Attribute::createAttribute(std::string name, uint32_t value) {
            this->attributes[name] = value;
        }

        void Attribute::enableAttribute(std::string name) {
            glEnableVertexAttribArray(this->attributes.at(name));
        }

        void Attribute::disableAttribute(std::string name) {
            glDisableVertexAttribArray(this->attributes.at(name));
        }

        void Attribute::pointer(std::string name, uint32_t size, GLenum type) {
            glVertexAttribPointer(this->attributes.at(name), size, type, GL_FALSE, 0, nullptr);
        }

        // Program
        void Program::init(std::vector<Shader*> shaders) {
            this->id = glCreateProgram();

            std::for_each(shaders.begin(), shaders.end(), [&](Shader* shader) {
                this->shaders.push_back(shader);
                glAttachShader(this->id, shader->id);
            });

            glLinkProgram(this->id);
        }

        void Program::release() {
            std::for_each(shaders.begin(), shaders.end(), [&](Shader* shader) {
                shader = nullptr;
                glDetachShader(this->id, shader->id);
            });

            shaders.clear();

            glDeleteProgram(this->id);
        }

        void Program::bind() {
            glUseProgram(this->id);
        }

        void Program::unbind() {
            glUseProgram(0);
        }


        // VertexBuffer
        void VertexBuffer::add1(float x) {
            this->list.push_back(x);
        }

        void VertexBuffer::add2(float x, float y) {
            this->list.push_back(x);
            this->list.push_back(y);
        }

        void VertexBuffer::add3(float x, float y, float z) {
            this->list.push_back(x);
            this->list.push_back(y);
            this->list.push_back(z);
        }

        void VertexBuffer::add4(float x, float y, float z, float w) {
            this->list.push_back(x);
            this->list.push_back(y);
            this->list.push_back(z);
            this->list.push_back(w);
        }

        void VertexBuffer::clear() {
            this->list.clear();
        }

        void VertexBuffer::init() {
            glGenBuffers(1, &this->id);
        }

        void VertexBuffer::release() {
            glDeleteBuffers(1, &this->id);
        }

        void VertexBuffer::update() {
            this->bind();
            glBufferData(GL_ARRAY_BUFFER, this->dataSize(), this->list.data(), GL_DYNAMIC_DRAW);
            this->unbind();
        }

        void VertexBuffer::bind() {
            glBindBuffer(GL_ARRAY_BUFFER, id);
        }

        void VertexBuffer::unbind() {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        size_t VertexBuffer::typeSize() {
            return sizeof(float);
        }

        size_t VertexBuffer::count() {
            return list.size();
        }

        size_t VertexBuffer::dataSize() {
            return this->typeSize() * this->count();
        }

        // IndexBuffer
        void IndexBuffer::add1(uint32_t x) {
            this->list.push_back(x);
        }

        void IndexBuffer::add2(uint32_t x, uint32_t y) {
            this->list.push_back(x);
            this->list.push_back(y);
        }

        void IndexBuffer::add3(uint32_t x, uint32_t y, uint32_t z) {
            this->list.push_back(x);
            this->list.push_back(y);
            this->list.push_back(z);
        }

        void IndexBuffer::add4(uint32_t x, uint32_t y, uint32_t z, uint32_t w) {
            this->list.push_back(x);
            this->list.push_back(y);
            this->list.push_back(z);
            this->list.push_back(w);
        }

        void IndexBuffer::clear() {
            this->list.clear();
        }

        void IndexBuffer::init() {
            glGenBuffers(1, &this->id);
        }

        void IndexBuffer::release() {
            glDeleteBuffers(1, &this->id);
        }

        void IndexBuffer::update() {
            this->bind();
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->dataSize(), this->list.data(), GL_DYNAMIC_DRAW);
            this->unbind();
        }

        void IndexBuffer::bind() {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        }

        void IndexBuffer::unbind() {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        size_t IndexBuffer::typeSize() {
            return sizeof(uint32_t);
        }

        size_t IndexBuffer::count() {
            return list.size();
        }

        size_t IndexBuffer::dataSize() {
            return this->typeSize() * this->count();
        }

    }
}