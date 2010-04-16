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

#include "WicImagingFactory.h"
#include "WicBitmapDecoder.h"

namespace DykBits { namespace Graphics { namespace Imaging
{
	WicBitmapDecoder^ WicImagingFactory::CreateDecoder(String^ fileName, Guid vendor, DesiredAccess desiredAccess, DecodeOptions options)
	{
		pin_ptr<const System::Char> pFileName = PtrToStringChars(fileName);
		GUID *pGuid = vendor == Guid::Empty ? NULL : (GUID*)&vendor;
		IWICBitmapDecoder* decoder;
		ComUtils::CheckResult(GetNative()->CreateDecoderFromFilename(pFileName, pGuid, (DWORD)desiredAccess, (WICDecodeOptions)options, &decoder));
		return gcnew WicBitmapDecoder(decoder);
	}

	WicBitmapDecoder^ WicImagingFactory::CreateDecoder(WicStream^ stream, Guid vendor, DecodeOptions options)
	{
		GUID *pGuid = vendor == Guid::Empty ? NULL : (GUID*)&vendor;
		IWICBitmapDecoder* decoder;
		ComUtils::CheckResult(GetNative()->CreateDecoderFromStream(
			(IStream*)stream->GetNative(),
			pGuid,
			(WICDecodeOptions)options,
			&decoder)
			);
		return gcnew WicBitmapDecoder(decoder);
	}

	WicStream^ WicImagingFactory::CreateStream()
	{
		IWICStream *stream;
		ComUtils::CheckResult(GetNative()->CreateStream(&stream));
		return gcnew WicStream(stream);
	}

}}}