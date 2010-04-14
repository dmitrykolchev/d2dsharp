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
#include "stdafx.h"

#include "Geometry.h"
#include "SimplifiedGeometrySink.h"

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	void Geometry::CombineWithGeometry(
			Geometry^ inputGeometry, 
			CombineMode combineMode, 
			Matrix3x2 inputGeometryTransform, 
			FLOAT flatteningTolerance, 
			SimplifiedGeometrySink^ geometrySink)
	{
		HRESULT hr = GetNative()->CombineWithGeometry(
			inputGeometry->GetNative(),
			(D2D1_COMBINE_MODE)combineMode,
			(D2D1_MATRIX_3X2_F *)&inputGeometryTransform,
			flatteningTolerance,
			geometrySink->GetNative());
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}

	GeometryRelation Geometry::CompareWithGeometry(
			Geometry^ inputGeometry,
			Matrix3x2 inputGeometryTransform, 
			FLOAT flatteningTolerance)
	{
		D2D1_GEOMETRY_RELATION relation;
		HRESULT hr = GetNative()->CompareWithGeometry(
			inputGeometry->GetNative(),
			(D2D1_MATRIX_3X2_F *)&inputGeometryTransform,
			flatteningTolerance,
			&relation);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
		return (GeometryRelation)relation;
	}
}}}