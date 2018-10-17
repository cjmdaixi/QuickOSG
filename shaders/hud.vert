#version 430

void main(){
    const vec4 vertices[4] = {
        vec4(-1, -1, 0, 1),
        vec4(1, -1, 0, 1),
        vec4(-1, 1, 0, 1),
        vec4(1, 1, 0, 1)
    };
   gl_Position = vertices[gl_VertexID];
}
