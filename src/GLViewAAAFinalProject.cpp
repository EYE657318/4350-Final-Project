#include "GLViewAAAFinalProject.h"

#include "WorldList.h" //This is where we place all of our WOs
#include "ManagerOpenGLState.h" //We can change OpenGL State attributes with this
#include "Axes.h" //We can set Axes to on/off with this
#include "PhysicsEngineODE.h"

//Different WO used by this module
#include "WO.h"
#include "WOStatic.h"
#include "WOStaticPlane.h"
#include "WOStaticTrimesh.h"
#include "WOTrimesh.h"
#include "WOHumanCyborg.h"
#include "WOHumanCal3DPaladin.h"
#include "WOWayPointSpherical.h"
#include "WOLight.h"
#include "WOSkyBox.h"
#include "WOCar1970sBeater.h"
#include "Camera.h"
#include "CameraStandard.h"
#include "CameraChaseActorSmooth.h"
#include "CameraChaseActorAbsNormal.h"
#include "CameraChaseActorRelNormal.h"
#include "Model.h"
#include "ModelDataShared.h"
#include "ModelMesh.h"
#include "ModelMeshDataShared.h"
#include "ModelMeshSkin.h"
#include "WONVStaticPlane.h"
#include "WONVPhysX.h"
#include "WONVDynSphere.h"
#include "WOImGui.h" //GUI Demos also need to #include "AftrImGuiIncludes.h"
#include "AftrImGuiIncludes.h"
#include "AftrGLRendererBase.h"

#include "Gladiator.h"
#include "GladiatorGUI.h"
#include "TestGUI.h"

using namespace Aftr;

GLViewAAAFinalProject* GLViewAAAFinalProject::New( const std::vector< std::string >& args )
{
   GLViewAAAFinalProject* glv = new GLViewAAAFinalProject( args );
   glv->init( Aftr::GRAVITY, Vector( 0, 0, -1.0f ), "aftr.conf", PHYSICS_ENGINE_TYPE::petODE );
   glv->onCreate();
   return glv;
}

////////////////////////////////////////////////////////////////////
//////////////////// GLADIATOR FUNCTIONS ///////////////////////////
////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////
//////////////////// NAME STUFF ///////////////////////////////
///////////////////////////////////////////////////////////////
//This is the list of names used to generate gladiator names.
//It makes no distinction between first and last names. 
//This is to emphasize the strangeness of this world.
std::vector<std::string> nameList = { "Achilles",  "Acrates", "Actius", "Adonios", "Aegyptus", "Aemilius", "Africana", "Africanus",
"Ajax", "Albanus", "Alexander", "Amandus", "Amethystus", "Amianthus", "Amor", "Ampliatus", "Anicetus", "Andromeda",
"Apelles", "Antonius", "Apollodoru" };

//Picks a name from the provided list
std::string dub(std::vector<std::string> nameList) {
    //srand(time(NULL));
    int vecsize = nameList.size();
    int index = rand() % vecsize;
    std::string theName = nameList[index];
    return theName;
}

/////////////////////////////////////////////////////////////////
/////////////////// COMBAT STUFF ////////////////////////////////
/////////////////////////////////////////////////////////////////

bool GLViewAAAFinalProject::combatPhase() {               //The bool returned is whether or not the player lost the fight (true means they lost)
    int players_lost = false;
    
    //////TODO: all of this
    //Turn on UI
    //Get the lengths of both teams
    // UNTIL IT IS OVER::::
    //Alternate between them
    //When selecting someone, first:
    ////move them
    ////find out if they are in range to use a skill
    ////find their AI
    ////use the skill, if applicable
    ////Remove people if they are dead
    
    return players_lost;
}

void GLViewAAAFinalProject::downtimePhase() {
    //////TODO: all of this
    //go through the vector of allies to turn UI on
    //??????
}

void GLViewAAAFinalProject::phaseHandler() {

    int rounds = 0;         //Currently I plan for there to be 10, but this can change
    bool lost = false;      //If the player has lost

    while (rounds < 10) {

        this->downtimePhase();      //Run through the downtime phase
        lost = this->combatPhase(); //Run through the combat phase
        if (lost) {break;} else {rounds++;} 
    }

    if (lost) {
        //TODO: you lost!
    }
    else {
        //TODO: you won!
    }

}


