#include "Input.h"
#include "Output.h"


Input::Input(window* pW) 
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_RECT: return DRAW_RECT; break;
			case ITM_Tria: return DRAW_TRI; break;
			case ITM_Line: return DRAW_LINE; break;
			case ITM_Elipse: return DRAW_ELLIPSE; break;
			case ITM_Rhombus: return DRAW_RHOMBUS; break;
			case ITM_Fill: return  CHNG_FILL_CLR; break;
			case ITM_Outline: return  CHNG_DRAW_CLR; break;
			case  ITM_Black: return A_Black; break;
			case  ITM_White: return A_White; break;
			case  ITM_Red: return A_Red; break;
			case  ITM_Green: return A_Green; break;
			case  ITM_Blue: return A_Blue; break;
			case ITM_Cut: return CUT; break;
			case ITM_Copy: return COPY; break;
			case ITM_Paste: return PASTE; break;
			case ITM_Del: return DEL; break;
			case ITM_Select: return SELECT; break;
			case ITM_SaveByType: return SAVE_BY_TYPE; break;
			case ITM_Save: return SAVE; break;
			case ITM_Switch:return TO_PLAY; break;
			case ITM_EXIT: return EXIT;	break;
			
			default: return EMPTY; break;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
		return TO_PLAY;	//just for now. This should be updated
	}	

}
/////////////////////////////////
	
Input::~Input()
{
}
