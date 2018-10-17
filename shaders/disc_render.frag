#version 430

layout(early_fragment_tests) in;

in vec3 color;
in vec3 normal;
in vec3 position;

out vec4 fragColor;

uniform vec2 viewport;

const vec3 lightDir = vec3(0, 0, 1);

void main(){
    float spec = dot(normal, lightDir);
    if(spec > 0)
        fragColor = vec4(color * spec, 1.0f);
    else
        fragColor = vec4(vec3(0.5, 0.5, 0.5) * (-spec), 1.0f);
}
