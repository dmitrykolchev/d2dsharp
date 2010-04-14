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
	public ref class TransformedGeometry: Geometry
	{
	internal:
		TransformedGeometry(ID2D1TransformedGeometry *native): Geometry(native)
		{
		}
	public:
		property Geometry^ SourceGeometry
		{
			Geometry^ get()
			{
				ID2D1Geometry *geometry;
				GetNative()->GetSourceGeometry(&geometry);
				return gcnew Geometry(geometry);
			}
		}

		property Matrix3x2 Transform
		{
			Matrix3x2 get()
			{
				Matrix3x2 transform;
				GetNative()->GetTransform((D2D1_MATRIX_3X2_F *)&transform);
				return transform;
			}
		}

	private:
		ID2D1TransformedGeometry *GetNative()
		{
			return (ID2D1TransformedGeometry *)Geometry::GetNative();
		}
	};
}}}