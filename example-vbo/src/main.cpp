#include "ofMain.h"
#include "ofxGui.h"
#include "ofxReflectionRefraction.h"

//Texture Map
//http://www.humus.name/index.php?page=Textures

class ofApp : public ofBaseApp {
	public:
		ofEasyCam cam;
		vector<ofImage> pos;
		vector<ofImage> neg;
        ofxPanel gui;
        ofParameter<ofVec3f> translate;
        ofxReflectionRefraction Ref;
        ofMesh sphere;

        void setup(){
            ofSetVerticalSync(false);

            gui.setup();
            gui.add(translate.set("translate",ofVec3f(0),ofVec3f(-1000),ofVec3f(1000)));

            sphere = ofMesh::sphere(100,20,OF_PRIMITIVE_TRIANGLES);
            ofImage px("cubemap6/posx.jpg"); pos.push_back(px);
            ofImage py("cubemap6/posy.jpg"); pos.push_back(py);
            ofImage pz("cubemap6/posz.jpg"); pos.push_back(pz);
            ofImage nx("cubemap6/negx.jpg"); neg.push_back(nx);
            ofImage ny("cubemap6/negy.jpg"); neg.push_back(ny);
            ofImage nz("cubemap6/negz.jpg"); neg.push_back(nz);
            Ref.setup(sphere,pos,neg);

			cam.setNearClip(.01);
			cam.setFarClip(100000);
		}

		void update(){
            ofSetWindowTitle(ofToString(ofGetFrameRate()));
		}

        void draw(){
            ofBackgroundGradient(ofColor(160),ofColor(0));

			cam.begin();
            ofEnableDepthTest();
            glEnable(GL_CULL_FACE);
            Ref.drawBackground(cam);
            Ref.drawMeshGlass(cam,translate.get());

            glDisable(GL_CULL_FACE);
            ofDisableDepthTest();
			cam.end();

            gui.draw();
		}

        void keyPressed(int key) {
            if(key == '1'){
                pos.clear(); neg.clear();
                ofImage px("cubemap1/posx.jpg"); pos.push_back(px);
                ofImage py("cubemap1/posy.jpg"); pos.push_back(py);
                ofImage pz("cubemap1/posz.jpg"); pos.push_back(pz);
                ofImage nx("cubemap1/negx.jpg"); neg.push_back(nx);
                ofImage ny("cubemap1/negy.jpg"); neg.push_back(ny);
                ofImage nz("cubemap1/negz.jpg"); neg.push_back(nz);
                Ref.setup(sphere,pos,neg);
            }
            if(key == '2'){
                pos.clear(); neg.clear();
                ofImage px("cubemap2/posx.jpg"); pos.push_back(px);
                ofImage py("cubemap2/posy.jpg"); pos.push_back(py);
                ofImage pz("cubemap2/posz.jpg"); pos.push_back(pz);
                ofImage nx("cubemap2/negx.jpg"); neg.push_back(nx);
                ofImage ny("cubemap2/negy.jpg"); neg.push_back(ny);
                ofImage nz("cubemap2/negz.jpg"); neg.push_back(nz);
                Ref.setup(sphere,pos,neg);
            }
            if(key == '3'){
                pos.clear(); neg.clear();
                ofImage px("cubemap3/posx.jpg"); pos.push_back(px);
                ofImage py("cubemap3/posy.jpg"); pos.push_back(py);
                ofImage pz("cubemap3/posz.jpg"); pos.push_back(pz);
                ofImage nx("cubemap3/negx.jpg"); neg.push_back(nx);
                ofImage ny("cubemap3/negy.jpg"); neg.push_back(ny);
                ofImage nz("cubemap3/negz.jpg"); neg.push_back(nz);
                Ref.setup(sphere,pos,neg);
            }
            if(key == '4'){
                pos.clear(); neg.clear();
                ofImage px("cubemap4/posx.jpg"); pos.push_back(px);
                ofImage py("cubemap4/posy.jpg"); pos.push_back(py);
                ofImage pz("cubemap4/posz.jpg"); pos.push_back(pz);
                ofImage nx("cubemap4/negx.jpg"); neg.push_back(nx);
                ofImage ny("cubemap4/negy.jpg"); neg.push_back(ny);
                ofImage nz("cubemap4/negz.jpg"); neg.push_back(nz);
                Ref.setup(sphere,pos,neg);
            }
            if(key == '5'){
                pos.clear(); neg.clear();
                ofImage px("cubemap5/posx.jpg"); pos.push_back(px);
                ofImage py("cubemap5/posy.jpg"); pos.push_back(py);
                ofImage pz("cubemap5/posz.jpg"); pos.push_back(pz);
                ofImage nx("cubemap5/negx.jpg"); neg.push_back(nx);
                ofImage ny("cubemap5/negy.jpg"); neg.push_back(ny);
                ofImage nz("cubemap5/negz.jpg"); neg.push_back(nz);
                Ref.setup(sphere,pos,neg);
            }
            if(key == '6'){
                pos.clear(); neg.clear();
                ofImage px("cubemap6/posx.jpg"); pos.push_back(px);
                ofImage py("cubemap6/posy.jpg"); pos.push_back(py);
                ofImage pz("cubemap6/posz.jpg"); pos.push_back(pz);
                ofImage nx("cubemap6/negx.jpg"); neg.push_back(nx);
                ofImage ny("cubemap6/negy.jpg"); neg.push_back(ny);
                ofImage nz("cubemap6/negz.jpg"); neg.push_back(nz);
                Ref.setup(sphere,pos,neg);
            }
            if(key == '7'){
                pos.clear(); neg.clear();
                ofImage px("cubemap7/posx.jpg"); pos.push_back(px);
                ofImage py("cubemap7/posy.jpg"); pos.push_back(py);
                ofImage pz("cubemap7/posz.jpg"); pos.push_back(pz);
                ofImage nx("cubemap7/negx.jpg"); neg.push_back(nx);
                ofImage ny("cubemap7/negy.jpg"); neg.push_back(ny);
                ofImage nz("cubemap7/negz.jpg"); neg.push_back(nz);
                Ref.setup(sphere,pos,neg);
            }
      }
};

int main(){
	ofSetupOpenGL(1024,768, OF_WINDOW);
	ofRunApp( new ofApp() );
}
