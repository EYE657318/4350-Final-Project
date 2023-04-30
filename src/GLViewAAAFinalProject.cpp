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
"Apelles", "Antonius", "Apollodoru", "Bellicus", "Brutus", "Balbus", "Badius", "Caelus", "Caesar", "Caesia", "Callistus",
"Camillus", "Capito", "Castus", "Catulus", "Ceius", "Celadus", "Cerdo", "Cerrinius", "Chius", "Chloe", "Coelius", "Conopis", 
"Corus", "Communis", "Dadanus", "Duacus", "Drusus", "Dido", "December", "Danne", "Danaus", "Damoetas", "Ecidia", "Entellus", 
"Eucinus", "Eros", "Epise", "Ephesus", "Euplia", "Epremus", "Elea", "Fabius", "Facilis", "Falax", "Fausta", "Faustilla", "Felicio", 
"Felix", "Filetus", "Fortuna", "Florus", "Fronto", "Gallus", "Gemellus", "Genialis", "Glyco", "Gratus", "Hecticus", "Hector", 
"Hedystus", "Helenus", "Heliodorus", "Herennius", "Hore", "Hostilius", "Hyginus", "Ianuaria", "Iarinus", "Iatacus",
"Icarus", "Irene", "Iris", "Isidorus", "Isthmus", "Iucudus", "Iulius", "Iuma", "Iupiter", "Ladicula", "Latona", "Lenas", 
"Lentulus", "Lepidus", "Lesbianus", "Libanis", "Litus", "Livia", "Lucida", "Lucilius", "Mago", "Marcellus", "Marianus", 
"Marcus", "Marina", "Martha", "Mathia", "Medusa", "Megiste", "Menander", "Minius", "Modesta", "Mola", "Mugo", "Mus", 
"Myrtilus", "Myrtis", "Mystis", "Narcissus", "Nauplis", "Neptunus", "Nero", "Nicerate", "Nicopolis",
"Ninnius", "Nucerinus", "Nymphe", "Odysseus", "Octavius", "Oceanus", "Occasus", "Otho", "Oppius", "Pallade",
"Palmyra", "Papirius", "Paris", "Pelagia", "Phileros", "Philippus", "Phoebe", "Phosphorus", "Pilades",
"Quintio",  "Quartilla", "Quieta", "Rarus", "Remus", "Restituta", "Romulus", "Romula", "Rufilla",
"Rustica", "Rusticus", "Sabina", "Sagitta", "Salvia", "Samius", "Satyr", "Saturninus",
"Sava", "Scodopordunicus", "Secundus", "Servilius", "Sittius", "Terentius", "Terminalis", "Tettius",
"Theophilos", "Thetis", "Thymele", "Tiburtinus", "Titus", "Trebonius", "Tyche", "Valens", "Valentina",
"Valeria", "Vatifon", "Veneria", "Venus", "Venuleius", "Vera", "Verecunnus", "Vibii", "Victor", "Zosimus", "Zeus" };

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
//These functions are all out of date. Check for the new ones down by OnKeyPress

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
   
   //Skins are crashing, not sure why
   for (int i = 0; i < 7; i++) {
       for (int j = 0; j < 7; j++) {
           WO* tile = p_board[i][j];
           tile->upon_async_model_loaded([tile]()
               {
                   std::optional<Aftr::Tex> the_skin = ManagerTex::loadTexAsync_unregistered("../mm/images/skins/Marble.png");
                   auto found = the_skin.value();
                   ModelMeshSkin skin(found);
                   skin.setMeshShadingType(MESH_SHADING_TYPE::mstSMOOTH);

                   tile->getModel()->getModelDataShared()->getModelMeshes().at(0)->getSkins().at(0) = std::move(skin);



               });
       }
   }
   for (int i = 0; i < 5; i++) {
       WO* piece1 = ally_pieces[i];
       WO* piece2 = enemy_pieces[i];
       piece1->upon_async_model_loaded([piece1]()
           {
               std::optional<Aftr::Tex> the_skin = ManagerTex::loadTexAsync_unregistered("../mm/images/skins/Ally.png");
               auto found = the_skin.value();
               ModelMeshSkin skin(found);
               skin.setMeshShadingType(MESH_SHADING_TYPE::mstSMOOTH);

               piece1->getModel()->getModelDataShared()->getModelMeshes().at(0)->getSkins().at(0) = std::move(skin);



           });
       piece2->upon_async_model_loaded([piece2]()
           {
               std::optional<Aftr::Tex> the_skin = ManagerTex::loadTexAsync_unregistered("../mm/images/skins/Enemy.png");
               auto found = the_skin.value();
               ModelMeshSkin skin(found);
               skin.setMeshShadingType(MESH_SHADING_TYPE::mstSMOOTH);

               piece2->getModel()->getModelDataShared()->getModelMeshes().at(0)->getSkins().at(0) = std::move(skin);



           });
   }
   

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
    //Important information
    int xpos = glad.xpos;
    int ypos = glad.ypos;

    //Remomve the gladiator from the old position
    board[xpos][ypos] = NULL;

    //Get the physical piece for the gladiator, then remove it
    WO* piece = pieces[xpos][ypos];
    pieces[xpos][ypos] = NULL;

    //Put the gladiator in the new space
    board[newx][newy] = &glad;
    glad.xpos = newx;
    glad.ypos = newy;
    
    //put the piece in its new place
    pieces[newx][newy] = piece;

    //Put the new piece in physical space
    auto vec = p_board[newx][newy]->getPosition();
    piece->setPosition(vec[0], vec[1], 4);


}

