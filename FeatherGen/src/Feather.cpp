// create feather class that uses the create bezier it creates all the curves for the feather input are the points user can manipulate
#include "Feather.h"
#include "Bezier.h"

Feather::Feather()
{
   // calamusBasePt = ngl::Vec3 (0.0f, 0.0f,0.0f);
//
   // rachisCtrlPt1 = ngl::Vec3 (0.0f,3.0f,0.0f);
   // rachisCtrlPt2 = ngl::Vec3 (0,10.0f,0.0f);
//
   // //top of the feather so end of rachis end of vane left end of vane right 
   // featherTopPt = ngl::Vec3 (0.0f,15.0f,0.0f);
//
   // //vanes points
   // //base point for both vanes 
   // vanesBasePt = ngl::Vec3 (0.0f,2.0f,0.0f);
//
   // // left vane control 1
   // leftVaneCtrlPt1 = ngl::Vec3 (-2.0f,5.0f,0.0f);
   // //left vane control 2
   // leftVaneCtrlPt2 = ngl::Vec3 (-2.0f,11.0f,0.0f);
   // // right vane control 1
   // rightVaneCtrlPt1 = ngl::Vec3 (2.0f,5.0f,0.0f);
   // //right vane control 2
   // rightVaneCtrlPt2 = ngl::Vec3 (2.0f,11.0f,0.0f);
   // //create rachis
   // //create leftVane
   // //create rightVane
//
   // // setCalamusBasePt(calamusBasePtValue);
   // // setRachisCtrlPt1(rachisCtrlPt1Value);
   // // setRachisCtrlPt2(rachisCtrlPt2Value);
   // // setFeatherTopPt(featherTopPtValue);
   // // setVanesBasePt(vanesBasePtValue);
   // // setLeftVaneCtrlPt1(leftVaneCtrlPt1Value);
   // // setLeftVaneCtrlPt2(leftVaneCtrlPt2Value);
   // // setRightVaneCtrlPt1(rightVaneCtrlPt1Value);
   // // setRightVaneCtrlPt2(rightVaneCtrlPt2Value);
//
   // //create Barbs
//
   // createRachisBezier(calamusBasePt, rachisCtrlPt1, rachisCtrlPt2, featherTopPt);
   // createLeftVaneBezier(vanesBasePt, leftVaneCtrlPt1, leftVaneCtrlPt2, featherTopPt);
   // createRightVaneBezier(vanesBasePt, rightVaneCtrlPt1, rightVaneCtrlPt2, featherTopPt);
   // createBarbBezier(ngl::Vec3 (0.0f,7.0f,0.0f), ngl::Vec3 (0.5f,8.0f,0.0f), ngl::Vec3 (0.8f,7.0f,0.0f), ngl::Vec3 (2.0f,5.0f,0.0f));
//
   

}

Feather::Feather(ngl::Vec3 _calamusBasePt, 
            ngl::Vec3 _rachisCtrlPt1, ngl::Vec3 _rachisCtrlPt2, 
            ngl::Vec3 _featherTopPt, 
            ngl::Vec3 _vanesBasePt,
            ngl::Vec3 _leftVaneCtrlPt1, ngl::Vec3 _leftVaneCtrlPt2,
            ngl::Vec3 _rightVaneCtrlPt1, ngl::Vec3 _rightVaneCtrlPt2)
{
    
    //create rachis
    //create leftVane
    //create rightVane

    // this could be also just setCalamusBasePt=_calamusBasePt and not use setters

    setCalamusBasePt(_calamusBasePt);
    setRachisCtrlPt1(_rachisCtrlPt1);
    setRachisCtrlPt2(_rachisCtrlPt2);
    setFeatherTopPt(_featherTopPt);
    setVanesBasePt(_vanesBasePt);
    setLeftVaneCtrlPt1(_leftVaneCtrlPt1);
    setLeftVaneCtrlPt2(_leftVaneCtrlPt2);
    setRightVaneCtrlPt1(_rightVaneCtrlPt1);
    setRightVaneCtrlPt2(_rightVaneCtrlPt2);

    //create Barbs

    createRachisBezier(calamusBasePt, rachisCtrlPt1, rachisCtrlPt2, featherTopPt);
    createLeftVaneBezier(vanesBasePt, leftVaneCtrlPt1, leftVaneCtrlPt2, featherTopPt);
    createRightVaneBezier(vanesBasePt, rightVaneCtrlPt1, rightVaneCtrlPt2, featherTopPt);
    //createBarbBezier(ngl::Vec3 (0.0f,7.0f,0.0f), ngl::Vec3 (0.5f,8.0f,0.0f), ngl::Vec3 (0.8f,7.0f,0.0f), ngl::Vec3 (2.0f,5.0f,0.0f));
    
   
    std::random_device rd; // obtain a random number from hardware
	//std::mt19937 gen(rd()); // seed the generator
	gen = std::mt19937(rd()); // seed the generator

    interpolateAllBarbs();

}

