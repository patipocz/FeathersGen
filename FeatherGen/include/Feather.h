#ifndef __FEATHER_H__
#define __FEATHER_H__

#include <iostream>
#include <ngl/Vec3.h>
#include <random>

class Feather
{
    private: 
    std::vector<ngl::Vec3>featherPoints;

    std::vector<ngl::Vec3>rachisPoints;
    std::vector<ngl::Vec3>leftVanePoints;
    std::vector<ngl::Vec3>rightVanePoints;
    std::vector<ngl::Vec3>barbPoints;

    //// feather private parts
    
    ngl::Vec3 calamusBasePt;
    ngl::Vec3 rachisCtrlPt1;
    ngl::Vec3 rachisCtrlPt2;
    //top of the feather so end of rachis end of vane left end of vane right 
    ngl::Vec3 featherTopPt;
    //vanes points
    //base point for both vanes 
    ngl::Vec3 vanesBasePt;
    // left vane control 1feather 
    ngl::Vec3 leftVaneCtrlPt1;
    //left vane control 2
    ngl::Vec3 leftVaneCtrlPt2;
    // right vane control 1
    ngl::Vec3 rightVaneCtrlPt1;
    //right vane control 2
    ngl::Vec3 rightVaneCtrlPt2;

    std::mt19937 gen;

    float barbVariationAmountFuzzy;
    float randomisationOnDistanceAmountFuzzy;

    public: 
    
    

    Feather();

    Feather(ngl::Vec3 _calamusBasePt, 
            ngl::Vec3 _rachisCtrlPt1, ngl::Vec3 _rachisCtrlPt2, 
            ngl::Vec3 _featherTopPt, 
            ngl::Vec3 _vanesBasePt,
            ngl::Vec3 _leftVaneCtrlPt1, ngl::Vec3 _leftVaneCtrlPt2,
            ngl::Vec3 _rightVaneCtrlPt1, ngl::Vec3 _rightVaneCtrlPt2);

    ~Feather();

    /// user modifible storage containers for values ??? to be modifiedin ngl scene

    //ngl::Vec3 calamusBasePtValue;
    //ngl::Vec3 rachisCtrlPt1Value;
    //ngl::Vec3 rachisCtrlPt2Value;
    //ngl::Vec3 featherTopPtValue;    
    //ngl::Vec3 vanesBasePtValue;
    //ngl::Vec3 leftVaneCtrlPt1Value;
    //ngl::Vec3 leftVaneCtrlPt2Value;
    //ngl::Vec3 rightVaneCtrlPt1Value;
    //ngl::Vec3 rightVaneCtrlPt2Value;
//


    //// setters declarations
    void setBarbVariationAmountFuzzy(float setBarbVariationAmountFuzzyValue);
    void setRandomisationOnDistanceAmountFuzzy(float randomisationOnDistanceAmountFuzzyValue);

    void setCalamusBasePt(ngl::Vec3 calamusBasePtValue);
    void setRachisCtrlPt1(ngl::Vec3 rachisCtrlPt1Value);
    void setRachisCtrlPt2(ngl::Vec3 rachisCtrlPt2Value);
    void setFeatherTopPt(ngl::Vec3 featherTopPtValue);
    void setVanesBasePt(ngl::Vec3 vanesBasePtValue);
    void setLeftVaneCtrlPt1(ngl::Vec3 leftVaneCtrlPt1Value);
    void setLeftVaneCtrlPt2(ngl::Vec3 leftVaneCtrlPt2Value);
    void setRightVaneCtrlPt1(ngl::Vec3 rightVaneCtrlPt1Value);
    void setRightVaneCtrlPt2(ngl::Vec3 rightVaneCtrlPt2Value);


    std::vector<ngl::Vec3>getFeatherPoints();
    std::vector<ngl::Vec3>getRachisPoints();
    std:: vector<ngl::Vec3>getLeftVanePoints();
    std:: vector<ngl::Vec3>getRightVanePoints();
    std:: vector<ngl::Vec3>getBarbPoints();

    //the spread between points how many it generates
    //int numPoints; 
    //double tParam;
    double tParamRachis;
    double tParamLeftVane;
    double tParamRightVane;
    double tParamBarb;
    int numRachisPoints;
    int numVanePoints;
    int numCalamusPoints;
    int numBarbPoints;

    
    float barbVariationAmountSmooth;
    float randomisationOnDistanceAmountSmooth;
    int smoothStart;
    int fuzzyEnd;
    


    

    void createRachisBezier(ngl::Vec3 _CP0,ngl::Vec3 _CP1,ngl::Vec3 _CP2,ngl::Vec3 _CP3);
    void createLeftVaneBezier(ngl::Vec3 _CP0,ngl::Vec3 _CP1,ngl::Vec3 _CP2,ngl::Vec3 _CP3);
    void createRightVaneBezier(ngl::Vec3 _CP0,ngl::Vec3 _CP1,ngl::Vec3 _CP2,ngl::Vec3 _CP3);
    void createBarbBezier(ngl::Vec3 _CP0,ngl::Vec3 _CP1,ngl::Vec3 _CP2,ngl::Vec3 _CP3);
    void interpolateLeftBarbsFuzzy();
    void interpolateLeftBarbsSmooth();
    void interpolateRightBarbsFuzzy();
    void interpolateRightBarbsSmooth();

    void interpolateAllBarbs();
    
    
};

#endif // __FEATHER_H__