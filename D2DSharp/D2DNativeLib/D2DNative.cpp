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