// rachis
void Feather::createRachisBezier(ngl::Vec3 _CP0,ngl::Vec3 _CP1,ngl::Vec3 _CP2,ngl::Vec3 _CP3)
{
    // need distance from 0 to calamus end and vanes begin so I can add more points there so there is the same number of points in the rachis and vanes 
    // distance between base of calamus and start of vanes

    // ratio of the whole rachis that the calamus is

    std::cout<< "\n\n\n" << featherTopPt << "\n\n\n";
    std::cout<< "\n\n\n" << calamusBasePt << "\n\n\n";
    float featherLength = (featherTopPt - calamusBasePt).length();
    std::cout<< "\n\n\n" << featherLength << "\n\n\n";

    std::cout<< "\n\n\n" << vanesBasePt << "\n\n\n";
    std::cout<< "\n\n\n" << calamusBasePt << "\n\n\n";
    float calamusLength = (vanesBasePt - calamusBasePt).length();
    std::cout<< "\n\n\n" << calamusLength << "\n\n\n";

    float calamusRatio = (calamusLength/featherLength);
    std::cout<< "\n\n\n" << calamusRatio << "\n\n\n";

    // mumber of vane points
    numVanePoints = 40;

    //ratio made into number of calamus points
    numCalamusPoints = ((numVanePoints*calamusRatio)/(1-calamusRatio));
    std::cout<< "\n\n\n" << numCalamusPoints << "\n\n\n";
    numRachisPoints = numVanePoints + numCalamusPoints; 
    std::cout<< "\n\n\n" << numRachisPoints << "\n\n\n";

    // number of points = number of vane points + number of calamus points
    
    tParamRachis = (1.0/numRachisPoints);


    // uses t to loop throught
    for(float t=0.0f; t<=1.0f; t+=tParamRachis) //make it a param
    {
        // std::cout<<bezier(t,CP0,CP1,CP2,CP3)<<'\n';
        auto p=bezier(t,_CP0,_CP1,_CP2,_CP3);
        //std::cout<<p.m_x<<' '<<p.m_y<<' '<<p.m_z<<'\n';
        if (t!=0 && t!=1)
        {
            rachisPoints.push_back(p);
        
        }

        //featherPoints.push_back(p);
    }
}

// left Vane
void Feather::createLeftVaneBezier(ngl::Vec3 _CP0,ngl::Vec3 _CP1,ngl::Vec3 _CP2,ngl::Vec3 _CP3)
{
    //int numVanePoints = 16;
    tParamLeftVane = 1.0/numVanePoints;


    // uses t to loop throught
    for(float t=0.0f; t<=1.0f; t+=tParamLeftVane) //make it a param
    {
        // std::cout<<bezier(t,CP0,CP1,CP2,CP3)<<'\n';
        auto p=bezier(t,_CP0,_CP1,_CP2,_CP3);
        //std::cout<<p.m_x<<' '<<p.m_y<<' '<<p.m_z<<'\n';
        if (t!=0 && t!=1)
        {
            leftVanePoints.push_back(p);
        
        }

        //featherPoints.push_back(p); //was just for drawing of the lines
    }
}


// right Vane
void Feather::createRightVaneBezier(ngl::Vec3 _CP0,ngl::Vec3 _CP1,ngl::Vec3 _CP2,ngl::Vec3 _CP3)
{
    //int numVanePoints = 100;
    tParamRightVane = 1.0/numVanePoints;


    // uses t to loop throught
    for(float t=0.0f; t<=1.0f; t+=tParamRightVane) //make it a param
    {
        // std::cout<<bezier(t,CP0,CP1,CP2,CP3)<<'\n';
        auto p=bezier(t,_CP0,_CP1,_CP2,_CP3);
        //std::cout<<p.m_x<<' '<<p.m_y<<' '<<p.m_z<<'\n';
        if (t!=0 && t!=1)
        {
            rightVanePoints.push_back(p);
        
        }

        //featherPoints.push_back(p); //was just for drawing of the lines
    }
}

