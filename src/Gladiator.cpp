#include "Gladiator.h"

//Stats are randomly determined
Gladiator::Gladiator(int team) {
	//Set the bases
	this->maxHP = (rand() % 20)+10;     this->curHP = this->maxhp;     //Ranges from 10 to 29
	this->baseAtk = (rand() % 5) + 1;   this->curAtk = this->baseAtk;  //Ranges from 1 to 5
	this->baseDef = (rand() % 5) + 1;   this->curDef = this->baseDef;  //Ranges from 1 to 5
	this->baseSup = (rand() % 10 + 2);  this->curSup = this->baseSup;  //Ranges from 2 to 11
	this->baseAcc = (rand() % 20) + 10; this->curAcc = this->baseAcc;  //Ranges from 10 to 29
	this->baseEv = (rand() % 20) + 10;  this->curEv = this->baseEv;    //Ranges from 10 to 29

	///These always start at 0 (they are irrelevant for enemy gladiators)
	this->favor = 0;
	this->fame = 0;

	///Defaults (set individually if something different is desired)
	this->off1 = Attack;
	this->off2 = Attack;      //TODO: consider randomizing the second offensive skill
	this->sup1 = Inspire;     //TODO: consider randomizing both support skills
	this->sup2 = Resolve;
	this->ai = Indecisive;    //TODO: consider randomizing ai
	this->personality = Warrior;   //TODO: DEFINITELY randomize this

	//The team
	this->team = team;

	//TODO: cosmetics

}

Gladiator::Gladiator(int hp, int atk, int def, int sup, int acc, int ev, int team) {
	
	///Set the bases
	this->maxHP = hp;     this->curHP = hp;
	this->baseAtk = atk;  this->curAtk = atk;
	this->baseDef = def;  this->curDef = def;
	this->baseSup = sup;  this->curSup = sup;
	this->baseAcc = acc;  this->curAcc = acc;
	this->baseEv = ev;    this->curEv = ev;

	///These always start at 0 (they are irrelevant for enemy gladiators)
	this->favor = 0;
	this->fame = 0;

	///Defaults (set individually if something different is desired)
	this->off1 = Attack;
	this->off2 = Attack;
	this->sup1 = Inspire;
	this->sup2 = Resolve;
	this->ai = Indecisive;
	this->personality = Warrior;   //Probably won't matter for any characters who aren't randomly generated

	//The team
	this->team = team;

	//TODO: cosmetics

}

//Gladiator::~Gladiator() {
	//TODO
//}