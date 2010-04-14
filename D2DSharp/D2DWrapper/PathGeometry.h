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
#include "Geometry.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	ref class GeometrySink;

	public ref class PathGeometry: Geometry
	{
	internal:
		PathGeometry(ID2D1PathGeometry *native): 
			Geometry(native)
		{
		}
	public:
		property int FigureCount
		{
			int get()
			{
				UINT32 count;
				HRESULT hr = GetNative()->GetFigureCount(&count);
				if(FAILED(hr))
					Marshal::ThrowExceptionForHR(hr);
				return (int)count;
			}
		}

		property int SegmentCount
		{
			int get()
			{
				UINT32 count;
				HRESULT hr = GetNative()->GetSegmentCount(&count);
				if(FAILED(hr))
					Marshal::ThrowExceptionForHR(hr);
				return (int)count;
			}
		}

		GeometrySink^ Open();
		void Stream(GeometrySink^ geometrySink);

	private:
		ID2D1PathGeometry *GetNative()
		{
			return (ID2D1PathGeometry *)Geometry::GetNative();
		}
	};
}}}