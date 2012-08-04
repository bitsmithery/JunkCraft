#ifndef APP_GRAPHICS_BASIC_PGRAM_HPP
    #define APP_GRAPHICS_BASIC_PROGRAM_HPP

    #include "../util/cache.hpp"
    #include "shader.hpp"
    #include <vector>
    #include <utility>
    #include <memory>

    namespace app
    {
        namespace graphics
        {
            class program_linking_failure
                : public std::runtime_error
            {
                public:
                    program_linking_failure(std::vector<std::string> const& paths, std::string const& log);
                    ~program_linking_failure() noexcept;

                    std::vector<std::string> paths;
                    std::string log;
            };
            class uniform_not_found
                : public std::runtime_error
            {
                public:
                    uniform_not_found(std::string const& name);
                    ~uniform_not_found() noexcept;

                    std::string parametr_name;
            };

            template <typename Program>
            class basic_program
            {
                public:
                    static util::cache<Program> cache;
                    GLuint handle;

                    basic_program(std::vector<std::shared_ptr<shader const>> const& shaders);
                    basic_program& operator=(basic_program const& that) = delete;
                    basic_program(basic_program const& that) = delete;
                    ~basic_program();

                protected:
                    template <typename... Arguments>
                    class uniform
                    {
                        public:
                            uniform(Program const* program, std::string const& name);
                            uniform& operator=(uniform const& that) = delete;
                            uniform(uniform const& that) = delete;

                            void operator()(Arguments... arguments) const;

                        private:
                            GLint location;
                            Program const* program;
                    };

                private:
                    std::vector<std::shared_ptr<shader const>> shaders;

                    GLuint get_linked_program(std::vector<std::shared_ptr<shader const>> const& sources);
            };
        }
    }

    #include "basic_program.inl"

#endif // APP_GRAPHICS_BASIC_PROGRAM_HPP
