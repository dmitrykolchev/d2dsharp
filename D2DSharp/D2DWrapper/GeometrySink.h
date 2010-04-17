/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "D2DCommon.h"
#include "SimplifiedGeometrySink.h"

namespace Managed { namespace Graphics { namespace Direct2D 
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
		property PointF Point 
		{ 
			PointF get() { return _point; }
		}
		property SizeF Size
		{
			SizeF get() { return _size; }
		}
		property Single RotationAngle
		{
			Single get() { return _rotationAngle; }
		}
		property Managed::Graphics::Direct2D::SweepDirection SweepDirection
		{
			Managed::Graphics::Direct2D::SweepDirection get() 
			{ 
				return (Managed::Graphics::Direct2D::SweepDirection)_sweepDirection; 
			}
		}
		property Managed::Graphics::Direct2D::ArcSize ArcSize
		{
			Managed::Graphics::Direct2D::ArcSize get()
			{
				return (Managed::Graphics::Direct2D::ArcSize)_arcSize;
			}
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

		property PointF Point1
		{
			PointF get() { return _point1; }
		}

		property PointF Point2
		{
			PointF get() { return _point2; }
		}
	};

	public interface class ICustomGeometrySink: ICustomSimplifiedGeometrySink
	{
	public:
		void AddArc(ArcSegment arc) = 0;
		void AddBezier(BezierSegment bezier) = 0;
		void AddLine(PointF point) = 0;
		void AddQuadraticBezier(QuadraticBezierSegment bezier) = 0;
		void AddQuadraticBeziers(array<QuadraticBezierSegment>^ beziers) = 0;
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

	class CustomGeometrySink: public ID2D1GeometrySink
	{
	public:
		CustomGeometrySink(ICustomGeometrySink^ sink): _refCount(1), _sink(sink)
		{
		}

		// ID2D1SimplifiedGeometrySink
		STDMETHOD_(void, SetFillMode)(D2D1_FILL_MODE fillMode);
    
		STDMETHOD_(void, SetSegmentFlags)(D2D1_PATH_SEGMENT vertexFlags);
    
		STDMETHOD_(void, BeginFigure)(D2D1_POINT_2F startPoint,	D2D1_FIGURE_BEGIN figureBegin);
    
		STDMETHOD_(void, AddLines)(	
			__in_ecount(pointsCount) CONST D2D1_POINT_2F *points,
			UINT pointsCount 
			);
    
		STDMETHOD_(void, AddBeziers)(
			__in_ecount(beziersCount) CONST D2D1_BEZIER_SEGMENT *beziers,
			UINT beziersCount 
			);
    
		STDMETHOD_(void, EndFigure)(D2D1_FIGURE_END figureEnd);
    
		STDMETHOD(Close)();

		// ID2D1GeometrySink
		STDMETHOD_(void, AddLine)(D2D1_POINT_2F point);
    
		STDMETHOD_(void, AddBezier)(__in CONST D2D1_BEZIER_SEGMENT *bezier);
    
		STDMETHOD_(void, AddQuadraticBezier)(__in CONST D2D1_QUADRATIC_BEZIER_SEGMENT *bezier);
    
		STDMETHOD_(void, AddQuadraticBeziers)(
			__in_ecount(beziersCount) CONST D2D1_QUADRATIC_BEZIER_SEGMENT *beziers,
			UINT beziersCount 
			);
    
		STDMETHOD_(void, AddArc)(__in CONST D2D1_ARC_SEGMENT *arc);
    public:
        unsigned long STDMETHODCALLTYPE AddRef();
        unsigned long STDMETHODCALLTYPE Release();
        HRESULT STDMETHODCALLTYPE QueryInterface(
            IID const& riid,
            void** ppvObject
        );

    protected:
        virtual ~CustomGeometrySink() { }

	private:
		gcroot<ICustomGeometrySink^> _sink;
		LONG _refCount;
	};
}}}