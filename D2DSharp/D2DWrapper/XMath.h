#pragma once

#include "../D2DNativeLib/D2DNative.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed {
	namespace DirectXMath {

		[StructLayout(LayoutKind::Sequential)]
		public value struct Vector4
		{
		public:
			FLOAT x;
			FLOAT y;
			FLOAT z;
			FLOAT w;
			Vector4(FLOAT x_, FLOAT y_, FLOAT z_, FLOAT w_) :x(x_), y(y_), z(z_), w(w_)
			{
			}
			Vector4(Managed::Graphics::Direct2D::Color c) : x(c.r), y(c.g), z(c.b), w(c.a)
			{
			}
			static operator Managed::Graphics::Direct2D::Color(Vector4 v)
			{
				return Managed::Graphics::Direct2D::Color::FromARGB(v.w, v.x, v.y, v.z);
			}
		};

		public ref class XMath
		{
		private: 
			XMath(){}
		public:
			static Vector4 ColorRgbToHsl(Vector4 rgb);
			static Vector4 ColorHslToRgb(Vector4 hsl);

			Vector4 ColorRgbToHsv(Vector4 rgb)
			{
				Vector4 result;
				DxColorRgbToHsv((const FLOAT*) &rgb, (FLOAT*) &result);
				return result;
			}

			Vector4 ColorHsvToRgb(Vector4 hsv)
			{
				Vector4 result;
				DxColorHsvToRgb((const FLOAT*) &hsv, (FLOAT*) &result);
				return result;
			}

			Vector4 ColorRgbToXyz(Vector4 rgb)
			{
				Vector4 result;
				DxColorRgbToHsv((const FLOAT*) &rgb, (FLOAT*) &result);
				return result;
			}

			Vector4 ColorXyzToRgb(Vector4 xyz)
			{
				Vector4 result;
				DxColorHsvToRgb((const FLOAT*) &xyz, (FLOAT*) &result);
				return result;
			}
			Vector4 ColorRgbToYuv(Vector4 rgb)
			{
				Vector4 result;
				DxColorRgbToYuv((const FLOAT*) &rgb, (FLOAT*) &result);
				return result;
			}

			Vector4 ColorYuvToRgb(Vector4 yuv)
			{
				Vector4 result;
				DxColorYuvToRgb((const FLOAT*) &yuv, (FLOAT*) &result);
				return result;
			}
		};

	}
}