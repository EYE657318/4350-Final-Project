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


				if (ImGui::Button("Next!")) {
					next = true;
				}

				ImGui::Text("%s %s %s", firstname.c_str(), lastname.c_str(), narration.c_str());
				ImGui::Text("%s %s says: %s", firstname.c_str(), lastname.c_str(), dialogue.c_str());

			}else {
				ImGui::Text("Combat GUI not enabled right now!");
				if (ImGui::Button("Start Combat")) {
					combatEnabled = true;
					//GLViewAAAFinalProject* glv = ManagerGLView::getGLViewT<GLViewAssignment6Networking>();
					//glv->changeCube(this->posX, this->posY, this->posZ, this->locX, this->locY, this->locZ, this->skin)
				}
			}


			ImGui::TreePop(); //ends your TreeNode (the "collapse" arrow hides all widgets
		}
		ImGui::Separator(); //draws bottom separator
	}

	void TestGUI::drawShop() {

		

		if (ImGui::TreeNode("Shop"))
		{
			if (shop_enabled) {

				if (std::find(items.begin(), items.end(), 1) != items.end()) {
					int cost = 10 + (gold/5);
					
					ImGui::Text("Offensive Skill: Pierce");

					Gladiator glad = (*allies)[0];
					std::string name = "Buy for " + glad.firstname + " " + glad.lastname;
					ImGui::Text("Price: %d gold", cost);
					if (ImGui::Button(name.c_str())) {
						//TODO
					}
					ImGui::SameLine();
					glad = (*allies)[1];
					name = "Buy for " + glad.firstname + " " + glad.lastname;
					if (ImGui::Button(name.c_str())) {
						//TODO
					}
					ImGui::SameLine();
					glad = (*allies)[2];
					name = "Buy for " + glad.firstname + " " + glad.lastname;
					if (ImGui::Button(name.c_str())) {
						//TODO
					}
					ImGui::SameLine();
					glad = (*allies)[3];
					name = "Buy for " + glad.firstname + " " + glad.lastname;
					if (ImGui::Button(name.c_str())) {
						//TODO
					}
					ImGui::SameLine();
					glad = (*allies)[4];
					name = "Buy for " + glad.firstname + " " + glad.lastname;
					if (ImGui::Button(name.c_str())) {
						//TODO
					}

				}

				if (std::find(items.begin(), items.end(), 2) != items.end()) {
					ImGui::Text("Offensive Skill: Bonebreaker");
				}

				if (std::find(items.begin(), items.end(), 3) != items.end()) {
					ImGui::Text("Offensive Skill: Swordbreaker");
				}

				if (std::find(items.begin(), items.end(), 4) != items.end()) {
					ImGui::Text("Support Skill: Heal");
				}

				if (std::find(items.begin(), items.end(), 5) != items.end()) {
					ImGui::Text("Support Skill: Train");
				}

				if (std::find(items.begin(), items.end(), 6) != items.end()) {
					ImGui::Text("Stat Boost: Attack");
				}

				if (std::find(items.begin(), items.end(), 7) != items.end()) {
					ImGui::Text("Stat Boost: Defense");
				}

				if (std::find(items.begin(), items.end(), 8) != items.end()) {
					ImGui::Text("Stat Boost: Accuracy");
				}

				if (std::find(items.begin(), items.end(), 9) != items.end()) {
					ImGui::Text("Stat Boost: Evade");
				}

				if (std::find(items.begin(), items.end(), 10) != items.end()) {
					ImGui::Text("Stat Boost: Support");
				}

			}
			else {
				ImGui::Text("Shop not currently enabled.");
			}

			ImGui::TreePop();
		}
		ImGui::Separator();
	}
