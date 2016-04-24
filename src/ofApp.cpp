#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    mouseWatcher = new MouseWatcher();
    this->renderer = new Renderer();
    this->renderer->Setup();
    this->renderer->SetMouseRecorder(mouseWatcher);
    ofEnableDepthTest();
    ofSetFrameRate(24);

}

//--------------------------------------------------------------
void ofApp::update()
{
    this->renderer->Update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofEnableDepthTest();

    this->renderer->Draw();

    ofDisableDepthTest();

	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == '1')
	{
		this->altKeyPressed = !this->altKeyPressed;
	}
	else if (key == '2')
	{
		this->ctrlKeyPressed = !this->ctrlKeyPressed;
	}
	else if (key == '3')
	{
		this->shiftKeyPressed = !this->shiftKeyPressed;
	}
	else if (key == 'w')
	{
		this->renderer->TestMoveUp();
	}
	else if(key == 's')
	{
		this->renderer->TestMoveDown();
	}
	else if (key == 'a')
	{
		this->renderer->TestMoveLeft();
	}
	else if (key == 'd')
	{
		this->renderer->TestMoveRight();
	}
	else if (key == 'q')
	{
		this->renderer->TestZoomOut();
	}
	else if (key == 'e')
	{
		this->renderer->TestZoomIn();
	}
	else if (key == 'r')
	{
		if (this->ctrlKeyPressed)
		{
			this->renderer->TestRotateY();
		}
		if (this->altKeyPressed)
		{
			this->renderer->TestRotateZ();
		}
		if (this->shiftKeyPressed)
		{
			this->renderer->TestRotateX();
		}
	}
	else if (key == 't')
	{
		if (this->ctrlKeyPressed)
		{
			this->renderer->TestRotateYNeg();
		}
		if (this->altKeyPressed)
		{
			this->renderer->TestRotateZNeg();
		}
		if (this->shiftKeyPressed)
		{
			this->renderer->TestRotateXNeg();
		}
		
	}
	else if (key == 'z')
	{
		this->renderer->TestCreateTetrahedron();
	}
	else if (key == 'x')
	{
		this->renderer->TestCreateHexahedron();
	}
	else if (key == 'c')
	{
		this->renderer->TestCreateOctahedron();
	}
	else if (key == 'v')
	{
		this->renderer->TestCreateDodecahedron();
	}
	else if (key == 'b')
	{
		this->renderer->TestCreateIcosahedron();
	}
	else if (key == 'f')
	{
		this->renderer->TestSelectPrevious();
	}
	else if (key == 'g')
	{
		this->renderer->TestSelectNext();
	}
	else if (key == 'h')
	{
		this->renderer->TestDeselectAll();
	}
	

    this->renderer->KeyDown(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    this->renderer->KeyUp(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    mouseWatcher->Record(x, y, button, MouseWatcher::Drag);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    mouseWatcher->Record(x, y, button, MouseWatcher::Down);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    mouseWatcher->Record(x, y, button, MouseWatcher::Up);
    mouseWatcher->StopRecording(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
    mouseWatcher->ResumeRecording();
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
    mouseWatcher->PauseRecording();
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
