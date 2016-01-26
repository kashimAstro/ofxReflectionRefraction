#include "ofMain.h"


#define str(A) #A
class GLSL{
    public:

    vector<string> setup() {
        vector<string> result;
        string version = "\n#version 150\n";

        string bgfrag = str(
		uniform samplerCube u_cubemap;
		in vec3 v_ray;
		out vec4 fragColor;

		void main(void){
			fragColor = texture(u_cubemap, v_ray);
		}
	);

        string bgvert = str(
		uniform mat4 u_viewProjectionMatrix;
		uniform mat4 u_modelMatrix;
		in vec4 a_vertex;
		out vec3 v_ray;

		void main(void) {
			v_ray = normalize(a_vertex.xyz);
		        gl_Position = u_viewProjectionMatrix*u_modelMatrix*a_vertex;
		}
	);

        string glassfrag = str(
		uniform samplerCube u_cubemap;
		in vec3 v_refraction;
		in vec3 v_reflection;
		in float v_fresnel;
		out vec4 fragColor;
		void main(void){
			vec4 refractionColor = texture(u_cubemap, normalize(v_refraction));
			vec4 reflectionColor = texture(u_cubemap, normalize(v_reflection));		
		        fragColor = mix(refractionColor, reflectionColor, v_fresnel);
		        fragColor.a=1.0;
		}
	);

        string glassvert = str(
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
	);

        result.push_back(version+bgvert);
        result.push_back(version+bgfrag);
        result.push_back(version+glassvert);
        result.push_back(version+glassfrag);
        return result;
    }

	
};
