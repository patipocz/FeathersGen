#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
//#include "Bezier.h"
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/VAOFactory.h>
#include <ngl/ShaderLib.h>
#include <iostream>


NGLScene::NGLScene()
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  setTitle("FeatherGen");

  // put this logic into a function
  feather = Feather(
      ngl::Vec3 (0.0f, 0.0f, 0.0f), //calamus base point
      ngl::Vec3 (0.0f, 3.0f, 0.0f), //rachis control point 1
      ngl::Vec3 (0.0f, 10.0f,0.0f), // rachis control point 2
      ngl::Vec3 (0.0f, 15.0f,0.0f), // feather top point
      ngl::Vec3 (0.0f, 3.0f, 0.0f), // vanes base point
      ngl::Vec3 (-3.0f, 4.0f, 0.0f), //left vane control point 1
      ngl::Vec3 (-4.0f, 15.0f,0.0f), // left vane control point 2
      ngl::Vec3 (3.0f, 4.0f, 0.0f), // right vane control point 1
      ngl::Vec3 (5.0f, 15.0f,0.0f) //right vane control point 2
    );

    // setters?
    //feather.setBarbVariationAmountFuzzy(0.9f);
    //feather.setRandomisationOnDistanceAmountFuzzy(0.5f);
}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}



void NGLScene::resizeGL(int _w , int _h)
{
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}


void NGLScene::initializeGL()
{
  // we must call that first before any other GL commands to load and link the
  // gl commands from the lib, if that is not done program will crash
  ngl::NGLInit::initialize();
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glClearColor(0.7f, 0.7f, 0.7f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);

  //shaders

  ngl::ShaderLib::createShaderProgram("SimpleShader");
  // now we are going to create empty shaders for Frag and Vert
  ngl::ShaderLib::attachShader("VertexShader",ngl::ShaderType::VERTEX);
  ngl::ShaderLib::attachShader("FragmentShader",ngl::ShaderType::FRAGMENT);
  // attach the source
  ngl::ShaderLib::loadShaderSource("VertexShader","shaders/VertexShader.glsl");
  ngl::ShaderLib::loadShaderSource("FragmentShader","shaders/FragmentShader.glsl");
  // compile the shaders
  ngl::ShaderLib::compileShader("VertexShader");
  ngl::ShaderLib::compileShader("FragmentShader");
  // add them to the program
  ngl::ShaderLib::attachShaderToProgram("SimpleShader","VertexShader");
  ngl::ShaderLib::attachShaderToProgram("SimpleShader","FragmentShader");

  // now we have associated this data we can link the shader
  ngl::ShaderLib::linkProgramObject("SimpleShader");
  // and make it active ready to load values
  ngl::ShaderLib::use("SimpleShader");
  ngl::ShaderLib::setUniform("Colour",1.0f,0.0f,0.0f,1.0f);



  //create a simple camera from graphics library
  // it is a static camera, oly set once
  // values for camera position
  ngl::Vec3 from(0,12,50);
  ngl::Vec3 to(0,0,0);
  ngl::Vec3 up(0,1,0);
  m_view=ngl::lookAt(from,to,up);
  // set the shape using FOV 45 Aspect Ratio based on Width and Height
  // The final two are near and far clipping planes of 0.5 and 10
  m_project=ngl::perspective(45.0f,720.0f/576.0f,0.05f,350.0f);



  m_vao=ngl::VAOFactory::createVAO(ngl::simpleVAO,GL_POINTS);
  
  createFeather();
  //feather.createBezier();

}

