/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "stdafx.h"

#include "GeometrySink.h"

using namespace Managed::Graphics::Direct2D;

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


//
// CustomSimplifiedGeometrySink
//
// ID2D1SimplifiedGeometrySink
void STDMETHODCALLTYPE CustomSimplifiedGeometrySink::SetFillMode(D2D1_FILL_MODE fillMode)
{
	_sink->SetFillMode((FillMode)fillMode);
}
    
void STDMETHODCALLTYPE CustomSimplifiedGeometrySink::SetSegmentFlags(D2D1_PATH_SEGMENT vertexFlags)
{
	_sink->SetSegmentFlags((PathSegment)vertexFlags);
}
    
void STDMETHODCALLTYPE CustomSimplifiedGeometrySink::BeginFigure(D2D1_POINT_2F startPoint, D2D1_FIGURE_BEGIN figureBegin)
{
	_sink->BeginFigure(*(PointF*)&startPoint, (FigureBegin)figureBegin);
}
    
void STDMETHODCALLTYPE CustomSimplifiedGeometrySink::AddLines(	
	__in_ecount(pointsCount) CONST D2D1_POINT_2F *points,
	UINT pointsCount 
	)
{
	array<PointF>^ mpoints = gcnew array<PointF>(pointsCount);
	pin_ptr<PointF> pPoints = &mpoints[0];
	memcpy(pPoints, points, sizeof(D2D1_POINT_2F) * pointsCount);
	_sink->AddLines(mpoints);
}
    
void STDMETHODCALLTYPE CustomSimplifiedGeometrySink::AddBeziers(
	__in_ecount(beziersCount) CONST D2D1_BEZIER_SEGMENT *beziers,
	UINT beziersCount 
	)
{
	array<BezierSegment>^ msegments = gcnew array<BezierSegment>(beziersCount);
	pin_ptr<BezierSegment> pSegments = &msegments[0];
	memcpy(pSegments, beziers, sizeof(D2D1_BEZIER_SEGMENT) * beziersCount);
	_sink->AddBeziers(msegments);
}
    
void STDMETHODCALLTYPE CustomSimplifiedGeometrySink::EndFigure(D2D1_FIGURE_END figureEnd)
{
	_sink->EndFigure((FigureEnd)figureEnd);
}
    
HRESULT STDMETHODCALLTYPE CustomSimplifiedGeometrySink::Close()
{
	try
	{
		_sink->Close();
	}
	catch(Exception^)
	{
		return E_FAIL;
	}
	return S_OK;
}

unsigned long STDMETHODCALLTYPE CustomSimplifiedGeometrySink::AddRef()
{
    return InterlockedIncrement(&_refCount);
}

unsigned long STDMETHODCALLTYPE CustomSimplifiedGeometrySink::Release()
{
    if (InterlockedDecrement(&_refCount) == 0)
    {
        delete this;
        return 0;
    }
    return _refCount;
}

HRESULT STDMETHODCALLTYPE CustomSimplifiedGeometrySink::QueryInterface(IID const& riid, void** ppvObject)
{
	if(__uuidof(ID2D1SimplifiedGeometrySink) == riid)
    {
        *ppvObject = static_cast<ID2D1SimplifiedGeometrySink*>(this);
    }
    else if (__uuidof(IUnknown) == riid)
    {
        *ppvObject = static_cast<IUnknown*>(this);
    }
    else
    {
        *ppvObject = NULL;
        return E_NOINTERFACE;
    }
    return S_OK;
}

//
// CustomGeometrySink
//

// ID2D1SimplifiedGeometrySink
void STDMETHODCALLTYPE CustomGeometrySink::SetFillMode(D2D1_FILL_MODE fillMode)
{
	_sink->SetFillMode((FillMode)fillMode);
}
    
void STDMETHODCALLTYPE CustomGeometrySink::SetSegmentFlags(D2D1_PATH_SEGMENT vertexFlags)
{
	_sink->SetSegmentFlags((PathSegment)vertexFlags);
}
    
void STDMETHODCALLTYPE CustomGeometrySink::BeginFigure(D2D1_POINT_2F startPoint, D2D1_FIGURE_BEGIN figureBegin)
{
	_sink->BeginFigure(*(PointF*)&startPoint, (FigureBegin)figureBegin);
}
    