// BARBS - for now one random barb
void Feather::createBarbBezier(ngl::Vec3 _CP0,ngl::Vec3 _CP1,ngl::Vec3 _CP2,ngl::Vec3 _CP3)
{
    numBarbPoints = 20;
    tParamBarb = 1.0/numBarbPoints;


    // uses t to loop throught
    for(float t=0.0f; t<=1.0f; t+=tParamBarb) //make it a param
    {
        // std::cout<<bezier(t,CP0,CP1,CP2,CP3)<<'\n';
        auto p=bezier(t,_CP0,_CP1,_CP2,_CP3);
        //std::cout<<p.m_x<<' '<<p.m_y<<' '<<p.m_z<<'\n';
        if (t!=0 && t!=1)
        {
            barbPoints.push_back(p);
        
        }

        //featherPoints.push_back(p); //was just for drawing of the lines
    }
}


//setters for values input

//void Feather::setBarbVariationAmountFuzzy(float barbVariationAmountFuzzyValue)
//{
//    barbVariationAmountFuzzy = barbVariationAmountFuzzyValue;
//}
//void Feather::setRandomisationOnDistanceAmountFuzzy(float randomisationOnDistanceAmountFuzzyValue)
//{
//    randomisationOnDistanceAmountFuzzy = randomisationOnDistanceAmountFuzzyValue;
//}
//float barbVariationAmountSmooth;
//float randomisationOnDistanceAmountSmooth;
//int smoothStart;



void Feather::interpolateAllBarbs()
{
    randomisationOnDistanceAmountFuzzy = 0.4f;
    barbVariationAmountFuzzy = 0.7f;
    randomisationOnDistanceAmountSmooth = 0.1f;
    barbVariationAmountSmooth = 0.1f;
    // number of fuzzy to smooth, integer number must be less or equal to number of vanes -1 (I think)
    smoothStart = 9;
    fuzzyEnd = numVanePoints-smoothStart-2;
    
    interpolateLeftBarbsFuzzy();
    interpolateLeftBarbsSmooth();
    interpolateRightBarbsFuzzy();
    interpolateRightBarbsSmooth(); 
}

void Feather::interpolateLeftBarbsFuzzy()
{   
    //amount of variation, number between 0,1 future user input
    
    for(int i = 1; i<numVanePoints-1-fuzzyEnd; ++i)
    {
        
        std::uniform_real_distribution<> distrDist(-randomisationOnDistanceAmountFuzzy, randomisationOnDistanceAmountFuzzy);
	    float randomisationOnDistance = distrDist(gen);

        //main control points
        ngl::Vec3 P0 (rachisPoints[numCalamusPoints+i-1]);
        ngl::Vec3 tempP3 (leftVanePoints[i]);
        ngl::Vec3 P3(tempP3.m_x + randomisationOnDistance, tempP3.m_y + randomisationOnDistance, 0.0f);
        // the internal control points
       
        float distance = (P3 - P0).length();
        std::uniform_real_distribution<> distrOneLeft(-distance*barbVariationAmountFuzzy, 0);
	    float variationRandomOne = distrOneLeft(gen);

        std::uniform_real_distribution<> distrTwoLeft(-distance*barbVariationAmountFuzzy, distance*barbVariationAmountFuzzy);
	    float variationRandomTwo = distrTwoLeft(gen);

        

        

        float v1 = variationRandomOne;
        float v2 = variationRandomTwo;
        float v3 = variationRandomTwo;
        float v4 = variationRandomOne;
        std::cout << '\n' << variationRandomOne << '\n';


        ngl::Vec3 P1 (P0.m_x + v1, P0.m_y + v2, 0.0f);
        ngl::Vec3 P2 (P3.m_x + v3, P3.m_y + v4, 0.0f);
        
        
        // random value between distance * barbVariationAmount and 0
        

        //float v1 = ((-distance*barbVariationAmount);
        //float v2 = ((-distance*barbVariationAmount), (float)(distance*barbVariationAmount), 0.0f);
        
        createBarbBezier(P0,P1,P2,P3);
    }
}

