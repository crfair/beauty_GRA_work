#include "ofMain.h"
#include "..\swarming.h"

int main() {
	
	ofSetupOpenGL(640, 480, OF_WINDOW);
	ofRunApp(new swarming());
	
	//swarming app;
	//app.backSubMOG2KNN("KNN");
}