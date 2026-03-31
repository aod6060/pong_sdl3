#include "sys.hpp"
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

        }
        
        void Uniform::uniform2i(std::string name, int x, int y) {

        }
        
        void Uniform::uniform3i(std::string name, int x, int y, int z) {

        }
        
        void Uniform::uniform4i(std::string name, int x, int y, int z, int w) {

        }
        
        // Float
        void Uniform::uniform1f(std::string name, float x) {

        }
        
        void Uniform::uniform2f(std::string name, float x, float y) {

        }
        
        void Uniform::uniform3f(std::string name, float x, float y, float z) {

        }
        
        void Uniform::uniform4f(std::string name, float x, float y, float z, float w) {

        }
        
        // Matrix
        void Uniform::uniformMat2(std::string name, const glm::mat2& m) {

        }
        
        void Uniform::uniformMat3(std::string name, const glm::mat3& m) {

        }
        
        void Uniform::uniformMat4(std::string name, const glm::mat4& m) {

        }
        
        // Attribute

        // Program

        // VertexBuffer

        // IndexBuffer


    }
}