#include "ofMain.h"
#include "glsl.h"

class ofxReflectionRefraction : public ofBaseApp{
	public:
        ofShader bg;
        ofShader glass;
        ofVbo vbo,Box;
        int sizeVboMesh,sizeBox;
        unsigned int Ctexture;
        GLSL glsl;

        void prepareCubeMap(vector<ofImage> facePositive, vector<ofImage> faceNegative){
            int size = facePositive[0].getWidth();
            glDeleteTextures(1, &Ctexture);

            glGenTextures(1, &Ctexture);
            glBindTexture(GL_TEXTURE_CUBE_MAP, Ctexture);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            ofPixels px,nx,py,ny,pz,nz;
            px = facePositive[0].getPixels();
            py = facePositive[1].getPixels();
            pz = facePositive[2].getPixels();
            nx = faceNegative[0].getPixels();
            ny = faceNegative[1].getPixels();
            nz = faceNegative[2].getPixels();
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, px.getData());
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, py.getData());
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, pz.getData());
            glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, nx.getData());
            glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, ny.getData());
            glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, nz.getData());
        }

        void setup(ofMesh _mesh, vector<ofImage> positive, vector<ofImage> negative, bool noSky, int sizeSkyBox=2000){
            sizeVboMesh=_mesh.getNumIndices();
            vbo.setMesh(_mesh, GL_STATIC_DRAW);

            if(noSky) {
                ofMesh xbox = ofMesh::sphere(sizeSkyBox,20,OF_PRIMITIVE_TRIANGLES);
                sizeBox=xbox.getNumIndices();
                Box.setMesh(xbox, GL_STATIC_DRAW);
            }

            ofDisableArbTex();
            vector<string> v = glsl.setup();
            if(noSky) {                
                bg.setupShaderFromSource(GL_VERTEX_SHADER,v[0]);
                bg.setupShaderFromSource(GL_FRAGMENT_SHADER,v[1]);
                if(ofIsGLProgrammableRenderer()) {
                    bg.bindDefaults();
                }
                bg.linkProgram();
            }
            //
            glass.setupShaderFromSource(GL_VERTEX_SHADER,v[2]);
            glass.setupShaderFromSource(GL_FRAGMENT_SHADER,v[3]);
            if(ofIsGLProgrammableRenderer()) {
                glass.bindDefaults();
            }
            glass.linkProgram();


            prepareCubeMap(positive,negative);
        }

        ofMatrix3x3 mat4ToMat3(ofMatrix4x4 mat4) {
            return ofMatrix3x3(mat4._mat[0][0], mat4._mat[0][1], mat4._mat[0][2],
                               mat4._mat[1][0], mat4._mat[1][1], mat4._mat[1][2],
                               mat4._mat[2][0], mat4._mat[2][1], mat4._mat[2][2]);
        }

        void drawBackground(ofCamera cam){
            bg.begin();
            bg.setUniformMatrix4f("u_viewProjectionMatrix",cam.getProjectionMatrix());
            bg.setUniformMatrix4f("u_modelMatrix",cam.getModelViewMatrix());
            bg.setUniform4f("u_camera",cam.getGlobalPosition().x, cam.getGlobalPosition().y, cam.getGlobalPosition().z,0);
            bg.setUniform1i("u_cubemap", 0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, Ctexture);
            Box.drawElements(GL_TRIANGLES, sizeBox);
            bg.end();
        }

        void drawMeshGlass(ofCamera cam,ofVec3f translate) {
            ofMatrix4x4 tra;
            tra.preMultTranslate(translate);
            glass.begin();
            glass.setUniformMatrix4f("u_viewProjectionMatrix",cam.getProjectionMatrix());
            glass.setUniformMatrix4f("u_modelMatrix",cam.getModelViewMatrix()*tra);
            glass.setUniformMatrix3f("u_normalMatrix",mat4ToMat3(ofGetCurrentNormalMatrix()));
            glass.setUniform4f("u_camera",cam.getGlobalPosition().x,
                                          cam.getGlobalPosition().y,
                                          cam.getGlobalPosition().z,0);
            glass.setUniform1i("u_cubemap", 0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, Ctexture);
                vbo.drawElements(GL_TRIANGLES, sizeVboMesh);
            glass.end();
        }
};