void Feather::interpolateLeftBarbsSmooth()
{   
    //amount of variation, number between 0,1 future user input
    
    
    for(int i = 1+smoothStart; i<numVanePoints-1; ++i)
    {
        
        std::uniform_real_distribution<> distrDist(-randomisationOnDistanceAmountSmooth, randomisationOnDistanceAmountSmooth);
	    float randomisationOnDistance = distrDist(gen);

        //main control points
        ngl::Vec3 P0 (rachisPoints[numCalamusPoints+i-1]);
        ngl::Vec3 tempP3 (leftVanePoints[i]);
        ngl::Vec3 P3(tempP3.m_x + randomisationOnDistance, tempP3.m_y + randomisationOnDistance, 0.0f);
        // the internal control points
       
        float distance = (P3 - P0).length();
        std::uniform_real_distribution<> distrOneLeft(-distance*barbVariationAmountSmooth, 0);
	    float variationRandomOne = distrOneLeft(gen);

        std::uniform_real_distribution<> distrTwoLeft(-distance*barbVariationAmountSmooth, distance*barbVariationAmountSmooth);
	    float variationRandomTwo = distrTwoLeft(gen);

        

        

        float v1 = variationRandomOne;
        float v2 = variationRandomTwo;
        float v3 = variationRandomTwo;
        float v4 = variationRandomOne;
        std::cout << '\n' << variationRandomOne << '\n';


        ngl::Vec3 P1 (P0.m_x + v1, P0.m_y + v2, 0.0f);
        ngl::Vec3 P2 (P3.m_x + v3, P3.m_y + v4, 0.0f);
        
        
        // random value between distance * barbVariationAmount and 0
        

        //float v1 = ((-distance*barbVariationAmount);
        //float v2 = ((-distance*barbVariationAmount), (float)(distance*barbVariationAmount), 0.0f);
        
        createBarbBezier(P0,P1,P2,P3);
    }
}

void Feather::interpolateRightBarbsFuzzy()
{   
    //amount of variation, number between 0,1 future user input
    
    for(int i = 1; i<numVanePoints-1-fuzzyEnd; ++i)
    {
        
        std::uniform_real_distribution<> distrDist(-randomisationOnDistanceAmountFuzzy, randomisationOnDistanceAmountFuzzy);
	    float randomisationOnDistance = distrDist(gen);

        //main control points
        ngl::Vec3 P0 (rachisPoints[numCalamusPoints+i-1]);
        ngl::Vec3 tempP3 (rightVanePoints[i]);
        ngl::Vec3 P3(tempP3.m_x + randomisationOnDistance, tempP3.m_y + randomisationOnDistance, 0.0f);
        // the internal control points
       
        float distance = (P3 - P0).length();
        std::uniform_real_distribution<> distrOneRight(-distance*barbVariationAmountFuzzy, 0);
	    float variationRandomOne = distrOneRight(gen);

        std::uniform_real_distribution<> distrTwoRight(-distance*barbVariationAmountFuzzy, distance*barbVariationAmountFuzzy);
	    float variationRandomTwo = distrTwoRight(gen);

        

        

        float v1 = variationRandomOne;
        float v2 = variationRandomTwo;
        float v3 = variationRandomTwo;
        float v4 = variationRandomOne;
        std::cout << '\n' << variationRandomOne << '\n';


        ngl::Vec3 P1 (P0.m_x + v1, P0.m_y + v2, 0.0f);
        ngl::Vec3 P2 (P3.m_x + v3, P3.m_y + v4, 0.0f);
        
        
        // random value between distance * barbVariationAmount and 0
        

        //float v1 = ((-distance*barbVariationAmount);
        //float v2 = ((-distance*barbVariationAmount), (float)(distance*barbVariationAmount), 0.0f);
        
        createBarbBezier(P0,P1,P2,P3);
    }
}

