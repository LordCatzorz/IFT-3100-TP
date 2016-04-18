#include "Surface.h"

Surface::Surface()
{
    int size = 200;
    mesh;// = ofMesh::plane(size, size, 100, 100, OF_PRIMITIVE_TRIANGLES);
    /*vector<ofVec3f> verts = mesh.getVertices();

        for (int i=0; i<verts.size(); i++) {
            mesh.setTexCoord(i, ofVec2f(verts[i].x, verts[i].y));
        }*/
    ofPoint p1, p2, p3, p4;
    p1.x = 0;
    p1.y = 0;
    p1.z = 0;

    p2.x = 0;
    p2.y = 0;
    p2.z = size;

    p3.x = size;
    p3.y = 0;
    p3.z = size;

    p4.x = size;
    p4.y = 0;
    p4.z = 0;
    /*s1 = new CatmullRom(p1, p2, 2);
    s2 = new CatmullRom(p2, p3, 2);
    s3 = new CatmullRom(p4, p3, 2);
    s4 = new CatmullRom(p1, p4, 2);

    for(double i = 0; i <= size; i++){
        for(double j = 0; j <= size; j++){
            double s = i / (double)size;
            double t = j / (double)size;
            points.push_back(((1 - t) * s4->getPointX(i) + t * s2->getPointX(i)) +
                             ((1 - s) * s1->getPointZ(j) + s * s3->getPointZ(j)) -
                                ((1 - s) * (1 - t) * p1 +
                                (1 - s) * t * p2 +
                                s * (1 - t) * p4 +
                                s * t * p3));
            mesh.addVertex(points[points.size() - 1]);
        }
    }

    for(int i = 0; i < size; i++){
        mesh.addVertex(points[i]);
    }

    int width = size, height = size;

    for (int y = 0; y<height-1; y++){
        for (int x=0; x<width-1; x++){
            mesh.addIndex(x+y*width);               // 0
            mesh.addIndex((x+1)+y*width);           // 1
            mesh.addIndex(x+(y+1)*width);           // 10

            mesh.addIndex((x+1)+y*width);           // 1
            mesh.addIndex((x+1)+(y+1)*width);       // 11
            mesh.addIndex(x+(y+1)*width);           // 10
        }
    }*/
}

void Surface::Draw(){
    ofPushMatrix();
    ofTranslate(400, 400, 250);
    mesh.drawWireframe();
    s1->Draw();
    s2->Draw();
    s3->Draw();
    s4->Draw();
    ofSetColor(200, 0, 0, 255);
    /*for(ofPoint & x : points){
        ofEllipse(x, 1, 1);
    }*/
    ofPopMatrix();
}

int Surface::lerp(int u, int v, int p1, int p2){
    return (1 - v)* p1 + v * p2;
}

int Surface::blerp(int u, int v, int p1, int p2, int p3, int p4){
    return (1 - u) * (1 - v) * p1 + u * (1 - v) * p2 + (1 - u) * v * p3 + u * v * p4;
}