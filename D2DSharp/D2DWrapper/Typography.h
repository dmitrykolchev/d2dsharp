/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "ComWrapper.h"
#include "ComUtils.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Managed::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace DirectWrite 
{
	[StructLayout(LayoutKind::Sequential)]
	public value struct FontFeature
	{
	private:
		FontFeatureTag _nameTag;
		UInt32 _parameter;
	public:
		FontFeature(FontFeatureTag nameTag, UInt32 parameter)
		{
			_nameTag = nameTag;
			_parameter = parameter;
		}

		property FontFeatureTag NameTag
		{
			FontFeatureTag get() { return _nameTag; }
			void set(FontFeatureTag value) { _nameTag = value; }
		}

		property UInt32 Parameter
		{
			UInt32 get() { return _parameter; }
			void set(UInt32 value) { _parameter = value; }
		}
	};

	public ref class Typography: ComWrapper
	{
	internal:
		Typography(IDWriteTypography* native): ComWrapper(native)
		{
		}
	public:
		void AddFontFeature(FontFeature fontFeature);
		void AddFontFeature(FontFeatureTag nameTag, UInt32 value);
		array<FontFeature>^ GetFontFeatures();
	};
}}}