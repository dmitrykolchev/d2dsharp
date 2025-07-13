# Direct2D wrapper for Microsoft .Net Framework

You can try completely managed vesion of Direct2d .Net wrapper [Pictoris Project](https://github.com/dmitrykolchev/Pictoris)

Direct2D, DirectWrite and Windows Imaging wrappers for .Net. 
This library allows to access Direct2D, DirectWrite and Windows Imaging Windows API from applications written in C#, Visual Basic.

Aim of the project is to simplify development of managed Direct2D applications.

# Direct2D for Microsoft .Net Updates
## 2018-12-01
* **breaking changes** PointF, PointU, SizeF, SizeU, RectF, RectU structs now read only
* new sample added [Managed.D2DSharp.Lines](https://github.com/dmitrykolchev/d2dsharp/tree/master/D2DSharp/Managed.D2DSharp.Lines)
![lines screenshot](images/lines.png)

## 2016-12-11
* DeviceContext  class added (see How to render by using a Direct2D device context (https://msdn.microsoft.com/en-us/library/windows/desktop/hh780339(v=vs.85).aspx)
* new sample added [Managed.D2DSharp.DCSample](https://github.com/dmitrykolchev/d2dsharp/tree/master/D2DSharp/Managed.D2DSharp.DCSample)
![bezier screenshot](images/bezier.png)

## 2014-09-25
* Direct2D sample added (Managed.D2DSharp.StarField)
* DirectWrite sample added (Managed.D2DSharp.Marquee)
![starfield screenshot](images/stars.png)
## 2014-09-24
* bug: some files missing from the solution

## 2014-09-23
* color conversion functions added (Managed.Graphics.XMath)
* Matrix3x2 new methods added 
* bug fixes and improvements
* new sample added (Managed.D2DSharp.Bezier)
* the solution file updated to version 2013, now target framework is 4.51
