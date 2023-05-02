#include "Gladiator.h"
#include "WOImGui.h" //GUI Demos also need to #include "AftrImGuiIncludes.h"
#include "AftrImGuiIncludes.h"

//Stats are randomly determined
Gladiator::Gladiator(int team) {
	//Set the bases
	this->maxHP = (rand() % 20)+10;     this->curHP = this->maxHP;     //Ranges from 10 to 29
	this->baseAtk = (rand() % 10) + 1;   this->curAtk = this->baseAtk;  //Ranges from 1 to 10
	this->baseDef = (rand() % 5) + 1;   this->curDef = this->baseDef;  //Ranges from 1 to 5
	this->baseSup = (rand() % 10 + 2);  this->curSup = this->baseSup;  //Ranges from 2 to 11
	this->baseAcc = (rand() % 20) + 10; this->curAcc = this->baseAcc;  //Ranges from 10 to 29
	this->baseEv = (rand() % 20) + 10;  this->curEv = this->baseEv;    //Ranges from 10 to 29

	///These always start at 0 (they are irrelevant for enemy gladiators)
	this->favor = 0;
	this->fame = 0;

	///Defaults (set individually if something different is desired)
	this->off1 = Attack;
	this->off2 = Attack;      
	this->sup1 = Inspire;     
	this->sup2 = Resolve;
	this->ai = Indecisive;    
	this->personality = Warrior;  //This is randomized later 

	//The team
	this->team = team;

	//cosmetics
	//this->portrait = "../mm/images/portraits/Eyesack.png";
	//Names will be set seperately
	this->personality = Warrior;   

	//randomize portrait
	int random = rand() % 33;
	switch (random) {
	case 0: this->portrait = "../mm/images/portraits/Applejuice.png"; break;
	case 1: this->portrait = "../mm/images/portraits/Beholding.png"; break;
	case 2: this->portrait = "../mm/images/portraits/Belgarath.png"; break;
	case 3: this->portrait = "../mm/images/portraits/Ojutai.png"; break;
	case 4: this->portrait = "../mm/images/portraits/Bluevel.png"; break;
	case 5: this->portrait = "../mm/images/portraits/Charles.png"; break;
	case 6: this->portrait = "../mm/images/portraits/Contessa.png"; break;
	case 7: this->portrait = "../mm/images/portraits/Cultist1.png"; break;
	case 8: this->portrait = "../mm/images/portraits/Cultist2.png"; break;
	case 9: this->portrait = "../mm/images/portraits/Cultist3.png"; break;
	case 10: this->portrait = "../mm/images/portraits/Cultist4.png"; break;
	case 11: this->portrait = "../mm/images/portraits/Dabe.png"; break;
	case 12: this->portrait = "../mm/images/portraits/Dino.png"; break;
	case 13: this->portrait = "../mm/images/portraits/Dong.png"; break;
	case 14: this->portrait = "../mm/images/portraits/Eyesack.png"; break;
	case 15: this->portrait = "../mm/images/portraits/Fire.png"; break;
	case 16: this->portrait = "../mm/images/portraits/Golfballs.png"; break;
	case 17: this->portrait = "../mm/images/portraits/GRIDa.png"; break;
	case 18: this->portrait = "../mm/images/portraits/Hand.png"; break;
	case 19: this->portrait = "../mm/images/portraits/Lin.png"; break;
	case 20: this->portrait = "../mm/images/portraits/Moth.png"; break;
	case 21: this->portrait = "../mm/images/portraits/Phantasm.png"; break;
	case 22: this->portrait = "../mm/images/portraits/Pigeon.png"; break;
	case 23: this->portrait = "../mm/images/portraits/Pirate.png"; break;
	case 24: this->portrait = "../mm/images/portraits/Shrom.png"; break;
	case 25: this->portrait = "../mm/images/portraits/Spinny.png"; break;
	case 26: this->portrait = "../mm/images/portraits/Stabby.png"; break;
	case 27: this->portrait = "../mm/images/portraits/Stauf.png"; break;
	case 28: this->portrait = "../mm/images/portraits/Stev.png"; break;
	case 29: this->portrait = "../mm/images/portraits/Sun.png"; break;
	case 30: this->portrait = "../mm/images/portraits/Ted.png"; break;
	case 31: this->portrait = "../mm/images/portraits/Waterlevel.png"; break;
	case 32: this->portrait = "../mm/images/portraits/Sorren.png"; break;
	}

	std::cout << "the portrait is: " << portrait << "\n";

	//Randomize personality
	random = rand() % 4;
	switch (random) {
		case 0: personality = Warrior; break;
		case 1: personality = Fearful; break;
		case 2: personality = Excited; break;
		case 3: personality = Quiet; break;
	}

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
		std::string truename = firstname + " " + lastname;
		if (!alive) {
			truename = truename + " (deceased)";
		}
		if (ImGui::TreeNode(truename.c_str()))
		{
			if (gui_enabled) {
				ImGui::Text("GLADIATOR INFORMATION");

				ImGui::Text("%s %s", firstname.c_str(), lastname.c_str());
				//Personality is hidden information
				//AI is hidden information           //TODO: since this is strategically relevant, consider changing this

				/*if (ImGui::Button("KILL (test)")) {
					active = false;
					alive = false;
				}*/
				switch (ai) {
				case Indecisive: ImGui::Text("AI: Indecisive"); break;
				case Offense: ImGui::Text("AI: Offensive"); break;
				case Support: ImGui::Text("AI: Support"); break;
				}

				switch (off1) {
				case 0:ImGui::Text("Skill 1: Attack"); break;
				case 1:ImGui::Text("Skill 1: Pierce"); break;
				case 2:ImGui::Text("Skill 1: Bonebreaker"); break;
				case 3:ImGui::Text("Skill 1: Swordbreaker"); break;
				default: ImGui::Text("Error! Skill %d does not have a display case", off1); break;
				}
				switch (off2) {
				case 0:ImGui::Text("Skill 2: Attack"); break;
				case 1:ImGui::Text("Skill 2: Pierce"); break;
				case 2:ImGui::Text("Skill 2: Bonebreaker"); break;
				case 3:ImGui::Text("Skill 2: Swordbreaker"); break;
				default: ImGui::Text("Error! Skill %d does not have a display case", off2); break;
				}
				switch (sup1) {
				case 0:ImGui::Text("Support 1: Heal"); break;
				case 1:ImGui::Text("Support 1: Inspire"); break;
				case 2:ImGui::Text("Support 1: Resolve"); break;
				case 3:ImGui::Text("Support 1: Train"); break;
				default: ImGui::Text("Error! Skill %d does not have a display case", sup1); break;
				}
				switch (sup2) {
				case 0:ImGui::Text("Support 2: Heal"); break;
				case 1:ImGui::Text("Support 2: Inspire"); break;
				case 2:ImGui::Text("Support 2: Resolve"); break;
				case 3:ImGui::Text("Support 2: Train"); break;
				default: ImGui::Text("Error! Skill %d does not have a display case", sup2); break;
				}
				

				ImGui::Text("Active: %d, Alive: %d", active, alive);

				if (upgrade_enabled) {
					ImGui::Text("Upgrade points: %d", points);
				}

				ImGui::Text("Hit Points: %d / %d", curHP, maxHP);
				if (upgrade_enabled) {
					if (ImGui::Button("Increase HP")) {
						if (points > 0) {
							maxHP++;
							points--;
							dialogue = D_IncreaseHP();
							PlayUpgrade();
						}
						else {
							dialogue = D_IncreaseFail();
						}
					}
				}

				ImGui::Text("Attack: %d / %d", curAtk, baseAtk);
				if (upgrade_enabled) {
					if (ImGui::Button("Increase Atk")) {
						if (points > 0) {
							baseAtk++;
							points--;
							dialogue = D_IncreaseAtk();
							PlayUpgrade();
						}
						else {
							dialogue = D_IncreaseFail();
						}
					}
				}

				ImGui::Text("Defense: %d / %d", curDef, baseDef);
				if (upgrade_enabled) {
					if (ImGui::Button("Increase Def")) {
						if (points > 0) {
							baseDef++;
							points--;
							dialogue = D_IncreaseDef();
							PlayUpgrade();
						}
						else {
							dialogue = D_IncreaseFail();
						}
					}
				}

				ImGui::Text("Accuracy: %d / %d", curAcc, baseAcc);
				if (upgrade_enabled) {
					if (ImGui::Button("Increase Acc")) {
						if (points > 0) {
							baseAcc++;
							points--;
							dialogue = D_IncreaseAcc();
							PlayUpgrade();
						}
						else {
							dialogue = D_IncreaseFail();
						}
					}
				}

				ImGui::Text("Evade: %d / %d", curEv, baseEv);
				if (upgrade_enabled) {
					if (ImGui::Button("Increase Ev")) {
						if (points > 0) {
							baseEv++;
							points--;
							dialogue = D_IncreaseEv();
							PlayUpgrade();
						}
						else {
							dialogue = D_IncreaseFail();
						}
					}
				}

				ImGui::Text("Support: %d / %d", curSup, baseSup);
				if (upgrade_enabled) {
					if (ImGui::Button("Increase Sup")) {
						if (points > 0) {
							baseSup++;
							points--;
							dialogue = D_IncreaseSup();
							PlayUpgrade();
						}
						else {
							dialogue = D_IncreaseFail();
						}
					}
				}


				ImGui::Text("%s %s Says: %s", firstname.c_str(), lastname.c_str(), dialogue.c_str());
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

void Gladiator::PlayUpgrade() {
	irrklang::ISound* s = engine->play2D("../mm/sounds/Upgrade.wav");
}

//////////////////////////////////////
//////// DIALOGUE FUNCS //////////////
//////////////////////////////////////

std::string Gladiator::D_IncreaseHP() {
	switch (this->personality) {
	case Warrior:
		return "''May life's struggles never wear me down.''";
		break;       //Why did I put break after all these??? They return????
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
		return "ERROR: D_IncreaseFail not implemented for this personality type!";
		break;

	}
}

std::string Gladiator::D_AttackHit() {
	switch (this->personality) {
	case Warrior:
		return "''Strike back, if you dare.''";
	case Fearful:
		return "''Wait, wait! It was an accident, I swear!''";
	case Excited:
		return "''Do you think the head would be a better target?''";
	case Quiet:
		return "''...''";
	case GodEmperor: 
		return "''PERISH!''";
	case Wolf:
		return "''Grrrr... grahhkk!''";
	default: return "ERROR: D_AttackHit not implemented for this personality type!";

	}

	return "???";
}

std::string Gladiator::D_AttackMiss() {
	switch (this->personality) {
	case Warrior:
		return "''There is always a chance of failure.''";
	case Fearful:
		return "''I sure hope the didn't notice that...''";
	case Excited:
		return "''Next time for sure!''";
	case Quiet:
		return "''...Ergh.''";
	case GodEmperor: 
		return "''YOUR FATE IS INEVITABLE.''";
	case Wolf:
		return "''Mrghhhh... grah...''";
	default:
		return "ERROR: D_AttackMiss not implemented for this personality type!";

	}

	return "???";
}

std::string Gladiator::D_SupportUse() {
	switch (this->personality) {
	case Warrior:
		return "''Fight onward!''";
	case Fearful:
		return "''The enemy's that way! I'll just stay here.''";
	case Excited:
		return "''Go get 'em!''";
	case Quiet:
		return "''...Good luck.''";
	case GodEmperor:
		return "''Destroy them, soldier!''";
	case Wolf:
		return "''Grakh! Grakh!''";
	default:
		return "''ERROR: D_SupportUse not implemented for this personality type!''";
	}

	return "???";
}

std::string Gladiator::D_Death() {
	switch (this->personality) {
	case Warrior:
		return "''I fall.... today....''";
	case Fearful:
		return "''No...''";
	case Excited:
		return "''Damn... too soon...''";
	case Quiet:
		return "''......''";
	case GodEmperor:
		return "''No...! Usupers...!''";
	case Wolf:
		return "''Whihhhhnnnk...''";
	default:
		return "ERROR: D_Death not implemented for this personality type!";

	}

	return "???";
}

std::string Gladiator::D_LearnOffenseSkill() {
	switch (this->personality) {
	case Warrior:
		return "''Another weapon in my arsenal.''";
	case Fearful:
		return "''So can I stand, like... farther away?''";
	case Excited:
		return "''A shame I have lose the old one.''";
	case Quiet:
		return "''You're making this too complicated.''";
	default:
		return "ERROR: D_LearnOffenseSkill not implemented for this personality type!";

	}

	return "???";
}

std::string Gladiator::D_LearnSupportSkill() {
	switch (this->personality) {
	case Warrior:
		return "''I will assist where needed.''";
	case Fearful:
		return "''Backline work! Yay!''";
	case Excited:
		return "''Yeah, I can use this!''";
	case Quiet:
		return "''...Whatever.''";
	default:
		return "ERROR: D_LearnSupportSkill not implemented for this personality type!";

	}

	return "???";
}

std::string Gladiator::D_MoveSuccess() {
	switch (this->personality) {
	case Warrior:
		return "''Ever onward.''";
	case Fearful:
		return "''Run away! Run away!''";
	case Excited:
		return "''Wheeeeee!!''";
	case Quiet:
		return "''...''";
	case GodEmperor:
		return "''We march. To victory!''";
	case Wolf:
		return "''Rahhhrk! Rahhhrk!''";
	default:
		return "ERROR: D_MoveSuccess not implemented for this personality type!";

	}

	return "???";
}

std::string Gladiator::D_MoveFail() {
	switch (this->personality) {
	case Warrior:
		return "''I must remain patient.''";
	case Fearful:
		return "''Please, let me out of here!''";
	case Excited:
		return "''Out of my way, out of my way!''";
	case Quiet:
		return "''...Move.''";
	case GodEmperor:
		return "''You are out of position. Move!''";
	case Wolf:
		return "''Grrrr......''";
	default:
		return "ERROR: D_MoveFail not implemented for this personality type!";

	}
	return "???";
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

