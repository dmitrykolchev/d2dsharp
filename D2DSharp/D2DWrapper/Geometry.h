/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "D2DCommon.h"
#include "D2DResource.h"
#include "Color.h"
#include "SimplifiedGeometrySink.h"

using namespace System;

namespace Managed { namespace Graphics { namespace Direct2D 
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
	interface class ICustomSimplifiedGeometrySink;

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

		void CombineWithGeometry(
			Geometry^ inputGeometry, 
			CombineMode combineMode, 
			Matrix3x2 inputGeometryTransform, 
			FLOAT flatteningTolerance, 
			ICustomSimplifiedGeometrySink^ customGeometrySink); 

		GeometryRelation CompareWithGeometry(
			Geometry^ inputGeometry,
			Matrix3x2 inputGeometryTransform, 
			FLOAT flatteningTolerance);

		Boolean FillContainsPoint(PointF point, Matrix3x2 worldTransform, FLOAT flatteningTolerance)
		{
			BOOL contains;

			ComUtils::CheckResult(GetNative()->FillContainsPoint(
				*(D2D1_POINT_2F*)&point,
				(D2D1_MATRIX_3X2_F *)&worldTransform,
				flatteningTolerance,
				&contains));

			return contains ? true : false;
		}

		Boolean StrokeContainsPoint(PointF point, FLOAT strokeWidth, StrokeStyle^ strokeStyle, Matrix3x2 worldTransform, FLOAT flatteningTolerance)
		{
			BOOL contains;
			ID2D1StrokeStyle *pStrokeStyle = strokeStyle == nullptr ? NULL : strokeStyle->GetNative();

			ComUtils::CheckResult(GetNative()->StrokeContainsPoint(
				*(D2D1_POINT_2F*)&point,
				strokeWidth,
				pStrokeStyle,
				(D2D1_MATRIX_3X2_F *)&worldTransform,
				flatteningTolerance,
				&contains));

			return contains ? true : false;
		}

		RectF GetBounds(Matrix3x2 worldTransform)
		{
			RectF bounds;

			ComUtils::CheckResult(GetNative()->GetBounds((D2D1_MATRIX_3X2_F *)&worldTransform, (D2D1_RECT_F*)&bounds));

			return bounds;
		}

		RectF GetWidenedBounds(FLOAT strokeWidth, StrokeStyle^ strokeStyle, Matrix3x2 worldTransform, FLOAT flatteningTolerance)
		{
			RectF bounds;
			
			ID2D1StrokeStyle *pStrokeStyle = strokeStyle == nullptr ? NULL : strokeStyle->GetNative();

			ComUtils::CheckResult(GetNative()->GetWidenedBounds(
				strokeWidth, 
				pStrokeStyle, 
				(D2D1_MATRIX_3X2_F *)&worldTransform,
				flatteningTolerance,
				(D2D1_RECT_F*)&bounds));
			
			return bounds;
		}

		void Outline(Matrix3x2 worldTransform, FLOAT flatteningTolerance, SimplifiedGeometrySink^ geometrySink)
		{
			ComUtils::CheckResult(GetNative()->Outline(
				(D2D1_MATRIX_3X2_F *)&worldTransform,
				flatteningTolerance,
				geometrySink->GetNative()));
		}

		void Outline(
			Matrix3x2 worldTransform, 
			FLOAT flatteningTolerance, 
			ICustomSimplifiedGeometrySink^ customGeometrySink);

		void Simplify(
			GeometrySimplificationOptions simplificationOptions, 
			Matrix3x2 worldTransform, FLOAT flatteningTolerance, SimplifiedGeometrySink^ geometrySink)
		{
			ComUtils::CheckResult(GetNative()->Simplify(
				(D2D1_GEOMETRY_SIMPLIFICATION_OPTION)simplificationOptions,
				(D2D1_MATRIX_3X2_F *)&worldTransform,
				flatteningTolerance,
				geometrySink->GetNative()));
		}

		void Simplify(
			GeometrySimplificationOptions simplificationOptions, 
			Matrix3x2 worldTransform, 
			FLOAT flatteningTolerance, 
			ICustomSimplifiedGeometrySink^ customGeometrySink);

		void Widen(FLOAT strokeWidth, StrokeStyle^ strokeStyle, Matrix3x2 worldTransform, FLOAT flatteningTolerance, SimplifiedGeometrySink^ geometrySink)
		{
			ID2D1StrokeStyle *pStrokeStyle = strokeStyle == nullptr ? NULL : strokeStyle->GetNative();

			ComUtils::CheckResult(GetNative()->Widen(
				strokeWidth,
				pStrokeStyle,
				(D2D1_MATRIX_3X2_F *)&worldTransform,
				flatteningTolerance,
				geometrySink->GetNative()));
		}

		void Widen(
			FLOAT strokeWidth, 
			StrokeStyle^ strokeStyle, 
			Matrix3x2 worldTransform, 
			FLOAT flatteningTolerance, 
			ICustomSimplifiedGeometrySink^ customGeometrySink);
	internal:
		ID2D1Geometry* GetNative() new
		{
			return (ID2D1Geometry*)D2DResource::GetNative();
		}
	};
}}}