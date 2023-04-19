#pragma once
#include "AftrConfig.h"
#include <string>
//#ifdef ASSIGNMENT_2_GUI

#include "WOImGuiAbstract.h"
#include "Gladiator.h"

namespace Aftr 
{

	class GladiatorGUI : public WOImGuiAbstract
	{

	public:
		static GladiatorGUI* New(WOGUI* parentWOGUI, Gladiator* gladiator, float width = 1.0f, float height = 1.0f);
		
		virtual ~GladiatorGUI();
		virtual void drawImGui_for_this_frame();
		virtual void onUpdateWO() override;

		int points = 10;
		Gladiator* gladiator;
		std::string dialogue = "''";



	protected:
		virtual void onCreate(float width, float height) override;
		GladiatorGUI(WOGUI* parentWOGUI);
		std::filesystem::path selected_path{ "./" };
		std::string origin_fileDialog = "None"; //not essential at all -- simply shows how title is used as a hashed key for file dialog




	};
}


//#endif