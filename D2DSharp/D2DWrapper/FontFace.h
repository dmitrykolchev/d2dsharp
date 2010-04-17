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

		//array<GlyphMetrics>^ GetGlyphMetrics(array<UInt16>^ glyphIndices, Boolean isSideways);
		//array<FontFile^>^ GetFiles();
		//FontMetrics GetGdiCompatibleMetrics(Single emSize, Single pixelsPerDip);
		//FontMetrics GetGdiCompatibleMetrics(Single emSize, Single pixelsPerDip, Managed::Graphics::Direct2D::Matrix3x2 transform);

		//array<UInt16>^ GetGlyphIndices();

		void GetGlyphRunOutline(Single emSize, array<UInt16>^ glyphIndices, array<Single>^ glyphAdvances, 
			array<GlyphOffset>^ glyphOffsets, Boolean isSideways, Boolean isRtl, GeometrySink^ geometrySink);


	internal:
		IDWriteFontFace* GetNative() new
		{
			return static_cast<IDWriteFontFace*>(ComWrapper::GetNative());
		}
	};
}}}