GLViewAAAFinalProject::GLViewAAAFinalProject( const std::vector< std::string >& args ) : GLView( args )
{
   //Initialize any member variables that need to be used inside of LoadMap() here.
   //Note: At this point, the Managers are not yet initialized. The Engine initialization
   //occurs immediately after this method returns (see GLViewAAAFinalProject::New() for
   //reference). Then the engine invoke's GLView::loadMap() for this module.
   //After loadMap() returns, GLView::onCreate is finally invoked.

   //The order of execution of a module startup:
   //GLView::New() is invoked:
   //    calls GLView::init()
   //       calls GLView::loadMap() (as well as initializing the engine's Managers)
   //    calls GLView::onCreate()

   //GLViewAAAFinalProject::onCreate() is invoked after this module's LoadMap() is completed.
}


void GLViewAAAFinalProject::onCreate()
{
   //GLViewAAAFinalProject::onCreate() is invoked after this module's LoadMap() is completed.
   //At this point, all the managers are initialized. That is, the engine is fully initialized.

   if( this->pe != NULL )
   {
      //optionally, change gravity direction and magnitude here
      //The user could load these values from the module's aftr.conf
      this->pe->setGravityNormalizedVector( Vector( 0,0,-1.0f ) );
      this->pe->setGravityScalar( Aftr::GRAVITY );
   }
   this->setActorChaseType( STANDARDEZNAV ); //Default is STANDARDEZNAV mode
   //this->setNumPhysicsStepsPerRender( 0 ); //pause physics engine on start up; will remain paused till set to 1
}


GLViewAAAFinalProject::~GLViewAAAFinalProject()
{
   //Implicitly calls GLView::~GLView()
}


void GLViewAAAFinalProject::updateWorld()
{
   GLView::updateWorld(); //Just call the parent's update world first.
                          //If you want to add additional functionality, do it after
                          //this call.
}


void GLViewAAAFinalProject::onResizeWindow( GLsizei width, GLsizei height )
{
   GLView::onResizeWindow( width, height ); //call parent's resize method.
}


void GLViewAAAFinalProject::onMouseDown( const SDL_MouseButtonEvent& e )
{
   GLView::onMouseDown( e );
}


void GLViewAAAFinalProject::onMouseUp( const SDL_MouseButtonEvent& e )
{
   GLView::onMouseUp( e );
}


void GLViewAAAFinalProject::onMouseMove( const SDL_MouseMotionEvent& e )
{
   GLView::onMouseMove( e );
}


void GLViewAAAFinalProject::onKeyDown( const SDL_KeyboardEvent& key )
{
   GLView::onKeyDown( key );
   if( key.keysym.sym == SDLK_0 )
      this->setNumPhysicsStepsPerRender( 1 );

   if( key.keysym.sym == SDLK_1 )
   {

   }
}


void GLViewAAAFinalProject::onKeyUp( const SDL_KeyboardEvent& key )
{
   GLView::onKeyUp( key );
}


