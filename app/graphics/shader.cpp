#include "shader.hpp"
#include <iostream>

namespace app
{
    namespace graphics
    {
        static std::vector<char> get_source_from_file(std::string path);
        static std::string get_log(GLuint shader);
        util::cache<shader> shader::cache;

        shader_compilation_failure::shader_compilation_failure(std::string const& path, std::string const& log)
            : runtime_error("shader_compilation_failure")
            , path(path)
            , log(log)
        {
        }
        shader_compilation_failure::~shader_compilation_failure() noexcept
        {
        }
        file_not_found::file_not_found(std::string const& path)
            : runtime_error("file_not_found")
            , path(path)
        {
        }
        file_not_found::~file_not_found() noexcept
        {
        }

        shader::shader(std::string const& path, GLenum type)
            :path(path)
            ,handle(compile_shader(path,type))
        {
        }

        GLuint shader::compile_shader(std::string const& path, GLenum type)
        {
            std::vector<char> source = get_source_from_file(path);
            GLuint sh = glCreateShader(type);

            const char* src = source.data();
            int length = source.size();

            glShaderSource(sh, 1, &src, &length);
            glCompileShader(sh);

            GLint compiled;
            glGetObjectParameterivARB(sh, GL_COMPILE_STATUS, &compiled);

            if (!compiled)
            {
                std::string log = get_log(sh);
                glDeleteShader(sh);
                throw shader_compilation_failure(path,log);
            }
            return sh;
        }

        static std::vector<char> get_source_from_file(std::string path)
        {
            std::vector<char> source;
            std::ifstream file(path, std::ios::in);
            if (!file.is_open())
            {
                throw file_not_found(path);
            }

            file.seekg(0, std::ios_base::end);
            int length = file.tellg();
            file.seekg(0);
            source.resize(length);
            file.read(source.data(), length);

            file.close();

            return source;
        }

        static std::string get_log(GLuint shader)
        {
            int len;
            glGetObjectParameterivARB(shader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &len);

            std::vector<char> log(len);
            glGetInfoLogARB(shader,len,0,log.data());
            return {log.begin(), log.end()};
        }

        shader::~shader()
        {
            glDeleteShader(handle);
        }
    }
}
