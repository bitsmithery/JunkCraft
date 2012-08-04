#include "basic_program.hpp"
namespace app
{
    namespace graphics
    {
        program_linking_failure::program_linking_failure(std::vector<std::string> const& paths, std::string const& log)
            :runtime_error("program_linking_failure")
            ,paths(paths)
            ,log(log)
        {
        }

        program_linking_failure::~program_linking_failure() noexcept
        {
        }
        uniform_not_found::uniform_not_found(std::string const& name)
            :runtime_error("uniform_not_found")
            ,parametr_name(name)
        {
        }

        uniform_not_found::~uniform_not_found() noexcept
        {
        }

        namespace detail
        {
            std::string get_log(GLuint program)
            {
                int len;
                glGetObjectParameterivARB(program, GL_OBJECT_INFO_LOG_LENGTH_ARB, &len);

                std::vector<char> log(len);
                glGetProgramInfoLog(program,len,0,log.data());
                return {log.begin(), log.end()};
            }
        }
    }
}
