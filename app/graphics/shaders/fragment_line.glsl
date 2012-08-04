#version 110
uniform vec3 parameters;

void main(void)
{
    float x = gl_FragCoord.x;
    float y = gl_FragCoord.y;
    if (abs(parameters.x*x + parameters.y*y + parameters.z)  <= 5.0)
    {
        gl_FragColor = vec4(1.0,1.0,0.0,1.0);
    }
}

