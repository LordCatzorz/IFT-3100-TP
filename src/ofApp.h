#pragma once

#include "ofMain.h"
#include "Shapes.h"
#include "GUI.h"
#include "MouseWatcher.h"
#include "Primitives.h"
#include <fstream>
#include <iterator>
#include <algorithm>

class ofApp : public ofBaseApp{

	public:
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
        ofMesh* mesh;
        void FileOpenCallback(string param);
    private:
        GUI* Gui;
        MouseWatcher * mouseWatcher;
        std::vector<Image> visibleImages;
        void saveFile(string path, std::ifstream & file);

        bool isRecordingMouseMouvements = false;
};
