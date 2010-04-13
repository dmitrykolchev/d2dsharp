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