//This function takes a gladiator, then returns what type of action they will take based on their AI
//true: attack
//false: support
bool getFirstAction(Gladiator glad) {

    int random = rand() % 4;
    AI ai = glad.ai;
   
    //No way in HELL am I nesting switch statements
    if (ai == Offense) {
        switch (random) {
            case 0: return true;
            case 1: return true;
            case 2: return true;
            case 3: return false;
        }
    }
    else if (ai == Support) {
        switch (random) {
            case 0: return false;
            case 1: return false;
            case 2: return false;
            case 3: return true;
        }
    }
    else {
        //Indecisive
        switch (random) {
            case 0: return true;
            case 1: return true;
            case 2: return false;
            case 3: return false;
        }

    }

    //This should never happen
    return false;

}

//Checks if two gladiators are on the same team
//0: the target does not exist
//1: the target is of the opposite team
//2: the target is of the same team;
int sameTeam(int actorx, int actory, int targetx, int targety, Gladiator* board[7][7]) {
    //Check for out of bonunds
    if (targetx > 6 || targetx < 0 || targety > 6 || targety < 0) {
        return 0;
    }
    //Check for empty space
    if (board[targetx][targety] == NULL) {
        //std::cout << "At" << targetx << ", " << targety << "is Null!!!\n";
        return 0;
    }
    return board[actorx][actory]->team == board[targetx][targety]->team ? 2 : 1;
}

//This tests the previously selected action type against the board; is it actually possible?
//Remember: true is attack, false is support.
//Return values:
//1: the originally selected action is valid. use that.
//2: the originally selected action is not valid, but the opposite is. use that.
//0: neither action is possible. don't act.
int getFinalAction(bool first_act, Gladiator glad, Gladiator* board[7][7]) {

    //NOTE: Right now, this only checks adjacency. if I make ranged skills, this can be expanded

    bool has_ally = false;   //Is there an ally in range?
    bool has_enemy = false;  //Is there an enemy in range?

    int xpos = glad.xpos;
    int ypos = glad.ypos;

    //For future expansion:
    // x = number of spaces of range (need to check everything <= x)
    // i is a number 0..x
    //[i][x-i]
    //[i][-x+i]
    //[-i][x-i]
    //[-i][-x+i]
    //there is probably a better way to do this^^^; it double counts every space

    int sameteam = sameTeam(xpos, ypos, xpos+1, ypos, board);
    switch (sameteam) {
        case 0: break;
        case 1: has_enemy = true; break;
        case 2: has_ally = true; break;
    }
    sameteam = sameTeam(xpos, ypos, xpos - 1, ypos, board);
    switch (sameteam) {
        case 0: break;
        case 1: has_enemy = true; break;
        case 2: has_ally = true; break;
    }
    sameteam = sameTeam(xpos, ypos, xpos, ypos+1, board);
    switch (sameteam) {
        case 0: break;
        case 1: has_enemy = true; break;
        case 2: has_ally = true; break;
    }
    sameteam = sameTeam(xpos, ypos, xpos, ypos - 1, board);
    switch (sameteam) {
        case 0: break;
        case 1: has_enemy = true; break;
        case 2: has_ally = true; break;
    }

    switch (first_act) {
        case true: return has_enemy ? 1 : (has_ally ? 2 : 0); break;
        case false: return has_ally ? 1 : (has_enemy ? 2 : 0);  break;
    }

    //This shouldn't happen
    return 0;

}

