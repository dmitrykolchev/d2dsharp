/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
* Copyright (C) 2010 Dmitry Kolchev
*
* This sourcecode is licenced under The GNU Lesser General Public License
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
* NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
* USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "Stdafx.h"

#include "DWCommon.h"
#include "DirectWriteFactory.h"
#include "TextFormat.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace DirectWrite 
{
	DirectWriteFactory^ DirectWriteFactory::Create(DirectWriteFactoryType factoryType)
	{
		IDWriteFactory *writeFactory;

		HRESULT hr = DWriteCreateFactory(
			(DWRITE_FACTORY_TYPE)factoryType, 
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&writeFactory));

		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		return gcnew DirectWriteFactory(writeFactory);
	}

	TextFormat^ DirectWriteFactory::CreateTextFormat(String^ fontFamilyName, FontCollection^ fontCollection, FontWeight fontWeight, FontStyle fontStyle, FontStretch fontStretch, FLOAT fontSize, String^ localeName)
	{
		if(fontFamilyName == nullptr)
			throw gcnew ArgumentNullException("fontFamilyName");

		pin_ptr<const System::Char> pFontFamily = PtrToStringChars(fontFamilyName);
		
		pin_ptr<const System::Char> pLocaleName = localeName == nullptr ? L"" : PtrToStringChars(fontFamilyName);
		
		IDWriteFontCollection* pFontCollection = fontCollection == nullptr ? NULL : fontCollection->GetNative();
		
		IDWriteTextFormat *textFormat;

		HRESULT hr = GetNative()->CreateTextFormat(
			pFontFamily, 
			pFontCollection, 
			(DWRITE_FONT_WEIGHT)fontWeight, 
			(DWRITE_FONT_STYLE)fontStyle,
			(DWRITE_FONT_STRETCH)fontStretch,
			fontSize,
			pLocaleName,
			&textFormat);
		
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		return gcnew TextFormat(textFormat);
	}
	
	TextLayout^ DirectWriteFactory::CreateTextLayout(String^ string, TextFormat^ textFormat, FLOAT maxWidth, FLOAT maxHeight)
	{
		pin_ptr<const System::Char> pString = PtrToStringChars(string);
		IDWriteTextLayout* textLayout;
		HRESULT hr = GetNative()->CreateTextLayout(
			pString,
			string->Length,
			textFormat->GetNative(),
			maxWidth,
			maxHeight,
			&textLayout);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		return gcnew TextLayout(textLayout);
	}
}}}