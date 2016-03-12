#pragma once

#include <stdio.h>
#include "Renderer.h"
#include <fstream>
#include <iterator>
#include <algorithm>
#include "ofMain.h"
#include "Shape.h"
#include "Shapes.h"
#include "GUI.h"
#include "MouseWatcher.h"
#include "Image.h"
#include "../DelegatesLib/FastDelegate.h"
#include "ofxAssimpModelLoader.h"

using namespace fastdelegate;
class ofApp : public ofBaseApp{

	public:
        const static int SCREEN_WIDTH = 1024, SCREEN_HEIGHT = 1024;

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        of3dPrimitive* primitive3d;
        /*void FileOpenCallback(string param);
        void PrintScreenTakenCallback(string param);
        void printScreenTakenCallback(int x, int y, int width, int height, string param);
        void PrintScreenSectionCallback(string arg);
        void ModeChangeCallback(GUI::ActionType newMode);
		void ImportObjFileCallback(string param);


        void someFunction(int x, int y);*/
    private:
        MouseWatcher * mouseWatcher;
        //typedef FastDelegate2<int, int> MouseActionDelegate;
        //MouseActionDelegate mouseDownDelegates[12];
        //MouseActionDelegate mouseUpDelegates[12];

        /*void beginSelectionZoneDraw(int x, int y);
        void endSelectionZoneDraw(int x, int y);

        void takeScreenshotSection(int x, int y);

        GUI* Gui;

        std::vector<Shape*> visibleShapes;
        std::vector<Shape*> selectedShapes;
        void saveFile(string path, std::ifstream & file);

        bool isRecordingMouseMouvements = false;
        bool isMakingScreenshotSection = false;*/

		ofxAssimpModelLoader* importedModel;
        
        //GUI::ActionType actionMode = GUI::ActionType::Select;
		int iteration;

        //Renderer* renderer;
};
