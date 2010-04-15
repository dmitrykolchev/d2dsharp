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
* THE SOFTWARE IS PROVIDED "AS IS"; WITHOUT WARRANTY OF ANY KIND; EXPRESS
* OR IMPLIED; INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
* NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM;
* DAMAGES OR OTHER LIABILITY; WHETHER IN AN ACTION OF CONTRACT; TORT OR
* OTHERWISE; ARISING FROM; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
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
        static const int AliceBlue = 0xF0F8FF;
        static const int AntiqueWhite = 0xFAEBD7;
        static const int Aqua = 0x00FFFF;
        static const int Aquamarine = 0x7FFFD4;
        static const int Azure = 0xF0FFFF;
        static const int Beige = 0xF5F5DC;
        static const int Bisque = 0xFFE4C4;
        static const int Black = 0x000000;
        static const int BlanchedAlmond = 0xFFEBCD;
        static const int Blue = 0x0000FF;
        static const int BlueViolet = 0x8A2BE2;
        static const int Brown = 0xA52A2A;
        static const int BurlyWood = 0xDEB887;
        static const int CadetBlue = 0x5F9EA0;
        static const int Chartreuse = 0x7FFF00;
        static const int Chocolate = 0xD2691E;
        static const int Coral = 0xFF7F50;
        static const int CornflowerBlue = 0x6495ED;
        static const int Cornsilk = 0xFFF8DC;
        static const int Crimson = 0xDC143C;
        static const int Cyan = 0x00FFFF;
        static const int DarkBlue = 0x00008B;
        static const int DarkCyan = 0x008B8B;
        static const int DarkGoldenrod = 0xB8860B;
        static const int DarkGray = 0xA9A9A9;
        static const int DarkGreen = 0x006400;
        static const int DarkKhaki = 0xBDB76B;
        static const int DarkMagenta = 0x8B008B;
        static const int DarkOliveGreen = 0x556B2F;
        static const int DarkOrange = 0xFF8C00;
        static const int DarkOrchid = 0x9932CC;
        static const int DarkRed = 0x8B0000;
        static const int DarkSalmon = 0xE9967A;
        static const int DarkSeaGreen = 0x8FBC8F;
        static const int DarkSlateBlue = 0x483D8B;
        static const int DarkSlateGray = 0x2F4F4F;
        static const int DarkTurquoise = 0x00CED1;
        static const int DarkViolet = 0x9400D3;
        static const int DeepPink = 0xFF1493;
        static const int DeepSkyBlue = 0x00BFFF;
        static const int DimGray = 0x696969;
        static const int DodgerBlue = 0x1E90FF;
        static const int Firebrick = 0xB22222;
        static const int FloralWhite = 0xFFFAF0;
        static const int ForestGreen = 0x228B22;
        static const int Fuchsia = 0xFF00FF;
        static const int Gainsboro = 0xDCDCDC;
        static const int GhostWhite = 0xF8F8FF;
        static const int Gold = 0xFFD700;
        static const int Goldenrod = 0xDAA520;
        static const int Gray = 0x808080;
        static const int Green = 0x008000;
        static const int GreenYellow = 0xADFF2F;
        static const int Honeydew = 0xF0FFF0;
        static const int HotPink = 0xFF69B4;
        static const int IndianRed = 0xCD5C5C;
        static const int Indigo = 0x4B0082;
        static const int Ivory = 0xFFFFF0;
        static const int Khaki = 0xF0E68C;
        static const int Lavender = 0xE6E6FA;
        static const int LavenderBlush = 0xFFF0F5;
        static const int LawnGreen = 0x7CFC00;
        static const int LemonChiffon = 0xFFFACD;
        static const int LightBlue = 0xADD8E6;
        static const int LightCoral = 0xF08080;
        static const int LightCyan = 0xE0FFFF;
        static const int LightGoldenrodYellow = 0xFAFAD2;
        static const int LightGreen = 0x90EE90;
        static const int LightGray = 0xD3D3D3;
        static const int LightPink = 0xFFB6C1;
        static const int LightSalmon = 0xFFA07A;
        static const int LightSeaGreen = 0x20B2AA;
        static const int LightSkyBlue = 0x87CEFA;
        static const int LightSlateGray = 0x778899;
        static const int LightSteelBlue = 0xB0C4DE;
        static const int LightYellow = 0xFFFFE0;
        static const int Lime = 0x00FF00;
        static const int LimeGreen = 0x32CD32;
        static const int Linen = 0xFAF0E6;
        static const int Magenta = 0xFF00FF;
        static const int Maroon = 0x800000;
        static const int MediumAquamarine = 0x66CDAA;
        static const int MediumBlue = 0x0000CD;
        static const int MediumOrchid = 0xBA55D3;
        static const int MediumPurple = 0x9370DB;
        static const int MediumSeaGreen = 0x3CB371;
        static const int MediumSlateBlue = 0x7B68EE;
        static const int MediumSpringGreen = 0x00FA9A;
        static const int MediumTurquoise = 0x48D1CC;
        static const int MediumVioletRed = 0xC71585;
        static const int MidnightBlue = 0x191970;
        static const int MintCream = 0xF5FFFA;
        static const int MistyRose = 0xFFE4E1;
        static const int Moccasin = 0xFFE4B5;
        static const int NavajoWhite = 0xFFDEAD;
        static const int Navy = 0x000080;
        static const int OldLace = 0xFDF5E6;
        static const int Olive = 0x808000;
        static const int OliveDrab = 0x6B8E23;
        static const int Orange = 0xFFA500;
        static const int OrangeRed = 0xFF4500;
        static const int Orchid = 0xDA70D6;
        static const int PaleGoldenrod = 0xEEE8AA;
        static const int PaleGreen = 0x98FB98;
        static const int PaleTurquoise = 0xAFEEEE;
        static const int PaleVioletRed = 0xDB7093;
        static const int PapayaWhip = 0xFFEFD5;
        static const int PeachPuff = 0xFFDAB9;
        static const int Peru = 0xCD853F;
        static const int Pink = 0xFFC0CB;
        static const int Plum = 0xDDA0DD;
        static const int PowderBlue = 0xB0E0E6;
        static const int Purple = 0x800080;
        static const int Red = 0xFF0000;
        static const int RosyBrown = 0xBC8F8F;
        static const int RoyalBlue = 0x4169E1;
        static const int SaddleBrown = 0x8B4513;
        static const int Salmon = 0xFA8072;
        static const int SandyBrown = 0xF4A460;
        static const int SeaGreen = 0x2E8B57;
        static const int SeaShell = 0xFFF5EE;
        static const int Sienna = 0xA0522D;
        static const int Silver = 0xC0C0C0;
        static const int SkyBlue = 0x87CEEB;
        static const int SlateBlue = 0x6A5ACD;
        static const int SlateGray = 0x708090;
        static const int Snow = 0xFFFAFA;
        static const int SpringGreen = 0x00FF7F;
        static const int SteelBlue = 0x4682B4;
        static const int Tan = 0xD2B48C;
        static const int Teal = 0x008080;
        static const int Thistle = 0xD8BFD8;
        static const int Tomato = 0xFF6347;
        static const int Turquoise = 0x40E0D0;
        static const int Violet = 0xEE82EE;
        static const int Wheat = 0xF5DEB3;
        static const int White = 0xFFFFFF;
        static const int WhiteSmoke = 0xF5F5F5;
        static const int Yellow = 0xFFFF00;
        static const int YellowGreen = 0x9ACD32;
	};
}}}