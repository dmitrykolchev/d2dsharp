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
#include "SimplifiedGeometrySink.h"

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	public enum class SweepDirection 
	{
  		CounterClockwise   = 0,
  		Clockwise          = 1 
	};

	public enum class ArcSize 
	{
  		Small   = 0,
  		Large   = 1 
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct ArcSegment 
	{
	private:
  		PointF        _point;
  		SizeF         _size;
  		float         _rotationAngle;
  		D2D1_SWEEP_DIRECTION _sweepDirection;
  		D2D1_ARC_SIZE        _arcSize;
	public:
		ArcSegment(PointF point, SizeF size, float rotationAngle, SweepDirection sweepDirection, ArcSize arcSize)
		{
			_point = point;
			_size = size;
			_rotationAngle = rotationAngle;
			_sweepDirection = (D2D1_SWEEP_DIRECTION)sweepDirection;
			_arcSize = (D2D1_ARC_SIZE)arcSize;
		}
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct QuadraticBezierSegment 
	{
	private:
		PointF _point1;
		PointF _point2;
	public:
		QuadraticBezierSegment(PointF point1, PointF point2)
		{
			_point1 = point1;
			_point2 = point2;
		}
	};


	public ref class GeometrySink: SimplifiedGeometrySink
	{
	internal:
		GeometrySink(ID2D1GeometrySink *native): 
			SimplifiedGeometrySink(native)
		{
		}
	public:
		void AddArc(ArcSegment arc);
		void AddBezier(BezierSegment bezier);
		void AddLine(PointF point);
		void AddQuadraticBezier(QuadraticBezierSegment bezier);
		void AddQuadraticBeziers(array<QuadraticBezierSegment>^ beziers);
	internal:
		ID2D1GeometrySink *GetNative() new
		{
			return (ID2D1GeometrySink *)SimplifiedGeometrySink::GetNative();
		}
	};
}}}