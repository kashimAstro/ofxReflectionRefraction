#version 150

//http://en.wikipedia.org/wiki/Refractive_index Reflectivity
//http://en.wikipedia.org/wiki/Schlick%27s_approximation

const float Air = 2.0;//1.0
const float Glass = 4.5667;//1.51714;
const float Eta = Air / Glass;
const float R0 = ((Air - Glass) * (Air - Glass)) / ((Air + Glass) * (Air + Glass));

uniform mat4 u_viewProjectionMatrix;
uniform mat4 u_modelMatrix;
uniform mat3 u_normalMatrix;
uniform vec4 u_camera;

in vec4 a_vertex;
in vec3 a_normal;

out vec3 v_reflection;
out vec3 v_refraction;
out float v_fresnel;

void main(void) {
	vec4 vertex = u_modelMatrix*a_vertex;	
	vec3 incident = normalize(vec3(vertex-u_camera));
	vec3 normal = u_normalMatrix*a_normal;	
	v_refraction = refract(incident, normal, Eta);
        v_reflection = reflect(incident, normal);
        v_fresnel = R0 + (1.0 - R0) * pow((1.0 - dot(-incident, normal)), 2.5);
	gl_Position = u_viewProjectionMatrix*vertex;
}