//Changes the skin of the game piece, so that the currently acting gladiator looks distinct from the others.
//team: what team the piece is on; true: ally, false: enemy
//activate: whether the piece needs to gain the gold border or lose it;
//true: select, false: deselect
void selectSkin(bool team, bool activate, WO* wo) {

    std::string skin_str;
    if (team) {
        if (activate) {
            skin_str = "../mm/images/skins/AllyG.png";
        }
        else {
            skin_str = "../mm/images/skins/Ally.png";
        }
    }
    else {
        if (activate) {
            skin_str = "../mm/images/skins/EnemyG.png";
        }
        else {
            skin_str = "../mm/images/skins/Enemy.png";
        }
    }

    std::optional<Aftr::Tex> the_skin = ManagerTex::loadTexAsync_unregistered(skin_str);
    auto found = the_skin.value();
    ModelMeshSkin skin(found);
    skin.setMeshShadingType(MESH_SHADING_TYPE::mstSMOOTH);
    wo->getModel()->getModelDataShared()->getModelMeshes().at(0)->getSkins().at(0) = std::move(skin);
    /*wo->upon_async_model_loaded([wo, skin_str]()
        {
            std::optional<Aftr::Tex> the_skin = ManagerTex::loadTexAsync_unregistered(skin_str);
            auto found = the_skin.value();
            ModelMeshSkin skin(found);
            skin.setMeshShadingType(MESH_SHADING_TYPE::mstSMOOTH);
            std::cout << "Setting the skin!\n";
            



        });*/

}

///////////////////////////////////////////////
////////////// ACTIONS ////////////////////////
///////////////////////////////////////////////
//
// Each of these functions corresponds to one offensive or support skill
//

void skillAttack(Gladiator &glad, Gladiator* board[7][7], WO* pieces[7][7], int xtarg, int ytarg) {

    int damage = glad.curAtk - board[xtarg][ytarg]->curDef;
    if (damage <= 0) { damage = 1; }
    int accuracy = 70 + glad.curAcc - board[xtarg][ytarg]->curEv;
    if (accuracy < 20) { accuracy = 20; }
    int accroll = rand() % 100;
    bool hit = true;
    if (accroll > accuracy) { hit = false; }
    if (hit) {
        std::cout << "The gladiator hit for " << damage << " damage!\n";
        //TODO: narration

        board[xtarg][ytarg]->curHP -= damage;
        std::cout << "The target now has " << board[xtarg][ytarg]->curHP << " HP left!\n";

        //TODO: test for death               

    }
    else {
        std::cout << "The gladiator missed!\n";
        //TODO: narration
    }
}


