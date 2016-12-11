/*
*
* Authors:
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*
*/
#pragma once

#include <d2d1helper.h>

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed {
	namespace Graphics {

		value struct Vector4;

		namespace Direct2D
		{
			public enum class FillMode
			{
				Alternate = 0,
				Winding = 1
			};

			public enum class PrimitiveBlend
			{
				SourceOver = D2D1_PRIMITIVE_BLEND_SOURCE_OVER,
				Copy = D2D1_PRIMITIVE_BLEND_COPY,
				Min = D2D1_PRIMITIVE_BLEND_MIN,
				Add = D2D1_PRIMITIVE_BLEND_ADD
			};

			public enum class BitmapInterpolationMode
			{
				NearestNeighbor = 0,
				Linear = 1
			};

			public enum class UnitMode
			{
				Dips = D2D1_UNIT_MODE_DIPS,
				Pixels = D2D1_UNIT_MODE_PIXELS
			};

			public enum class InterpolationMode
			{
				NearestNeighbor = D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
				Linear = D2D1_INTERPOLATION_MODE_LINEAR,
				Cubic = D2D1_INTERPOLATION_MODE_CUBIC,
				MultiSampleLinear = D2D1_INTERPOLATION_MODE_MULTI_SAMPLE_LINEAR,
				Anisotropic = D2D1_INTERPOLATION_MODE_ANISOTROPIC,
				HighQualityCubic = D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC
			};
			public enum class CompositeMode
			{
				SourceOver = D2D1_COMPOSITE_MODE_SOURCE_OVER,
				DestinationOver = D2D1_COMPOSITE_MODE_DESTINATION_OVER,
				SourceIn = D2D1_COMPOSITE_MODE_SOURCE_IN,
				DestinationIn = D2D1_COMPOSITE_MODE_DESTINATION_IN,
				SourceOut = D2D1_COMPOSITE_MODE_SOURCE_OUT,
				DestinationOut = D2D1_COMPOSITE_MODE_DESTINATION_OUT,
				SourceAtop = D2D1_COMPOSITE_MODE_SOURCE_ATOP,
				DestinationAtop = D2D1_COMPOSITE_MODE_DESTINATION_ATOP,
				Xor = D2D1_COMPOSITE_MODE_XOR,
				Plus = D2D1_COMPOSITE_MODE_PLUS,
				SourceCopy = D2D1_COMPOSITE_MODE_SOURCE_COPY,
				BoundedSourceCopy = D2D1_COMPOSITE_MODE_BOUNDED_SOURCE_COPY,
				MaskInvert = D2D1_COMPOSITE_MODE_MASK_INVERT
			};
			public enum class ExtendMode
			{
				Clamp = 0,
				Wrap = 1,
				Mirror = 2
			};

			public enum class Gamma
			{
				Gamma22 = 0,
				Gamma10 = 1
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
				SizeU(D2D1_SIZE_U sizeu) :
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
			internal:
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
				SizeF(D2D1_SIZE_F sizef) : _width(sizef.width), _height(sizef.height)
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

				property UINT32 X
				{
					UINT32 get() { return _left; }
					void set(UINT32 value) { _left = value; }
				}

				property UINT32 Y
				{
					UINT32 get() { return _top; }
					void set(UINT32 value) { _top = value; }
				}

				property UINT32 Width
				{
					UINT32 get() { return _right - _left; }
				}

				property UINT32 Height
				{
					UINT32 get() { return _bottom - _top; }
				}
			};


			[StructLayout(LayoutKind::Sequential)]
			public value struct RectF
			{
			private:
				static const FLOAT FloatMax = 3.402823466e+38F;
				FLOAT _left;
				FLOAT _top;
				FLOAT _right;
				FLOAT _bottom;
			public:
				static RectF FromLTBR(FLOAT left, FLOAT top, FLOAT right, FLOAT bottom)
				{
					RectF rect;
					rect._left = left;
					rect._top = top;
					rect._right = right;
					rect._bottom = bottom;
					return rect;
				}

				initonly static RectF Infinite = FromLTBR(-FloatMax, -FloatMax, FloatMax, FloatMax);

				RectF(FLOAT x, FLOAT y, FLOAT width, FLOAT height)
				{
					_left = x;
					_top = y;
					_right = x + width;
					_bottom = y + height;
				}

				RectF(PointF p1, PointF p2)
				{
					_left = p1.X;
					_top = p1.Y;
					_right = p2.X;
					_bottom = p2.Y;
				}

				RectF(PointF point, SizeF size)
				{
					_left = point.X;
					_top = point.Y;
					_right = _left + size.Width;
					_bottom = _top + size.Height;
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

				property FLOAT Determinant
				{
					FLOAT get() {
						return (_11 * _22) - (_12 * _21);
					}
				}

				property bool IsIdentity
				{
					bool get()
					{
						return _11 == 1.f && _12 == 0.f	&& _21 == 0.f && _22 == 1.f	&& _31 == 0.f && _32 == 0.f;
					}
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
					D2D1MakeRotateMatrix(angle, *(D2D1_POINT_2F*) &center, (D2D1_MATRIX_3X2_F*) &rotation);
					return rotation;
				}

				static Matrix3x2 Skew(FLOAT angleX, FLOAT angleY, PointF center)
				{
					Matrix3x2 skew;
					D2D1MakeSkewMatrix(angleX, angleY, *(D2D1_POINT_2F*) &center, (D2D1_MATRIX_3X2_F*) &skew);
					return skew;
				}

				property bool IsInvertible
				{
					bool get() {
						return Matrix3x2::IsInvertibleInternal(*this);
					}
				}

				bool Invert()
				{
					return Invert(*this);
				}

				void SetProduct(Matrix3x2 a, Matrix3x2 b)
				{
					_11 = a._11 * b._11 + a._12 * b._21;
					_12 = a._11 * b._12 + a._12 * b._22;
					_21 = a._21 * b._11 + a._22 * b._21;
					_22 = a._21 * b._12 + a._22 * b._22;
					_31 = a._31 * b._11 + a._32 * b._21 + b._31;
					_32 = a._31 * b._12 + a._32 * b._22 + b._32;
				}

				static Matrix3x2 operator*(Matrix3x2 a, Matrix3x2 b)
				{
					Matrix3x2 result;
					result.SetProduct(a, b);
					return result;
				}

				PointF TransformPoint(PointF point)
				{
					PointF result = PointF(
						point._x * _11 + point._y * _21 + _31,
						point._x * _12 + point._y * _22 + _32
						);
					return result;
				}

				static PointF operator*(PointF point, Matrix3x2 matrix)
				{
					return matrix.TransformPoint(point);
				}

				static bool operator == (Matrix3x2 m1, Matrix3x2 m2)
				{
					return m1.Equals(m2);
				}

				property FLOAT M11 { FLOAT get() { return _11; } }
				property FLOAT M12 { FLOAT get() { return _12; } }
				property FLOAT M21 { FLOAT get() { return _21; } }
				property FLOAT M22 { FLOAT get() { return _22; } }
				property FLOAT M31 { FLOAT get() { return _31; } }
				property FLOAT M32 { FLOAT get() { return _32; } }
			private:
				static bool IsInvertibleInternal([In]Matrix3x2% matrix)
				{
					pin_ptr<Matrix3x2> p = &matrix;
					return D2D1IsMatrixInvertible((const D2D1_MATRIX_3X2_F*) p) != 0;
				}

				static bool Invert([In, Out]Matrix3x2% matrix)
				{
					pin_ptr<Matrix3x2> p = &matrix;
					return D2D1InvertMatrix((D2D1_MATRIX_3X2_F*) p) != 0;
				}
			};

			[StructLayout(LayoutKind::Sequential)]
			public value struct Matrix4x4 {
			private:
				FLOAT _11, _12, _13, _14;
				FLOAT _21, _22, _23, _24;
				FLOAT _31, _32, _33, _34;
				FLOAT _41, _42, _43, _44;
			private:
				Matrix4x4(bool identity)
				{
					_11 = 1;
					_12 = 0;
					_13 = 0;
					_14 = 0;

					_21 = 0;
					_22 = 1;
					_23 = 0;
					_24 = 0;

					_31 = 0;
					_32 = 0;
					_33 = 1;
					_34 = 0;

					_41 = 0;
					_42 = 0;
					_43 = 0;
					_44 = 1;
				}
			public:
				initonly static Matrix4x4 Identity = Matrix4x4(true);

				Matrix4x4(
					FLOAT m11, FLOAT m12, FLOAT m13, FLOAT m14,
					FLOAT m21, FLOAT m22, FLOAT m23, FLOAT m24,
					FLOAT m31, FLOAT m32, FLOAT m33, FLOAT m34,
					FLOAT m41, FLOAT m42, FLOAT m43, FLOAT m44)
				{
					_11 = m11;
					_12 = m12;
					_13 = m13;
					_14 = m14;

					_21 = m21;
					_22 = m22;
					_23 = m23;
					_24 = m24;

					_31 = m31;
					_32 = m32;
					_33 = m33;
					_34 = m34;

					_41 = m41;
					_42 = m42;
					_43 = m43;
					_44 = m44;
				}

				static bool Equals(Matrix4x4 l, Matrix4x4 r)
				{
					return l._11 == r._11 && l._12 == r._12 && l._13 == r._13 && l._14 == r._14 &&
						l._21 == r._21 && l._22 == r._22 && l._23 == r._23 && l._24 == r._24 &&
						l._31 == r._31 && l._32 == r._32 && l._33 == r._33 && l._34 == r._34 &&
						l._41 == r._41 && l._42 == r._42 && l._43 == r._43 && l._44 == r._44;

				}

				static bool operator == (Matrix4x4 l, Matrix4x4 r)
				{
					return Equals(l, r);
				}

				static bool operator != (Matrix4x4 l, Matrix4x4 r)
				{
					return !Equals(l, r);
				}

				static Matrix4x4 Translation(FLOAT x, FLOAT y, FLOAT z)
				{
					Matrix4x4 translation;

					translation._11 = 1.0; translation._12 = 0.0; translation._13 = 0.0; translation._14 = 0.0;
					translation._21 = 0.0; translation._22 = 1.0; translation._23 = 0.0; translation._24 = 0.0;
					translation._31 = 0.0; translation._32 = 0.0; translation._33 = 1.0; translation._34 = 0.0;
					translation._41 = x;   translation._42 = y;   translation._43 = z;   translation._44 = 1.0;

					return translation;
				}

				static Matrix4x4 Scale(FLOAT x, FLOAT y, FLOAT z)
				{
					Matrix4x4 scale;

					scale._11 = x;   scale._12 = 0.0; scale._13 = 0.0; scale._14 = 0.0;
					scale._21 = 0.0; scale._22 = y;   scale._23 = 0.0; scale._24 = 0.0;
					scale._31 = 0.0; scale._32 = 0.0; scale._33 = z;   scale._34 = 0.0;
					scale._41 = 0.0; scale._42 = 0.0; scale._43 = 0.0; scale._44 = 1.0;

					return scale;
				}

				static Matrix4x4 RotationX(FLOAT degreeX)
				{
					FLOAT angleInRadian = degreeX * (3.141592654f / 180.0f);

					FLOAT sinAngle = 0.0;
					FLOAT cosAngle = 0.0;
					D2D1SinCos(angleInRadian, &sinAngle, &cosAngle);

					return Matrix4x4(
						1, 0, 0, 0,
						0, cosAngle, sinAngle, 0,
						0, -sinAngle, cosAngle, 0,
						0, 0, 0, 1
						);
				}

				static Matrix4x4 RotationY(FLOAT degreeY)
				{
					FLOAT angleInRadian = degreeY * (3.141592654f / 180.0f);

					FLOAT sinAngle = 0.0;
					FLOAT cosAngle = 0.0;
					D2D1SinCos(angleInRadian, &sinAngle, &cosAngle);

					return Matrix4x4(
						cosAngle, 0, -sinAngle, 0,
						0, 1, 0, 0,
						sinAngle, 0, cosAngle, 0,
						0, 0, 0, 1
						);
				}
				static Matrix4x4 RotationZ(FLOAT degreeZ)
				{
					FLOAT angleInRadian = degreeZ * (3.141592654f / 180.0f);

					FLOAT sinAngle = 0.0;
					FLOAT cosAngle = 0.0;
					D2D1SinCos(angleInRadian, &sinAngle, &cosAngle);

					return Matrix4x4(
						cosAngle, sinAngle, 0, 0,
						-sinAngle, cosAngle, 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1
						);
				}

				static Matrix4x4 RotationArbitraryAxis(FLOAT x, FLOAT y, FLOAT z, FLOAT degree)
				{
					// Normalize the vector represented by x, y, and z
					FLOAT magnitude = D2D1Vec3Length(x, y, z);
					x /= magnitude;
					y /= magnitude;
					z /= magnitude;

					FLOAT angleInRadian = degree * (3.141592654f / 180.0f);

					FLOAT sinAngle = 0.0;
					FLOAT cosAngle = 0.0;
					D2D1SinCos(angleInRadian, &sinAngle, &cosAngle);

					FLOAT oneMinusCosAngle = 1 - cosAngle;

					return Matrix4x4(
						1 + oneMinusCosAngle * (x * x - 1),
						z  * sinAngle + oneMinusCosAngle *  x * y,
						-y * sinAngle + oneMinusCosAngle *  x * z,
						0,

						-z * sinAngle + oneMinusCosAngle *  y * x,
						1 + oneMinusCosAngle * (y * y - 1),
						x  * sinAngle + oneMinusCosAngle *  y * z,
						0,

						y  * sinAngle + oneMinusCosAngle *  z * x,
						-x * sinAngle + oneMinusCosAngle *  z * y,
						1 + oneMinusCosAngle * (z * z - 1),
						0,

						0, 0, 0, 1
						);
				}
				static Matrix4x4 SkewX(FLOAT degreeX)
				{
					FLOAT angleInRadian = degreeX * (3.141592654f / 180.0f);

					FLOAT tanAngle = D2D1Tan(angleInRadian);

					return Matrix4x4(
						1, 0, 0, 0,
						tanAngle, 1, 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1
						);
				}
				static Matrix4x4 SkewY(FLOAT degreeY)
				{
					FLOAT angleInRadian = degreeY * (3.141592654f / 180.0f);

					FLOAT tanAngle = D2D1Tan(angleInRadian);

					return Matrix4x4(
						1, tanAngle, 0, 0,
						0, 1, 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1
						);
				}
				static Matrix4x4 PerspectiveProjection(FLOAT depth)
				{
					float proj = 0;

					if (depth > 0)
					{
						proj = -1 / depth;
					}

					return Matrix4x4(
						1, 0, 0, 0,
						0, 1, 0, 0,
						0, 0, 1, proj,
						0, 0, 0, 1
						);
				}
				property FLOAT Determinant
				{
					FLOAT get()
					{
						FLOAT minor1 = _41 * (_12 * (_23 * _34 - _33 * _24) - _13 * (_22 * _34 - _24 * _32) + _14 * (_22 * _33 - _23 * _32));
						FLOAT minor2 = _42 * (_11 * (_21 * _34 - _31 * _24) - _13 * (_21 * _34 - _24 * _31) + _14 * (_21 * _33 - _23 * _31));
						FLOAT minor3 = _43 * (_11 * (_22 * _34 - _32 * _24) - _12 * (_21 * _34 - _24 * _31) + _14 * (_21 * _32 - _22 * _31));
						FLOAT minor4 = _44 * (_11 * (_22 * _33 - _32 * _23) - _12 * (_21 * _33 - _23 * _31) + _13 * (_21 * _32 - _22 * _31));

						return minor1 - minor2 + minor3 - minor4;
					}
				}
				property bool IsIdentity
				{
					bool get() {
						return _11 == 1.f && _12 == 0.f && _13 == 0.f && _14 == 0.f
							&& _21 == 0.f && _22 == 1.f && _23 == 0.f && _24 == 0.f
							&& _31 == 0.f && _32 == 0.f && _33 == 1.f && _34 == 0.f
							&& _41 == 0.f && _42 == 0.f && _43 == 0.f && _44 == 1.f;
					}
				}
				void SetProduct(Matrix4x4 a, Matrix4x4 b)
				{
					_11 = a._11 * b._11 + a._12 * b._21 + a._13 * b._31 + a._14 * b._41;
					_12 = a._11 * b._12 + a._12 * b._22 + a._13 * b._32 + a._14 * b._42;
					_13 = a._11 * b._13 + a._12 * b._23 + a._13 * b._33 + a._14 * b._43;
					_14 = a._11 * b._14 + a._12 * b._24 + a._13 * b._34 + a._14 * b._44;

					_21 = a._21 * b._11 + a._22 * b._21 + a._23 * b._31 + a._24 * b._41;
					_22 = a._21 * b._12 + a._22 * b._22 + a._23 * b._32 + a._24 * b._42;
					_23 = a._21 * b._13 + a._22 * b._23 + a._23 * b._33 + a._24 * b._43;
					_24 = a._21 * b._14 + a._22 * b._24 + a._23 * b._34 + a._24 * b._44;

					_31 = a._31 * b._11 + a._32 * b._21 + a._33 * b._31 + a._34 * b._41;
					_32 = a._31 * b._12 + a._32 * b._22 + a._33 * b._32 + a._34 * b._42;
					_33 = a._31 * b._13 + a._32 * b._23 + a._33 * b._33 + a._34 * b._43;
					_34 = a._31 * b._14 + a._32 * b._24 + a._33 * b._34 + a._34 * b._44;

					_41 = a._41 * b._11 + a._42 * b._21 + a._43 * b._31 + a._44 * b._41;
					_42 = a._41 * b._12 + a._42 * b._22 + a._43 * b._32 + a._44 * b._42;
					_43 = a._41 * b._13 + a._42 * b._23 + a._43 * b._33 + a._44 * b._43;
					_44 = a._41 * b._14 + a._42 * b._24 + a._43 * b._34 + a._44 * b._44;
				}

				static Matrix4x4 operator*(Matrix4x4 a, Matrix4x4 b)
				{
					Matrix4x4 result;

					result.SetProduct(a, b);

					return result;
				}

				static Vector4 operator*(Matrix4x4 a, Vector4 v);
				static Vector4 operator*(Vector4 v, Matrix4x4 a);

				property FLOAT M11 { FLOAT get() { return _11; } }
				property FLOAT M12 { FLOAT get() { return _12; } }
				property FLOAT M13 { FLOAT get() { return _13; } }
				property FLOAT M14 { FLOAT get() { return _14; } }

				property FLOAT M21 { FLOAT get() { return _21; } }
				property FLOAT M22 { FLOAT get() { return _22; } }
				property FLOAT M23 { FLOAT get() { return _23; } }
				property FLOAT M24 { FLOAT get() { return _24; } }

				property FLOAT M31 { FLOAT get() { return _31; } }
				property FLOAT M32 { FLOAT get() { return _32; } }
				property FLOAT M33 { FLOAT get() { return _33; } }
				property FLOAT M34 { FLOAT get() { return _34; } }

				property FLOAT M41 { FLOAT get() { return _41; } }
				property FLOAT M42 { FLOAT get() { return _42; } }
				property FLOAT M43 { FLOAT get() { return _43; } }
				property FLOAT M44 { FLOAT get() { return _44; } }
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

			public enum class ThreadingMode
			{

				/// <summary>
				/// Resources may only be invoked serially.  Reference counts on resources are
				/// interlocked, however, resource and render target state is not protected from
				/// multi-threaded access
				/// </summary>
				SingleThreaded = 0,

				/// <summary>
				/// Resources may be invoked from multiple threads. Resources use interlocked
				/// reference counting and their state is protected.
				/// </summary>
				MultiThreaded = 1

			} D2D1_THREADING_MODE;

		}
	}
}