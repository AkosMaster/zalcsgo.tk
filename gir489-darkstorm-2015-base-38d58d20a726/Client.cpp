#include "SDK.h"
#include "Client.h"
#include <windows.h>
#include "Netvars.h"
#include "CDrawManager.h"
using namespace std;
bool lastSht = false;
float backY = 0;
float backX = 0;
bool toggle = false;
//============================================================================================
bool __fastcall Hooked_CreateMove(PVOID ClientMode, int edx, float input_sample_frametime, CUserCmd* pCmd)
{
	//If you want taunt slide, you will need to hook CHLClient::CreateMove and do it there. If you do it here, you'll just shimmy forward.
	VMTManager& hook = VMTManager::GetHook(ClientMode); //Get a pointer to the instance of your VMTManager with the function GetHook.
	bool bReturn = hook.GetMethod<bool(__thiscall*)(PVOID, float, CUserCmd*)>(gOffsets.iCreateMoveOffset)(ClientMode, input_sample_frametime, pCmd); //Call the original.
	try
	{
		CBaseEntity* MeP = gInts.EntList->GetClientEntity(gInts.Engine->GetLocalPlayer());
		CBaseEntity* Pl = gInts.EntList->GetClientEntity(bE);
		if (*(byte*)(MeP + pVars.m_lifeState) != LIFE_ALIVE) {
			bE = 0;
			return true;

		}

		

		if (bE == 0) {
			return true;
		}

		if (GetKeyState(VK_INSERT)) {
			toggle = !toggle;
		}

		if (toggle) {
			*(int*)(MeP + pVars.m_iObserverMode) = 1;
		}
		else
		{
			*(int*)(MeP + pVars.m_iObserverMode) = 0;
		}

		if (lastSht && !(pCmd->buttons & IN_ATTACK)) {
			gInts.Engine->GetViewAngles(pCmd->viewangles);
			lastSht = false;
		}

		if (pCmd->buttons & IN_ATTACK) {
			if (!lastSht) {
				backX = pCmd->viewangles.x;
				backY = pCmd->viewangles.y;
				gInts.Engine->SetViewAngles(pCmd->viewangles);
			}
			lastSht = true;
			CBaseEntity* pBaseEntity = GetBaseEntity(me); //Grab the local player's entity pointer.

			if (pBaseEntity == NULL) //This should never happen, but never say never. 0xC0000005 is no laughing matter.
				return bReturn;
			CBaseEntity* Me = gInts.EntList->GetClientEntity(gInts.Engine->GetLocalPlayer());
			

			if (Pl == NULL || Pl->IsDormant()) //Always check for null pointers.
				return true;

			if (Me == NULL || Me->IsDormant()) //Always check for null pointers.
				return true;

			Vector lower = Me->GetAbsOrigin();
			Vector upper(lower.x, lower.y, lower.z + 90);
			Vector lowerE = Pl->GetAbsOrigin();
			Vector upperE(lowerE.x, lowerE.y, lowerE.z + 50);
			Vector Screen;
			gDrawManager.WorldToScreen(upper, Screen);



			//TEST
			int bone = 6;




			int classNum = *(int*)(Pl + pVars.m_Class);



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

			if (!Pl || Pl->IsDormant())
				return bReturn;
			matrix3x4 matrix[128];
			if (!Pl->SetupBones(matrix, 128, 0x00000100, gInts.Engine->Time()))
				return bReturn;
			HitboxPos = Vector(matrix[bone][0][3], matrix[bone][1][3], matrix[bone][2][3]);

			//2

			bone = 6;




			classNum = *(int*)(Me + pVars.m_Class);



			clsTR = to_string(classNum);
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

			

			if (!Me || Me->IsDormant())
				return bReturn;
			
			if (!Me->SetupBones(matrix, 128, 0x00000100, gInts.Engine->Time()))
				return bReturn;
			Vector HitboxPos2 = Vector(matrix[bone][0][3], matrix[bone][1][3], matrix[bone][2][3]);
			
			//TEST

			upperE = HitboxPos;
			upper = HitboxPos2;

			pCmd->viewangles.y += ((atan2((upperE.y - upper.y), (upperE.x - upper.x)) * 180 / PI) - pCmd->viewangles.y) * 1;
			double distanceB = hypot(hypot(upperE.x - upper.x, upperE.y - upper.y), upperE.z - upper.z);
			pCmd->viewangles.x += (((upper.z - upperE.z) / (distanceB / 57.295779513082)) - pCmd->viewangles.x) * 1;

			

		

			bReturn = false;
		}

		if (GetKeyState(VK_LEFT))
		{
			pCmd->viewangles.y += 90;
			bReturn = false;
		}

		//if (GetKeyState(VK_DOWN))
		//{
		//	pCmd->viewangles.y -= 180;
		//	bReturn = false;
		//}

		//if (GetKeyState(VK_UP))
		//{
		//	pCmd->viewangles.y += 180;
		//	bReturn = false;
		//}

		if (GetKeyState(VK_RIGHT))
		{
			pCmd->viewangles.y -= 90;
			bReturn = false;
		}

		
	}
	catch(...)
	{
		Log::Fatal("Failed Hooked_CreateMove");
	}
	return bReturn; //If bReturn is true, CInput::CreateMove will call CEngine::SetViewAngles(pCommand->viewangles). If you want silent aim, return false, but make sure to call SetViewAngles manually.
}
//============================================================================================


