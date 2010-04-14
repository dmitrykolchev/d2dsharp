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
	WicBitmapDecoder^ WicImagingFactory::CreateDecoderFromFilename(String^ fileName, Guid vendor, FileAccess fileAccess, DecodeOptions options)
	{
		pin_ptr<const System::Char> pFileName = PtrToStringChars(fileName);
		GUID *pGuid = vendor == Guid::Empty ? NULL : (GUID*)&vendor;
		DWORD fa = GENERIC_READ;
		switch(fileAccess)
		{
		case FileAccess::Read:
			fa = GENERIC_READ;
			break;
		case FileAccess::Write:
			fa = GENERIC_WRITE;
			break;
		case FileAccess::ReadWrite:
			fa = GENERIC_READ | GENERIC_WRITE;
			break;
		}
		IWICBitmapDecoder* decoder;
		HRESULT hr = GetNative()->CreateDecoderFromFilename(pFileName, pGuid, fa, (WICDecodeOptions)options, &decoder);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
		return gcnew WicBitmapDecoder(decoder);
	}

}}}