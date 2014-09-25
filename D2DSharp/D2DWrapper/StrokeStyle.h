/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "D2DCommon.h"
#include "D2DResource.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Direct2D 
{
	public enum class LineCapStyle
	{
		Flat       = 0,
		Square     = 1,
		Round      = 2,
		Triangle   = 3 
	};

	public enum class LineJoin
	{
		Miter            = 0,
		Bevel            = 1,
		Round            = 2,
		MiterOrBevel   	 = 3 
	};

	public enum class DashStyle
	{
		Solid          = 0,
		Dash           = 1,
		Dot            = 2,
		DashDot        = 3,
		DashDotDot     = 4,
		Custom         = 5 
	};

	public enum class StrokeTransformType : System::Int32
	{
		//
		// The stroke respects the world transform, the DPI, and the stroke width.
		//
		Normal = 0,
		//
		// The stroke does not respect the world transform, but it does respect the DPI and
		// the stroke width.
		//
		Fixed = 1,
		//
		// The stroke is forced to one pixel wide.
		//
		Hairline = 2,
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct StrokeStyleProperties
	{
	private:
		D2D1_CAP_STYLE  _startCap;
  		D2D1_CAP_STYLE  _endCap;
  		D2D1_CAP_STYLE  _dashCap;
  		D2D1_LINE_JOIN  _lineJoin;
  		FLOAT           _miterLimit;
  		D2D1_DASH_STYLE _dashStyle;
  		FLOAT           _dashOffset;
	public:
		StrokeStyleProperties(LineCapStyle startCap, LineCapStyle endCap, LineCapStyle dashCap, LineJoin lineJoin, FLOAT miterLimit, DashStyle dashStyle, FLOAT dashOffset)
		{
			_startCap = (D2D1_CAP_STYLE)startCap;
			_endCap = (D2D1_CAP_STYLE)endCap;
			_dashCap = (D2D1_CAP_STYLE)dashCap;
			_lineJoin = (D2D1_LINE_JOIN)lineJoin;
			_miterLimit = miterLimit;
			_dashStyle = (D2D1_DASH_STYLE)dashStyle;
			_dashOffset = dashOffset;
		}
		property LineCapStyle StartCap
		{
			LineCapStyle get() { return (LineCapStyle) _startCap; }
			void set(LineCapStyle value) { _startCap = (D2D1_CAP_STYLE) value; }
		}
		property LineCapStyle EndCap
		{
			LineCapStyle get() { return (LineCapStyle) _endCap; }
			void set(LineCapStyle value) { _endCap = (D2D1_CAP_STYLE) value; }
		}
		property LineCapStyle DashCap
		{
			LineCapStyle get() { return (LineCapStyle) _dashCap; }
			void set(LineCapStyle value) { _dashCap = (D2D1_CAP_STYLE) value; }
		}
		property Managed::Graphics::Direct2D::LineJoin LineJoin
		{
			Managed::Graphics::Direct2D::LineJoin get() { return (Managed::Graphics::Direct2D::LineJoin) _lineJoin; }
			void set(Managed::Graphics::Direct2D::LineJoin value) { _lineJoin = (D2D1_LINE_JOIN) value; }
		}
		property FLOAT MiterLimit
		{
			FLOAT get() { return _miterLimit; }
			void set(FLOAT value) { _miterLimit = value; }
		}
		property Managed::Graphics::Direct2D::DashStyle DashStyle
		{
			Managed::Graphics::Direct2D::DashStyle get() { return (Managed::Graphics::Direct2D::DashStyle)_dashStyle; }
			void set(Managed::Graphics::Direct2D::DashStyle value) { _dashStyle = (D2D1_DASH_STYLE)value; }
		}
		property FLOAT DashOffset
		{
			FLOAT get() { return _dashOffset; }
			void set(FLOAT value) { _dashOffset = value; }
		}
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct StrokeStyleProperties1
	{
	private:
		D2D1_CAP_STYLE	_startCap;
		D2D1_CAP_STYLE	_endCap;
		D2D1_CAP_STYLE	_dashCap;
		D2D1_LINE_JOIN	_lineJoin;
		FLOAT			_miterLimit;
		D2D1_DASH_STYLE _dashStyle;
		FLOAT			_dashOffset;
		//
		// How the nib of the stroke is influenced by the context properties.
		//
		D2D1_STROKE_TRANSFORM_TYPE _transformType;
	public:
		StrokeStyleProperties1(LineCapStyle startCap, LineCapStyle endCap, LineCapStyle dashCap, LineJoin lineJoin, FLOAT miterLimit, DashStyle dashStyle, FLOAT dashOffset, StrokeTransformType transformType)
		{
			_startCap = (D2D1_CAP_STYLE) startCap;
			_endCap = (D2D1_CAP_STYLE) endCap;
			_dashCap = (D2D1_CAP_STYLE) dashCap;
			_lineJoin = (D2D1_LINE_JOIN) lineJoin;
			_miterLimit = miterLimit;
			_dashStyle = (D2D1_DASH_STYLE) dashStyle;
			_dashOffset = dashOffset;
			_transformType = (D2D1_STROKE_TRANSFORM_TYPE) transformType;
		}
		property LineCapStyle StartCap
		{
			LineCapStyle get() { return (LineCapStyle)_startCap; }
			void set(LineCapStyle value) { _startCap = (D2D1_CAP_STYLE) value; }
		}
		property LineCapStyle EndCap
		{
			LineCapStyle get() { return (LineCapStyle) _endCap; }
			void set(LineCapStyle value) { _endCap = (D2D1_CAP_STYLE) value; }
		}
		property LineCapStyle DashCap
		{
			LineCapStyle get() { return (LineCapStyle) _dashCap; }
			void set(LineCapStyle value) { _dashCap = (D2D1_CAP_STYLE) value; }
		}
		property Managed::Graphics::Direct2D::LineJoin LineJoin
		{
			Managed::Graphics::Direct2D::LineJoin get() { return (Managed::Graphics::Direct2D::LineJoin) _lineJoin; }
			void set(Managed::Graphics::Direct2D::LineJoin value) { _lineJoin = (D2D1_LINE_JOIN) value; }
		}
		property FLOAT MiterLimit
		{
			FLOAT get() { return _miterLimit; }
			void set(FLOAT value) { _miterLimit = value; }
		}
		property Managed::Graphics::Direct2D::DashStyle DashStyle
		{
			Managed::Graphics::Direct2D::DashStyle get() { return (Managed::Graphics::Direct2D::DashStyle)_dashStyle; }
			void set(Managed::Graphics::Direct2D::DashStyle value) { _dashStyle = (D2D1_DASH_STYLE)value; }
		}
		property FLOAT DashOffset
		{
			FLOAT get() { return _dashOffset; }
			void set(FLOAT value) { _dashOffset = value; }
		}
		property StrokeTransformType TransformType
		{
			StrokeTransformType get() { return (StrokeTransformType) _transformType; }
			void set(StrokeTransformType value) { _transformType = (D2D1_STROKE_TRANSFORM_TYPE) value; }
		}
	};

	public ref class StrokeStyle: D2DResource
	{
	internal:
		StrokeStyle(ID2D1StrokeStyle* native): 
			D2DResource(native)
		{
		}
		property LineCapStyle DashCap 
		{ 
			LineCapStyle get() 
			{
				return (LineCapStyle)GetNative<ID2D1StrokeStyle>()->GetDashCap();
			}
		}
		property array<FLOAT>^ Dashes
		{
			array<FLOAT>^ get()
			{
				ID2D1StrokeStyle* native = GetNative<ID2D1StrokeStyle>();
				UINT32 count = native->GetDashesCount();
				array<FLOAT>^ dashes = gcnew array<FLOAT>(count);
				pin_ptr<FLOAT> ptr = &dashes[0];
				native->GetDashes(ptr, count);
				return dashes;
			}
		}
		virtual property StrokeTransformType TransformType
		{
			StrokeTransformType get() {
				return StrokeTransformType::Normal;
			}
		}
	};

	private ref class StrokeStyle1 : StrokeStyle
	{
	internal:
		StrokeStyle1(ID2D1StrokeStyle1* native) : StrokeStyle(native)
		{
		}
	public:
		virtual property StrokeTransformType TransformType
		{
			StrokeTransformType get() override 
			{
				return (StrokeTransformType)GetNative<ID2D1StrokeStyle1>()->GetStrokeTransformType();
			}
		}
	};
}}}