#include "ofMain.h"

#include "ofxTinyObjLoader.h"

class ofApp : public ofBaseApp
{
	ofEasyCam cam;
	ofLight light;
	vector<ofxTinyObjLoader::Shape> shapes;
	
public:
	
	void setup()
	{
		ofSetFrameRate(60);
		ofSetVerticalSync(true);
		
		shapes = ofxTinyObjLoader::load("cornell_box.obj");
		
		cout << "size: " << shapes.size() << endl;
		
		light.enable();
	}
	
	void update()
	{
		
	}
	
	void draw()
	{
		cam.begin();
		
		ofDrawAxis(100);
		
		for (auto s: shapes)
			s.draw();
		
		cam.end();
	}
};



#pragma mark -
#pragma mark main
int main(){
	ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofRunApp(new ofApp());
}