void STDMETHODCALLTYPE CustomGeometrySink::AddLines(	
	__in_ecount(pointsCount) CONST D2D1_POINT_2F *points,
	UINT pointsCount 
	)
{
	array<PointF>^ mpoints = gcnew array<PointF>(pointsCount);
	pin_ptr<PointF> pPoints = &mpoints[0];
	memcpy(pPoints, points, sizeof(D2D1_POINT_2F) * pointsCount);
	_sink->AddLines(mpoints);
}
    
void STDMETHODCALLTYPE CustomGeometrySink::AddBeziers(
	__in_ecount(beziersCount) CONST D2D1_BEZIER_SEGMENT *beziers,
	UINT beziersCount 
	)
{
	array<BezierSegment>^ msegments = gcnew array<BezierSegment>(beziersCount);
	pin_ptr<BezierSegment> pSegments = &msegments[0];
	memcpy(pSegments, beziers, sizeof(D2D1_BEZIER_SEGMENT) * beziersCount);
	_sink->AddBeziers(msegments);
}
    
void STDMETHODCALLTYPE CustomGeometrySink::EndFigure(D2D1_FIGURE_END figureEnd)
{
	_sink->EndFigure((FigureEnd)figureEnd);
}
    
HRESULT STDMETHODCALLTYPE CustomGeometrySink::Close()
{
	try
	{
		_sink->Close();
	}
	catch(Exception^)
	{
		return E_FAIL;
	}
	return S_OK;
}

// ID2D1GeometrySink
void STDMETHODCALLTYPE CustomGeometrySink::AddLine(D2D1_POINT_2F point)
{
	_sink->AddLine(PointF(point.x, point.y));
}
    
void STDMETHODCALLTYPE CustomGeometrySink::AddBezier(__in CONST D2D1_BEZIER_SEGMENT *bezier)
{
	_sink->AddBezier(
		BezierSegment(
			PointF(bezier->point1.x, bezier->point1.y),
			PointF(bezier->point2.x, bezier->point2.y),
			PointF(bezier->point3.x, bezier->point3.y)
			));
}
    
void STDMETHODCALLTYPE CustomGeometrySink::AddQuadraticBezier(__in CONST D2D1_QUADRATIC_BEZIER_SEGMENT *bezier)
{
	_sink->AddQuadraticBezier(
		QuadraticBezierSegment(
			PointF(bezier->point1.x, bezier->point1.y),
			PointF(bezier->point2.x, bezier->point2.y)
			));
}
    
void STDMETHODCALLTYPE CustomGeometrySink::AddQuadraticBeziers(
	__in_ecount(beziersCount) CONST D2D1_QUADRATIC_BEZIER_SEGMENT *beziers,
	UINT beziersCount 
	)
{
	array<QuadraticBezierSegment>^ a = gcnew array<QuadraticBezierSegment>(beziersCount);
	pin_ptr<QuadraticBezierSegment> p = &a[0];
	memcpy(p, beziers, sizeof(D2D1_QUADRATIC_BEZIER_SEGMENT) * beziersCount);
	_sink->AddQuadraticBeziers(a);
}
    
void STDMETHODCALLTYPE CustomGeometrySink::AddArc(__in CONST D2D1_ARC_SEGMENT *arc)
{
	_sink->AddArc(
		ArcSegment(
			PointF(arc->point.x, arc->point.y),
			SizeF(arc->size.width, arc->size.height),
			arc->rotationAngle,
			(SweepDirection)arc->sweepDirection,
			(ArcSize)arc->arcSize));
}

unsigned long STDMETHODCALLTYPE CustomGeometrySink::AddRef()
{
    return InterlockedIncrement(&_refCount);
}

unsigned long STDMETHODCALLTYPE CustomGeometrySink::Release()
{
    if (InterlockedDecrement(&_refCount) == 0)
    {
        delete this;
        return 0;
    }
    return _refCount;
}

HRESULT STDMETHODCALLTYPE CustomGeometrySink::QueryInterface(IID const& riid, void** ppvObject)
{
    if (__uuidof(ID2D1GeometrySink) == riid)
    {
        *ppvObject = static_cast<ID2D1GeometrySink*>(this);
    }
	else if(__uuidof(ID2D1SimplifiedGeometrySink) == riid)
    {
        *ppvObject = static_cast<ID2D1SimplifiedGeometrySink*>(this);
    }
    else if (__uuidof(IUnknown) == riid)
    {
        *ppvObject = static_cast<IUnknown*>(this);
    }
    else
    {
        *ppvObject = NULL;
        return E_NOINTERFACE;
    }
    return S_OK;
}
