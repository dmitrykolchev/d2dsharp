/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Imaging
{
	public ref class WicDecoders
	{
	private:
		WicDecoders()
		{
		}
	public:
		initonly static Guid Bmp = Guid(0x6b462062u, 0x7cbf, 0x400d, 0x9f, 0xdb, 0x81, 0x3d, 0xd1, 0x0f, 0x27, 0x78);
		initonly static Guid Png = Guid(0x389ea17bu, 0x5078, 0x4cde, 0xb6, 0xef, 0x25, 0xc1, 0x51, 0x75, 0xc7, 0x51);
		initonly static Guid Ico = Guid(0xc61bfcdfu, 0x2e0f, 0x4aad, 0xa8, 0xd7, 0xe0, 0x6b, 0xaf, 0xeb, 0xcd, 0xfe);
		initonly static Guid Jpeg = Guid(0x9456a480u, 0xe88b, 0x43ea, 0x9e, 0x73, 0x0b, 0x2d, 0x9b, 0x71, 0xb1, 0xca);
		initonly static Guid Gif = Guid(0x381dda3cu, 0x9ce9, 0x4834, 0xa2, 0x3e, 0x1f, 0x98, 0xf8, 0xfc, 0x52, 0xbe);
		initonly static Guid Tiff = Guid(0xb54e85d9u, 0xfe23, 0x499f, 0x8b, 0x88, 0x6a, 0xce, 0xa7, 0x13, 0x75, 0x2b);
		initonly static Guid Wmp = Guid(0xa26cec36u, 0x234c, 0x4950, 0xae, 0x16, 0xe3, 0x4a, 0xac, 0xe7, 0x1d, 0x0d);
	};

	public ref class WicEncoders
	{
	private:
		WicEncoders()
		{
		}
	public:
		initonly static Guid Bmp = Guid(0x69be8bb4u, 0xd66d, 0x47c8, 0x86, 0x5a, 0xed, 0x15, 0x89, 0x43, 0x37, 0x82);
		initonly static Guid Png = Guid(0x27949969u, 0x876a, 0x41d7, 0x94, 0x47, 0x56, 0x8f, 0x6a, 0x35, 0xa4, 0xdc);
		initonly static Guid Jpeg = Guid(0x1a34f5c1u, 0x4a5a, 0x46dc, 0xb6, 0x44, 0x1f, 0x45, 0x67, 0xe7, 0xa6, 0x76);
		initonly static Guid Gif = Guid(0x114f5598u, 0x0b22, 0x40a0, 0x86, 0xa1, 0xc8, 0x3e, 0xa4, 0x95, 0xad, 0xbd);
		initonly static Guid Tiff = Guid(0x0131be10u, 0x2001, 0x4c5f, 0xa9, 0xb0, 0xcc, 0x88, 0xfa, 0xb6, 0x4c, 0xe8);
		initonly static Guid Wmp = Guid(0xac4ce3cbu, 0xe1c1, 0x44cd, 0x82, 0x15, 0x5a, 0x16, 0x65, 0x50, 0x9e, 0xc2);
	};

	public ref class WicContainerFormats
	{
	private:
		WicContainerFormats() {}
	public:
		initonly static Guid Bmp = Guid(0x0af1d87eu, 0xfcfe, 0x4188, 0xbd, 0xeb, 0xa7, 0x90, 0x64, 0x71, 0xcb, 0xe3);
		initonly static Guid Png = Guid(0x1b7cfaf4u, 0x713f, 0x473c, 0xbb, 0xcd, 0x61, 0x37, 0x42, 0x5f, 0xae, 0xaf);
		initonly static Guid Ico = Guid(0xa3a860c4u, 0x338f, 0x4c17, 0x91, 0x9a, 0xfb, 0xa4, 0xb5, 0x62, 0x8f, 0x21);
		initonly static Guid Jpeg = Guid(0x19e4a5aau, 0x5662, 0x4fc5, 0xa0, 0xc0, 0x17, 0x58, 0x02, 0x8e, 0x10, 0x57);
		initonly static Guid Tiff = Guid(0x163bcc30u, 0xe2e9, 0x4f0b, 0x96, 0x1d, 0xa3, 0xe9, 0xfd, 0xb7, 0x88, 0xa3);
		initonly static Guid Gif = Guid(0x1f8a5601u, 0x7d4d, 0x4cbd, 0x9c, 0x82, 0x1b, 0xc8, 0xd4, 0xee, 0xb9, 0xa5);
		initonly static Guid Wmp = Guid(0x57a37caau, 0x367a, 0x4540, 0x91, 0x6b, 0xf1, 0x83, 0xc5, 0x09, 0x3a, 0x4b);
	};


	public ref class WicVendors
	{
	private:
		WicVendors() {}
	public:
		initonly static Guid Microsoft = Guid(0xf0e749cau, 0xedef, 0x4589, 0xa7, 0x3a, 0xee, 0xe, 0x62, 0x6a, 0x2a, 0x2b);
		initonly static Guid MicrosoftBuiltIn = Guid(0x257a30fdu, 0x6b6, 0x462b, 0xae, 0xa4, 0x63, 0xf7, 0xb, 0x86, 0xe5, 0x33);
	};

	public ref class WicComponentIdentifiers
	{
	private: 
		WicComponentIdentifiers() {}
	public:
		initonly static Guid ImagingCategories = Guid(0xfae3d380u, 0xfea4, 0x4623, 0x8c, 0x75, 0xc6, 0xb6, 0x11, 0x10, 0xb6, 0x81);
		initonly static Guid BitmapDecoders = Guid(0x7ed96837u, 0x96f0, 0x4812, 0xb2, 0x11, 0xf1, 0x3c, 0x24, 0x11, 0x7e, 0xd3);
		initonly static Guid BitmapEncoders = Guid(0xac757296u, 0x3522, 0x4e11, 0x98, 0x62, 0xc1, 0x7b, 0xe5, 0xa1, 0x76, 0x7e);
		initonly static Guid PixelFormats = Guid(0x2b46e70fu, 0xcda7, 0x473e, 0x89, 0xf6, 0xdc, 0x96, 0x30, 0xa2, 0x39, 0x0b);
		initonly static Guid FormatConverters = Guid(0x7835eae8u, 0xbf14, 0x49d1, 0x93, 0xce, 0x53, 0x3a, 0x40, 0x7b, 0x22, 0x48);
		initonly static Guid MetadataReader = Guid(0x05af94d8u, 0x7174, 0x4cd2, 0xbe, 0x4a, 0x41, 0x24, 0xb8, 0x0e, 0xe4, 0xb8);
		initonly static Guid MetadataWriter = Guid(0xabe3b9a4u, 0x257d, 0x4b97, 0xbd, 0x1a, 0x29, 0x4a, 0xf4, 0x96, 0x22, 0x2e);
	};

	public ref class WicFormatConverters
	{
	private:
		WicFormatConverters() {}
	public:
		initonly static Guid Default = Guid(0x1a3f11dcu, 0xb514, 0x4b17, 0x8c, 0x5f, 0x21, 0x54, 0x51, 0x38, 0x52, 0xf1);
		initonly static Guid HighColor = Guid(0xac75d454u, 0x9f37, 0x48f8, 0xb9, 0x72, 0x4e, 0x19, 0xbc, 0x85, 0x60, 0x11);
		initonly static Guid NChannel = Guid(0xc17cabb2u, 0xd4a3, 0x47d7, 0xa5, 0x57, 0x33, 0x9b, 0x2e, 0xfb, 0xd4, 0xf1);
		initonly static Guid WMPhoto = Guid(0x9cb5172bu, 0xd600, 0x46ba, 0xab, 0x77, 0x77, 0xbb, 0x7e, 0x3a, 0x00, 0xd9);
	};
}}}