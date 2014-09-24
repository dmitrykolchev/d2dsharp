/*
* D2DNative.cpp
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
#include <Windows.h>
#include <DirectXMath.h>

using namespace DirectX;

void WINAPI DxColorRgbToHsl(const FLOAT* rgb, FLOAT* hsl)
{
	XMStoreFloat4((XMFLOAT4*) hsl, XMColorRGBToHSL(XMLoadFloat4((const XMFLOAT4*) rgb)));
}

void WINAPI DxColorHslToRgb(const FLOAT* hsl, FLOAT* rgb)
{
	XMStoreFloat4((XMFLOAT4*) rgb, XMColorHSLToRGB(XMLoadFloat4((const XMFLOAT4*) hsl)));
}

void WINAPI DxColorRgbToSrgb(const FLOAT* rgb, FLOAT* srgb)
{
	XMStoreFloat4((XMFLOAT4*) srgb, XMColorRGBToHSL(XMLoadFloat4((const XMFLOAT4*) rgb)));
}

void WINAPI DxColorSrgbToRgb(const FLOAT* srgb, FLOAT* rgb)
{
	XMStoreFloat4((XMFLOAT4*) rgb, XMColorHSLToRGB(XMLoadFloat4((const XMFLOAT4*) srgb)));
}

void WINAPI DxColorRgbToHsv(const FLOAT* rgb, FLOAT* hsv)
{
	XMStoreFloat4((XMFLOAT4*) hsv, XMColorRGBToHSV(XMLoadFloat4((const XMFLOAT4*) rgb)));
}

void WINAPI DxColorHsvToRgb(const FLOAT* hsv, FLOAT* rgb)
{
	XMStoreFloat4((XMFLOAT4*) rgb, XMColorHSVToRGB(XMLoadFloat4((const XMFLOAT4*) hsv)));
}

void WINAPI DxColorRgbToXyz(const FLOAT* rgb, FLOAT* xyz)
{
	XMStoreFloat4((XMFLOAT4*) xyz, XMColorRGBToXYZ(XMLoadFloat4((const XMFLOAT4*) rgb)));
}

void WINAPI DxColorXyzToRgb(const FLOAT* xyz, FLOAT* rgb)
{
	XMStoreFloat4((XMFLOAT4*) rgb, XMColorXYZToRGB(XMLoadFloat4((const XMFLOAT4*) xyz)));
}

void WINAPI DxColorRgbToYuv(const FLOAT* rgb, FLOAT* yuv)
{
	XMStoreFloat4((XMFLOAT4*) yuv, XMColorRGBToYUV(XMLoadFloat4((const XMFLOAT4*) rgb)));
}

void WINAPI DxColorYuvToRgb(const FLOAT* yuv, FLOAT* rgb)
{
	XMStoreFloat4((XMFLOAT4*) rgb, XMColorYUVToRGB(XMLoadFloat4((const XMFLOAT4*) yuv)));
}

void WINAPI DxColorAdjustContrast(const FLOAT* src, FLOAT contrast, FLOAT* dst)
{
	XMStoreFloat4((XMFLOAT4*) dst, XMColorAdjustContrast(XMLoadFloat4((const XMFLOAT4*) src), contrast));
}

void WINAPI DxColorAdjustSaturation(const FLOAT* src, FLOAT contrast, FLOAT* dst)
{
	XMStoreFloat4((XMFLOAT4*) dst, XMColorAdjustSaturation(XMLoadFloat4((const XMFLOAT4*) src), contrast));
}

void WINAPI DxColorModulate(const FLOAT* c1, const FLOAT* c2, FLOAT* dst)
{
	XMStoreFloat4((XMFLOAT4*) dst, XMColorModulate(XMLoadFloat4((const XMFLOAT4*) c1), XMLoadFloat4((const XMFLOAT4*) c2)));
}

float WINAPI DxConvertToDegrees(float radians)
{
	return XMConvertToDegrees(radians);
}

float WINAPI DxConvertToRadians(float degrees)
{
	return XMConvertToRadians(degrees);
}

void WINAPI DxVectorAbs(const FLOAT* src, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorAbs(XMLoadFloat4((const XMFLOAT4*) src)));
}
void WINAPI DxVectorNegate(const FLOAT* src, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorNegate(XMLoadFloat4((const XMFLOAT4*) src)));
}
void WINAPI DxVectorAdd(const FLOAT* l, const FLOAT* r, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorAdd(XMLoadFloat4((const XMFLOAT4*) l), XMLoadFloat4((const XMFLOAT4*) r)));
}
void WINAPI DxVectorSubtract(const FLOAT* l, const FLOAT* r, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorSubtract(XMLoadFloat4((const XMFLOAT4*) l), XMLoadFloat4((const XMFLOAT4*) r)));
}
void WINAPI DxVectorAddAngles(const FLOAT* l, const FLOAT* r, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorAddAngles(XMLoadFloat4((const XMFLOAT4*) l), XMLoadFloat4((const XMFLOAT4*) r)));
}
void WINAPI DxVectorSubtractAngles(const FLOAT* l, const FLOAT* r, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorSubtractAngles(XMLoadFloat4((const XMFLOAT4*) l), XMLoadFloat4((const XMFLOAT4*) r)));
}
void WINAPI DxVectorCeiling(const FLOAT* src, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorCeiling(XMLoadFloat4((const XMFLOAT4*) src)));
}
void WINAPI DxVectorFloor(const FLOAT* src, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorFloor(XMLoadFloat4((const XMFLOAT4*) src)));
}
void WINAPI DxVectorClamp(const FLOAT* v, const FLOAT* min, const FLOAT* max, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorClamp(XMLoadFloat4((const XMFLOAT4*) v), XMLoadFloat4((const XMFLOAT4*) min), XMLoadFloat4((const XMFLOAT4*) max)));
}
void WINAPI DxVectorDivide(const FLOAT* l, const FLOAT* r, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorDivide(XMLoadFloat4((const XMFLOAT4*) l), XMLoadFloat4((const XMFLOAT4*) r)));
}
void WINAPI DxVectorMultiply(const FLOAT* l, const FLOAT* r, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorMultiply(XMLoadFloat4((const XMFLOAT4*) l), XMLoadFloat4((const XMFLOAT4*) r)));
}
void WINAPI DxVectorMultiplyAdd(const FLOAT* v1, const FLOAT* v2, const FLOAT* v3, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorMultiplyAdd(XMLoadFloat4((const XMFLOAT4*) v1), XMLoadFloat4((const XMFLOAT4*) v2), XMLoadFloat4((const XMFLOAT4*) v3)));
}
void WINAPI DxVectorNegativeMultiplySubtract(const FLOAT* v1, const FLOAT* v2, const FLOAT* v3, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorNegativeMultiplySubtract(XMLoadFloat4((const XMFLOAT4*) v1), XMLoadFloat4((const XMFLOAT4*) v2), XMLoadFloat4((const XMFLOAT4*) v3)));
}
void WINAPI DxVectorMod(const FLOAT* l, const FLOAT* r, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorMod(XMLoadFloat4((const XMFLOAT4*) l), XMLoadFloat4((const XMFLOAT4*) r)));
}
void WINAPI DxVectorMax(const FLOAT* l, const FLOAT* r, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorMax(XMLoadFloat4((const XMFLOAT4*) l), XMLoadFloat4((const XMFLOAT4*) r)));
}
void WINAPI DxVectorMin(const FLOAT* l, const FLOAT* r, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorMin(XMLoadFloat4((const XMFLOAT4*) l), XMLoadFloat4((const XMFLOAT4*) r)));
}
void WINAPI DxVectorModAngles(const FLOAT* src, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorModAngles(XMLoadFloat4((const XMFLOAT4*) src)));
}
void WINAPI DxVectorPow(const FLOAT* l, const FLOAT* r, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorPow(XMLoadFloat4((const XMFLOAT4*) l), XMLoadFloat4((const XMFLOAT4*) r)));
}
void WINAPI DxVectorReciprocal(const FLOAT* src, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorReciprocal(XMLoadFloat4((const XMFLOAT4*) src)));
}
void WINAPI DxVectorReciprocalEst(const FLOAT* src, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorReciprocalEst(XMLoadFloat4((const XMFLOAT4*) src)));
}
void WINAPI DxVectorReciprocalSqrt(const FLOAT* src, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorReciprocalSqrt(XMLoadFloat4((const XMFLOAT4*) src)));
}
void WINAPI DxVectorReciprocalSqrtEst(const FLOAT* src, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorReciprocalSqrtEst(XMLoadFloat4((const XMFLOAT4*) src)));
}
void WINAPI DxVectorRound(const FLOAT* src, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorRound(XMLoadFloat4((const XMFLOAT4*) src)));
}
void WINAPI DxVectorTruncate(const FLOAT* src, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorTruncate(XMLoadFloat4((const XMFLOAT4*) src)));
}
void WINAPI DxVectorSaturate(const FLOAT* src, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorSaturate(XMLoadFloat4((const XMFLOAT4*) src)));
}
void WINAPI DxVectorScale(const FLOAT* src, FLOAT scale, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorScale(XMLoadFloat4((const XMFLOAT4*) src), scale));
}
void WINAPI DxVectorSqrt(const FLOAT* src, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorSqrt(XMLoadFloat4((const XMFLOAT4*) src)));
}
void WINAPI DxVectorSqrtEst(const FLOAT* src, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorSqrtEst(XMLoadFloat4((const XMFLOAT4*) src)));
}

void WINAPI DxVectorLerp(const FLOAT* v0, const FLOAT* v1, float t, FLOAT* result)
{
	XMStoreFloat4((XMFLOAT4*) result, XMVectorLerp(XMLoadFloat4((const XMFLOAT4*) v0), XMLoadFloat4((const XMFLOAT4*) v1), t));
}