#include "shape.hpp"
#include <iostream>
#include <fstream>
#include <string>

namespace app
{
    namespace graphics
    {
        shaders::shader_loader loader;
        shape::shape()
        {

            loader.load_circle_shader();
            loader.load_line_shader();
            cached = false;

            nodes.push_back({{500,500},100,0,primitives::node_type::inner});
            nodes.push_back({{600,600},100,0,primitives::node_type::inner});
        }
        shape::~shape()
        {

        }
        bool shape::is_cached()
        {
            return cached;
        }
        static
        primitives::canonical_line calculate_canonical_line(primitives::node node_a, primitives::node node_b)
        {
            float buf1,buf2;
            float vx = node_b.center.x - node_a.center.x;
            float vy = node_b.center.y - node_a.center.y;
            float d1 = +node_a.radius;
            float d2 = +node_b.radius;

            buf2 = vx*vx+vy*vy;
            buf1 = sqrt(buf2-(d2-d1)*(d2-d1));

            float a = ((d2-d1)*vx+vy*buf1)/buf2;
            float b = ((d2-d1)*vy-vx*buf1)/buf2;
            float c = d1 - a*node_a.center.x - b*node_a.center.y;
            return {a,b,c};
        }
        void shape::cache()
        {
            for(auto i=nodes.begin(); i!=nodes.end(); ++i)
            {

            }
        }
        void shape::draw()
        {

            glUseProgram(loader.line_prog);
            primitives::canonical_line strei = calculate_canonical_line(nodes[0],nodes[1]);
            loader.set_shader_uniform3f(loader.line_prog,"parameters",strei.a,strei.b,strei.c);
            glBegin(GL_QUADS);
                glVertex2f(0,0);
                glVertex2f(0,1280);
                glVertex2f(1920,1280);
                glVertex2f(1920,0);
            glEnd();

            glUseProgram(loader.circle_prog);
            for(auto i=nodes.begin(); i!=nodes.end(); ++i)
            {
                loader.set_shader_uniform3f(loader.line_prog,"parameters",i->center.x,i->center.y,i->radius);
                glBegin(GL_QUADS);
                    glVertex2f(0,0);
                    glVertex2f(0,1280);
                    glVertex2f(1920,1280);
                    glVertex2f(1920,0);
                glEnd();

            }
            glUseProgram(0);
        }
    }
}
