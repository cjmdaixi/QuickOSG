#version 120

varying vec3 color;
varying vec3 normal;
varying vec3 position;

const vec3 lightDir = vec3(0, 0, 1);

void main(){
    float spec = dot(normal, lightDir);
    if(spec > 0)
        gl_FragColor = vec4(color * spec, 1.0f);
    else
        gl_FragColor = vec4(vec3(0.5, 0.5, 0.5) * (-spec), 1.0f);
}
