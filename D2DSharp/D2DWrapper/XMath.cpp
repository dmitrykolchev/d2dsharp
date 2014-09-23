#include "Stdafx.h"
#include "XMath.h"

#pragma comment(lib, "D2DNativeLib.lib")

namespace Managed {
	namespace DirectXMath {
		Vector4 XMath::ColorRgbToHsl(Vector4 rgb)
		{
			Vector4 result;
			DxColorRgbToHsl((const FLOAT*) &rgb, (FLOAT*)&result);
			return result;
		}

		Vector4 XMath::ColorHslToRgb(Vector4 hsl)
		{
			Vector4 result;
			DxColorHslToRgb((const FLOAT*) &hsl, (FLOAT*) &result);
			return result;
		}

	}
}