void Aftr::GLViewAAAFinalProject::loadMap()
{
   this->worldLst = new WorldList(); //WorldList is a 'smart' vector that is used to store WO*'s
   this->actorLst = new WorldList();
   this->netLst = new WorldList();

   ManagerOpenGLState::GL_CLIPPING_PLANE = 1000.0;
   ManagerOpenGLState::GL_NEAR_PLANE = 0.1f;
   ManagerOpenGLState::enableFrustumCulling = false;
   Axes::isVisible = true;
   this->glRenderer->isUsingShadowMapping( false ); //set to TRUE to enable shadow mapping, must be using GL 3.2+

   this->cam->setPosition( 15,15,10 );

   std::string shinyRedPlasticCube( ManagerEnvironmentConfiguration::getSMM() + "/models/cube4x4x4redShinyPlastic_pp.wrl" );
   std::string wheeledCar( ManagerEnvironmentConfiguration::getSMM() + "/models/rcx_treads.wrl" );
   std::string grass( ManagerEnvironmentConfiguration::getSMM() + "/models/grassFloor400x400_pp.wrl" );
   std::string human( ManagerEnvironmentConfiguration::getSMM() + "/models/human_chest.wrl" );
   
   //SkyBox Textures readily available
   std::vector< std::string > skyBoxImageNames; //vector to store texture paths
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_water+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_dust+6.jpg" );
   skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_mountains+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_winter+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/early_morning+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_afternoon+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_cloudy+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_cloudy3+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_day+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_day2+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_deepsun+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_evening+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_morning+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_morning2+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_noon+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_warp+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_Hubble_Nebula+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_gray_matter+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_easter+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_hot_nebula+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_ice_field+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_lemon_lime+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_milk_chocolate+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_solar_bloom+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_thick_rb+6.jpg" );

   {
      //Create a light
      float ga = 0.1f; //Global Ambient Light level for this module
      ManagerLight::setGlobalAmbientLight( aftrColor4f( ga, ga, ga, 1.0f ) );
      WOLight* light = WOLight::New();
      light->isDirectionalLight( true );
      light->setPosition( Vector( 0, 0, 100 ) );
      //Set the light's display matrix such that it casts light in a direction parallel to the -z axis (ie, downwards as though it was "high noon")
      //for shadow mapping to work, this->glRenderer->isUsingShadowMapping( true ), must be invoked.
      light->getModel()->setDisplayMatrix( Mat4::rotateIdentityMat( { 0, 1, 0 }, 90.0f * Aftr::DEGtoRAD ) );
      light->setLabel( "Light" );
      worldLst->push_back( light );
   }

   {
      //Create the SkyBox
      WO* wo = WOSkyBox::New( skyBoxImageNames.at( 0 ), this->getCameraPtrPtr() );
      wo->setPosition( Vector( 0, 0, 0 ) );
      wo->setLabel( "Sky Box" );
      wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
      worldLst->push_back( wo );
   }

   { 
      ////Create the infinite grass plane (the floor)
      WO* wo = WO::New( grass, Vector( 1, 1, 1 ), MESH_SHADING_TYPE::mstFLAT );
      wo->setPosition( Vector( 0, 0, 0 ) );
      wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
      wo->upon_async_model_loaded( [wo]()
         {
            ModelMeshSkin& grassSkin = wo->getModel()->getModelDataShared()->getModelMeshes().at( 0 )->getSkins().at( 0 );
            grassSkin.getMultiTextureSet().at( 0 ).setTexRepeats( 5.0f );
            grassSkin.setAmbient( aftrColor4f( 0.4f, 0.4f, 0.4f, 1.0f ) ); //Color of object when it is not in any light
            grassSkin.setDiffuse( aftrColor4f( 1.0f, 1.0f, 1.0f, 1.0f ) ); //Diffuse color components (ie, matte shading color of this object)
            grassSkin.setSpecular( aftrColor4f( 0.4f, 0.4f, 0.4f, 1.0f ) ); //Specular color component (ie, how "shiney" it is)
            grassSkin.setSpecularCoefficient( 10 ); // How "sharp" are the specular highlights (bigger is sharper, 1000 is very sharp, 10 is very dull)
         } );
      wo->setLabel( "Grass" );
      worldLst->push_back( wo );
   }

   //{
   //   //Create the infinite grass plane that uses the Open Dynamics Engine (ODE)
   //   WO* wo = WOStatic::New( grass, Vector(1,1,1), MESH_SHADING_TYPE::mstFLAT );
   //   ((WOStatic*)wo)->setODEPrimType( ODE_PRIM_TYPE::PLANE );
   //   wo->setPosition( Vector(0,0,0) );
   //   wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
   //   wo->getModel()->getModelDataShared()->getModelMeshes().at(0)->getSkins().at(0).getMultiTextureSet().at(0)->setTextureRepeats( 5.0f );
   //   wo->setLabel( "Grass" );
   //   worldLst->push_back( wo );
   //}

   //{
   //   //Create the infinite grass plane that uses NVIDIAPhysX(the floor)
   //   WO* wo = WONVStaticPlane::New( grass, Vector( 1, 1, 1 ), MESH_SHADING_TYPE::mstFLAT );
   //   wo->setPosition( Vector( 0, 0, 0 ) );
   //   wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
   //   wo->getModel()->getModelDataShared()->getModelMeshes().at( 0 )->getSkins().at( 0 ).getMultiTextureSet().at( 0 )->setTextureRepeats( 5.0f );
   //   wo->setLabel( "Grass" );
   //   worldLst->push_back( wo );
   //}

   //{
   //   //Create the infinite grass plane (the floor)
   //   WO* wo = WONVPhysX::New( shinyRedPlasticCube, Vector( 1, 1, 1 ), MESH_SHADING_TYPE::mstFLAT );
   //   wo->setPosition( Vector( 0, 0, 50.0f ) );
   //   wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
   //   wo->setLabel( "Grass" );
   //   worldLst->push_back( wo );
   //}

   //{
   //   WO* wo = WONVPhysX::New( shinyRedPlasticCube, Vector( 1, 1, 1 ), MESH_SHADING_TYPE::mstFLAT );
   //   wo->setPosition( Vector( 0, 0.5f, 75.0f ) );
   //   wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
   //   wo->setLabel( "Grass" );
   //   worldLst->push_back( wo );
   //}

   //{
   //   WO* wo = WONVDynSphere::New( ManagerEnvironmentConfiguration::getVariableValue( "sharedmultimediapath" ) + "/models/sphereRp5.wrl", Vector( 1.0f, 1.0f, 1.0f ), mstSMOOTH );
   //   wo->setPosition( 0, 0, 100.0f );
   //   wo->setLabel( "Sphere" );
   //   this->worldLst->push_back( wo );
   //}

   //{
   //   WO* wo = WOHumanCal3DPaladin::New( Vector( .5, 1, 1 ), 100 );
   //   ((WOHumanCal3DPaladin*)wo)->rayIsDrawn = false; //hide the "leg ray"
   //   ((WOHumanCal3DPaladin*)wo)->isVisible = false; //hide the Bounding Shell
   //   wo->setPosition( Vector( 20, 20, 20 ) );
   //   wo->setLabel( "Paladin" );
   //   worldLst->push_back( wo );
   //   actorLst->push_back( wo );
   //   netLst->push_back( wo );
   //   this->setActor( wo );
   //}
   //
   //{
   //   WO* wo = WOHumanCyborg::New( Vector( .5, 1.25, 1 ), 100 );
   //   wo->setPosition( Vector( 20, 10, 20 ) );
   //   wo->isVisible = false; //hide the WOHuman's bounding box
   //   ((WOHuman*)wo)->rayIsDrawn = false; //show the 'leg' ray
   //   wo->setLabel( "Human Cyborg" );
   //   worldLst->push_back( wo );
   //   actorLst->push_back( wo ); //Push the WOHuman as an actor
   //   netLst->push_back( wo );
   //   this->setActor( wo ); //Start module where human is the actor
   //}

   //{
   //   //Create and insert the WOWheeledVehicle
   //   std::vector< std::string > wheels;
   //   std::string wheelStr( "../../../shared/mm/models/WOCar1970sBeaterTire.wrl" );
   //   wheels.push_back( wheelStr );
   //   wheels.push_back( wheelStr );
   //   wheels.push_back( wheelStr );
   //   wheels.push_back( wheelStr );
   //   WO* wo = WOCar1970sBeater::New( "../../../shared/mm/models/WOCar1970sBeater.wrl", wheels );
   //   wo->setPosition( Vector( 5, -15, 20 ) );
   //   wo->setLabel( "Car 1970s Beater" );
   //   ((WOODE*)wo)->mass = 200;
   //   worldLst->push_back( wo );
   //   actorLst->push_back( wo );
   //   this->setActor( wo );
   //   netLst->push_back( wo );
   //}
   
   //Make a Dear Im Gui instance via the WOImGui in the engine... This calls
   //the default Dear ImGui demo that shows all the features... To create your own,
   //inherit from WOImGui and override WOImGui::drawImGui_for_this_frame(...) (among any others you need).
   // 
   // TODO: look closer at this, because apparently I'm gonna need to figure out subscribe_drawImGuiWidget
   // 
   //WOImGui* gui = WOImGui::New( nullptr );
   //gui->setLabel( "My Gui" );
   //gui->subscribe_drawImGuiWidget(
   //   [this, gui]() //this is a lambda, the capture clause is in [], the input argument list is in (), and the body is in {}
   //   {
   //      ImGui::ShowDemoWindow(); //Displays the default ImGui demo from C:/repos/aburn/engine/src/imgui_implot/implot_demo.cpp
   //      WOImGui::draw_AftrImGui_Demo( gui ); //Displays a small Aftr Demo from C:/repos/aburn/engine/src/aftr/WOImGui.cpp
   //      ImPlot::ShowDemoWindow(); //Displays the ImPlot demo using ImGui from C:/repos/aburn/engine/src/imgui_implot/implot_demo.cpp
   //   } );
   //this->worldLst->push_back( gui );

   ////////////////////////////////////////////////////////////////////////////////
   ////////////////////////////     MY STUFF    ///////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////
   
   srand(time(NULL));

   for (int i = 0; i < 5; i++) {
       Gladiator newglad = Gladiator(1);
       newglad.firstname = dub(nameList);
       newglad.lastname = dub(nameList);
       allies.push_back(newglad);
       //TODO: also make the pieces
   }

   for (int i = 0; i < 5; i++) {
       std::cout << "The " << i << "th ally gladiator is named " << allies[i].firstname << " " << allies[i].lastname << "." << std::endl;
   }


   //Gladiator* testGlad = &allies[0];
   //Gladiator* testGlad2 = &allies[1];

   //GladiatorGUI* test = GladiatorGUI::New(nullptr, testGlad, 5.0f, 5.0f);
   //test->gladiator = testGlad;
   //this->worldLst->push_back(test);

   //test = GladiatorGUI::New(nullptr, testGlad, 5.0f, 5.0f);
   //GladiatorGUI* test2 = GladiatorGUI::New(nullptr, testGlad2, 5.0f, 5.0f);
   
   //int theParam = 42;

   tester = TestGUI();//TestGUI(board, p_board, pieces, allies, enemies);
   TestGUI* tester2 = &tester;
   //std::vector<TestGUI> unmutable;
   //unmutable.push_back(tester);

   WOImGui* gui = WOImGui::New(nullptr);
   gui->subscribe_drawImGuiWidget(
       [this, gui, tester2]()
       {
           //Here is a super neato paradigm that could be extended to support real-time introspection.
           //This is the glue code that is called from within the WOImGui instance...
           //Whenever a WO wants to draw some Gui stuff about that WO's internal state,
           //it simply asks the gui to call a function. That function is this lambda.
           //Since we don't want to put the entire ImGui draw call right here (even though
           //we could), let's just have the lambda call the corresponding WO's drawImGui_
           //method.
           //this->
           Gladiator* glad0 = &allies[0];
           Gladiator* glad1 = &allies[1];
           Gladiator* glad2 = &allies[2];
           Gladiator* glad3 = &allies[3];
           Gladiator* glad4 = &allies[4];
           glad0->my_ImGui_draw_method();
           glad1->my_ImGui_draw_method();
           glad2->my_ImGui_draw_method();
           glad3->my_ImGui_draw_method();
           glad4->my_ImGui_draw_method();
           //TestGUI* tester2 = &unmutable[0];
           tester2->drawMover();
           tester2->drawCombat();
 

       });
   this->worldLst->push_back(gui);


   for (int i = 0; i < 7; i++) {
       for (int j = 0; j < 7; j++) {
           WO* wo = WO::New(shinyRedPlasticCube, Vector(1, 1, 1), MESH_SHADING_TYPE::mstFLAT);
           wo->setPosition(4*i, 4*j, 0);
           p_board[i][j] = wo;
           this->worldLst->push_back(wo);
       }
   }

   for (int i = 0; i < 5; i++) {        //Create ally pieces
       WO* wo = WO::New(shinyRedPlasticCube, Vector(0.5, 0.5, 0.5), MESH_SHADING_TYPE::mstFLAT);
       auto vec = p_board[0][i]->getPosition();
       float x = vec[0]; float y = vec[1];
       wo->setPosition(x, y, 4);
       pieces[0][i] = wo;
       this->worldLst->push_back(wo);
   }

   for (int i = 0; i < 5; i++) {       //Create enemy pieces
       WO* wo = WO::New(shinyRedPlasticCube, Vector(0.5, 0.5, 0.5), MESH_SHADING_TYPE::mstFLAT);
       auto vec = p_board[6][6-i]->getPosition();
       float x = vec[0]; float y = vec[1];
       wo->setPosition(x, y, 4);
       pieces[6][6-i] = wo;
       this->worldLst->push_back(wo);
   }

   for (int i = 0; i < 5; i++) {     //Assign the allies to their places on the board
       board[0][i] = &allies[i];
   }



   createAAAFinalProjectWayPoints();
}

//TODO list:
//1. Combat <------ the big one
//2. Shop




void GLViewAAAFinalProject::createAAAFinalProjectWayPoints()
{
   // Create a waypoint with a radius of 3, a frequency of 5 seconds, activated by GLView's camera, and is visible.
   WayPointParametersBase params(this);
   params.frequency = 5000;
   params.useCamera = true;
   params.visible = true;
   WOWayPointSpherical* wayPt = WOWayPointSpherical::New( params, 3 );
   wayPt->setPosition( Vector( 50, 0, 3 ) );
   worldLst->push_back( wayPt );
}
