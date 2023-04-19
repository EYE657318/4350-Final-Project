#include "AftrConfig.h"
//#ifdef ASSIGNMENT_2_GUI

#include "GladiatorGUI.h"

//These include files are the ones specific to ImGui and are in userland
//at usr/include/imgui/. They provide the ImGui:: functions you need to draw
//your GUI.
#include "AftrImGuiIncludes.h"
#include <filesystem>

using namespace Aftr;


GladiatorGUI* GladiatorGUI::New(WOGUI* parentWOGUI, Gladiator* gladiator, float width, float height)
{
	GladiatorGUI* imgui = new GladiatorGUI(parentWOGUI);
	imgui->onCreate(width, height);
    imgui->gladiator = gladiator;
	return imgui;
}


GladiatorGUI::GladiatorGUI(WOGUI* parentWOGUI) : IFace(this), WOImGuiAbstract(parentWOGUI) {}

void GladiatorGUI::onCreate( float width, float height )
{
   //unless you are familiar with Dear ImGui and the base class, you probably just
   //want to call the parent's onCreate(). See the engine's WOImGui_DemoAbstract for reference.
   WOImGuiAbstract::onCreate( width, height );

   //this->selected_path = std::filesystem::path{ "." };
}

GladiatorGUI::~GladiatorGUI() {}

void GladiatorGUI::onUpdateWO() {}

void GladiatorGUI::drawImGui_for_this_frame()
{



    ImGui::Begin("GLADIATOR INFORMATION");


    //TODO: image stuff ImGui::Image();
    ImGui::Text("%s %s", gladiator->firstname.c_str(), gladiator->lastname.c_str());
    //Personality is hidden information
    //AI is hidden information           //TODO: since this is strategically relevant, consider changing this

    ImGui::Text("Upgrade points: %d", points);

    ImGui::Text("Hit Points: %d", gladiator->maxHP);
    if (ImGui::Button("Increase HP")) {
        if (points > 0) {
            gladiator->maxHP++;
            points--;
            dialogue = gladiator->D_IncreaseHP();
        }
        else {
            dialogue = gladiator->D_IncreaseFail();
        }
    }

    ImGui::Text("Attack: %d", gladiator->baseAtk);
    if (ImGui::Button("Increase Atk")) {
        if (points > 0) {
            gladiator->baseAtk++;
            points--;
            dialogue = gladiator->D_IncreaseAtk();
        }
        else {
            dialogue = gladiator->D_IncreaseFail();
        }
    }

    ImGui::Text("Defense: %d", gladiator->baseDef);
    if (ImGui::Button("Increase Def")) {
        if (points > 0) {
            gladiator->baseDef++;
            points--;
            dialogue = gladiator->D_IncreaseDef();
        }
        else {
            dialogue = gladiator->D_IncreaseFail();
        }
    }

    ImGui::Text("Accuracy: %d", gladiator->baseAcc);
    if (ImGui::Button("Increase Acc")) {
        if (points > 0) {
            gladiator->baseAcc++;
            points--;
            dialogue = gladiator->D_IncreaseAcc();
        }
        else {
            dialogue = gladiator->D_IncreaseFail();
        }
    }

    ImGui::Text("Evade: %d", gladiator->baseEv);
    if (ImGui::Button("Increase Ev")) {
        if (points > 0) {
            gladiator->baseEv++;
            points--;
            dialogue = gladiator->D_IncreaseEv();
        }
        else {
            dialogue = gladiator->D_IncreaseFail();
        }
    }

    ImGui::Text("Support: %d", gladiator->baseSup);
    if (ImGui::Button("Increase Sup")) {
        if (points > 0) {
            gladiator->baseSup++;
            points--;
            dialogue = gladiator->D_IncreaseSup();
        }
        else {
            dialogue = gladiator->D_IncreaseFail();
        }
    }


    ImGui::Text("%s %s Says: %s", gladiator->firstname.c_str(), gladiator->lastname.c_str(), dialogue.c_str());

    ImGui::End();



   //All Dear ImGui specific state and drawing commands should be updated within this method.
   //The render simply uses what is created here and draws that onto the WOGUI Overlay.
   /*static int counter = 0; //in the real world, get rid of this static non-sense and just make the variables members of this class.
   static float f = 0;
   static bool show_demo_window = true;
   static bool show_another_window = false;
   static ImVec4 clear_color = ImVec4( 0.45f, 0.55f, 0.60f, 0 );

   ImGui::ShowDemoWindow( &show_demo_window ); //This creates that big, huge, elaborate example to see all of ImGui's neato features.

   ImGui::Begin( "Hello, world!" );                          // Create a window called "Hello, world!" and append into it.

   ImGui::Text( "This is some useful text." );               // Display some text (you can use a format strings too)
   ImGui::Checkbox( "Demo Window", &show_demo_window );      // Edit bools storing our window open/close state
   ImGui::Checkbox( "Another Window", &show_another_window );

   ImGui::SliderFloat( "float", &f, 0.0f, 1.0f );            // Edit 1 float using a slider from 0.0f to 1.0f
   ImGui::ColorEdit3( "clear color", (float*)&clear_color ); // Edit 3 floats representing a color

   if( ImGui::Button( "Select a directory!" ) )
      this->fileDialog_show_SelectDirectory( "Select Directory" ); //The window title is a key, that must match fileDialog_has/get...( title );
   if( this->fileDialog_has_selected_path( "Select Directory" ) ){
      this->selected_path = *this->fileDialog_get_selected_path( "Select Directory" ); //can only get one time, this clears the dialog's state!
      this->origin_fileDialog = "Select Directory: ";
   }

   if( ImGui::Button( "Open a file!" ) )
      this->fileDialog_show_Open( "Choose File##MyUniqueLabel_Open");
   if( this->fileDialog_has_selected_path( "Choose File##MyUniqueLabel_Open" ) ) {
      this->selected_path = *this->fileDialog_get_selected_path( "Choose File##MyUniqueLabel_Open" ); //can only get one time, this clears the dialog's state!
      this->origin_fileDialog = "Choose File##MyUniqueLabel_Open: ";
   }

   if( ImGui::Button( "Save a file!" ) )
      this->fileDialog_show_Save( "Choose File###labelSave");
   if( this->fileDialog_has_selected_path( "Choose File###labelSave" ) ) {
      this->selected_path = *this->fileDialog_get_selected_path( "Choose File###labelSave" ); //can only get one time, this clears the dialog's state!
      this->origin_fileDialog = "Choose File###labelSave: ";
   }

   //This prints the selected path and it is prepended with which file dialog title was used
   ImGui::Text( "Selected Path is %s: '%s'", this->origin_fileDialog.c_str(), this->selected_path.string().c_str() );

   if( ImGui::Button( "Button" ) )                            // Buttons return true when clicked (most widgets return true when edited/activated)
      counter++;
   ImGui::SameLine();
   ImGui::Text( "counter = %d", counter );

   //Just an example to show how a Texture from the AftrBurner engine can be drawn.
   this->drawImGui_Texture( ManagerTexture::getDefaultTexture() );

   ImGui::Text( "Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate );
   ImGui::End();

   this->fileDialog_update_after_ImGui_end_is_called(); //If you use any this->fileDialog_* methods, your drawImGui_for_this_frame() *must*
                                       //call this method *AFTER* you call to ImGui::End() or the FileDialog will not work as expected.
    */
   }









//#endif