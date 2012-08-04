#ifndef APP_GRAPHICS_SHADER_HPP
    #define APP_GRAPHICS_SHADERS_HPP

    #include <istream>
    #include <fstream>
    #include <vector>
    #include <stdexcept>
    #include "../util/cache.hpp"
    #include "../gl.hpp"

    namespace app
    {
        namespace graphics
        {
            class shader_compilation_failure
                : public std::runtime_error
            {
                public:
                    std::string path;
                    std::string log;
                    shader_compilation_failure(std::string const& path, std::string const& log);
                    ~shader_compilation_failure() noexcept;
            };

            class file_not_found
                : public std::runtime_error
            {
                public:
                    std::string path;
                    file_not_found(std::string const& path);
                    ~file_not_found() noexcept;
            };

            class shader
            {
                public:
                    static util::cache<shader> cache;

                    const std::string path;
                    const GLuint handle;

                    shader(std::string const& path, GLenum type);
                    shader& operator=(shader const& that) = delete;
                    shader(shader const& that) = delete;
                    ~shader();

                private:
                    GLuint compile_shader(std::string const& path, GLenum type);


            };


        }
    }


#endif // APP_SHADERS_HPP
