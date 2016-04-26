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
        const static int SCREEN_WIDTH = 1024, SCREEN_HEIGHT = 768;

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

    private:
		bool ctrlKeyPressed;
		bool altKeyPressed;
		bool shiftKeyPressed;
        MouseWatcher * mouseWatcher;
        int iteration;

        Renderer* renderer;
};
