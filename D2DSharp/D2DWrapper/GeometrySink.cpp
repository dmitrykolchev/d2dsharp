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

#include "GeometrySink.h"

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	void GeometrySink::AddArc(ArcSegment arc)
	{
		GetNative()->AddArc((D2D1_ARC_SEGMENT*)&arc);
	}

	void GeometrySink::AddBezier(BezierSegment bezier)
	{
		GetNative()->AddBezier((D2D1_BEZIER_SEGMENT*)&bezier);
	}

	void GeometrySink::AddLine(PointF point)
	{
		GetNative()->AddLine(*(D2D1_POINT_2F*)&point);
	}

	void GeometrySink::AddQuadraticBezier(QuadraticBezierSegment bezier)
	{
		GetNative()->AddQuadraticBezier((D2D1_QUADRATIC_BEZIER_SEGMENT *)&bezier);
	}

	void GeometrySink::AddQuadraticBeziers(array<QuadraticBezierSegment>^ beziers)
	{
		if(beziers == nullptr)
			throw gcnew ArgumentNullException("beziers");
		pin_ptr<QuadraticBezierSegment> p = &beziers[0];
		GetNative()->AddQuadraticBeziers((D2D1_QUADRATIC_BEZIER_SEGMENT *)p, beziers->Length);
	}
}}}