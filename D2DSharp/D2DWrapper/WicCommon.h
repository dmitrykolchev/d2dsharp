#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Imaging
{
	[StructLayout(LayoutKind::Sequential)]
	public value struct WicColor
	{
	public:
		Byte R;
		Byte G;
		Byte B;
		Byte A;
	};

	public enum class BitmapCreateCacheOption 
	{
		NoCache         = 0x00000000,
		CacheOnDemand   = 0x00000001,
		CacheOnLoad     = 0x00000002 
	};

	public enum class DecodeOptions
	{
		MetadataCacheOnDemand   = 0x00000000,
		MetadataCacheOnLoad     = 0x00000001 
	};

	public enum class BitmapPaletteType 
	{
		  Custom             = 0x00000000,
		  MedianCut          = 0x00000001,
		  FixedBW            = 0x00000002,
		  FixedHalftone8     = 0x00000003,
		  FixedHalftone27    = 0x00000004,
		  FixedHalftone64    = 0x00000005,
		  FixedHalftone125   = 0x00000006,
		  FixedHalftone216   = 0x00000007,
		  FixedWebPalette    = FixedHalftone216,
		  FixedHalftone252   = 0x00000008,
		  FixedHalftone256   = 0x00000009,
		  FixedGray4         = 0x0000000A,
		  FixedGray16        = 0x0000000B,
		  FixedGray256       = 0x0000000C 
	};

	public enum class BitmapDitherType 
	{
		None             = 0x00000000,
		Solid            = 0x00000000,
		Ordered4x4       = 0x00000001,
		Ordered8x8       = 0x00000002,
		Ordered16x16     = 0x00000003,
		Spiral4x4        = 0x00000004,
		Spiral8x8        = 0x00000005,
		DualSpiral4x4    = 0x00000006,
		DualSpiral8x8    = 0x00000007,
		ErrorDiffusion   = 0x00000008 
	};


	[StructLayout(LayoutKind::Sequential)]
	public value struct WicRect
	{
	public:
		int X;
		int Y;
		int Width;
		int Height;
	};
}}}