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

