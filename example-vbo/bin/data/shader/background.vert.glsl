#version 150

uniform mat4 u_viewProjectionMatrix;
uniform mat4 u_modelMatrix;
in vec4 a_vertex;
out vec3 v_ray;

void main(void) {
	v_ray = normalize(a_vertex.xyz);
        gl_Position = u_viewProjectionMatrix*u_modelMatrix*a_vertex;
}
