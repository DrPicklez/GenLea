#include "ofMain.h"
#ifndef LEAFCLASS_H
#define LEAFCLASS_H


class LeafClass
{
public:
    void setup(int wid, int hig, int _nPoints);
    void createBFly();
    void draw();
    vector<ofVec2f> edgePoints;
    vector<ofVec2f> stemPoints;

private:
        vector<ofVec2f> startWingPoints();
        vector<ofVec2f> curvePoints(float l, float r);
        vector<ofVec2f> createStem(vector <ofVec2f> _edgePoints);
        int pX, pY, width, height;
        int nPoints;
};

#endif // LEAFCLASS_H
