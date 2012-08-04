#ifndef SHAPE_HPP_INCLUDED
    #define SHAPE_HPP_INCLUDED

    #include "../gl.hpp"
    #include <vector>
    #include "primitives.hpp"
    #include <utility>
    #include "shaders.hpp"

    namespace app
    {
        namespace graphics
        {
            class shape
            {
                public:
                    shape();
                    ~shape();

                    bool is_cached();
                    void draw();
                private:
                    bool cached;
                    void load_shaders();
                    void cache();

                    void set_parametr(math::pointf position, float radius);

                    std::vector<primitives::node> nodes;
                    std::vector<primitives::canonical_line> lines;
            };
        }
    }

#endif // SHAPE_HPP_INCLUDED
