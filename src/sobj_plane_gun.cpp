#include "main.h"
#include "sobj_plane_gun.h"

void Sobj_PlaneGun::InitFrom(Sobj_PlaneGun* o) {
	plane = o->plane;
	scene = o->scene;
	level = o->level;
	fireCD = o->fireCD;
	bulletDamage = o->bulletDamage;
	fireableFrameNumber = o->fireableFrameNumber;
}
