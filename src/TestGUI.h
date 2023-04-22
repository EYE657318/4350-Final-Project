#pragma once
#include "AftrConfig.h"
#include <string>

#include "WOImGuiAbstract.h"
#include "Gladiator.h"
#include "WO.h"



	class TestGUI {

	public:
		//TestGUI(Gladiator* board[7][7], Aftr::WO* p_board[7][7], Aftr::WO* pieces[7][7], std::vector<Gladiator> allies, std::vector<Gladiator> enemies);
		void drawMover(); //Drawing the gui  //consider putting variables here intead of constructor
		void drawCombat();
		TestGUI();
		bool to_move = false;
		bool next = false;
		bool combatEnabled = false;

		//narration is commentary on what has just happened
		//dialogue is what the ally gladiator has to say about it
		std::string narration;
		std::string dialogue;

		//these are the names of the character currently speaking
		std::string firstname;
		std::string lastname;

	protected:
		/*Gladiator* board[7][7];
		Aftr::WO* p_board[7][7];
		Aftr::WO* pieces[7][7];
		std::vector<Gladiator> allies; 
		std::vector<Gladiator> enemies;*/

		


	};
