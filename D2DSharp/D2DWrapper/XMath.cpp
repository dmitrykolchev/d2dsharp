/*
* XMath.cpp
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