#version 430
layout(location=0) in vec4 vPosition;
layout(location=1) in vec3 vColor;
layout(location=2) in vec3 vNormal;

uniform mat4 osg_ModelViewMatrix;
uniform mat4 osg_ModelViewProjectionMatrix;
uniform mat3 osg_NormalMatrix;
uniform mat4 osg_ProjectionMatrix;

out vec3 color;
out vec3 normal;
out vec3 position;

void main(){
   color = vColor;
   //color = vec3(1, 0, 0);
   normal = osg_NormalMatrix * vNormal;

   gl_Position = osg_ModelViewProjectionMatrix * vPosition;
   vec4 mvPos = osg_ModelViewMatrix * vPosition;
/*   if(gl_Position.w > 1.0f)
       color = vec3(1, 0, 0);
   else
       color = vec3(0, 1, 0)*/;
   gl_PointSize = 800.0f / length(mvPos.xyz);
   //gl_PointSize = 10 * smoothstep(0, 1, gl_Position.z/gl_Position.w);
   position = gl_Position.xyz;
}
