#include "Gladiator.h"
#include "WOImGui.h" //GUI Demos also need to #include "AftrImGuiIncludes.h"
#include "AftrImGuiIncludes.h"

//Stats are randomly determined
Gladiator::Gladiator(int team) {
	//Set the bases
	this->maxHP = (rand() % 20)+10;     this->curHP = this->maxHP;     //Ranges from 10 to 29
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

	//cosmetics
	this->portrait = "../mm/images/portraits/Eyesack.png"; //TODO: actually randomize this
	//Names will be set seperately
	this->personality = Warrior;   //TODO: actually randomize this

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

	//cosmetics
	this->portrait = "../mm/images/portraits/Eyesack.png"; //TODO: actually randomize this
	//Names will be set seperately
	this->personality = Warrior;   //TODO: actually randomize this


}

//////////////////////////////////////
///////////// GUI STUFF //////////////
//////////////////////////////////////
void Gladiator::my_ImGui_draw_method() {
		if (ImGui::TreeNode("Gladiator"))
		{
			if (gui_enabled) {
				ImGui::Text("GLADIATOR INFORMATION");


				//TODO: image stuff ImGui::Image();
				ImGui::Text("%s %s", this->firstname.c_str(), this->lastname.c_str());
				//Personality is hidden information
				//AI is hidden information           //TODO: since this is strategically relevant, consider changing this

				ImGui::Text("Upgrade points: %d", this->points);

				ImGui::Text("Hit Points: %d", this->maxHP);
				if (ImGui::Button("Increase HP")) {
					if (points > 0) {
						this->maxHP++;
						points--;
						dialogue = this->D_IncreaseHP();
					}
					else {
						dialogue = this->D_IncreaseFail();
					}
				}

				ImGui::Text("Attack: %d", this->baseAtk);
				if (ImGui::Button("Increase Atk")) {
					if (points > 0) {
						this->baseAtk++;
						points--;
						dialogue = this->D_IncreaseAtk();
					}
					else {
						dialogue = this->D_IncreaseFail();
					}
				}

				ImGui::Text("Defense: %d", this->baseDef);
				if (ImGui::Button("Increase Def")) {
					if (points > 0) {
						this->baseDef++;
						points--;
						dialogue = this->D_IncreaseDef();
					}
					else {
						dialogue = this->D_IncreaseFail();
					}
				}

				ImGui::Text("Accuracy: %d", this->baseAcc);
				if (ImGui::Button("Increase Acc")) {
					if (points > 0) {
						this->baseAcc++;
						points--;
						dialogue = this->D_IncreaseAcc();
					}
					else {
						dialogue = this->D_IncreaseFail();
					}
				}

				ImGui::Text("Evade: %d", this->baseEv);
				if (ImGui::Button("Increase Ev")) {
					if (points > 0) {
						this->baseEv++;
						points--;
						dialogue = this->D_IncreaseEv();
					}
					else {
						dialogue = this->D_IncreaseFail();
					}
				}

				ImGui::Text("Support: %d", this->baseSup);
				if (ImGui::Button("Increase Sup")) {
					if (points > 0) {
						this->baseSup++;
						points--;
						dialogue = this->D_IncreaseSup();
					}
					else {
						dialogue = this->D_IncreaseFail();
					}
				}


				ImGui::Text("%s %s Says: %s", this->firstname.c_str(), this->lastname.c_str(), dialogue.c_str());
			}
			else {
				ImGui::Text("This GUI is not available at this time!");
			}


			//ImGui::Checkbox( "Add More Widgets here", &myVal);
			ImGui::TreePop(); //ends your TreeNode (the "collapse" arrow hides all widgets 
			//between here and the above call to ImGui::TreeNode(...)
		}
		ImGui::Separator(); //draws bottom separator
}



//////////////////////////////////////
//////// DIALOGUE FUNCS //////////////
//////////////////////////////////////

