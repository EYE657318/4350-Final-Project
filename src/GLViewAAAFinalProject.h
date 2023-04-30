#pragma once

#include "GLView.h"
#include "Gladiator.h"
#include "TestGUI.h"

namespace Aftr
{
   class Camera;

/**
   \class GLViewAAAFinalProject
   \author Scott Nykl 
   \brief A child of an abstract GLView. This class is the top-most manager of the module.

   Read \see GLView for important constructor and init information.

   \see GLView

    \{
*/

class GLViewAAAFinalProject : public GLView
{
public:
   static GLViewAAAFinalProject* New( const std::vector< std::string >& outArgs );
   virtual ~GLViewAAAFinalProject();
   virtual void updateWorld(); ///< Called once per frame
   virtual void loadMap(); ///< Called once at startup to build this module's scene
   virtual void createAAAFinalProjectWayPoints();
   virtual void onResizeWindow( GLsizei width, GLsizei height );
   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );
   virtual void onKeyDown( const SDL_KeyboardEvent& key );
   virtual void onKeyUp( const SDL_KeyboardEvent& key );

   ///////////////////////
   ////Gladiator Stuff////
   ///////////////////////
   //ally gladiator vec
   std::vector<Gladiator> allies;              //In hindsight, these two shouldn't have been vectors. it's inconsistant
   //enemy gladiator vec
   std::vector<Gladiator> enemies;
   //the board (gladiator information)
   Gladiator* board[7][7];
   //the board (physical representation)
   WO* p_board[7][7];
   //the pieces (physical representation)
   WO* pieces[7][7];
   //Individual pieces for each team (makes resetting the board easier)
   WO* ally_pieces[5];
   WO* enemy_pieces[5];
   //tester GUI (please stop being const
   TestGUI tester;
   
   //////////////////////////////
   //// Other Combat Stuff //////
   //////////////////////////////
   //The gladiator who is currently being moved
   int cur_actor;    

protected:
   GLViewAAAFinalProject( const std::vector< std::string >& args );
   virtual void onCreate();   

   void downtimePhase();
   bool combatPhase();
   void phaseHandler();
   bool somethingMoves();
   bool somethingActs();

   //pacing control
   bool began = false;
   int phase = 0; //0 is downtime, 1 is combat
   int step = 0; //only used in combat. 0 is ally move, 1 ally act, 2 enemy move, 3 enemy act
};

/** \} */

} //namespace Aftr
