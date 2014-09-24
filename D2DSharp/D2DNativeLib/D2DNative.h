/*
* D2DNative.h
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

	void WINAPI DxColorRgbToSrgb(const FLOAT* rgb, FLOAT* srgb);
	void WINAPI DxColorSrgbToRgb(const FLOAT* srgb, FLOAT* rgb);

	void WINAPI DxColorRgbToHsl(const FLOAT* rgb, FLOAT* hsl);
	void WINAPI DxColorHslToRgb(const FLOAT* hsl, FLOAT* rgb);

	void WINAPI DxColorRgbToHsv(const FLOAT* rgb, FLOAT* hsv);
	void WINAPI DxColorHsvToRgb(const FLOAT* hsv, FLOAT* rgb);

	void WINAPI DxColorRgbToXyz(const FLOAT* rgb, FLOAT* xyz);
	void WINAPI DxColorXyzToRgb(const FLOAT* xyz, FLOAT* rgb);

	void WINAPI DxColorRgbToYuv(const FLOAT* rgb, FLOAT* yuv);
	void WINAPI DxColorYuvToRgb(const FLOAT* yuv, FLOAT* rgb);

	void WINAPI DxColorAdjustContrast(const FLOAT* src, FLOAT contrast, FLOAT* dst);
	void WINAPI DxColorAdjustSaturation(const FLOAT* src, FLOAT saturation, FLOAT* dst);

	void WINAPI DxColorModulate(const FLOAT* c1, const FLOAT* c2, FLOAT* dst);

	float WINAPI DxConvertToDegrees(float radians);
	float WINAPI DxConvertToRadians(float degrees);

	void WINAPI DxVectorAbs(const FLOAT* src, FLOAT* result);
	void WINAPI DxVectorNegate(const FLOAT* src, FLOAT* result);
	void WINAPI DxVectorAdd(const FLOAT* l, const FLOAT* r, FLOAT* result);
	void WINAPI DxVectorSubtract(const FLOAT* l, const FLOAT* r, FLOAT* result);
	void WINAPI DxVectorAddAngles(const FLOAT* l, const FLOAT* r, FLOAT* result);
	void WINAPI DxVectorSubtractAngles(const FLOAT* l, const FLOAT* r, FLOAT* result);
	void WINAPI DxVectorCeiling(const FLOAT* src, FLOAT* result);
	void WINAPI DxVectorFloor(const FLOAT* src, FLOAT* result);
	void WINAPI DxVectorClamp(const FLOAT* v, const FLOAT* min, const FLOAT* max, FLOAT* result);
	void WINAPI DxVectorDivide(const FLOAT* l, const FLOAT* r, FLOAT* result); 
	void WINAPI DxVectorMultiply(const FLOAT* l, const FLOAT* r, FLOAT* result);
	void WINAPI DxVectorMultiplyAdd(const FLOAT* v1, const FLOAT* v2, const FLOAT* v3, FLOAT* result);
	void WINAPI DxVectorNegativeMultiplySubtract(const FLOAT* v1, const FLOAT* v2, const FLOAT* v3, FLOAT* result);
	void WINAPI DxVectorMod(const FLOAT* l, const FLOAT* r, FLOAT* result);
	void WINAPI DxVectorMax(const FLOAT* l, const FLOAT* r, FLOAT* result);
	void WINAPI DxVectorMin(const FLOAT* l, const FLOAT* r, FLOAT* result);
	void WINAPI DxVectorModAngles(const FLOAT* src, FLOAT* result);

	void WINAPI DxVectorPow(const FLOAT* l, const FLOAT* r, FLOAT* result);
	void WINAPI DxVectorReciprocal(const FLOAT* src, FLOAT* result);
	void WINAPI DxVectorReciprocalEst(const FLOAT* src, FLOAT* result);
	void WINAPI DxVectorReciprocalSqrt(const FLOAT* src, FLOAT* result);
	void WINAPI DxVectorReciprocalSqrtEst(const FLOAT* src, FLOAT* result);

	void WINAPI DxVectorRound(const FLOAT* src, FLOAT* result);
	void WINAPI DxVectorTruncate(const FLOAT* src, FLOAT* result);
	void WINAPI DxVectorSaturate(const FLOAT* src, FLOAT* result);
	void WINAPI DxVectorScale(const FLOAT* src, FLOAT contrast, FLOAT* dst);
	void WINAPI DxVectorSqrt(const FLOAT* src, FLOAT* result);
	void WINAPI DxVectorSqrtEst(const FLOAT* src, FLOAT* result);

	void WINAPI DxVectorLerp(const FLOAT* v0, const FLOAT* v1, float t, FLOAT* result);