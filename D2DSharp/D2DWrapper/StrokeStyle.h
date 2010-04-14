/* 
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

#include "D2DCommon.h"
#include "D2DResource.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	public enum class LineCapStyle
	{
		Flat       = 0,
		Square     = 1,
		Round      = 2,
		Triangle   = 3 
	};

	public enum class LineJoin
	{
		Miter            = 0,
		Bevel            = 1,
		Round            = 2,
		MiterOrBevel   	 = 3 
	};

	public enum class DashStyle
	{
		Solid          = 0,
		Dash           = 1,
		Dot            = 2,
		DashDot        = 3,
		DashDotDot     = 4,
		Custom         = 5 
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct StrokeStyleProperties
	{
	private:
		D2D1_CAP_STYLE  _startCap;
  		D2D1_CAP_STYLE  _endCap;
  		D2D1_CAP_STYLE  _dashCap;
  		D2D1_LINE_JOIN  _lineJoin;
  		FLOAT           _miterLimit;
  		D2D1_DASH_STYLE _dashStyle;
  		FLOAT           _dashOffset;
	public:
		StrokeStyleProperties(LineCapStyle startCap, LineCapStyle endCap, LineCapStyle dashCap, LineJoin lineJoin, FLOAT miterLimit, DashStyle dashStyle, FLOAT dashOffset)
		{
			_startCap = (D2D1_CAP_STYLE)startCap;
			_endCap = (D2D1_CAP_STYLE)endCap;
			_dashCap = (D2D1_CAP_STYLE)dashCap;
			_lineJoin = (D2D1_LINE_JOIN)lineJoin;
			_miterLimit = miterLimit;
			_dashStyle = (D2D1_DASH_STYLE)dashStyle;
			_dashOffset = dashOffset;
		}
	};


	public ref class StrokeStyle: D2DResource
	{
	internal:
		StrokeStyle(ID2D1StrokeStyle* native): 
			D2DResource(native)
		{
		}

	internal:
		ID2D1StrokeStyle* GetNative() new
		{
			return (ID2D1StrokeStyle*)D2DResource::GetNative();
		}
	};
}}}