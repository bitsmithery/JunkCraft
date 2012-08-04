namespace app
{
    namespace graphics
    {
        namespace detail
        {
            std::string get_log(GLuint program);

            inline void set_uniform(GLint location, float x)
            {
                glUniform1f(location, x);
            }
            inline void set_uniform(GLint location, float x, float y)
            {
                glUniform2f(location, x, y);
            }
            inline void set_uniform(GLint location, float x, float y, float z)
            {
                glUniform3f(location, x, y, z);
            }
            inline void set_uniform(GLint location, float x, float y, float z, float w)
            {
                glUniform4f(location, x, y, z, w);
            }
        }

        template <typename Program>
        util::cache<Program> basic_program<Program>::cache;

        template <typename Program>
        basic_program<Program>::basic_program(std::vector<std::shared_ptr<shader const>> const& sources)
            : handle(get_linked_program(sources))
            , shaders(sources)
        {
        }

        template <typename Program>
        basic_program<Program>::~basic_program()
        {
            glDeleteProgram(handle);
        }

        template <typename Program>
        GLuint basic_program<Program>::get_linked_program(std::vector<std::shared_ptr<shader const>> const& shaders)
        {
            GLuint program_object = glCreateProgram();

            for (auto i = shaders.begin(); i != shaders.end(); ++i)
            {
                 glAttachShader(program_object, (*i)->handle);
            }

            glLinkProgram(program_object);

            GLint linked;
            glGetProgramiv(program_object, GL_LINK_STATUS, &linked);
            if (!linked)
            {
                std::vector<std::string> paths;
                paths.reserve(shaders.size());
                for(auto i = shaders.begin(); i != shaders.end(); ++i)
                    paths.push_back((*i)->path);
                std::string log = detail::get_log(handle);
                glDeleteProgram(program_object);
                throw program_linking_failure(paths,log);
            }
            return program_object;
        }

        template <typename Program>
        template <typename... Arguments>
        basic_program<Program>::uniform<Arguments...>::uniform(Program const* program, std::string const& name)
            : location(glGetUniformLocation(program->handle, name.data()))
            , program(program)
        {
            if (location == -1)
                throw uniform_not_found(name);
        }

        template <typename Program>
        template <typename... Arguments>
        void basic_program<Program>::uniform<Arguments...>::operator()(Arguments... arguments) const
        {
            detail::set_uniform(location,arguments...);
        }
    }
}
