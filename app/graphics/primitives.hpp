#ifndef PRIMITIVES_HPP_INCLUDED
    #define PRIMITIVES_HPP_INCLUDED
    #include "../math/point.hpp"

    namespace app
    {
        namespace graphics
        {
            namespace primitives
            {
                enum class node_type {inner,outer};
                class node
                {
                    public:
                        math::pointf center;
                        float radius;
                        float inner_radius;
                        bool orientation;
                        node_type type;

                        node(math::pointf center, float radius, float inner_radius,node_type type);
                };

                inline
                node::node(math::pointf center, float radius, float inner_radius,node_type type )
                    :center(center)
                    ,radius(radius)
                    ,inner_radius(inner_radius)
                    ,type(type)
                {
                }

                class canonical_line
                {
                    public:
                        float a;
                        float b;
                        float c;

                        canonical_line(float a, float b, float c);
                };

                inline
                canonical_line::canonical_line(float a, float b, float c)
                    :a(a)
                    ,b(b)
                    ,c(c)
                {
                }
            }
        }
    }

#endif // PRIMITIVES_HPP_INCLUDED
