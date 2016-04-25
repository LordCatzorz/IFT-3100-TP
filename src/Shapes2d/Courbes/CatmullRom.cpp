#include "CatmullRom.h"

CatmullRom::CatmullRom(int controlPoints, int initialOndulation)
{
    ctrlPoints = controlPoints + 1;
    baseOndulation = initialOndulation;
    shapeHasBorders = false;
}

void CatmullRom::Create(int x1, int y1, int width, int height, bool isXInverted, bool isYInverted){
    creator(x1, y1, 0, width * (isXInverted ? -1 : 1), height * (isYInverted ? -1 : 1), 0);
}

void CatmullRom::Create(const ofPoint &p0, const ofPoint &p1){
    creator(p0.x, p0.y, p0.z, p1.x, p1.y, p1.z, false);
}

void CatmullRom::creator(int x1, int y1, int z1, int width, int height, int depth, bool fixCoordinates){

    points.clear();

    double xDiff;
    double yDiff;
    double zDiff;

    if(fixCoordinates){
        this->setTranslation(ofVec3f(x1, y1, z1));
        points.push_back(ofPoint(width < 0 ? -width : 0, height < 0? -height : 0, depth < 0? depth : 0));
        xDiff = width / ctrlPoints;
        yDiff = height / ctrlPoints;
        zDiff = depth / ctrlPoints;
    }else{
        points.push_back(ofPoint(x1, y1, z1));
        xDiff = (width - x1) / ctrlPoints;
        yDiff = (height - y1) / ctrlPoints;
        zDiff = (depth - z1) / ctrlPoints;
    }

    for(int i = 1; i < ctrlPoints; i++){
        ofPoint tmp;
        tmp.x = points[i - 1].x + xDiff;
        tmp.y = points[i - 1].y + yDiff;
        tmp.z = points[i - 1].z + zDiff;
        points.push_back(tmp);
    }


        for(int i = 1; i < ctrlPoints; i++){
            points[i].y += baseOndulation;
            baseOndulation *= -1;
        }

        if(fixCoordinates){
            points.push_back(ofPoint(width < 0 ? 0 : width, height < 0 ? 0 : height, depth < 0? 0 : depth));
        }else{
            points.push_back(ofPoint(width, height, depth));
        }

    topLeftPoint.set(0, 0);
    topRightPoint.set(abs(width), 0);
    bottomLeftPoint.set(0, abs(height));
    bottomRightPoint.set(abs(width), abs(height));
    refreshBorders();
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
