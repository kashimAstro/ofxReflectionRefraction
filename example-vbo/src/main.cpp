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
        vector<ofxReflectionRefraction> Ref;
        ofMesh sphere;
        ofMesh box;

        void setup(){
            ofSetVerticalSync(false);

            gui.setup();
            gui.add(translate.set("translate",ofVec3f(120,0,150),ofVec3f(-1000),ofVec3f(1000)));

            sphere = ofMesh::sphere(100,20,OF_PRIMITIVE_TRIANGLES);
            box   = ofMesh::box(100,100,100,1,1,1);
            ofImage px("cubemap6/posx.jpg"); pos.push_back(px);
            ofImage py("cubemap6/posy.jpg"); pos.push_back(py);
            ofImage pz("cubemap6/posz.jpg"); pos.push_back(pz);
            ofImage nx("cubemap6/negx.jpg"); neg.push_back(nx);
            ofImage ny("cubemap6/negy.jpg"); neg.push_back(ny);
            ofImage nz("cubemap6/negz.jpg"); neg.push_back(nz);

            ofxReflectionRefraction r1;
            r1.setup(sphere,pos,neg,true);
            Ref.push_back(r1);
            ofxReflectionRefraction r2;
            r2.setup(box,pos,neg,false);
            Ref.push_back(r2);

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

            Ref[0].drawBackground(cam);

            Ref[0].drawMeshGlass(cam,ofVec3f(0));
            Ref[1].drawMeshGlass(cam,translate.get());

            glDisable(GL_CULL_FACE);
            ofDisableDepthTest();
            cam.end();

            gui.draw();
        }

        void reload(int num) {
            pos.clear(); neg.clear(); Ref.clear();
            ofImage px("cubemap"+ofToString(num)+"/posx.jpg"); pos.push_back(px);
            ofImage py("cubemap"+ofToString(num)+"/posy.jpg"); pos.push_back(py);
            ofImage pz("cubemap"+ofToString(num)+"/posz.jpg"); pos.push_back(pz);
            ofImage nx("cubemap"+ofToString(num)+"/negx.jpg"); neg.push_back(nx);
            ofImage ny("cubemap"+ofToString(num)+"/negy.jpg"); neg.push_back(ny);
            ofImage nz("cubemap"+ofToString(num)+"/negz.jpg"); neg.push_back(nz);
            ofxReflectionRefraction r;
            r.setup(sphere,pos,neg,true);
            Ref.push_back(r);
            r.setup(box,pos,neg,false);
        }

        void keyPressed(int key) {
            if(key == '1') reload(1);
            if(key == '2') reload(2);
            if(key == '3') reload(3);
            if(key == '4') reload(4);
            if(key == '5') reload(5);
            if(key == '6') reload(6);
            if(key == '7') reload(7);
      }
};

int main(){
    ofGLWindowSettings s;
    s.setGLVersion(3, 2);
    s.width=1366;
    s.height=768;
    ofCreateWindow(s);
    ofRunApp( new ofApp() );
}
