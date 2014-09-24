/*
* XMath.h
*
* Authors:
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*
* Copyright (C) 2010 Dmitry Kolchev
*
* This sourcecode is licenced under The GNU Lesser General Public License
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
* NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
* USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once

#include "../D2DNativeLib/D2DNative.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed {
	namespace Graphics {
		[StructLayout(LayoutKind::Sequential)]
		public value struct Vector3
		{
		private:
			FLOAT x;
			FLOAT y;
			FLOAT z;
		public:
			Vector3(FLOAT _x, FLOAT _y, FLOAT _z)
			{
				x = _x; y = _y; z = _z;
			}
			property FLOAT X { FLOAT get(){ return x; }}
			property FLOAT Y { FLOAT get(){ return y; }}
			property FLOAT Z { FLOAT get(){ return z; }}
		};

		[StructLayout(LayoutKind::Sequential)]
		public value struct Vector4
		{
		private:
			FLOAT x;
			FLOAT y;
			FLOAT z;
			FLOAT w;
		public:
			Vector4(FLOAT x_, FLOAT y_, FLOAT z_, FLOAT w_) :x(x_), y(y_), z(z_), w(w_)
			{
			}
			Vector4(Managed::Graphics::Direct2D::Color c) : x(c.r), y(c.g), z(c.b), w(c.a)
			{
			}
			static operator Managed::Graphics::Direct2D::Color(Vector4 v)
			{
				return Managed::Graphics::Direct2D::Color::FromRGB(v.x, v.y, v.z, v.w);
			}
			property FLOAT X { FLOAT get(){ return x; }}
			property FLOAT Y { FLOAT get(){ return y; }}
			property FLOAT Z { FLOAT get(){ return z; }}
			property FLOAT W { FLOAT get(){ return w; }}
			
			//void WINAPI DxVectorAbs(const FLOAT* src, FLOAT* result);
			static Vector4 Abs(Vector4 v)
			{
				Vector4 result;
				DxVectorAbs((const FLOAT*) &v, (FLOAT*) &result);
				return result;
			}
			//void WINAPI DxVectorNegate(const FLOAT* src, FLOAT* result);
			static Vector4 Negate(Vector4 v)
			{
				Vector4 result;
				DxVectorNegate((const FLOAT*) &v, (FLOAT*) &result);
				return result;
			}
			//void WINAPI DxVectorAdd(const FLOAT* l, const FLOAT* r, FLOAT* result);
			static Vector4 Add(Vector4 v1, Vector4 v2)
			{
				Vector4 result;
				DxVectorAdd((const FLOAT*) &v1, (const FLOAT*) &v2, (FLOAT*) &result);
				return result;
			}
			//void WINAPI DxVectorSubtract(const FLOAT* l, const FLOAT* r, FLOAT* result);
			//void WINAPI DxVectorAddAngles(const FLOAT* l, const FLOAT* r, FLOAT* result);
			//void WINAPI DxVectorSubtractAngles(const FLOAT* l, const FLOAT* r, FLOAT* result);
			//void WINAPI DxVectorCeiling(const FLOAT* src, FLOAT* result);
			//void WINAPI DxVectorFloor(const FLOAT* src, FLOAT* result);
			//void WINAPI DxVectorClamp(const FLOAT* v, const FLOAT* min, const FLOAT* max, FLOAT* result);
			//void WINAPI DxVectorDivide(const FLOAT* l, const FLOAT* r, FLOAT* result);
			//void WINAPI DxVectorMultiply(const FLOAT* l, const FLOAT* r, FLOAT* result);
			//void WINAPI DxVectorMultiplyAdd(const FLOAT* v1, const FLOAT* v2, const FLOAT* v3, FLOAT* result);
			//void WINAPI DxVectorNegativeMultiplySubtract(const FLOAT* v1, const FLOAT* v2, const FLOAT* v3, FLOAT* result);
			//void WINAPI DxVectorMod(const FLOAT* l, const FLOAT* r, FLOAT* result);
			//void WINAPI DxVectorMax(const FLOAT* l, const FLOAT* r, FLOAT* result);
			//void WINAPI DxVectorMin(const FLOAT* l, const FLOAT* r, FLOAT* result);
			//void WINAPI DxVectorModAngles(const FLOAT* src, FLOAT* result);

			//void WINAPI DxVectorPow(const FLOAT* l, const FLOAT* r, FLOAT* result);
			//void WINAPI DxVectorReciprocal(const FLOAT* src, FLOAT* result);
			//void WINAPI DxVectorReciprocalEst(const FLOAT* src, FLOAT* result);
			//void WINAPI DxVectorReciprocalSqrt(const FLOAT* src, FLOAT* result);
			//void WINAPI DxVectorReciprocalSqrtEst(const FLOAT* src, FLOAT* result);

			//void WINAPI DxVectorRound(const FLOAT* src, FLOAT* result);
			//void WINAPI DxVectorTruncate(const FLOAT* src, FLOAT* result);
			//void WINAPI DxVectorSaturate(const FLOAT* src, FLOAT* result);
			//void WINAPI DxVectorScale(const FLOAT* src, FLOAT contrast, FLOAT* dst);
			//void WINAPI DxVectorSqrt(const FLOAT* src, FLOAT* result);
			//void WINAPI DxVectorSqrtEst(const FLOAT* src, FLOAT* result);

			//void WINAPI DxVectorLerp(const FLOAT* v0, const FLOAT* v1, float t, FLOAT* result);
			static Vector4 Lerp(Vector4 v0, Vector4 v1, float t)
			{
				Vector4 result;
				DxVectorLerp((const FLOAT*) &v0, (const FLOAT*) &v1, t, (FLOAT*) &result);
				return result;
			}
		};

		public ref class XMath
		{
		private:
			XMath(){}
		public:
			static Vector4 ColorRgbToHsl(Vector4 rgb);
			static Vector4 ColorHslToRgb(Vector4 hsl);

			static Vector4 ColorRgbToSrgb(Vector4 rgb)
			{
				Vector4 result;
				DxColorRgbToSrgb((const FLOAT*) &rgb, (FLOAT*) &result);
				return result;
			}
			static Vector4 ColorSrgbToRgb(Vector4 srgb)
			{
				Vector4 result;
				DxColorSrgbToRgb((const FLOAT*) &srgb, (FLOAT*) &result);
				return result;
			}

			static Vector4 ColorRgbToHsv(Vector4 rgb)
			{
				Vector4 result;
				DxColorRgbToHsv((const FLOAT*) &rgb, (FLOAT*) &result);
				return result;
			}
			static Vector4 ColorHsvToRgb(Vector4 hsv)
			{
				Vector4 result;
				DxColorHsvToRgb((const FLOAT*) &hsv, (FLOAT*) &result);
				return result;
			}

			static Vector4 ColorRgbToXyz(Vector4 rgb)
			{
				Vector4 result;
				DxColorRgbToHsv((const FLOAT*) &rgb, (FLOAT*) &result);
				return result;
			}
			static Vector4 ColorXyzToRgb(Vector4 xyz)
			{
				Vector4 result;
				DxColorHsvToRgb((const FLOAT*) &xyz, (FLOAT*) &result);
				return result;
			}

			static Vector4 ColorRgbToYuv(Vector4 rgb)
			{
				Vector4 result;
				DxColorRgbToYuv((const FLOAT*) &rgb, (FLOAT*) &result);
				return result;
			}
			static Vector4 ColorYuvToRgb(Vector4 yuv)
			{
				Vector4 result;
				DxColorYuvToRgb((const FLOAT*) &yuv, (FLOAT*) &result);
				return result;
			}
			static Vector4 ColorAdjustContrast(Vector4 src, FLOAT contrast)
			{
				Vector4 result;
				DxColorAdjustContrast((const FLOAT*) &src, contrast, (FLOAT*) &result);
				return result;
			}
			static Vector4 ColorAdjustSaturation(Vector4 src, FLOAT saturation)
			{
				Vector4 result;
				DxColorAdjustSaturation((const FLOAT*) &src, saturation, (FLOAT*) &result);
				return result;
			}
			static Vector4 ColorModulate(Vector4 c1, Vector4 c2)
			{
				Vector4 result;
				DxColorModulate((const FLOAT*) &c1, (const FLOAT*) &c2, (FLOAT*) &result);
				return result;
			}

			static FLOAT ConvertToDegrees(FLOAT radians)
			{
				return DxConvertToDegrees(radians);
			}

			static FLOAT ConvertToRadians(FLOAT degrees)
			{
				return DxConvertToRadians(degrees);
			}
		};

	}
}