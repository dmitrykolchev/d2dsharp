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

#include "D2DCommon.h"
#include "Brush.h"
#include "Color.h"

using namespace System;

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	public ref class SolidColorBrush: Brush
	{
	internal:
		SolidColorBrush(ID2D1SolidColorBrush* brush): 
			Brush(brush)
		{
		}
	public:
		property DykBits::Graphics::Direct2D::Color Color
		{
			DykBits::Graphics::Direct2D::Color get()
			{
				return DykBits::Graphics::Direct2D::Color(GetNative()->GetColor());
			}
			void set(DykBits::Graphics::Direct2D::Color color)
			{
				GetNative()->SetColor((D2D1_COLOR_F*)&color);
			}
		}
	private:
		ID2D1SolidColorBrush* GetNative() new
		{
			return (ID2D1SolidColorBrush*)Brush::GetNative();
		}
	};
}}}