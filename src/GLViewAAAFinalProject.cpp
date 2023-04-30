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

bool GLViewAAAFinalProject::somethingMoves() {
    //TODO: port moving code here. team-agnostic
    
    //consider returning index of ally acting
    return false;
}

bool GLViewAAAFinalProject::somethingActs() {
    //TODO: acting code. team-agnostic

    return false;
}

bool GLViewAAAFinalProject::combatPhase() {               //The bool returned is whether or not the player lost the fight (true means they lost)
    int players_lost = false;
    //Turn on combat UI
    tester.combatEnabled = true;
    //Get the lengths of both teams
    int ally_len = allies.size();
    int enem_len = enemies.size();

    //when "next" is clicked on the combat UI, this is set to true
    //bool next = false; 

    std::cout << "setup for combat phase" << std::endl;

    tester.narration = " taps their foot... it's time for the next round.";
  
    //while (!tester.next) {

   // }
   // tester.next = false;

    //TODO: create the enemies (put it before we get enemies.size())
    
    while (true){
        //////TODO: all of this

        ////
        ////  AN ALLY MOVES
        ////
        
        //Check the allies to see if there is anyone left who is both alive and has not taken a turn yet.
        //Return the index of the first valid gladiator
        int to_move = -1;
        for (int i = 0; i < ally_len; i++) {
            if (allies[i].alive && allies[i].active) {
                to_move = i;
                break;
            }
        }
        std::cout << "after first pass, to_move is " << to_move << std::endl;
        //If no one was found, refresh all the gladiators who are alive, then return the index of the first one
        if (to_move == -1) {
            //Refresh them all
            for (int i = 0; i < ally_len; i++) {
                if (allies[i].alive) {
                    allies[i].active = true;
                }
            }
            std::cout << "refreshed allies" << std::endl;
            //Get the first one
            for (int i = 0; i < ally_len; i++) {
                if (allies[i].alive && allies[i].active) {
                    to_move = i;
                    break;
                }
            }
        }
        std::cout << "after second pass, to_move is " << to_move << std::endl;
        //If, after all that there STILL isn't a valid gladiator, they are all dead. exit
        if (to_move == -1) {
            players_lost = true;
            break;
        }

      
        
        /*//The actual movement
        if (board[ally_move_x][ally_move_y] != NULL) {
            tester.firstname = allies[to_move].firstname;
            tester.lastname = allies[to_move].lastname;
            tester.narration = "encountered a problem trying to move to their chosen space.";
            //TODO: dialogue
        }
        else {
            tester.firstname = allies[to_move].firstname;
            tester.lastname = allies[to_move].lastname;
            tester.narration = "should have just moved (but didn't cause that's not implemented yet).";
        }
        */

        //TODO, FOR THE ALLY:
        ////move them
        ////find out if they are in range to use a skill
        ////find their AI
        ////use the skill, if applicable
        ////Remove people if they are dead


        //TODO, FOR THE ENEMY:
        ////figure out which one is chosen
        ////move them
        ////find out if they are in range to use a skill
        ////find their AI
        ////use the skill, if applicable
        ////Remove people if they are dead

        //TEMP FOR TESTING:
        break;
    }
    
    
    return players_lost;
}

void GLViewAAAFinalProject::downtimePhase() {
    //////TODO: all of this
    //go through the vector of allies to turn UI on
    //??????
    std::cout << "temp downtime phase signifier" << std::endl;
}

