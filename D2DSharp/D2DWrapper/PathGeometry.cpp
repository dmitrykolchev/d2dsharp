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
#include "stdafx.h"

#include "PathGeometry.h"

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	GeometrySink^ PathGeometry::Open()
	{
		ID2D1GeometrySink *geometrySink;
		
		HRESULT hr = GetNative()->Open(&geometrySink);
		
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		return gcnew GeometrySink(geometrySink);
	}

	void PathGeometry::Stream(GeometrySink^ geometrySink)
	{
		HRESULT hr = GetNative()->Stream(geometrySink->GetNative());
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}
}}}