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

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	public enum class FillMode
	{
		Alternate   = 0,
		Winding     = 1 
	};

	public enum class BitmapInterpolationMode  
	{
		NearestNeighbor   = 0,
		Linear            = 1 
	};

	/// <summary>
	/// The measuring method used for text layout.
	/// </summary>
	public enum class MeasuringMode
	{
	    /// <summary>
	    /// Text is measured using glyph ideal metrics whose values are independent to the current display resolution.
	    /// </summary>
	    Natural = DWRITE_MEASURING_MODE_NATURAL,

	    /// <summary>
	    /// Text is measured using glyph display compatible metrics whose values tuned for the current display resolution.
	    /// </summary>
	    GdiClassic = DWRITE_MEASURING_MODE_GDI_CLASSIC,

	    /// <summary>
	    /// Text is measured using the same glyph display metrics as text measured by GDI using a font
	    /// created with CLEARTYPE_NATURAL_QUALITY.
	    /// </summary>
	    GdiNatural = DWRITE_MEASURING_MODE_GDI_NATURAL

	};



	[StructLayout(LayoutKind::Sequential)]
	public value struct SizeU
	{
	private:
		UINT32 _width;
		UINT32 _height;
	internal:
		SizeU(D2D1_SIZE_U sizeu): 
			_width(sizeu.width), 
			_height(sizeu.height)
		{
		}
	public:
		SizeU(UINT32 width, UINT32 height)
		{
			_width = width;
			_height = height;
		}

		property UINT32 Width
		{
			UINT32 get() { return _width; }
			void set(UINT32 value) { _width = value; }
		}

		property UINT32 Height
		{
			UINT32 get() { return _height; }
			void set(UINT32 value) { _height = value; }
		}
	};


	[StructLayout(LayoutKind::Sequential)]
	public value struct PointF
	{
	private:
		FLOAT _x;
		FLOAT _y;
	public:
		PointF(FLOAT x, FLOAT y)
		{
			_x = x;
			_y = y;
		}

		property FLOAT X
		{
			FLOAT get() { return _x; }
			void set(FLOAT value) { _x = value; }
		}

		property FLOAT Y
		{
			FLOAT get() { return _y; }
			void set(FLOAT value) { _y = value; }
		}
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct PointU
	{
	private:
		UINT32 _x;
		UINT32 _y;
	public:
		PointU(UINT32 x, UINT32 y)
		{
			_x = x;
			_y = y;
		}

		property UINT32 X
		{
			UINT32 get() { return _x; }
			void set(UINT32 value) { _x = value; }
		}

		property UINT32 Y
		{
			UINT32 get() { return _y; }
			void set(UINT32 value) { _y = value; }
		}
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct SizeF
	{
	private:
		FLOAT _width;
		FLOAT _height;
	internal:
		SizeF(D2D1_SIZE_F sizef): _width(sizef.width), _height(sizef.height)
		{
		}
	public:
		SizeF(FLOAT width, FLOAT height)
		{
			_width = width;
			_height = height;
		}

		property FLOAT Width
		{
			FLOAT get() { return _width; }
			void set(FLOAT value) { _width = value; }
		}

		property FLOAT Height
		{
			FLOAT get() { return _height; }
			void set(FLOAT value) { _height = value; }
		}
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct RectU
	{
	private:
	    UINT32 _left;
	    UINT32 _top;
	    UINT32 _right;
	    UINT32 _bottom;
	public:
		RectU(UINT32 x, UINT32 y, UINT32 width, UINT32 height)
		{
			_left = x;
			_top = y;
			_right = x + width;
			_bottom = y + height;
		}
	};


	[StructLayout(LayoutKind::Sequential)]
	public value struct RectF
	{
	private:
	    FLOAT _left;
	    FLOAT _top;
	    FLOAT _right;
	    FLOAT _bottom;
	public:
		RectF(FLOAT x, FLOAT y, FLOAT width, FLOAT height)
		{
			_left = x;
			_top = y;
			_right = x + width;
			_bottom = y + height;
		}

	    property FLOAT X
		{
			FLOAT get() { return _left; }
			void set(FLOAT value) { _left = value; }
		}
	    property FLOAT Y
		{
			FLOAT get() { return _top; }
			void set(FLOAT value) { _top = value; }
		}

	    property FLOAT Width
		{
			FLOAT get() { return _right - _left; }
		}

	    property FLOAT Height
		{
			FLOAT get() { return _bottom - _top; }
		}

		property PointF TopLeft
		{
			PointF get() { return PointF(X, Y); }
		}

		property PointF BottomRight
		{
			PointF get() { return PointF(X + Width, Y + Height); }
		}

		property PointF Center
		{
			PointF get() { return PointF((_left + _right) / 2, (_top + _bottom) / 2); }
		}
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct RoundedRect
	{
	private:
		RectF _rect;
		FLOAT _radiusX;
		FLOAT _radiusY;
	public:
		RoundedRect(RectF rect, FLOAT radiusX, FLOAT radiusY)
		{
			_rect = rect;
			_radiusX = radiusX;
			_radiusY = radiusY;
		}

		property RectF Bounds
		{
			RectF get() { return _rect; }
			void set(RectF value) { _rect = value; }
		}

		property FLOAT RadiusX
		{
			FLOAT get() { return _radiusX; }
			void set(FLOAT value) { _radiusX = value; }
		}

		property FLOAT RadiusY
		{
			FLOAT get() { return _radiusY; }
			void set(FLOAT value) { _radiusY = value; }
		}
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct Ellipse
	{
	private:
		PointF _center;
		FLOAT _radiusX;
		FLOAT _radiusY;
	public:
		Ellipse(FLOAT x, FLOAT y, FLOAT radiusX, FLOAT radiusY)
		{
			_center = PointF(x, y);
			_radiusX = radiusX;
			_radiusY = radiusY;
		}

		Ellipse(RectF rect)
		{
			_center = rect.Center;
			_radiusX = rect.Width / 2;
			_radiusY = rect.Height / 2;
		}

		Ellipse(PointF center, FLOAT radiusX, FLOAT radiusY)
		{
			_center = center;
			_radiusX = radiusX;
			_radiusY = radiusY;
		}

		property PointF Center
		{
			PointF get() { return _center; }
			void set(PointF value) { _center = value; }
		}

		property FLOAT RadiusX
		{
			FLOAT get() { return _radiusX; }
			void set(FLOAT value) { _radiusX = value; }
		}

		property FLOAT RadiusY
		{
			FLOAT get() { return _radiusY; }
			void set(FLOAT value) { _radiusY = value; }
		}

		property RectF Bounds
		{
			RectF get()
			{
				return RectF(Center.X - RadiusX, Center.Y - RadiusY, RadiusX * 2, RadiusY * 2);
			}
		}
	};


	[StructLayout(LayoutKind::Sequential)]
	public value struct Matrix3x2
	{
	private:
		FLOAT _11;
		FLOAT _12;
		FLOAT _21;
		FLOAT _22;
		FLOAT _31;
		FLOAT _32;
	public:
		initonly static Matrix3x2 Identity = Matrix3x2(1., 0, 0, 1., 0, 0);

		Matrix3x2(FLOAT m11, FLOAT m12, FLOAT m21, FLOAT m22, FLOAT m31, FLOAT m32)
		{
			_11 = m11;
			_12 = m12;
			_21 = m21;
			_22 = m22;
			_31 = m31;
			_32 = m32;
		}

		static Matrix3x2 Translation(FLOAT x, FLOAT y)
		{
			return Matrix3x2(1, 0, 0, 1, x, y);
		}

		static Matrix3x2 Translation(SizeF size)
		{
			return Translation(size.Width, size.Height);
		}

		static Matrix3x2 Scale(SizeF size, PointF center)
	    {
	        Matrix3x2 scale;
	        scale._11 = size.Width; scale._12 = 0.0;
	        scale._21 = 0.0; scale._22 = size.Height;
	        scale._31 = center.X - size.Width * center.X;
	        scale._32 = center.Y - size.Height * center.Y;
	        return scale;
	    }

	    static Matrix3x2 Scale(FLOAT x, FLOAT y, PointF center)
	    {
	        return Scale(SizeF(x, y), center);
	    }

	    static Matrix3x2 Rotation(FLOAT angle, PointF center)
	    {
	        Matrix3x2 rotation;

	        D2D1MakeRotateMatrix(angle, *(D2D1_POINT_2F*)&center, (D2D1_MATRIX_3X2_F*)&rotation);

	        return rotation;
	    }
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct Triangle
	{
	private:
		PointF _point1;
		PointF _point2;
		PointF _point3;
	public:
		Triangle(PointF point1, PointF point2, PointF point3)
		{
			_point1 = point1;
			_point2 = point2;
			_point3 = point3;
		}
	};
}}}