void NGLScene::createFeather()
{

  //control points to be modified by the user and UI possibly later, points the feather custom constructor will take in
  
  ////// change it into set functions 

 // //rachis points
 // //start of the feather calamus so base
 // ngl::Vec3 calamusBasePt = ngl::Vec3 (0.0f, 0.0f,0.0f);
 // 
 // ngl::Vec3 rachisCtrlPt1 = ngl::Vec3 (0.0f,3.0f,0.0f);
//
 // ngl::Vec3 rachisCtrlPt2 = ngl::Vec3 (0,10.0f,0.0f);
//
 // //top of the feather so end of rachis end of vane left end of vane right 
 // ngl::Vec3 featherTopPt = ngl::Vec3 (0.0f,15.0f,0.0f);
//
 // //vanes points
 // //base point for both vanes 
 // ngl::Vec3 vanesBasePt = ngl::Vec3 (0.0f,2.0f,0.0f);
//
 // // left vane control 1
 // ngl::Vec3 leftVaneCtrlPt1 = ngl::Vec3 (-2.0f,5.0f,0.0f);
 // //left vane control 2
 // ngl::Vec3 leftVaneCtrlPt2 = ngl::Vec3 (-2.0f,11.0f,0.0f);
//
 // // right vane control 1
 // ngl::Vec3 rightVaneCtrlPt1 = ngl::Vec3 (2.0f,5.0f,0.0f);
 // //right vane control 2
 // ngl::Vec3 rightVaneCtrlPt2 = ngl::Vec3 (2.0f,11.0f,0.0f);

  


 //////  ////// barbs are interpolated 
 //////  ////// possibly let user decide how many points they want to draw so how dense the feather is 
 ////// //rachis points
 //////  //start of the feather calamus so base
 //////  feather.calamusBasePtValue = 
 //////  feather.rachisCtrlPt1Value = ngl::Vec3 (0.0f,3.0f,0.0f);
 //////  feather.rachisCtrlPt2Value = ngl::Vec3 (0,10.0f,0.0f);
////// 
 //////  //top of the feather so end of rachis end of vane left end of vane right 
 //////  feather.featherTopPtValue = ngl::Vec3 (0.0f,15.0f,0.0f);
////// 
 //////  //vanes points
 //////  //base point for both vanes 
 //////  feather.vanesBasePtValue = ngl::Vec3 (0.0f,2.0f,0.0f);
////// 
 //////  // left vane control 1
 //////  feather.leftVaneCtrlPt1Value = ngl::Vec3 (-2.0f,5.0f,0.0f);
 //////  //left vane control 2
 //////  feather.leftVaneCtrlPt2Value = ngl::Vec3 (-2.0f,11.0f,0.0f);
 //////  // right vane control 1
 //////  feather.rightVaneCtrlPt1Value = ngl::Vec3 (2.0f,5.0f,0.0f);
 //////  //right vane control 2
 //////  feather.rightVaneCtrlPt2Value = ngl::Vec3 (2.0f,11.0f,0.0f);
////// 
////// 
 //////  
 //////  feather.setCalamusBasePt(ngl::Vec3 (0.0f, 0.0f,0.0f);
 //////  feather.setRachisCtrlPt1(feather.rachisCtrlPt1Value);
 //////  feather.setRachisCtrlPt2(feather.rachisCtrlPt2Value);
 //////  feather.setFeatherTopPt(feather.featherTopPtValue);
 //////  feather.setVanesBasePt(feather.vanesBasePtValue);
 //////  feather.setLeftVaneCtrlPt1(feather.leftVaneCtrlPt1Value);
 //////  feather.setLeftVaneCtrlPt2(feather.leftVaneCtrlPt2Value);
 //////  feather.setRightVaneCtrlPt1(feather.rightVaneCtrlPt1Value);
 //////  feather.setRightVaneCtrlPt2(feather.rightVaneCtrlPt2Value);


  



   
  //setup VAO
  
  //m_vao=ngl::VAOFactory::createVAO("bezierVAO", GL_LINES);
  m_vao->bind();
  auto buffSize = feather.getFeatherPoints().size();

  // now we have our data add it to the VAO, we need to tell the VAO the following
  // how much (in bytes) data we are copying
  // a pointer to the first element of data (in this case the address of the first element of the
  // std::vector
  m_vao->setData(ngl::SimpleVAO::VertexData(buffSize * sizeof(ngl::Vec3), feather.getFeatherPoints()[0].m_x));

  // Map the VAO vec3 data to the shaders inputs (in this simple case its expect inVert, but dunno what your shaders are like)
  // attribute vec3 inVert; attribute 0
  // 
  // We tell it the size of vertData, the format (float) and how many elements there are (3). There's 0 stride in this case
  m_vao->setVertexAttributePointer(0, 3, GL_FLOAT, sizeof(ngl::Vec3), 0);

  // Tell the vao how many points we have to draw
  m_vao->setNumIndices(buffSize);

  // finally we have finished for now so time to unbind the VAO
  m_vao->unbind();


}

void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);
  ngl::ShaderLib::use("SimpleShader");


  ngl::Mat4 MVP;
  MVP=m_project*m_view*m_mouseGlobalTX;
  ngl::ShaderLib::setUniform("MVP",MVP);

  
  m_mouseGlobalTX;
  // add the translations
  m_mouseGlobalTX.m_m[3][0] = m_modelPos.m_x;
  m_mouseGlobalTX.m_m[3][1] = m_modelPos.m_y;
  m_mouseGlobalTX.m_m[3][2] = m_modelPos.m_z;

  glPointSize (3);
  m_vao->bind();
  m_vao->draw();
  m_vao->unbind();

  

}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_Space :
      m_win.spinXFace=0;
      m_win.spinYFace=0;
      m_modelPos.set(ngl::Vec3::zero());

  break;
  default : break;
  }
  // finally update the GLWindow and re-draw

    update();
}
