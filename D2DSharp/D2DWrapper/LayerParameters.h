#pragma once

#include "D2DCommon.h"
#include "D2DResource.h"

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	public enum class LayerOptions
	{
  		None                       = 0x00000000,
  		InitializeForCleartype   = 0x00000001 
	};

	ref class Geometry;

	public ref class LayerParameters
	{
	public:
		LayerParameters()
		{
		}

		property RectF Bounds
		{
			RectF get() { return _contentBounds; }
			void set(RectF value) { _contentBounds = value; }
		}

		property Geometry^ Mask
		{
			Geometry^ get() { return _geometricMask; }
			void set(Geometry^ value) { _geometricMask = value; }
		}

		property DykBits::Graphics::Direct2D::AntialiasMode MaskAntialiasMode 
		{
			DykBits::Graphics::Direct2D::AntialiasMode get() { return _antialiasMode; }
			void set(DykBits::Graphics::Direct2D::AntialiasMode value) { _antialiasMode = value; }
		}

		property Matrix3x2 MaskTransform
		{
			Matrix3x2 get() { return _maskTransform; }
			void set(Matrix3x2 value) { _maskTransform = value; }
		}

		property FLOAT Opacity
		{
			FLOAT get() { return _opacity; }
			void set(FLOAT value) { _opacity = value; }
		}

		property Brush^ OpacityBrush
		{
			Brush^ get() { return _opacityBrush; }
			void set(Brush^ value) { _opacityBrush = value; }
		}

		property DykBits::Graphics::Direct2D::LayerOptions LayerOptions
		{
			DykBits::Graphics::Direct2D::LayerOptions get() { return _layerOptions; }
			void set(DykBits::Graphics::Direct2D::LayerOptions value) { _layerOptions = value; }
		}

	private:
		RectF _contentBounds;
		Geometry^ _geometricMask;
		AntialiasMode _antialiasMode;
		Matrix3x2 _maskTransform;
		FLOAT _opacity;
		Brush^ _opacityBrush;
		DykBits::Graphics::Direct2D::LayerOptions _layerOptions;
	};
}}}