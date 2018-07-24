#include "SDK.h"
#include "Client.h"
#include <windows.h>
#include "Netvars.h"
#include "CDrawManager.h"

extern Vector GetHitboxPosition(int Hitbox, Vector& HitboxPos, CBaseEntity* target)
{
	if (!target || target->IsDormant())
		return Vector();
	matrix3x4 matrix[128];
	if (!(target->SetupBones(matrix, 128, 0x00000100, gInts.Engine->Time())))
		return Vector();
	HitboxPos = Vector(matrix[Hitbox][0][3], matrix[Hitbox][1][3], matrix[Hitbox][2][3]);
	return HitboxPos;
}