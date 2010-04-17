/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#pragma comment(lib, "dwrite.lib")

#include "ComWrapper.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Managed::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace DirectWrite 
{
	/// <summary>
	/// Specifies the type of DirectWrite factory object.
	/// DirectWrite factory contains internal state such as font loader registration and cached font data.
	/// In most cases it is recommended to use the shared factory object, because it allows multiple components
	/// that use DirectWrite to share internal DirectWrite state and reduce memory usage.
	/// However, there are cases when it is desirable to reduce the impact of a component,
	/// such as a plug-in from an untrusted source, on the rest of the process by sandboxing and isolating it
	/// from the rest of the process components. In such cases, it is recommended to use an isolated factory for the sandboxed
	/// component.
	/// </summary>
	public enum class DirectWriteFactoryType
	{
	    /// <summary>
	    /// Shared factory allow for re-use of cached font data across multiple in process components.
	    /// Such factories also take advantage of cross process font caching components for better performance.
	    /// </summary>
	    Shared = DWRITE_FACTORY_TYPE_SHARED,

	    /// <summary>
	    /// Objects created from the isolated factory do not interact with internal DirectWrite state from other components.
	    /// </summary>
	    Isolated = DWRITE_FACTORY_TYPE_ISOLATED
	};

	ref class TextFormat;
	ref class FontCollection;
	ref class TextLayout;
	ref class Typography;

	public ref class DirectWriteFactory: ComWrapper
	{
	private:
		DirectWriteFactory(IDWriteFactory* native): 
		   ComWrapper(native)
		{
		}
	public:
		static DirectWriteFactory^ Create(DirectWriteFactoryType factoryType);
		TextFormat^ CreateTextFormat(String^ fontFamilyName, FontCollection^ fontCollection, FontWeight fontWeight, FontStyle fontStyle, FontStretch fontStretch, FLOAT fontSize, String^ localeName);
		TextLayout^ CreateTextLayout(String^ string, TextFormat^ textFormat, FLOAT maxWidth, FLOAT maxHeight);
		Typography^ CreateTypography();
		static void GetDpiScale([Out]Single% dpiScaleX, [Out]Single% dpiScaleY);
	internal:
		IDWriteFactory* GetNative() new
		{
			return (IDWriteFactory*)ComWrapper::GetNative();
		}
	};
}}}
