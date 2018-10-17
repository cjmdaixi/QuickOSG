#version 430
out vec4 fragColor;

uniform vec2 viewport;

struct FillingSwapData{
    uint color;
    float nx, ny, nz;
    float z;
    bool empty, valid;
};

layout(std430, binding=2) buffer SurfSplitsSwap{
    FillingSwapData p[];
};

const vec3 lightDir = vec3(0, 0, 1);
void main(){
    int storePos = int(viewport.x * gl_FragCoord.y + gl_FragCoord.x);

    if(p[storePos].valid){
        vec4 clr = unpackUnorm4x8(p[storePos].color);
        vec3 normal = vec3(p[storePos].nx, p[storePos].ny, p[storePos].nz);
        float spec = dot(normal, lightDir);
        if(spec > 0)
            fragColor = vec4(clr.rgb * spec, 1.0f);
        else
            fragColor = vec4(vec3(clr.r, clr.r, clr.r) * (-spec), 1.0f);
        //fragColor = vec4(1, 0, 0, 1.0f);
    }
    else{
        discard;
    }

//    if(delta > 1.5f){
//        fragColor = vec4(1.0, 0, 0, 1);
//    }else{
//        fragColor = vec4(0, 1, 0, 1);
//    }
}
