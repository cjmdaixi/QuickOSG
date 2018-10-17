#version 120

uniform mat4 osg_ModelViewMatrix;
uniform mat4 osg_ModelViewProjectionMatrix;
uniform mat3 osg_NormalMatrix;

varying vec3 color;
varying vec3 normal;
varying vec3 position;

void main(){
   color = gl_Color.rgb;
   normal = osg_NormalMatrix * gl_Normal;
   gl_Position = osg_ModelViewProjectionMatrix * gl_Vertex;
   position = gl_Position.xyz;
}