void Feather::interpolateRightBarbsSmooth()
{   
    //amount of variation, number between 0,1 future user input
   
    
    for(int i = 1+smoothStart; i<numVanePoints-1; ++i)
    {
        
        std::uniform_real_distribution<> distrDist(-randomisationOnDistanceAmountSmooth, randomisationOnDistanceAmountSmooth);
	    float randomisationOnDistance = distrDist(gen);

        //main control points
        ngl::Vec3 P0 (rachisPoints[numCalamusPoints+i-1]);
        ngl::Vec3 tempP3 (rightVanePoints[i]);
        ngl::Vec3 P3(tempP3.m_x + randomisationOnDistance, tempP3.m_y + randomisationOnDistance, 0.0f);
        // the internal control points
       
        float distance = (P3 - P0).length();
        std::uniform_real_distribution<> distrOneRight(-distance*barbVariationAmountSmooth, 0);
	    float variationRandomOne = distrOneRight(gen);

        std::uniform_real_distribution<> distrTwoRight(-distance*barbVariationAmountSmooth, distance*barbVariationAmountSmooth);
	    float variationRandomTwo = distrTwoRight(gen);

        

        

        float v1 = variationRandomOne;
        float v2 = variationRandomTwo;
        float v3 = variationRandomTwo;
        float v4 = variationRandomOne;
        std::cout << '\n' << variationRandomOne << '\n';


        ngl::Vec3 P1 (P0.m_x + v1, P0.m_y + v2, 0.0f);
        ngl::Vec3 P2 (P3.m_x + v3, P3.m_y + v4, 0.0f);
        
        
        // random value between distance * barbVariationAmount and 0
        

        //float v1 = ((-distance*barbVariationAmount);
        //float v2 = ((-distance*barbVariationAmount), (float)(distance*barbVariationAmount), 0.0f);
        
        createBarbBezier(P0,P1,P2,P3);
    }
}


// add a duplicate method thing/parameter? so I can divide the rachis into 2 parts and give the barbs different values in variation



// need to implement from paper https://ieeexplore.ieee.org/abstract/document/1167157?casa_token=H7dgsZohCYgAAAAA:u2vSB6gZ9btROSFvSGp_RdtFabARI4gh9aC1bOcGWuwwOo5vsBJ_5vgE7E5EC3axrYY21QtOuw 

Feather::~Feather()
{
}

// setters

//// change it later to private and do get stuff






    
void Feather::setCalamusBasePt(ngl::Vec3 calamusBasePtValue)
{
    calamusBasePt = calamusBasePtValue;
}
void Feather::setRachisCtrlPt1(ngl::Vec3 rachisCtrlPt1Value)
{
    rachisCtrlPt1 = rachisCtrlPt1Value;
}
void Feather::setRachisCtrlPt2(ngl::Vec3 rachisCtrlPt2Value)
{
    rachisCtrlPt2 = rachisCtrlPt2Value;
}
void Feather::setFeatherTopPt(ngl::Vec3 featherTopPtValue)
{
    featherTopPt = featherTopPtValue;
}
void Feather::setVanesBasePt(ngl::Vec3 vanesBasePtValue)
{
    vanesBasePt = vanesBasePtValue;
}
void Feather::setLeftVaneCtrlPt1(ngl::Vec3 leftVaneCtrlPt1Value)
{
    leftVaneCtrlPt1 = leftVaneCtrlPt1Value;
}
void Feather::setLeftVaneCtrlPt2(ngl::Vec3 leftVaneCtrlPt2Value)
{
    leftVaneCtrlPt2 = leftVaneCtrlPt2Value;
}
void Feather::setRightVaneCtrlPt1(ngl::Vec3 rightVaneCtrlPt1Value)
{
    rightVaneCtrlPt1 = rightVaneCtrlPt1Value;
}
void Feather::setRightVaneCtrlPt2(ngl::Vec3 rightVaneCtrlPt2Value)
{
    rightVaneCtrlPt2 = rightVaneCtrlPt2Value;

} 










std::vector<ngl::Vec3>Feather::getRachisPoints()
{
    return rachisPoints;
}

std::vector<ngl::Vec3>Feather::getLeftVanePoints()
{
    return leftVanePoints;
}

std::vector<ngl::Vec3>Feather::getRightVanePoints()
{
    return rightVanePoints;
}

std::vector<ngl::Vec3>Feather::getBarbPoints()
{
    return barbPoints;
}


std::vector<ngl::Vec3>Feather::getFeatherPoints()
{
    //change it so it combines all points together not just returns rachis points or change vao to be separate for each feather part


    std::vector<ngl::Vec3> result;

    result.insert(result.end(), rachisPoints.begin(), rachisPoints.end());
    //result.insert(result.end(), leftVanePoints.begin(), leftVanePoints.end());
    //result.insert(result.end(), rightVanePoints.begin(), rightVanePoints.end());
    result.insert(result.end(), barbPoints.begin(), barbPoints.end());
    // etc

    return result;


}