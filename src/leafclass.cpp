#include "leafclass.h"
//--------------------------------------------------------------
void LeafClass::setup(int wid, int hig, int _nPoints){
    width = wid;
    height = hig;
    nPoints = _nPoints;
    createBFly();


}
//--------------------------------------------------------------
void LeafClass::createBFly(){
    edgePoints = startWingPoints();
    float curveL = (1. / ofGetWidth()) * ofGetMouseX();
    float curveR = (1. / ofGetHeight()) * ofGetMouseY();

    for(int i = 0; i < edgePoints.size() + 1; i++){
        edgePoints[i].x = ((edgePoints[i].x * curvePoints(curveL, curveR)[i].x)) + width/2;
        edgePoints[i].y += ((edgePoints[0].y * curvePoints(curveL, curveR)[i].y));        ////TO FIX !!!!!
    }
    stemPoints = createStem(edgePoints);
}

//--------------------------------------------------------------
void LeafClass::draw(){
    createBFly();

    for(int i = 0; i < edgePoints.size()/2 -1; i++){
        int n = i;
        ofVec2f cP1 = stemPoints[n];
        ofVec2f cP2 = stemPoints[n+1];
        ofNoFill();
        ofDrawBezier(edgePoints[n].x, edgePoints[n].y, cP1.x, cP1.y,cP2.x, cP2.y, edgePoints[n+1].x, edgePoints[n+1].y);
        n = i + edgePoints.size()/2;        //other side
        ofDrawBezier(edgePoints[n].x, edgePoints[n].y, cP1.x, cP1.y,cP2.x, cP2.y, edgePoints[n+1].x, edgePoints[n+1].y);
    }
}
//--------------------------------------------------------------
vector<ofVec2f> LeafClass::startWingPoints(){
    int halfway = nPoints / 2;
    vector <ofVec2f> _points;
    for(int i = 0; i < nPoints; i++){
        int n = i % halfway;
        int x, y;


        y = height - (height/ halfway) * n;
        x = (width/2) - ((width/  nPoints) * n);
        ofVec2f point = ofVec2f(x, y);
        _points.push_back(point);
    }
    return _points;
}
//--------------------------------------------------------------
vector <ofVec2f> LeafClass::curvePoints(float l, float r){
    float curveL = PI * l;
    float mod = (PI * r) * 10;
    float curveR = curveL;                           //deBug
//    float mod = 1;                                   //randomPoint
    vector<ofVec2f> _points;
    int halfway = nPoints / 2;

    float x;
    float y;
    float xModL;
    float xModR;

    for(int i = 1; i <= nPoints; i++){
        int n = i % halfway;

        if(i <= halfway){
            xModL = sin((mod /halfway) * n) * 0.15;       //randomPoint
            x = sin((curveR /halfway) * n);
            x += xModL;
            y = x;
            y *= 0.15;

        }
        else{
            xModR = sin((mod /halfway) * n) * 0.15;       //randomPoint
            x = sin((curveL /halfway) * n);
            x += xModR;
            x *= -1;        //LeftCurve
            y = (x * -1);
            y *= 0.15;

        }
        ofVec2f point = ofVec2f(x, y);
        _points.push_back(point);
    }
    return _points;
}
//--------------------------------------------------------------
vector<ofVec2f> LeafClass::createStem(vector <ofVec2f> _edgePoints){
    vector <ofVec2f> lStem;
    vector <ofVec2f> rStem;
    vector <ofVec2f> _stemPoints;
    for(int i = 0; i < _edgePoints.size(); i++){
        if(i < _edgePoints.size()/ 2){
            lStem.push_back(edgePoints[i]);
        }
        else{
            rStem.push_back(edgePoints[i]);}
    }
    for(int i = 0; i < lStem.size(); i++){
        ofVec2f middle = lStem[i].getMiddle(rStem[i]);
        _stemPoints.push_back(middle);
    }
    return _stemPoints;
}
//--------------------------------------------------------------
//            float yStep = abs(sin((HALF_PI/ halfway) * (halfway-n)));
//            yStep *= height/halfway;
//            yStep *= n;
//            y = height - yStep;