//The big one
//This is the function that is called to make a gladiator actually act
//act_type is the type of action being performed (true = attack, false = support)
//This will likely have a lot of bugs at the start! Hopefully they're fixed by the time anyone else sees this!
void Act(bool act_type, Gladiator &glad, Gladiator* board[7][7], WO* pieces[7][7]) {

    //Get info about gladiator
    int xpos = glad.xpos;
    int ypos = glad.ypos;

    //The position of whoever will be targeted
    int xtarg = 0;
    int ytarg = 0;

    //Figure out who is being targeted
    //NOTE: this is not really random... consider fixing it if time allows

    //0: DNE
    //1: opp team
    //2: same team
    int sameteam = sameTeam(xpos, ypos, xpos + 1, ypos, board);
    switch (sameteam) {
        case 0: break;
        case 1: act_type ? (xtarg = xpos + 1) : (false); act_type ? (ytarg = ypos) : (false); break;
        case 2: act_type ? (false) : (xtarg = xpos + 1); act_type ? (false) : (ytarg = ypos); break;
    }
    sameteam = sameTeam(xpos, ypos, xpos - 1, ypos, board);
    switch (sameteam) {
        case 0: break;
        case 1: act_type ? (xtarg = xpos - 1) : (false); act_type ? (ytarg = ypos) : (false); break;
        case 2: act_type ? (false) : (xtarg = xpos - 1); act_type ? (false) : (ytarg = ypos); break;
    }
    sameteam = sameTeam(xpos, ypos, xpos, ypos + 1, board);
    switch (sameteam) {
        case 0: break;
        case 1: act_type ? (xtarg = xpos) : (false); act_type ? (ytarg = ypos + 1) : (false); break;
        case 2: act_type ? (false) : (xtarg = xpos); act_type ? (false) : (ytarg = ypos + 1); break;
    }
    sameteam = sameTeam(xpos, ypos, xpos, ypos - 1, board);
    switch (sameteam) {
        case 0: break;
        case 1: act_type ? (xtarg = xpos) : (false); act_type ? (ytarg = ypos - 1) : (false); break;
        case 2: act_type ? (false) : (xtarg = xpos); act_type ? (false) : (ytarg = ypos - 1); break;
    }

    //Great. Now we have the target!
    if (act_type) {
        std::cout << "This character will attack the gladiator at (" << xtarg << ", " << ytarg << ").\n";
    }
    else {
        std::cout << "This character will support the gladiator at (" << xtarg << ", " << ytarg << ").\n";
    }
    
    //Actually use the skill
    if(act_type){
        //get the skill that will be used
        int random = rand() % 2;
        OffSkill action = (random == 0) ? glad.off1 : glad.off2;

        //Do the thing                                                  //NOTE: to add a new skill, add it here! (and to enum)
        switch (action) {                                               //Maybe to random generation/shop depending
        //OFFENSIVE ACTION: ATTACK
        //A normal attack. Calculates accuracy versus evade, and attack versus defense
        case Attack: skillAttack(glad, board, pieces, xtarg, ytarg); break;
        case Pierce: {} break;
        case Bonebreaker: {} break;
        case Swordbreaker: {} break;
        }
    
    
    }else{
        //get the skill that will be used
        int random = rand() % 2;
        SupSkill action = (random == 0) ? glad.sup1 : glad.sup2;
    
    
    }

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
           cur_actor = -1; //so that unselecting the enemy skin doesn't break things
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
           //probably make a new function



       }
       else {
          //We are in combat.
           switch (step) {
           case 0:
               {/*move ally*/
               if (cur_actor != -1) {   //Unselect enemy skin
                   selectSkin(0, 0, enemy_pieces[cur_actor]);
               }
                   cur_actor = -1;
                   if (hasLiving(allies)) {
                       cur_actor = getNext(allies);
                       selectSkin(1, 1, ally_pieces[cur_actor]);
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
                       //TODO: end game
                   }
               }
               break;
           case 1:
               {/*TODO: act ally*/
                                        //NOTE: If I ever add an effect that would allow for movement to kill someone,
                                        //check if cur_actor is still alive here
               bool act_type = getFirstAction(allies[cur_actor]);
               int act_change = getFinalAction(act_type, allies[cur_actor], board);
               bool act = true;
               switch (act_change) {
                   //There is no valid action
                   case 0: std::cout << "Ally " << cur_actor << " has no valid targets.\n"; act = false; break; 
                   case 1: break; //Nothing needs to change
                   case 2: act_type = !act_type; //Change to the other action type

               }
               if (act) {
                   Act(act_type, allies[cur_actor], board, pieces);
               }
               step++;
               }
               break;
           case 2:
               {/*move enemy*/
               selectSkin(1, 0, ally_pieces[cur_actor]);  //Unselect skin of previous ally
               std::cout << "Phase: move enemy\n";
               cur_actor = -1;
               if (hasLiving(enemies)) {
                   cur_actor = getNext(enemies);
                   selectSkin(0, 1, enemy_pieces[cur_actor]); //Select skin for new actor
                   enemies[cur_actor].active = false;                            //Deactivate them; this is their turn.
                   int move[2];
                   bool valid_move = targetPos(move, board, enemies[cur_actor].xpos, enemies[cur_actor].ypos);
                   if (valid_move) {
                       std::cout << "Enemy at (" << enemies[cur_actor].xpos << ", " << enemies[cur_actor].ypos <<
                           ") should move to (" << move[0] << ", " << move[1] << ").\n";
                       movePiece(enemies[cur_actor], board, pieces, move[0], move[1], p_board);
                   }
                   else {
                       std::cout << "Enemy at (" << enemies[cur_actor].xpos << ", " << enemies[cur_actor].ypos <<
                           ") can't move to (" << move[0] << ", " << move[1] << ").\n";
                   }
                   step++;
               }
               else {
                   std::cout << "All enemies dead, none to move!\n";
                   //TODO: end battle
               }
                }
               break;
           case 3:
               {/*TODO: act enemy*/
                                        //NOTE: If I ever add an effect that would allow for movement to kill someone,
                                        //check if cur_actor is still alive here
               bool act_type = getFirstAction(enemies[cur_actor]);
               int act_change = getFinalAction(act_type, enemies[cur_actor], board);
               bool act = true;
               switch (act_change) {
                   //There is no valid action
                   case 0: std::cout << "Enemy " << cur_actor << " has no valid targets.\n"; act = false; break;
                   case 1: break; //Nothing needs to change
                   case 2: act_type = !act_type; //Change to the other action type

               }
               if (act) {
                   Act(act_type, enemies[cur_actor], board, pieces);
               }
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

   //std::string marble = "../mm/images/skins/Marble.png";

   for (int i = 0; i < 7; i++) {   //Create the board
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
       ally_pieces[i] = wo;
       this->worldLst->push_back(wo);
   }

   for (int i = 0; i < 5; i++) {       //Create enemy pieces
       WO* wo = WO::New(shinyRedPlasticCube, Vector(0.5, 0.5, 0.5), MESH_SHADING_TYPE::mstFLAT);
       auto vec = p_board[6][6-i]->getPosition();
       float x = vec[0]; float y = vec[1];
       wo->setPosition(x, y, 4);
       pieces[6][6-i] = wo;
       enemy_pieces[i] = wo;
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
