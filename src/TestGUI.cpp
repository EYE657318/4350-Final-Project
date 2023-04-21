#include "AftrConfig.h"
#include <string>

#include "WOImGuiAbstract.h"
#include "Gladiator.h"
#include "WO.h"
#include "TestGUI.h"
#include "WOImGui.h" //GUI Demos also need to #include "AftrImGuiIncludes.h"
#include "AftrImGuiIncludes.h"


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


			ImGui::TreePop(); //ends your TreeNode (the "collapse" arrow hides all widgets
		}
		ImGui::Separator(); //draws bottom separator
	}

	void TestGUI::drawCombat() {
		if (ImGui::TreeNode("FighterGUI"))
		{
			if (ImGui::Button("Next!")) {
				//to_move = true;
			}


			ImGui::TreePop(); //ends your TreeNode (the "collapse" arrow hides all widgets
		}
		ImGui::Separator(); //draws bottom separator
	}