void GLViewAAAFinalProject::phaseHandler() {

    int rounds = 0;         //Currently I plan for there to be 10, but this can change
    bool lost = false;      //If the player has lost
   
    std::cout << "combat disabled" << std::endl;

    while (rounds < 10) {

        this->downtimePhase();      //Run through the downtime phase
        lost = this->combatPhase(); //Run through the combat phase
        if (lost) { break; std::cout << "we lost!" << std::endl; }
        else { rounds++; std::cout << "onto the next round! current is"  << rounds << std::endl; }
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

   //I don't like running this if statement every second, but putting this in onCreate meant the engine never really started, so.....
   //if (!began) {
       /////////////////////
       ////////BEGIN////////
       /////////////////////
   //    began = true;
   //    phaseHandler();
   //}

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


//This function takes a team of gladiators.
//Return:
//true: at least one gladiator is alive
//false: none are alive
bool hasLiving(std::vector<Gladiator> team) {
    bool index = false;
    for (int i = 0; i < team.size(); i++) {
        if (team[i].alive){
            index = true;
            break;
        }
    }
    return index;
}

//This function takes a team of gladiators.
//Return: the index of the next active gladiator (refreshes list if necessary)
int getNext(std::vector<Gladiator> &team) {
    int index = -1;
    for (int i = 0; i < team.size(); i++) {
        if (team[i].active && team[i].alive) {
            //std::cout << "index " << i << " is valid\n";
            return i;
        }
        else {
            //std::cout << "index " << i << " is not valid\n";
        }
    }
    //If it hasn't returned an index, none of them are both active and alive
    //Refresh the list
    for (int i = 0; i < team.size(); i++) {
        if (team[i].alive) {
            team[i].active = true;
        }
    }
    //Call the function again with the new list
    index = getNext(team);
    return index;


}

//This function figures out where a gladiator will move next.
//It edits targets so that targets[0] is the xpos and targets[1] is the ypos 
//the board is the board, which will be checked for occupancy of the targeted space
//curposx and curposy are the current positions of the gladiator being checked.
//The function returns a bool that communicates whether the targeted space is occupied or not
//The actual movement itself is handled by a seperate function.
bool targetPos(int (&targets)[2], Gladiator* board[7][7], int curposx, int curposy) {    //[target xpos, target ypos]

    //Determine where to move
    //Movement is biased towards moving closer to the center
    //I have no idea why I didn't just calculate x movement and y movement seperately, but I'm not changing it now.
    if (curposx - 3 < 0 && curposy - 3 < 0) {
        //biased to going positive in both directions
        int random = rand() % 6;
        switch (random) {
            case 0: targets[0] = curposx + 1; targets[1] = curposy; break;
            case 1: targets[0] = curposx + 1; targets[1] = curposy; break;
            case 2: targets[0] = curposx; targets[1] = curposy + 1; break;
            case 3: targets[0] = curposx; targets[1] = curposy + 1; break;
            case 4: targets[0] = curposx - 1; targets[1] = curposy; break;
            case 5: targets[0] = curposx; targets[1] = curposy - 1; break;
        }
    }
    else if (curposx - 3 < 0 && curposy - 3 >= 0) {
        //biased to going positive x,  negative y
        int random = rand() % 6;
        switch (random) {
            case 0: targets[0] = curposx + 1; targets[1] = curposy; break;
            case 1: targets[0] = curposx + 1; targets[1] = curposy; break;
            case 2: targets[0] = curposx; targets[1] = curposy - 1; break;
            case 3: targets[0] = curposx; targets[1] = curposy - 1; break;
            case 4: targets[0] = curposx - 1; targets[1] = curposy; break;
            case 5: targets[0] = curposx; targets[1] = curposy + 1; break;
        }
    }
    else if (curposx - 3 >= 0 && curposy - 3 < 0) {
        //biased to going negative x, positive y
        int random = rand() % 6;
        switch (random) {
            case 0: targets[0] = curposx - 1; targets[1] = curposy; break;
            case 1: targets[0] = curposx - 1; targets[1] = curposy; break;
            case 2: targets[0] = curposx; targets[1] = curposy + 1; break;
            case 3: targets[0] = curposx; targets[1] = curposy + 1; break;
            case 4: targets[0] = curposx + 1; targets[1] = curposy; break;
            case 5: targets[0] = curposx; targets[1] = curposy - 1; break;
        }
    }
    else {
        //biased to going negative in both directions
        int random = rand() % 6;
        switch (random) {
            case 0: targets[0] = curposx - 1; targets[1] = curposy; break;
            case 1: targets[0] = curposx - 1; targets[1] = curposy; break;
            case 2: targets[0] = curposx; targets[1] = curposy - 1; break;
            case 3: targets[0] = curposx; targets[1] = curposy - 1; break;
            case 4: targets[0] = curposx + 1; targets[1] = curposy; break;
            case 5: targets[0] = curposx; targets[1] = curposy + 1; break;
        }
    }

    //Account for potential out-of-bounds (make them go in the opposite direction)
    if (targets[0] == -1) { targets[0] = 1; }
    if (targets[0] == 7) { targets[0] = 5; }
    if (targets[1] == -1) { targets[1] = 1; }
    if (targets[1] == 7) { targets[1] = 5; }

    if (board[targets[0]][targets[1]] == NULL){
        return true;
    }
    else {
        return false;
    }

    //TEMP for debugging
    return true;

}

//This function is given a position and a gladiator, and moves the gladiator to that position
//This must update the board of gladiators, the board of pieces, and the gladiator's variables
//Maybe even more! Expect bugs from this for a long time. It's one of the trickier functions
void movePiece(Gladiator &glad, Gladiator* (& board)[7][7], WO* (&pieces)[7][7], int newx, int newy, WO* (&p_board)[7][7]) {
    //TODO:
    int xpos = glad.xpos;
    int ypos = glad.ypos;

    board[xpos][ypos] = NULL;

    WO* piece = pieces[xpos][ypos];
    pieces[xpos][ypos] = NULL;

    board[newx][newy] = &glad;
    glad.xpos = newx;
    glad.ypos = newy;
    
    //set the new position on the pieces to the piece
    pieces[newx][newy] = piece;
    auto vec = p_board[newx][newy]->getPosition();
    piece->setPosition(vec[0], vec[1], 4);


}


void GLViewAAAFinalProject::onKeyDown( const SDL_KeyboardEvent& key )
{
   GLView::onKeyDown( key );
   if( key.keysym.sym == SDLK_0 )
      this->setNumPhysicsStepsPerRender( 1 );

   if (key.keysym.sym == SDLK_SPACE) {

       if (phase == 0) {
           //We are in downtime. Switch to combat
           step = 0;
           phase = 1;
           std::cout << "Phase: end downtime\n";
           
           //Create a new set of enemies
           //enemies.clear();
           //for (int i = 0; i < 5; i++) {
           //    Gladiator newglad = Gladiator(1);
           //    newglad.firstname = dub(nameList);
           //    newglad.lastname = dub(nameList);
           //    enemies.push_back(newglad);
           //}
           
           //TODO: all of this



       }
       else {
          //We are in combat.
           switch (step) {
           case 0:
               {/*TODO: move ally*/
                   cur_actor = -1;
                   if (hasLiving(allies)) {
                       cur_actor = getNext(allies);
                       allies[cur_actor].active = false;                            //Deactivate them; this is their turn.
                       int move[2];
                       bool valid_move = targetPos(move, board, allies[cur_actor].xpos, allies[cur_actor].ypos);
                       if (valid_move) {
                           std::cout << "Ally at (" << allies[cur_actor].xpos << ", " << allies[cur_actor].ypos <<
                               ") should move to (" << move[0] << ", " << move[1] << ").\n";
                           movePiece(allies[cur_actor], board, pieces, move[0], move[1], p_board);
                       }
                       else {
                           std::cout << "Ally at (" << allies[cur_actor].xpos << ", " << allies[cur_actor].ypos <<
                               ") can't move to (" << move[0] << ", " << move[1] << ").\n";
                       }
                       step++;
                   }
                   else {
                       std::cout << "All allies dead, none to move!\n";
                   }
               }
               break;
           case 1:
               {/*TODO: act ally*/
                                        //NOTE: If I ever add an effect that would allow for movement to kill someone,
                                        //check if cur_actor is still alive here
               std::cout << "Phase: act ally " << cur_actor << "\n";
               step++;
               }
               break;
           case 2:
               {/*TODO: move enemy*/
               std::cout << "Phase: move enemy\n";
               cur_actor = -1;
               if (hasLiving(enemies)) {
                   cur_actor = getNext(enemies);
                   enemies[cur_actor].active = false;                            //Deactivate them; this is their turn.
                   int move[2];
                   bool valid_move = targetPos(move, board, enemies[cur_actor].xpos, enemies[cur_actor].ypos);
                   if (valid_move) {
                       std::cout << "Enemy at (" << enemies[cur_actor].xpos << ", " << enemies[cur_actor].ypos <<
                           ") should move to (" << move[0] << ", " << move[1] << ").\n";
                   }
                   else {
                       std::cout << "Enemy at (" << enemies[cur_actor].xpos << ", " << enemies[cur_actor].ypos <<
                           ") can't move to (" << move[0] << ", " << move[1] << ").\n";
                   }
                   //std::cout << "Phase: move enemy " << cur_actor << "\n";
                   step++;
               }
               else {
                   std::cout << "All allies dead, none to move!\n";
               }
                }
               break;
           case 3:
               {/*TODO: act enemy*/
                                        //NOTE: If I ever add an effect that would allow for movement to kill someone,
                                        //check if cur_actor is still alive here
               std::cout << "Phase: act enemy " << cur_actor << "\n";
               step = 0;
                }
               break;
           default: 
                {/*This should not happen*/
               std::cout << "This should not happen\n";
               step = 0;
                }
           }


       }
      
       //Problems with figuring out how to wait for stuff before, so new plan:
       //Spacebar is the "do next thing" button.
       //We will keep track of what "phase" (combat/downtime) we are on and what "step" (movement/action) we are on
       //
       //phase: combat
       //step 1: move ally
       //step 2: act ally
       //step 3: move enemy
       //step 4: act enemy
       //loop
       //
       //phase: downtime
       //space should just end this, it's all menus for editing characters


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
       Gladiator newglad = Gladiator(0);
       newglad.firstname = dub(nameList);
       newglad.lastname = dub(nameList);
       allies.push_back(newglad);
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

   //NULL everything on the board to start
   for (int i = 0; i < 7; i++) {
       for (int j = 0; j < 7; j++) {
           board[i][j] = NULL;
       }
   }

   //enemy gladiator piece and assignment to board
   for (int i = 0; i < 5; i++) {
       Gladiator newglad = Gladiator(1);
       newglad.firstname = dub(nameList);
       newglad.lastname = dub(nameList);
       enemies.push_back(newglad);
   }
   for (int i = 0; i < 5; i++) {
       board[6][6 - i] = &enemies[i];
       enemies[i].xpos = 6;
       enemies[i].ypos = 6 - i;
   }

   for (int i = 0; i < 5; i++) {     //Assign the allies to their places on the board
       board[0][i] = &allies[i];
       allies[i].xpos = 0;
       allies[i].ypos = i;
   }



   createAAAFinalProjectWayPoints();

   

}

//TODO list:
//1. Combat <------ the big one
//2. Shop

//Misc:
//textures, models, skubox
//get portraits to actually work
//more names




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