std::string Gladiator::D_IncreaseHP() {
	switch (this->personality) {
	case Warrior:
		return "''May life's struggles never wear me down.''";
		break;
	case Fearful:
		return "''You're not going to let them hit me, right? ...Right?''";
		break;
	case Excited:
		return "''I mean, I prefer to stab, but sure!''";
		break;
	case Quiet:
		return "''...Helpful.''";
		break;
	default:
		return "ERROR: D_IncreaseHP not implemented for this personality type!";
		break;

	}
}

std::string Gladiator::D_IncreaseAtk() {
	switch (this->personality) {
		case Warrior:
			return "''I must grow to match my opponents.''";
			break;
		case Fearful:
			return "''I would, um, prefer I not get within range in the first place.''";
			break;
		case Excited:
			return "''Haha! Let me at 'em!''";
			break;
		case Quiet:
			return "''...Good.''";
			break;
		default:
			return "ERROR: D_IncreaseAtk not implemented for this personality yet!";
			break;

	}
}

std::string Gladiator::D_IncreaseDef() {
	switch (this->personality) {
		case Warrior:
			return "''Even I can not escape my enemies' blades.''";
			break;
		case Fearful:
			return "''Does it protect my eyes? I really don't want to lose an eye...''";
			break;
		case Excited:
			return "''I can just *imageine* the looks on their faces when they can't even *touch* me!''";
			break;
		case Quiet:
			return "''...Thank you.''";
			break;
		default:
			return "''ERROR: D_IncreaseDef not implemented for this personality type!''";
			break;

	}
}

std::string Gladiator::D_IncreaseSup() {
	switch (this->personality) {
	case Warrior:
		return "''We must watch eachothers' backs.''";
		break;
	case Fearful:
		return "''Oh good! I'll let everyone else do the fighting.''";
		break;
	case Excited:
		return "''My potions only SOMETIMES explode!''";
		break;
	case Quiet:
		return "''...Lovely.''";
		break;
	default:
		return "ERROR: D_IncreaseSup not implemented for this personality type!";
		break;

	}
}

std::string Gladiator::D_IncreaseAcc() {
	switch (this->personality) {
		case Warrior:
			return "''The fundamentals are the most important.''";
			break;
		case Fearful:
			return "''Can I *throw* my sword instead? Please?''";
			break;
		case Excited:
			return "''Hahaha! Wait... which end of this am I supposed to use again?''";
			break;
		case Quiet:
			return "''...Sure.''";
			break;
		default:
			return "ERROR: D_IncreaseAcc not implemented for this personality type!";
			break;

	}
}

std::string Gladiator::D_IncreaseEv() {
	switch (this->personality) {
	case Warrior:
		return "''It is easier to parry than evade.''";
		break;
	case Fearful:
		return "''Oh believe me, I can run as far as you'd like!''";
		break;
	case Excited:
		return "''I'll run circles around them!''";
		break;
	case Quiet:
		return "''...Acceptable.''";
		break;
	default:
		return "ERROR: D_IncraseEv not implemented for this personality type!";
		break;

	}
}

std::string Gladiator::D_IncreaseFail() {
	switch (this->personality) {
	case Warrior:
		return "''I have only so much room to grow.''";
		break;
	case Fearful:
		return "''Thanks! ...Wait, no, that didn't work.''";
		break;
	case Excited:
		return "''Aww, I really wanted that...''";
		break;
	case Quiet:
		return "''A shame.''";
		break;
	default:
		return "ERROR: D_IncreaseFail not implemented for this personality type!''";
		break;

	}
}

//dialogue template
/*std::string Gladiator::D_IncreaseAtk() {
	switch (this->personality) {
		case Warrior:
			break;
		case Fearful:
			break;
		case Excited:
			break;
		case Quiet:
			break;
		default:
			break;

	}
}*/


//Gladiator::~Gladiator() {
	//TODO
//}

