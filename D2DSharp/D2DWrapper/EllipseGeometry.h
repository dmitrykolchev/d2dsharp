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

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	public ref class EllipseGeometry: Geometry
	{
	internal:
		EllipseGeometry(ID2D1EllipseGeometry *native): Geometry(native)
		{
		}
	public:
		property DykBits::Graphics::Direct2D::Ellipse Ellipse
		{
			DykBits::Graphics::Direct2D::Ellipse get()
			{
				DykBits::Graphics::Direct2D::Ellipse ellipse;
				GetNative()->GetEllipse((D2D1_ELLIPSE *)&ellipse);
				return ellipse;
			}
		}
	private:
		ID2D1EllipseGeometry *GetNative()
		{
			return (ID2D1EllipseGeometry *)Geometry::GetNative();
		}
	};
}}}