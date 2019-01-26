#pragma once
#include "../Hacks/Misc.h"
#include "Autowall.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::min

class Hitbox
{
public:
	Vector points[9];

	bool GetHitbox(CBaseEntity* Player, int HitboxID)
	{
		if (!Player)
			return false;

		matrix3x4 matrix[128];
		if (!Player->SetupBones(matrix, 128, 0x00000100, GetTickCount64()))
			return false;
		const model_t* mod = Player->GetModel();
		if (!mod)
			return false;
		studiohdr_t* hdr = Interfaces.g_pModelInfo->GetStudioModel(mod);
		if (!hdr)
			return false;
		mstudiohitboxset_t* set = hdr->GetHitboxSet(0);
		if (!set)
			return false;
		mstudiobbox_t* hitbox = set->pHitbox(HitboxID);
		if (!hitbox)
			return false;

		Vector points[] = { ((hitbox->bbmin + hitbox->bbmax) * .5f),
			Vector(hitbox->bbmin.x, hitbox->bbmin.y, hitbox->bbmin.z),
			Vector(hitbox->bbmin.x, hitbox->bbmax.y, hitbox->bbmin.z),
			Vector(hitbox->bbmax.x, hitbox->bbmax.y, hitbox->bbmin.z),
			Vector(hitbox->bbmax.x, hitbox->bbmin.y, hitbox->bbmin.z),
			Vector(hitbox->bbmax.x, hitbox->bbmax.y, hitbox->bbmax.z),
			Vector(hitbox->bbmin.x, hitbox->bbmax.y, hitbox->bbmax.z),
			Vector(hitbox->bbmin.x, hitbox->bbmin.y, hitbox->bbmax.z),
			Vector(hitbox->bbmax.x, hitbox->bbmin.y, hitbox->bbmax.z) };

		for (int index = 0; index < 9; ++index)
		{
			float multiplier = 100.f / Vars.Ragebot.Hitscan.PointScale;
			g_Math.VectorTransform2(points[index], matrix[hitbox->bone], this->points[index]);
		}

		return true;
	}

	Vector& GetCenter()
	{
		Vector Aimspot;
		return Aimspot = this->points[0];
	}

	void FixHitbox(CBaseEntity* entity)
	{
		for (int index = 0; index <= 8; ++index)
		{
			trace_t tr;
			Ray_t ray;
			CTraceFilterEntity filter;
			filter.pHit = entity;
			ray.Init(points[index], points[0]);
			Interfaces.pTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);

			points[index] = tr.endpos;
		}
	}

	float GetBestPoint(Vector& aimspot)
	{
		int amount = /*(Settings.GetSetting( Tab_Ragebot, Ragebot_Multibox ) <= 1 ) ? 27 :*/ 9;
		if (amount < 1)
			amount = 1;
		float bestdamage = -1;
		for (int index = 0; index < amount; ++index)
		{
			float damage = Autowall::GetDamage(this->points[index]);
			if (damage > bestdamage)
			{
				aimspot = points[index];
				bestdamage = damage;
			}
		}
		return bestdamage;
	}

	float ScanCenter(Vector& Aimspot)
	{
		Aimspot = this->points[0];
		return this->points[0] == Vector(0, 0, 0) ? -1.f : Autowall::GetDamage(this->points[0]);
	}
};
