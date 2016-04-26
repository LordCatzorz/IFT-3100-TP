#include "Surface.h"

Surface::Surface(int var1, int var2, int var3, int var4, const ofFloatColor & color)
{
    int size = 200;
    mesh;

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
    s1 = new CatmullRom(var1, 20);
    s1->Create(p1, p2);
    s2 = new CatmullRom(var2, 20);
    s2->Create(p2, p3);
    s3 = new CatmullRom(var3, 20);
    s3->Create(p4, p3);
    s4 = new CatmullRom(var4, 20);
    s4->Create(p1, p4);

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
        }
    }

    for(int i = 0; i < size * size; i++){
        mesh.addVertex(points[i]);
    }

    int width = size, height = size;
    for (int y = 0; y<height; y++){
        for (int x=0; x<width; x++){
            mesh.addIndex(x+y*width);
            mesh.addIndex((x+1)+y*width);
            mesh.addIndex(x+(y+1)*width);

            mesh.addIndex((x+1)+y*width);
            mesh.addIndex((x+1)+(y+1)*width);
            mesh.addIndex(x+(y+1)*width);
        }
    }
    setMaterialColor(color);
}

void Surface::Draw(){
    ofPushMatrix();
    ofTranslate(400, 400, 250);
    mesh.drawVertices();
    ofPopMatrix();
}

void Surface::setMaterialColor(const ofFloatColor &color){
    material.setAmbientColor(color);
    material.setEmissiveColor(color);
    material.setDiffuseColor(color);
}

int Surface::lerp(int u, int v, int p1, int p2){
    return (1 - v)* p1 + v * p2;
}

int Surface::blerp(int u, int v, int p1, int p2, int p3, int p4){
    return (1 - u) * (1 - v) * p1 + u * (1 - v) * p2 + (1 - u) * v * p3 + u * v * p4;
}
