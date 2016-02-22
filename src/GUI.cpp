#include "GUI.h"

GUI::GUI()
{
    openFileBtn.addListener(this, &GUI::openFileBtnCallback);
    gui.setup();
    gui.add(openFileBtn.setup("Ouvir une image"));
}

void GUI::AddImageOpenedListener(void (inCallBackFunction)(string)){
    callBackFunction = inCallBackFunction;
}

void GUI::Draw(){
    ofSetColor(255);
    ofFill();
    gui.draw();
}

void GUI::openFileBtnCallback(){
    ofFileDialogResult result = requestUsrFile();
    std::ifstream input( result.filePath, std::ios::binary );
    saveFile("./data/" + result.fileName, input);
    input.close();

    callBackFunction(result.fileName);
}

/*
    ofImage * image = new ofImage();
    image->load("labo3.png");
    image->draw(10, 10, 300, 300);
    */

ofFileDialogResult GUI::requestUsrFile(){
    ofFileDialogResult result = ofSystemLoadDialog("Open File");
    return result;
}

void GUI::saveFile(string path, std::ifstream & file){
    std::ofstream output(path, std::ios::binary );

    std::copy(
     std::istreambuf_iterator<char>(file),
     std::istreambuf_iterator<char>( ),
     std::ostreambuf_iterator<char>(output));
    output.close();
}
