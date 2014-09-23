#include <Windows.h>
#include <DirectXMath.h>
#include "D2DNative.h"

using namespace DirectX;

void WINAPI DxColorRgbToHsl(const FLOAT* rgb, FLOAT* hsl)
{
	XMStoreFloat4((XMFLOAT4*) hsl, XMColorRGBToHSL(XMLoadFloat4((const XMFLOAT4*) rgb)));
}

void WINAPI DxColorHslToRgb(const FLOAT* hsl, FLOAT* rgb)
{
	XMStoreFloat4((XMFLOAT4*) rgb, XMColorHSLToRGB(XMLoadFloat4((const XMFLOAT4*) hsl)));
}

void WINAPI DxColorRgbToHsv(const FLOAT* rgb, FLOAT* hsv)
{
	XMStoreFloat4((XMFLOAT4*) hsv, XMColorRGBToHSV(XMLoadFloat4((const XMFLOAT4*) rgb)));
}

void WINAPI DxColorHsvToRgb(const FLOAT* hsv, FLOAT* rgb)
{
	XMStoreFloat4((XMFLOAT4*) rgb, XMColorHSVToRGB(XMLoadFloat4((const XMFLOAT4*) hsv)));
}

void WINAPI DxColorRgbToXyz(const FLOAT* rgb, FLOAT* xyz)
{
	XMStoreFloat4((XMFLOAT4*) xyz, XMColorRGBToXYZ(XMLoadFloat4((const XMFLOAT4*) rgb)));
}

void WINAPI DxColorXyzToRgb(const FLOAT* xyz, FLOAT* rgb)
{
	XMStoreFloat4((XMFLOAT4*) rgb, XMColorXYZToRGB(XMLoadFloat4((const XMFLOAT4*) xyz)));
}

void WINAPI DxColorRgbToYuv(const FLOAT* rgb, FLOAT* yuv)
{
	XMStoreFloat4((XMFLOAT4*) yuv, XMColorRGBToYUV(XMLoadFloat4((const XMFLOAT4*) rgb)));
}

void WINAPI DxColorYuvToRgb(const FLOAT* yuv, FLOAT* rgb)
{
	XMStoreFloat4((XMFLOAT4*) rgb, XMColorYUVToRGB(XMLoadFloat4((const XMFLOAT4*) yuv)));
}
