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

#include "Color.h"

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	public ref class Colors sealed
	{
	private:
		Colors()
		{
		}
	public:
		initonly static Color White = Color::FromRGB(1, 1, 1);
		initonly static Color Gray = Color::FromRGB(0.5f, 0.5f, 0.5f);
		initonly static Color Black = Color::FromRGB(0, 0, 0);
		initonly static Color Red = Color::FromRGB(1, 0, 0);
		initonly static Color Green = Color::FromRGB(0, 1, 0);
		initonly static Color Blue = Color::FromRGB(0, 0, 1);
		initonly static Color Cyan = Color::FromRGB(0, 1, 1);
		initonly static Color Magenta = Color::FromRGB(1, 0, 1);
		initonly static Color Yellow = Color::FromRGB(1, 1, 0);
	};
}}}