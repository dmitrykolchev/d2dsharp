/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "ComWrapper.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Managed::Runtime::InteropServices;
using namespace Managed::Graphics::Direct2D;

namespace Managed { namespace Graphics { namespace DirectWrite
{
	public ref class FontFace: ComWrapper
	{
	internal:
		FontFace(IDWriteFontFace* native): ComWrapper(native)
		{
		}
		FontFace(IDWriteFontFace* native, Boolean addRef): ComWrapper(native, addRef)
		{
		}
	public:
		property UInt32 GlyphCount
		{
			UInt32 get()
			{
				return GetNative()->GetGlyphCount();
			}
		}

		property UInt32 Index
		{
			UInt32 get()
			{
				return GetNative()->GetIndex();
			}
		}

		property FontMetrics Metrics
		{
			FontMetrics get()
			{
				FontMetrics metrics;
				GetNative()->GetMetrics(
					(DWRITE_FONT_METRICS*)&metrics);
				return metrics;
			}
		}

		property FontSimulations Simulations
		{
			FontSimulations get()
			{
				return (FontSimulations)GetNative()->GetSimulations();
			}
		}

		property Boolean IsSymbolFont
		{
			Boolean get()
			{
				return GetNative()->IsSymbolFont() != 0;
			}
		}

		property Managed::Graphics::DirectWrite::FontFaceType FontFaceType
		{
			Managed::Graphics::DirectWrite::FontFaceType get()
			{
				return (Managed::Graphics::DirectWrite::FontFaceType)GetNative()->GetType();
			}
		}


		array<GlyphMetrics>^ GetDesignGlyphMetrics(array<UInt16>^ glyphIndices, Boolean isSideways);
		//array<FontFile^>^ GetFiles();
		//FontMetrics GetGdiCompatibleMetrics(Single emSize, Single pixelsPerDip);
		//FontMetrics GetGdiCompatibleMetrics(Single emSize, Single pixelsPerDip, Managed::Graphics::Direct2D::Matrix3x2 transform);

		array<UInt16>^ GetGlyphIndices(array<UInt32>^ codePoints);

		void GetGlyphRunOutline(Single emSize, array<UInt16>^ glyphIndices, array<Single>^ glyphAdvances, 
			array<GlyphOffset>^ glyphOffsets, Boolean isSideways, Boolean isRtl, GeometrySink^ geometrySink);
		void GetGlyphRunOutline(Single emSize, array<UInt16>^ glyphIndices, array<Single>^ glyphAdvances, 
			array<GlyphOffset>^ glyphOffsets, Boolean isSideways, Boolean isRtl, ICustomGeometrySink^ customGeometrySink);

	internal:
		IDWriteFontFace* GetNative() new
		{
			return static_cast<IDWriteFontFace*>(ComWrapper::GetNative());
		}
	};
}}}