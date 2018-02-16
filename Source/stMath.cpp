#include "stMath.h"

namespace ST
{
	namespace Math
	{
		void SetWorldRotation(BaseObject *obj, const Vector &angle, const ROTATIONORDER &order)
		{
			Matrix mg = obj->GetMg();
			Vector pos = mg.off;
			Matrix mr = HPBToMatrix(angle, order);
			mr.off = pos;
			obj->SetMg(mr);
		}
	}
}