#version 110
uniform vec3 parameters;

void main(void)
{
    float x = gl_FragCoord.x;
    float y = gl_FragCoord.y;
    float xc = parameters.x;
    float yc = parameters.y;
    float r = parameters.z;
    if ((x-xc)*(x-xc)+(y-yc)*(y-yc) <= r*r)
    {
        gl_FragColor = vec4(0.0,1.0,0.0,1.0);
    }
}

