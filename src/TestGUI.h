#pragma once
#include "AftrConfig.h"
#include <string>

#include "WOImGuiAbstract.h"
#include "Gladiator.h"
#include "WO.h"
#include "../include/irrklang/irrKlang.h"



	class TestGUI {

	public:
		//TestGUI(Gladiator* board[7][7], Aftr::WO* p_board[7][7], Aftr::WO* pieces[7][7], std::vector<Gladiator> allies, std::vector<Gladiator> enemies);
		void drawMover(); //Drawing the gui  //consider putting variables here intead of constructor
		void drawCombat();
		void drawShop();
		TestGUI();
		bool to_move = false;
		bool next = false;
		bool combatEnabled = false;

		//narration is commentary on what has just happened
		//dialogue is what the ally gladiator has to say about it
		//VESTIGIAL
		std::string narration;
		//STILL USED
		std::string dialogue;
		//NEW; holds everything that needs to be printed EXCEPT for what the gladiator says
		std::vector<std::string> text;

		//these are the names of the character currently speaking
		std::string firstname;
		std::string lastname;

		//Each item the shop can have has an id; this is a list of the ids available right now;
		std::vector<int> items = {1, 2, 3, 4};
		//If the shope is currently enabled
		bool shop_enabled = false;

		//The allies who can be edited by the shop
		std::vector<Gladiator>* allies;

		//gold!
		int gold = 20;

		//The player must click on this to allow combat to start
		bool ready_to_go = false;

		//Sound Stuff
		void PlayPurchase();
		irrklang::ISoundEngine* engine;

		//combats!
		int combats;

	protected:
		/*Gladiator* board[7][7];
		Aftr::WO* p_board[7][7];
		Aftr::WO* pieces[7][7];
		std::vector<Gladiator> allies; 
		std::vector<Gladiator> enemies;*/

		


	};
