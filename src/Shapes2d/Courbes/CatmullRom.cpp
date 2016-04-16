#include "CatmullRom.h"

CatmullRom::CatmullRom(int controlPoints)
{
    ctrlPoints = controlPoints + 1;
}

void CatmullRom::Create(int x1, int y1, int width, int height){

    this->setTranslation(ofVec3f(x1, y1));

    int padding = width < 10 ? 0 : 5;
    points.clear();

    points.push_back(ofPoint(padding, padding));

    double xDiff = (width) / ctrlPoints;
    double yDiff = (height) / ctrlPoints;
    double zDiff = 0;//(endPoint.z - startPoint.z) / ctrlPoints;

    for(int i = 1; i < ctrlPoints; i++){
        ofPoint tmp;
        tmp.x = points[i - 1].x + xDiff;
        tmp.y = points[i - 1].y + yDiff;
        tmp.z = points[i - 1].z + zDiff;
        points.push_back(tmp);
    }

    points.push_back(ofPoint(width - padding, height - padding));

    topLeftPoint.set(0, 0);
    topRightPoint.set(width, 0);
    bottomLeftPoint.set(0, height);
    bottomRightPoint.set(width, height);
    refreshBorders();
}

void CatmullRom::AddTranslation(int x, int y, ofVec3f _draggedPixelVector){
    ofPoint * inersected = intersectsPoint(x - this->getTranslation().x, y - this->getTranslation().y);
    if(inersected == nullptr){
        Object2D::AddTranslation(x, y, _draggedPixelVector);
    }else{
        inersected->x = x - this->getTranslation().x;
        inersected->y = y - this->getTranslation().y;
    }

}

void CatmullRom::drawShape(){
    if(points.size() < 2)
        return;
    ofFill();
    ofSetColor(0);
    for(ofPoint & p : points){
        ofEllipse(p.x, p.y, 10, 10);
    }
    curve.clear();

    for(float t = 0.f; t <= 1; t += 0.01f){
        curve.curveTo(Catmull(points[0], points[0], points[1], points[2], t));
    }

    for (int i = 0; i < points.size() - 3; i++){
        for(float t = 0.f; t <= 1; t += 0.01f){
            ofPoint tmp = Catmull(points[i], points[i + 1], points[i + 2], points[i + 3], t);
            curve.curveTo(Catmull(points[i], points[i + 1], points[i + 2], points[i + 3], t));
        }
    }

    for(float t = 0.f; t <= 1; t += 0.01f){
        curve.curveTo(Catmull(points[points.size() - 3], points[points.size() - 2], points[points.size() - 1], points[points.size() - 1], t));
    }

    curve.draw();
}

void CatmullRom::refreshPoints(){}

void CatmullRom::affectPoint(int deltaX, int deltaY){
    ofPoint * toAffect = intersectsPoint(deltaX, deltaY);
    if(toAffect == nullptr)
        return;
    toAffect->x = deltaX;
    toAffect->y = deltaY;
}

ofPoint CatmullRom::getPointX(int val){
    int index = -1;

    for (int i = 0; i < points.size() && index < 0; i++){
        if(points[i].x > val){
            index = i - 1;
            break;
        }
    }

    if(index  == 1){
        bool a = true;
    }else if(index > 1){
        bool a = true;
    }

    float tVal;
    ofPoint * p0, * p1, * p2, * p3;
    if(index == 0){
         p0 = &points[0];
         p1 = &points[0];
         p2 = &points[1];
         p3 = &points[2];
         tVal = (float) (val - p1->x) / (float)(p2->x - p1->x);
    }else if(index > points.size() - 3){
        p0 = &points[points.size() - 3];
        p1 = &points[points.size() - 2];
        p2 = &points[points.size() - 1];
        p3 = &points[points.size() - 1];
        tVal = (float) (val - p1->x) / (float)(p2->x - p1->x);
    }else{
        p0 = &points[index - 1];
        p1 = &points[index];
        p2 = &points[index + 1];
        p3 = &points[index + 2];
        tVal = (float) (val - p1->x) / (float)(p2->x - p1->x);
    }

    return Catmull(*p0, *p1, *p2, *p3, tVal);
}

ofPoint CatmullRom::getPointZ(int val){
    int index = -1;

    for (int i = 0; i < points.size() && index < 0; i++){
        if(points[i].z > val){
            index = i - 1;
            break;
        }
    }

    if(index  == 1){
        bool a = true;
    }else if(index > 1){
        bool a = true;
    }

    float tVal;
    ofPoint * p0, * p1, * p2, * p3;
    if(index == 0){
         p0 = &points[0];
         p1 = &points[0];
         p2 = &points[1];
         p3 = &points[2];
         tVal = (float) (val - p1->z) / (float)(p2->z - p1->z);
    }else if(index > points.size() - 3){
        p0 = &points[points.size() - 3];
        p1 = &points[points.size() - 2];
        p2 = &points[points.size() - 1];
        p3 = &points[points.size() - 1];
        tVal = (float) (val - p1->z) / (float)(p2->z - p1->z);
    }else{
        p0 = &points[index - 1];
        p1 = &points[index];
        p2 = &points[index + 1];
        p3 = &points[index + 2];
        tVal = (float) (val - p1->z) / (float)(p2->z - p1->z);
    }

    return Catmull(*p0, *p1, *p2, *p3, tVal);
}

ofPoint CatmullRom::Catmull(const ofPoint & p0, const ofPoint & p1, const ofPoint & p2, const ofPoint & p3, float t){
    return 0.5 * (  (2 * p1) + (-p0 + p2) * t +
                    (2 * p0 - 5 * p1 + 4 * p2 - p3) * pow(t, 2) +
                    (-p0 + 3 * p1 - 3 * p2 + p3) * pow(t, 3));
}
