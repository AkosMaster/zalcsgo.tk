#include "SDK.h"
#include "Panels.h"
#include "CDrawManager.h"
#include "Netvars.h"
#include "Client.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>


using namespace std;
int bE = 0;
CScreenSize gScreenSize;

int bone = 6;


//===================================================================================
void __fastcall Hooked_PaintTraverse( PVOID pPanels, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce )
{
	
	

	try
	{
		VMTManager& hook = VMTManager::GetHook(pPanels); //Get a pointer to the instance of your VMTManager with the function GetHook.
		hook.GetMethod<void(__thiscall*)(PVOID, unsigned int, bool, bool)>(gOffsets.iPaintTraverseOffset)(pPanels, vguiPanel, forceRepaint, allowForce); //Call the original.

		static unsigned int vguiMatSystemTopPanel;

		if (vguiMatSystemTopPanel == NULL)
		{
			const char* szName = gInts.Panels->GetName(vguiPanel);
			if( szName[0] == 'M' && szName[3] == 'S' ) //Look for MatSystemTopPanel without using slow operations like strcmp or strstr.
			{
				vguiMatSystemTopPanel = vguiPanel;
				Intro();
			}
		}
		
		if ( vguiMatSystemTopPanel == vguiPanel ) //If we're on MatSystemTopPanel, call our drawing code.
		{

			//gDrawManager.DrawString(10, 10, COLORCODE(244, 66, 66, 200), "www.zalcsgo.ml");
			if( gInts.Engine->IsDrawingLoadingImage() || !gInts.Engine->IsInGame( ) || !gInts.Engine->IsConnected() || gInts.Engine->Con_IsVisible( ) || ( ( GetAsyncKeyState(VK_F12) || gInts.Engine->IsTakingScreenshot( ) ) ) )
			{
				return; //We don't want to draw at the menu.
			}
			gDrawManager.DrawString(10, 10, COLORCODE(255, 0, 0, 255), "zalcheats.ml");

			

			CBaseEntity* MeP = gInts.EntList->GetClientEntity(gInts.Engine->GetLocalPlayer());
			
			if (*(byte*)(MeP + pVars.m_lifeState) != LIFE_ALIVE) {
				bE = 0;
				return;
				
			}

			


			if (false) {
				gDrawManager.DrawRect(0, 0, gScreenSize.iScreenWidth / 6, gScreenSize.iScreenHeight / 4, COLORCODE(0, 0, 0, 204));
				gDrawManager.DrawRect(0, 0, gScreenSize.iScreenWidth / 4, 10, COLORCODE(0, 0, 0, 255));
				gDrawManager.DrawString(0, 0, COLORCODE(255, 0, 0, 255), "zalcsgo.ml");

				gDrawManager.DrawString(0, 10, COLORCODE(255, 0, 0, 255), "Silent Aimbot");
				gDrawManager.DrawString(0, 20, COLORCODE(255, 0, 0, 255), "Visuals");
			}
			


			//This section will be called when the player is not at the menu game and can see the screen or not taking a screenshot.
			 //Remove this if you want.
			
			//Test ESP code.
			
			int bestE = 0;

			double bestDist = 10000;
			bE = 0;
			for (int i = 1; i < gInts.EntList->GetHighestEntityIndex(); i++) {
				
				bool bestMe = false;
				CBaseEntity *current = GetBaseEntity(i);  //Grab the local player's entity.

				if (current == NULL || current->IsDormant()) //Always check for null pointers.
					continue;

				if (*(byte*)(current + pVars.m_lifeState) != LIFE_ALIVE) {
					continue;
				}

			    

				Vector worldPos, screenPos;
				Vector lower = current->GetAbsOrigin();
				Vector upper(lower.x, lower.y, lower.z + 90);

				Vector bottom, top;

				current->GetWorldSpaceCenter(worldPos);
				int myTeam = *(int*)(gInts.EntList->GetClientEntity(1) + pVars.m_iTeamNumber);
				int teamNum = *(int*)(current + pVars.m_iTeamNumber);
				if ((string)current->GetClientClass()->chName != "CTFPlayer") {
					continue;
				}
					
				
				
				
				
				

				if (gDrawManager.WorldToScreen(lower, bottom) && gDrawManager.WorldToScreen(upper, top)) {

					int size = bottom.y - top.y;
					int w = size / 3;
					int x = bottom.x - (w / 2), y = top.y, h = size;

					int health = *(int*)(current + pVars.m_iHealth);
					
					
					//player_info_t* pinf;
					//gInts.Engine->GetPlayerInfo(i, pinf);

					int xP = gScreenSize.iScreenWidth / 2;
					int yP = gScreenSize.iScreenHeight / 2;
					float aP = top.x;
					float bP = top.y;

					double newDist = sqrt(pow(xP - aP, 2) + pow(yP - bP, 2));
					
					if ( newDist < bestDist && i != gInts.Engine->GetLocalPlayer()) {

						bestDist = newDist;
						bestE = i;
						bestMe = true;
					}
					
					//gDrawManager.DrawString(bottom.x, top.y - size/10, COLORCODE(69, 67, 188,255), pinf->name);

					
					
					gDrawManager.DrawString(x + w + w / 5 + 2, top.y, COLORCODE(255, 255, 255, 255), to_string(health).c_str());
					
					
					
					if (teamNum == 2) {
						gDrawManager.OutlineRect(x, top.y, size / 3, h, COLORCODE(186, 52, 53, 255));
						gDrawManager.DrawRect(x + w, top.y, w / 5, size, COLORCODE(186, 52, 53, 155));
					}
					else if (teamNum == 3) {
						gDrawManager.OutlineRect(x, top.y, size / 3, h, COLORCODE(0, 128, 255, 255));
						gDrawManager.DrawRect(x + w, top.y, w / 5, size, COLORCODE(0, 128, 255, 155));
					}

					
						
					

					//gDrawManager.DrawString(x + w + w / 5 + 2, top.y + size/2, COLORCODE(69, 67, 188, 255), to_string().c_str());

					//bones
					bone = 6;
					
					
					
					
					int classNum = *(int*)(current + pVars.m_Class);
					
						

						string clsTR = to_string(classNum);
						if (clsTR.substr(0, 4) == "1667") {
							clsTR = "Medic";
						}
						if (clsTR.substr(0, 4) == "1920") {
							clsTR = "Pyro";
						}
						if (clsTR.substr(0, 4) == "7958") {
							clsTR = "Demo";
							bone = 16;
						}
						if (clsTR.substr(0, 4) == "2037") {
							clsTR = "Heavy";
						}
						if (clsTR.substr(0, 4) == "1768") {
							clsTR = "Soldier";
						}
						if (clsTR.substr(0, 4) == "1852") {
							clsTR = "Engineer";
							bone = 8;
						}
						if (clsTR.substr(0, 4) == "1953") {
							clsTR = "Scout";
						}
						if (clsTR.substr(0, 4) == "1701") {
							clsTR = "Sniper";
						}
						if (clsTR.substr(0, 4) == "1882") {
							clsTR = "Spy";
						}
						
						Vector headPos;
						Vector ScrnHead;
						Vector HitboxPos;

						if (!current || current->IsDormant())
							continue;
						matrix3x4 matrix[128];
						if (!current->SetupBones(matrix, 128, 0x00000100, gInts.Engine->Time()))
							continue;
						HitboxPos = Vector(matrix[bone][0][3], matrix[bone][1][3], matrix[bone][2][3]);



						gDrawManager.WorldToScreen(HitboxPos, ScrnHead);

						gDrawManager.OutlineRect(ScrnHead.x - 10, ScrnHead.y - 10, w / 5, w / 5, COLORCODE(255, 255, 255, 255));

						gDrawManager.DrawString(x + w/5, top.y - size/20, COLORCODE(255, 255, 255, 255), clsTR.c_str());
			
					
				}
			
			}
			bE = bestE;

			if (bestE == 0) {
				return;
			}

			CBaseEntity *bestP = gInts.EntList->GetClientEntity(bestE);


			//TEST
			if (bestP == NULL || bestP->IsDormant()) //Always check for null pointers.
				return;

			if (*(byte*)(bestP + pVars.m_lifeState) != LIFE_ALIVE) {
				return;
			}



			Vector worldPos, screenPos;
			Vector lower = bestP->GetAbsOrigin();
			Vector upper(lower.x, lower.y, lower.z + 90);

			Vector bottom, top;

			bestP->GetWorldSpaceCenter(worldPos);

			if ((string)bestP->GetClientClass()->chName != "CTFPlayer") {
				return;
			}







			if (gDrawManager.WorldToScreen(lower, bottom) && gDrawManager.WorldToScreen(upper, top)) {

				int size = bottom.y - top.y;
				int w = size / 3;
				int x = bottom.x - (w / 2), y = top.y, h = size;

				int health = *(int*)(bestP + pVars.m_iHealth);
				int teamNum = *(int*)(bestP + pVars.m_iTeamNumber);

				//player_info_t* pinf;
				//gInts.Engine->GetPlayerInfo(i, pinf);

				

				//gDrawManager.DrawString(bottom.x, top.y - size/10, COLORCODE(69, 67, 188,255), pinf->name);



				gDrawManager.DrawString(x + w + w / 5 + 2, top.y, COLORCODE(255, 255, 255, 255), to_string(health).c_str());


				
					gDrawManager.OutlineRect(x, top.y, size / 3, h, COLORCODE(0, 255, 0, 255));
					//gDrawManager.DrawRect(x + w, top.y, w / 5, size, COLORCODE(0, 255, 0, 155));
				
				

			}
			//TEST



		}
	}
	catch(...)
	{
		Log::Fatal("Failed PaintTraverse");
	}
}
//===================================================================================
void Intro( void )
{
	try
	{
		gDrawManager.Initialize(); //Initalize the drawing class.
		pVars.init();
		Log::Msg("Injection Successful"); //If the module got here without crashing, it is good day.
	}
	catch(...)
	{
		Log::Fatal("Failed Intro");
	}
}

double distanceBetweenTwoPoints(double x, double y, double a, double b) {
	return sqrt(pow(x - a, 2) + pow(y - b, 2));
}




