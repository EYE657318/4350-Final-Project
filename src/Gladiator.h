#include <vector>
#include <string>

#include "../include/irrklang/irrKlang.h"

#pragma once
//////////////////////////////////////////
////////////// ENUMS /////////////////////
//////////////////////////////////////////

//Enum: Offensive skills the gladiators can have
//Add more as needed                                //NOTE: to add a skill, put it here, and put its code in Act(),
enum OffSkill{                                      //maybe random generation/shop too depending
	Attack,          //A normal attack
	Pierce,          //An attack that ignores some defense
	Bonebreaker,     //An attack that (temporarily) reduces the target's defense
	Swordbreaker,    //An attack that (temporarily) reduces the target's attack
	//Sweep,         //Attacks enemies adjacent to the target
	//// ENEMY ONLY: ////
	AttackMaul,      //Reduces target's attack by a lot
	DefenseMaul,     //Reduces target's defense by a lot
	AccuracyMaul,    //Reduces target's accuracy by a lot
	EvadeMaul,       //Reduces target's evade by a lot
	DeificBlast,     //Reduces all of target's stats by 3. +5 damage.
};

//Enum: Support skills the gladiators can have
//Add more as needed
enum SupSkill{
	Heal,            //Heals ally
	Inspire,         //Boosts ally's attack
	Resolve,         //Boosts ally's defense
	Train,           //PERMANENTLY boosts ally's attack
};

//Enum: gladiator AI
//Add more as needed
enum AI {
	Offense,          //Attacks whenever possible
	Support,          //Supports whenever possible
	Indecisive,       //Picks at random
};

//Enum: personality has no gameplay effect; it just determines dialogue
//Add more as needed
enum Personality {
	Warrior,
	Fearful,
	Excited,
	Quiet,
	//// ENEMY ONLY ////
	GodEmperor,
	Wolf,
};

///////////////////////////////////////////
///////////// GLADIATOR CLASS /////////////
///////////////////////////////////////////
class Gladiator {
	public:

		///////////////////////////////
		////////  IMPORTANT  //////////
		///////////////////////////////
		Gladiator(int team);                                                    //Constructor (random values)
		Gladiator(int hp, int atk, int def, int sup, int acc, int ev, int team);  //Constructor (specific values)
		
		//~Gladiator(){}

		///////////////////////////////
		/////////// STATS /////////////
		///////////////////////////////
		//cur is what is used in combat
		//base is what it's set to after combat
		//(temporary stat modifiers influence cur)
		
		//How much damage until KO
		int maxHP;
		int curHP;

		//Damage dealt
		int baseAtk;
		int curAtk;

		//Damage resisted
		int baseDef;
		int curDef;

		//Power of support skills
		int baseSup;
		int curSup;

		//Accuracy of attacks
		int baseAcc;
		int curAcc;

		//Chance of evading attacks
		int baseEv;
		int curEv;

		/////////////////////////////////
		///////////// SKILLS ////////////
		/////////////////////////////////

		//The gladiator's two offensive skills
		OffSkill off1;
		OffSkill off2;

		//The gladiator's two support skills
		SupSkill sup1;
		SupSkill sup2;

		/////////////////////////////////
		//////// INFLUENCES /////////////
		/////////////////////////////////

		int favor; //How much Augustus likes the gladiator
		int fame;  //How much the crowd likes the gladiator
		//Note: both range from 0 - 100; at 0, they always vote for this gladiator to die. at 100, they never do.
		//Both must vote for death for the gladiator to be executed

		int team;  //Whose team are they on? 0 = player, 1 = enemy;

		bool active = true;  //When the unit has already taken a turn, this becomes false
		bool original = true;  //false if this replaced a dead gladiator
		bool alive = true;

		/////////////////////////////////
		/////////// COSMETIC ////////////
		/////////////////////////////////

		std::string portrait; //The path to the gladiator's character icon
		std::string firstname; //The character's first name
		std::string lastname;  //The character's last name
		Personality personality; //The character's personality

		std::string dialogue;


		/////////////////////////////////
		/////////// OTHER ///////////////
		/////////////////////////////////

		AI ai;     //How the gladiator acts in combat

		int xpos;  //The gladiator's x and y positions on the board
		int ypos;

		irrklang::ISoundEngine* engine;

		/////////////////////////////////
		///////// GUI STUFF /////////////
		/////////////////////////////////


		int points = 5; //Points remaining for upgrades
		bool gui_enabled = true; //whether we should be able to see the gladiator gui
		bool upgrade_enabled = true; //whether we should be able to see the upgrade guis
		void my_ImGui_draw_method(); //Drawing the gui

		/////////////////////////////////
		/////////// FUNCTIONS ///////////
		/////////////////////////////////

		void PlayUpgrade();
		

		/////////////////////////////////
		////////// DIALOGUE /////////////
		/////////////////////////////////

		std::string D_IncreaseHP();
		std::string D_IncreaseAtk();
		std::string D_IncreaseDef();
		std::string D_IncreaseSup();
		std::string D_IncreaseAcc();
		std::string D_IncreaseEv();
		std::string D_IncreaseFail();
		std::string D_AttackHit();
		std::string D_AttackMiss();
		std::string D_SupportUse();
		std::string D_Death();
		std::string D_LearnOffenseSkill();
		std::string D_LearnSupportSkill();
		std::string D_MoveSuccess();
		std::string D_MoveFail();


};




