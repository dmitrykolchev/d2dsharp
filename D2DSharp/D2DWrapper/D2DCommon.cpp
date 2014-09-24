#include "Stdafx.h"
#include "D2DCommon.h"
#include "XMath.h"

namespace Managed {
	namespace Graphics {
		namespace Direct2D {
			Vector4 Matrix4x4::operator*(Matrix4x4 a, Vector4 v)
			{
				Vector4 result = Vector4(
					a.M11 * v.X + a.M12 * v.Y + a.M13 * v.Z + a.M14 * v.W,
					a.M21 * v.X + a.M22 * v.Y + a.M23 * v.Z + a.M24 * v.W,
					a.M31 * v.X + a.M32 * v.Y + a.M33 * v.Z + a.M34 * v.W,
					a.M41 * v.X + a.M42 * v.Y + a.M43 * v.Z + a.M44 * v.W);
				return result;
			}

			Vector4 Matrix4x4::operator*(Vector4 v, Matrix4x4 a)
			{
				Vector4 result = Vector4(
					a.M11 * v.X + a.M21 * v.Y + a.M31 * v.Z + a.M41 * v.W,
					a.M12 * v.X + a.M22 * v.Y + a.M32 * v.Z + a.M42 * v.W,
					a.M13 * v.X + a.M23 * v.Y + a.M33 * v.Z + a.M43 * v.W,
					a.M14 * v.X + a.M24 * v.Y + a.M34 * v.Z + a.M44 * v.W);
				return result;
			}
		}
	}
}