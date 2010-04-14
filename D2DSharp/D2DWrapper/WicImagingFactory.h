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
#pragma once

#pragma comment(lib, "Windowscodecs.lib")
#pragma comment(lib, "Ole32.lib")

#include "WicCommon.h"
#include "WicComponentInfo.h"
#include "WicBitmap.h"
#include "WicFormatConverter.h"

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Imaging
{
	ref class WicBitmapDecoder;

	public ref class WicImagingFactory: ComWrapper
	{
	private:
		WicImagingFactory(IWICImagingFactory* native): ComWrapper(native)
		{
		}
	public:
		static WicImagingFactory^ Create()
		{
			IWICImagingFactory* factory;
			HRESULT hr = CoCreateInstance(
				CLSID_WICImagingFactory, 
				NULL, 
				CLSCTX_INPROC_SERVER,
				IID_IWICImagingFactory,
				(LPVOID*)&factory);
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
			return gcnew WicImagingFactory(factory);
		}
		WicBitmap^ CreateBitmap(int width, int height, Guid pixelFormat, BitmapCreateCacheOption option)
		{
			IWICBitmap *bitmap;
			HRESULT hr = GetNative()->CreateBitmap(width, height, *(GUID*)&pixelFormat, (WICBitmapCreateCacheOption)option, &bitmap);
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
			return gcnew WicBitmap(bitmap);
		}
		WicBitmapDecoder^ CreateDecoderFromFilename(String^ fileName, Guid vendor, FileAccess fileAccess, DecodeOptions options);
		WicFormatConverter^ CreateFormatConverter()
		{
			IWICFormatConverter* converter;
			HRESULT hr = GetNative()->CreateFormatConverter(&converter);
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
			return gcnew WicFormatConverter(converter);
		}
	internal:
		IWICImagingFactory* GetNative() new
		{
			return (IWICImagingFactory*)ComWrapper::GetNative();
		}
	};
}}}