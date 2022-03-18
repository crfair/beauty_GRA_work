#include "ofMain.h"
#include "..\swarming.h"

int main() {
	ofSetupOpenGL(1280, 1060, OF_WINDOW);
	ofRunApp(new swarming());
	
	//swarming app;
	//app.backSubKNN();
}