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
#include "D2DResource.h"
#include "Color.h"
#include "SimplifiedGeometrySink.h"

using namespace System;

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	public enum class CombineMode  
	{
		Union       = 0,
		Intersect   = 1,
		Xor         = 2,
		Exclude     = 3 
	};

	public enum class GeometryRelation 
	{
		Unknown        = 0,
		Disjoint       = 1,
		IsContained    = 2,
		Contains       = 3,
		Overlap        = 4 
	};

	public enum class GeometrySimplificationOptions 
	{
		CubicsAndLines   = 0,
		Lines            = 1 
	};


	ref class SimplifiedGeometrySink;

	public ref class Geometry: D2DResource
	{
	internal:
		Geometry(ID2D1Geometry* native): 
			 D2DResource(native)
		{
		}
	public:
		void CombineWithGeometry(
			Geometry^ inputGeometry, 
			CombineMode combineMode, 
			Matrix3x2 inputGeometryTransform, 
			FLOAT flatteningTolerance, 
			SimplifiedGeometrySink^ geometrySink); 
		GeometryRelation CompareWithGeometry(
			Geometry^ inputGeometry,
			Matrix3x2 inputGeometryTransform, 
			FLOAT flatteningTolerance);

		Boolean FillContainsPoint(PointF point, Matrix3x2 worldTransform, FLOAT flatteningTolerance)
		{
			BOOL contains;
			HRESULT hr = GetNative()->FillContainsPoint(
				*(D2D1_POINT_2F*)&point,
				(D2D1_MATRIX_3X2_F *)&worldTransform,
				flatteningTolerance,
				&contains);
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
			return contains ? true : false;
		}

		Boolean StrokeContainsPoint(PointF point, FLOAT strokeWidth, StrokeStyle^ strokeStyle, Matrix3x2 worldTransform, FLOAT flatteningTolerance)
		{
			BOOL contains;
			ID2D1StrokeStyle *pStrokeStyle = strokeStyle == nullptr ? NULL : strokeStyle->GetNative();
			HRESULT hr = GetNative()->StrokeContainsPoint(
				*(D2D1_POINT_2F*)&point,
				strokeWidth,
				pStrokeStyle,
				(D2D1_MATRIX_3X2_F *)&worldTransform,
				flatteningTolerance,
				&contains);
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
			return contains ? true : false;
		}

		RectF GetBounds(Matrix3x2 worldTransform)
		{
			RectF bounds;
			HRESULT hr = GetNative()->GetBounds((D2D1_MATRIX_3X2_F *)&worldTransform, (D2D1_RECT_F*)&bounds);
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
			return bounds;
		}

		RectF GetWidenedBounds(FLOAT strokeWidth, StrokeStyle^ strokeStyle, Matrix3x2 worldTransform, FLOAT flatteningTolerance)
		{
			RectF bounds;
			
			ID2D1StrokeStyle *pStrokeStyle = strokeStyle == nullptr ? NULL : strokeStyle->GetNative();

			HRESULT hr = GetNative()->GetWidenedBounds(
				strokeWidth, 
				pStrokeStyle, 
				(D2D1_MATRIX_3X2_F *)&worldTransform,
				flatteningTolerance,
				(D2D1_RECT_F*)&bounds);
			
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
			
			return bounds;
		}

		void Outline(Matrix3x2 worldTransform, FLOAT flatteningTolerance, SimplifiedGeometrySink^ geometrySink)
		{
			HRESULT hr = GetNative()->Outline(
				(D2D1_MATRIX_3X2_F *)&worldTransform,
				flatteningTolerance,
				geometrySink->GetNative());
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
		}

		void Simplify(
			GeometrySimplificationOptions simplificationOptions, 
			Matrix3x2 worldTransform, FLOAT flatteningTolerance, SimplifiedGeometrySink^ geometrySink)
		{
			HRESULT hr = GetNative()->Simplify(
				(D2D1_GEOMETRY_SIMPLIFICATION_OPTION)simplificationOptions,
				(D2D1_MATRIX_3X2_F *)&worldTransform,
				flatteningTolerance,
				geometrySink->GetNative());
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
		}

		void Widen(FLOAT strokeWidth, StrokeStyle^ strokeStyle, Matrix3x2 worldTransform, FLOAT flatteningTolerance, SimplifiedGeometrySink^ geometrySink)
		{
			ID2D1StrokeStyle *pStrokeStyle = strokeStyle == nullptr ? NULL : strokeStyle->GetNative();

			HRESULT hr = GetNative()->Widen(
				strokeWidth,
				pStrokeStyle,
				(D2D1_MATRIX_3X2_F *)&worldTransform,
				flatteningTolerance,
				geometrySink->GetNative());

			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
		}
	internal:
		ID2D1Geometry* GetNative() new
		{
			return (ID2D1Geometry*)D2DResource::GetNative();
		}
	};
}}}