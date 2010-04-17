/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace DirectWrite
{
	/// <summary>
	/// The font weight enumeration describes common values for degree of blackness or thickness of strokes of characters in a font.
	/// Font weight values less than 1 or greater than 999 are considered to be invalid, and they are rejected by font API functions.
	/// </summary>
	public enum class FontWeight
	{
	    /// <summary>
	    /// Predefined font weight : Thin (100).
	    /// </summary>
	    Thin = 100,

	    /// <summary>
	    /// Predefined font weight : Extra-light (200).
	    /// </summary>
	    ExtraLight = 200,

	    /// <summary>
	    /// Predefined font weight : Ultra-light (200).
	    /// </summary>
	    UltraLight = 200,

	    /// <summary>
	    /// Predefined font weight : Light (300).
	    /// </summary>
	    Light = 300,

	    /// <summary>
	    /// Predefined font weight : Normal (400).
	    /// </summary>
	    Normal = 400,

	    /// <summary>
	    /// Predefined font weight : Regular (400).
	    /// </summary>
	    Regular = 400,

	    /// <summary>
	    /// Predefined font weight : Medium (500).
	    /// </summary>
	    Medium = 500,

	    /// <summary>
	    /// Predefined font weight : Demi-bold (600).
	    /// </summary>
	    DemiBold = 600,

	    /// <summary>
	    /// Predefined font weight : Semi-bold (600).
	    /// </summary>
	    SemiBold = 600,

	    /// <summary>
	    /// Predefined font weight : Bold (700).
	    /// </summary>
	    Bold = 700,

	    /// <summary>
	    /// Predefined font weight : Extra-bold (800).
	    /// </summary>
	    ExtraBold = 800,

	    /// <summary>
	    /// Predefined font weight : Ultra-bold (800).
	    /// </summary>
	    UltraBold = 800,

	    /// <summary>
	    /// Predefined font weight : Black (900).
	    /// </summary>
	    Black = 900,

	    /// <summary>
	    /// Predefined font weight : Heavy (900).
	    /// </summary>
	    Heavy = 900,

	    /// <summary>
	    /// Predefined font weight : Extra-black (950).
	    /// </summary>
	    ExtraBlack = 950,

	    /// <summary>
	    /// Predefined font weight : Ultra-black (950).
	    /// </summary>
	    UltraBlack = 950
	};

	/// <summary>
	/// The font stretch enumeration describes relative change from the normal aspect ratio
	/// as specified by a font designer for the glyphs in a font.
	/// Values less than 1 or greater than 9 are considered to be invalid, and they are rejected by font API functions.
	/// </summary>
	public enum class FontStretch
	{
	    /// <summary>
	    /// Predefined font stretch : Not known (0).
	    /// </summary>
	    Undefined = 0,

	    /// <summary>
	    /// Predefined font stretch : Ultra-condensed (1).
	    /// </summary>
	    UltraCondensed = 1,

	    /// <summary>
	    /// Predefined font stretch : Extra-condensed (2).
	    /// </summary>
	    ExtraCondensed = 2,

	    /// <summary>
	    /// Predefined font stretch : Condensed (3).
	    /// </summary>
	    Condensed = 3,

	    /// <summary>
	    /// Predefined font stretch : Semi-condensed (4).
	    /// </summary>
	    SemiCondensed = 4,

	    /// <summary>
	    /// Predefined font stretch : Normal (5).
	    /// </summary>
	    Normal = 5,

	    /// <summary>
	    /// Predefined font stretch : Medium (5).
	    /// </summary>
	    Medium = 5,

	    /// <summary>
	    /// Predefined font stretch : Semi-expanded (6).
	    /// </summary>
	    SemiExpanded = 6,

	    /// <summary>
	    /// Predefined font stretch : Expanded (7).
	    /// </summary>
	    Expanded = 7,

	    /// <summary>
	    /// Predefined font stretch : Extra-expanded (8).
	    /// </summary>
	    ExtraExpanded = 8,

	    /// <summary>
	    /// Predefined font stretch : Ultra-expanded (9).
	    /// </summary>
	    UltraExpanded = 9
	};

	/// <summary>
	/// The font style enumeration describes the slope style of a font face, such as Normal, Italic or Oblique.
	/// Values other than the ones defined in the enumeration are considered to be invalid, and they are rejected by font API functions.
	/// </summary>
	public enum class FontStyle
	{
	    /// <summary>
	    /// Font slope style : Normal.
	    /// </summary>
	    Normal = DWRITE_FONT_STYLE_NORMAL,

	    /// <summary>
	    /// Font slope style : Oblique.
	    /// </summary>
	    Oblique = DWRITE_FONT_STYLE_OBLIQUE,

	    /// <summary>
	    /// Font slope style : Italic.
	    /// </summary>
	    Italic = DWRITE_FONT_STYLE_ITALIC
	};

	/// <summary>
	/// Alignment of paragraph text along the flow direction axis relative to the
	/// flow's beginning and ending edge of the layout box.
	/// </summary>
	public enum class ParagraphAlignment
	{
	    /// <summary>
	    /// The first line of paragraph is aligned to the flow's beginning edge of the layout box.
	    /// </summary>
	    Near = DWRITE_PARAGRAPH_ALIGNMENT_NEAR,

	    /// <summary>
	    /// The last line of paragraph is aligned to the flow's ending edge of the layout box.
	    /// </summary>
	    Far = DWRITE_PARAGRAPH_ALIGNMENT_FAR,

	    /// <summary>
	    /// The center of the paragraph is aligned to the center of the flow of the layout box.
	    /// </summary>
	    Center = DWRITE_PARAGRAPH_ALIGNMENT_CENTER
	};

	/// <summary>
	/// Alignment of paragraph text along the reading direction axis relative to 
	/// the leading and trailing edge of the layout box.
	/// </summary>
	public enum class TextAlignment
	{
	    /// <summary>
	    /// The leading edge of the paragraph text is aligned to the layout box's leading edge.
	    /// </summary>
	    Leading = DWRITE_TEXT_ALIGNMENT_LEADING,

	    /// <summary>
	    /// The trailing edge of the paragraph text is aligned to the layout box's trailing edge.
	    /// </summary>
	    Trailing = DWRITE_TEXT_ALIGNMENT_TRAILING,

	    /// <summary>
	    /// The center of the paragraph text is aligned to the center of the layout box.
	    /// </summary>
	    Center = DWRITE_TEXT_ALIGNMENT_CENTER
	};

	/// <summary>
	/// Direction for how reading progresses.
	/// </summary>
	public enum class ReadingDirection
	{
	    /// <summary>
	    /// Reading progresses from left to right.
	    /// </summary>
	    LeftToRight = DWRITE_READING_DIRECTION_LEFT_TO_RIGHT,

	    /// <summary>
	    /// Reading progresses from right to left.
	    /// </summary>
	    RightToLeft = DWRITE_READING_DIRECTION_RIGHT_TO_LEFT
	};


	/// <summary>
	/// Direction for how lines of text are placed relative to one another.
	/// </summary>
	public enum class FlowDirection
	{
	    /// <summary>
	    /// Text lines are placed from top to bottom.
	    /// </summary>
	    TopToBottom = DWRITE_FLOW_DIRECTION_TOP_TO_BOTTOM
	};

}}}