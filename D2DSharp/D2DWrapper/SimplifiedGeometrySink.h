/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "ComWrapper.h"
#include "D2DCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Managed::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Direct2D 
{
	[StructLayout(LayoutKind::Sequential)]
	public value struct BezierSegment
	{
	private:
		PointF _point1;
		PointF _point2;
		PointF _point3;
	public:
		BezierSegment(PointF point1, PointF point2, PointF point3)
		{
			_point1 = point1;
			_point2 = point2;
			_point3 = point3;
		}
		property PointF Point1
		{
			PointF get() { return _point1; }
		}

		property PointF Point2
		{
			PointF get() { return _point2; }
		}

		property PointF Point3
		{
			PointF get() { return _point3; }
		}
	};

	public enum class FigureBegin 
	{
		Filled   = 0,
		Hollow   = 1 
	};

	public enum class FigureEnd 
	{
		Open     = 0,
		Closed   = 1 
	};

	public enum class PathSegment 
	{
		None                    = 0x00000000,
		ForceUnstroked         	= 0x00000001,
		ForceRoundLineJoin   	= 0x00000002 
	};

	public interface class ICustomSimplifiedGeometrySink
	{
	public:
		void AddBeziers(array<BezierSegment>^ beziers) = 0;
		void AddLines(array<PointF>^ points) = 0;
		void BeginFigure(PointF startPoint, FigureBegin figureBegin) = 0;
		void Close() = 0;
		void EndFigure(FigureEnd figureEnd) = 0;
		void SetFillMode(FillMode fillMode) = 0;
		void SetSegmentFlags(PathSegment vertexFlags) = 0;
	};

	public ref class SimplifiedGeometrySink: ComWrapper
	{
	internal:
		SimplifiedGeometrySink(ID2D1SimplifiedGeometrySink *native):
			ComWrapper(native)
		{
		}
		ID2D1SimplifiedGeometrySink* GetNative() new
		{
			return (ID2D1SimplifiedGeometrySink*)ComWrapper::GetNative();
		}
	public:
		void AddBeziers(array<BezierSegment>^ beziers)
		{
			if(beziers == nullptr)
				throw gcnew ArgumentNullException("beziers");
			pin_ptr<BezierSegment> p = &beziers[0];
			GetNative()->AddBeziers((D2D1_BEZIER_SEGMENT *)p, beziers->Length);
		}

		void AddLines(array<PointF>^ points)
		{
			if(points == nullptr)
				throw gcnew ArgumentNullException("points");
			pin_ptr<PointF> p = &points[0];
			GetNative()->AddLines((D2D1_POINT_2F *)p, points->Length);
		}

		void BeginFigure(PointF startPoint, FigureBegin figureBegin)
		{
			GetNative()->BeginFigure(*(D2D1_POINT_2F*)&startPoint, (D2D1_FIGURE_BEGIN)figureBegin);
		}

		void Close()
		{
			GetNative()->Close();
		}

		void EndFigure(FigureEnd figureEnd)
		{
			GetNative()->EndFigure((D2D1_FIGURE_END)figureEnd);
		}

		void SetFillMode(FillMode fillMode)
		{
			GetNative()->SetFillMode((D2D1_FILL_MODE)fillMode);
		}

		void SetSegmentFlags(PathSegment vertexFlags)
		{
			GetNative()->SetSegmentFlags((D2D1_PATH_SEGMENT)vertexFlags);
		}
	};
}}}