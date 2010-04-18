/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "stdafx.h"

#include "Geometry.h"
#include "SimplifiedGeometrySink.h"

using namespace Managed::Graphics::Direct2D;

void Geometry::CombineWithGeometry(
		Geometry^ inputGeometry, 
		CombineMode combineMode, 
		Matrix3x2 inputGeometryTransform, 
		FLOAT flatteningTolerance, 
		SimplifiedGeometrySink^ geometrySink)
{
	ComUtils::CheckResult(GetNative()->CombineWithGeometry(
		inputGeometry->GetNative(),
		(D2D1_COMBINE_MODE)combineMode,
		(D2D1_MATRIX_3X2_F *)&inputGeometryTransform,
		flatteningTolerance,
		geometrySink->GetNative()));
}

void Geometry::CombineWithGeometry(
	Geometry^ inputGeometry, 
	CombineMode combineMode, 
	Matrix3x2 inputGeometryTransform, 
	FLOAT flatteningTolerance, 
	ICustomSimplifiedGeometrySink^ customGeometrySink)
{
	CustomSimplifiedGeometrySink *pSink = new CustomSimplifiedGeometrySink(customGeometrySink);
	try
	{
		ComUtils::CheckResult(GetNative()->CombineWithGeometry(
			inputGeometry->GetNative(),
			(D2D1_COMBINE_MODE)combineMode,
			(D2D1_MATRIX_3X2_F *)&inputGeometryTransform,
			flatteningTolerance,
			static_cast<ID2D1SimplifiedGeometrySink*>(pSink)));
	}
	finally
	{
		pSink->Release();
	}
}

GeometryRelation Geometry::CompareWithGeometry(
		Geometry^ inputGeometry,
		Matrix3x2 inputGeometryTransform, 
		FLOAT flatteningTolerance)
{
	D2D1_GEOMETRY_RELATION relation;
	ComUtils::CheckResult(GetNative()->CompareWithGeometry(
		inputGeometry->GetNative(),
		(D2D1_MATRIX_3X2_F *)&inputGeometryTransform,
		flatteningTolerance,
		&relation));
	return (GeometryRelation)relation;
}

void Geometry::Outline(
	Matrix3x2 worldTransform, 
	FLOAT flatteningTolerance, 
	ICustomSimplifiedGeometrySink^ customGeometrySink)
{
	CustomSimplifiedGeometrySink *pSink = new CustomSimplifiedGeometrySink(customGeometrySink);
	try
	{
		ComUtils::CheckResult(GetNative()->Outline(
			(D2D1_MATRIX_3X2_F *)&worldTransform,
			flatteningTolerance,
			static_cast<ID2D1SimplifiedGeometrySink*>(pSink)));
	}
	finally
	{
		pSink->Release();
	}
}

void Geometry::Simplify(
	GeometrySimplificationOptions simplificationOptions, 
	Matrix3x2 worldTransform, 
	FLOAT flatteningTolerance, 
	ICustomSimplifiedGeometrySink^ customGeometrySink)
{
	CustomSimplifiedGeometrySink *pSink = new CustomSimplifiedGeometrySink(customGeometrySink);
	try
	{
		ComUtils::CheckResult(GetNative()->Simplify(
			(D2D1_GEOMETRY_SIMPLIFICATION_OPTION)simplificationOptions,
			(D2D1_MATRIX_3X2_F *)&worldTransform,
			flatteningTolerance,
			static_cast<ID2D1SimplifiedGeometrySink*>(pSink)));
	}
	finally
	{
		pSink->Release();
	}
}

void Geometry::Widen(
	FLOAT strokeWidth, 
	StrokeStyle^ strokeStyle, 
	Matrix3x2 worldTransform, 
	FLOAT flatteningTolerance, 
	ICustomSimplifiedGeometrySink^ customGeometrySink)
{
	CustomSimplifiedGeometrySink *pSink = new CustomSimplifiedGeometrySink(customGeometrySink);
	try
	{
		ID2D1StrokeStyle *pStrokeStyle = strokeStyle == nullptr ? NULL : strokeStyle->GetNative();

		ComUtils::CheckResult(GetNative()->Widen(
			strokeWidth,
			pStrokeStyle,
			(D2D1_MATRIX_3X2_F *)&worldTransform,
			flatteningTolerance,
			static_cast<ID2D1SimplifiedGeometrySink*>(pSink)));
	}
	finally
	{
		pSink->Release();
	}
}
