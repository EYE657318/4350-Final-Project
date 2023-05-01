#include "AftrConfig.h"
#include <string>

#include "WOImGuiAbstract.h"
#include "Gladiator.h"
#include "WO.h"
#include "TestGUI.h"
#include "WOImGui.h" //GUI Demos also need to #include "AftrImGuiIncludes.h"
#include "AftrImGuiIncludes.h"
#include "GLViewAAAFinalProject.h"
#include "GLView.h"
#include "WorldContainer.h"
#include "AftrManagers.h"
#include <iostream>
#include <sstream>
#include <string>
#include "AftrManagers.h"
#include "Vector.h"
#include "WO.h"
#include "GLView.h"
#include "WorldContainer.h"



	/*TestGUI::TestGUI(Gladiator* board[7][7], Aftr::WO* p_board[7][7], Aftr::WO* pieces[7][7], std::vector<Gladiator> allies, std::vector<Gladiator> enemies) {
		this->board = board;
		this->p_board = p_board;
		this->pieces = pieces;
		this->allies = allies;
		this->enemies = enemies;
	}*/
	TestGUI::TestGUI() {

	}
	

	void TestGUI::drawMover() {
		if (ImGui::TreeNode("MoverGUI"))
		{
				if (ImGui::Button("Move!")) {
					to_move = true;
				}
				
				ImGui::Text("%d", to_move);
		


			ImGui::TreePop(); //ends your TreeNode (the "collapse" arrow hides all widgets
		}
		ImGui::Separator(); //draws bottom separator
	}

	void TestGUI::drawCombat() {
		if (ImGui::TreeNode("FighterGUI"))
		{
			if (combatEnabled) {


				for (int i = 0; i < text.size(); i++) {
					ImGui::Text(text[i].c_str());
				}

				ImGui::Text(dialogue.c_str());

			} else {
				ImGui::Text("Combat GUI not enabled right now!");
				//if (ImGui::Button("Start Combat")) {
				//	combatEnabled = true;
					//GLViewAAAFinalProject* glv = ManagerGLView::getGLViewT<GLViewAssignment6Networking>();
					//glv->changeCube(this->posX, this->posY, this->posZ, this->locX, this->locY, this->locZ, this->skin)
				//}
			}


			ImGui::TreePop(); //ends your TreeNode (the "collapse" arrow hides all widgets
		}
		ImGui::Separator(); //draws bottom separator
	}

	void TestGUI::drawShop() {

		

		if (ImGui::TreeNode("Shop"))
		{

			ImGui::Text("[Current Gold: %d]", gold);

			if (shop_enabled) {

				//Shope for: Pierce
				if (std::find(items.begin(), items.end(), 1) != items.end()) {
					int cost = 10 + (gold/5);
					
					ImGui::Text("***Offensive Skill: Pierce***");
					ImGui::Text("$ Price: %d gold", cost);

					Gladiator glad = (*allies)[0];
					std::string name = "Buy Pierce for " + glad.firstname + " " + glad.lastname;
					
					if (gold >= cost) {
						if (ImGui::Button(name.c_str())) {
							(*allies)[0].off2 = Pierce;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[1];
						name = "Buy Pierce for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[1].off2 = Pierce;
							gold -= cost;
						}
						glad = (*allies)[2];
						name = "Buy Pierce for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[2].off2 = Pierce;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[3];
						name = "Buy Pierce for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[3].off2 = Pierce;
							gold -= cost;
						}
						glad = (*allies)[4];
						name = "Buy Pierce for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[4].off2 = Pierce;
							gold -= cost;
						}
					}

				}

				if (std::find(items.begin(), items.end(), 2) != items.end()) {
					int cost = 10 + (gold / 5);
					ImGui::Text("***Offensive Skill: Bonebreaker***");
					ImGui::Text("$ Price: %d gold", cost);

					Gladiator glad = (*allies)[0];
					std::string name = "Buy Bonebreaker for " + glad.firstname + " " + glad.lastname;

					if (gold >= cost) {
						if (ImGui::Button(name.c_str())) {
							(*allies)[0].off2 = Bonebreaker;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[1];
						name = "Buy Bonebreaker for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[1].off2 = Bonebreaker;
							gold -= cost;
						}
						glad = (*allies)[2];
						name = "Buy Bonebreaker for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[2].off2 = Bonebreaker;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[3];
						name = "Buy Bonebreaker for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[4].off2 = Bonebreaker;
							gold -= cost;
						}
						glad = (*allies)[4];
						name = "Buy Bonebreaker for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[4].off2 = Bonebreaker;
							gold -= cost;
						}
					}
					
				}

				if (std::find(items.begin(), items.end(), 3) != items.end()) {
					int cost = 10 + (gold / 5);
					ImGui::Text("***Offensive Skill: Swordbreaker***");
					ImGui::Text("$ Price: %d gold", cost);

					Gladiator glad = (*allies)[0];
					std::string name = "Buy Swordbreaker for " + glad.firstname + " " + glad.lastname;

					if (gold >= cost) {
						if (ImGui::Button(name.c_str())) {
							(*allies)[0].off2 = Swordbreaker;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[1];
						name = "Buy Swordbreaker for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[1].off2 = Swordbreaker;
							gold -= cost;
						}
						glad = (*allies)[2];
						name = "Buy Swordbreaker for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[2].off2 = Swordbreaker;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[3];
						name = "Buy Swordbreaker for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[3].off2 = Swordbreaker;
							gold -= cost;
						}
						glad = (*allies)[4];
						name = "Buy Swordbreaker for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[4].off2 = Swordbreaker;
							gold -= cost;
						}
					}
				}

				if (std::find(items.begin(), items.end(), 4) != items.end()) {
					int cost = 10 + (gold / 4);
					ImGui::Text("***Support Skill: Heal***");
					ImGui::Text("$ Price: %d gold", cost);

					Gladiator glad = (*allies)[0];
					std::string name = "Buy Heal for " + glad.firstname + " " + glad.lastname;

					if (gold >= cost) {
						if (ImGui::Button(name.c_str())) {
							(*allies)[0].sup2 = Heal;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[1];
						name = "Buy Heal for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[1].sup2 = Heal;
							gold -= cost;
						}
						glad = (*allies)[2];
						name = "Buy Heal for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[2].sup2 = Heal;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[3];
						name = "Buy Heal for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[3].sup2 = Heal;
							gold -= cost;
						}
						glad = (*allies)[4];
						name = "Buy Heal for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[4].sup2 = Heal;
							gold -= cost;
						}
					}
				}

				if (std::find(items.begin(), items.end(), 5) != items.end()) {
					int cost = 20 + (gold / 3);
					ImGui::Text("***Support Skill: Train***");

					ImGui::Text("$ Price: %d gold", cost);

					Gladiator glad = (*allies)[0];
					std::string name = "Buy Train for " + glad.firstname + " " + glad.lastname;

					if (gold >= cost) {
						if (ImGui::Button(name.c_str())) {
							(*allies)[0].sup2 = Train;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[1];
						name = "Buy Train for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[1].sup2 = Train;
							gold -= cost;
						}
						glad = (*allies)[2];
						name = "Buy Train for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[2].sup2 = Train;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[3];
						name = "Buy Train for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[3].sup2 = Train;
							gold -= cost;
						}
						glad = (*allies)[4];
						name = "Buy Train for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[4].sup2 = Train;
							gold -= cost;
						}
					}
				}

				if (std::find(items.begin(), items.end(), 6) != items.end()) {
					int cost = 6 + (gold / 10);
					ImGui::Text("***Stat Boost: Attack***");

					ImGui::Text("$ Price: %d gold", cost);

					Gladiator glad = (*allies)[0];
					std::string name = "Buy Attack for " + glad.firstname + " " + glad.lastname;

					if (gold >= cost) {
						if (ImGui::Button(name.c_str())) {
							(*allies)[0].baseAtk += 2;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[1];
						name = "Buy Attack for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[1].baseAtk += 2;
							gold -= cost;
						}
						glad = (*allies)[2];
						name = "Buy Attack for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[2].baseAtk += 2;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[3];
						name = "Buy Attack for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[3].baseAtk += 2;
							gold -= cost;
						}
						glad = (*allies)[4];
						name = "Buy Attack for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[4].baseAtk += 2;
							gold -= cost;
						}
					}
				}

				if (std::find(items.begin(), items.end(), 7) != items.end()) {
					int cost = 6 + (gold / 10);
					ImGui::Text("***Stat Boost: Defense***");

					ImGui::Text("$ Price: %d gold", cost);

					Gladiator glad = (*allies)[0];
					std::string name = "Buy Defense for " + glad.firstname + " " + glad.lastname;

					if (gold >= cost) {
						if (ImGui::Button(name.c_str())) {
							(*allies)[0].baseDef += 2;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[1];
						name = "Buy Defense for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[1].baseDef += 2;
							gold -= cost;
						}
						glad = (*allies)[2];
						name = "Buy Defense for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[2].baseDef += 2;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[3];
						name = "Buy Defense for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[3].baseDef += 2;
							gold -= cost;
						}
						glad = (*allies)[4];
						name = "Buy Defense for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[4].baseDef += 2;
							gold -= cost;
						}
					}
				}

				if (std::find(items.begin(), items.end(), 8) != items.end()) {
					int cost = 6 + (gold / 10);
					ImGui::Text("***Stat Boost: Accuracy***");

					ImGui::Text("$ Price: %d gold", cost);

					Gladiator glad = (*allies)[0];
					std::string name = "Buy Accuracy for " + glad.firstname + " " + glad.lastname;

					if (gold >= cost) {
						if (ImGui::Button(name.c_str())) {
							(*allies)[0].baseAcc += 2;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[1];
						name = "Buy Accuracy for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[1].baseAcc += 2;
							gold -= cost;
						}
						glad = (*allies)[2];
						name = "Buy Accuracy for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[2].baseAcc += 2;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[3];
						name = "Buy Accuracy for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[3].baseAcc += 2;
							gold -= cost;
						}
						glad = (*allies)[4];
						name = "Buy Accuracy for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[4].baseAcc += 2;
							gold -= cost;
						}
					}
				}

				if (std::find(items.begin(), items.end(), 9) != items.end()) {
					int cost = 6 + (gold / 10);
					ImGui::Text("***Stat Boost: Evade***");

					ImGui::Text("$ Price: %d gold", cost);

					Gladiator glad = (*allies)[0];
					std::string name = "Buy Evade for " + glad.firstname + " " + glad.lastname;

					if (gold >= cost) {
						if (ImGui::Button(name.c_str())) {
							(*allies)[0].baseEv += 2;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[1];
						name = "Buy Evade for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[1].baseEv += 2;
							gold -= cost;
						}
						glad = (*allies)[2];
						name = "Buy Evade for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[2].baseEv += 2;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[3];
						name = "Buy Evade for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[3].baseEv += 2;
							gold -= cost;
						}
						glad = (*allies)[4];
						name = "Buy Evade for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[4].baseEv += 2;
							gold -= cost;
						}
					}
				}

				if (std::find(items.begin(), items.end(), 10) != items.end()) {
					int cost = 6 + (gold / 10);
					ImGui::Text("***Stat Boost: Support***");

					ImGui::Text("$ Price: %d gold", cost);

					Gladiator glad = (*allies)[0];
					std::string name = "Buy Support for " + glad.firstname + " " + glad.lastname;

					if (gold >= cost) {
						if (ImGui::Button(name.c_str())) {
							(*allies)[0].baseSup += 2;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[1];
						name = "Buy Support for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[1].baseSup += 2;
							gold -= cost;
						}
						glad = (*allies)[2];
						name = "Buy Support for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[2].baseSup += 2;
							gold -= cost;
						}
						ImGui::SameLine();
						glad = (*allies)[3];
						name = "Buy Support for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[3].baseSup += 2;
							gold -= cost;
						}
						glad = (*allies)[4];
						name = "Buy Support for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							(*allies)[4].baseSup += 2;
							gold -= cost;
						}
					}
				}

			}
			else {
				ImGui::Text("Shop not currently enabled.");
			}

			ImGui::TreePop();
		}
		ImGui::Separator();
	}


	/*ImGui::Text("$ Price: %d gold", cost);

					Gladiator glad = (*allies)[0];
					std::string name = "Buy for " + glad.firstname + " " + glad.lastname;

					if (gold >= cost) {
						if (ImGui::Button(name.c_str())) {
							//TODO: code
						}
						ImGui::SameLine();
						glad = (*allies)[1];
						name = "Buy for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							//TODO: code
						}
						glad = (*allies)[2];
						name = "Buy for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							//TODO: code
						}
						ImGui::SameLine();
						glad = (*allies)[3];
						name = "Buy for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							//TODO: code
						}
						glad = (*allies)[4];
						name = "Buy for " + glad.firstname + " " + glad.lastname;
						if (ImGui::Button(name.c_str())) {
							//TODO: code
						}
					}*/