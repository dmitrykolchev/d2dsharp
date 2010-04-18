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
	/// Specifies the type of DirectWrite factory object.
	/// DirectWrite factory contains internal state such as font loader registration and cached font data.
	/// In most cases it is recommended to use the shared factory object, because it allows multiple components
	/// that use DirectWrite to share internal DirectWrite state and reduce memory usage.
	/// However, there are cases when it is desirable to reduce the impact of a component,
	/// such as a plug-in from an untrusted source, on the rest of the process by sandboxing and isolating it
	/// from the rest of the process components. In such cases, it is recommended to use an isolated factory for the sandboxed
	/// component.
	/// </summary>
	public enum class DirectWriteFactoryType
	{
	    /// <summary>
	    /// Shared factory allow for re-use of cached font data across multiple in process components.
	    /// Such factories also take advantage of cross process font caching components for better performance.
	    /// </summary>
	    Shared = DWRITE_FACTORY_TYPE_SHARED,

	    /// <summary>
	    /// Objects created from the isolated factory do not interact with internal DirectWrite state from other components.
	    /// </summary>
	    Isolated = DWRITE_FACTORY_TYPE_ISOLATED
	};

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

	/// <summary>
	/// Typographic feature of text supplied by the font.
	/// </summary>
	public enum class FontFeatureTag
	{
		AlternativeFractions               = 0x63726661, // 'afrc'
		PetiteCapitalsFromCapitals       = 0x63703263, // 'c2pc'
		SmallCapitalsFromCapitals        = 0x63733263, // 'c2sc'
		ContextualAlternates               = 0x746c6163, // 'calt'
		CaseSensitiveForms                = 0x65736163, // 'case'
		GlyphCompositionDecomposition     = 0x706d6363, // 'ccmp'
		ContextualLigatures                = 0x67696c63, // 'clig'
		CapitalSpacing                     = 0x70737063, // 'cpsp'
		ContextualSwash                    = 0x68777363, // 'cswh'
		CursivePositioning                 = 0x73727563, // 'curs'
		Default                             = 0x746c6664, // 'dflt'
		Discretionary_Ligatures             = 0x67696c64, // 'dlig'
		ExpertForms                        = 0x74707865, // 'expt'
		Fractions                           = 0x63617266, // 'frac'
		FullWidth                          = 0x64697766, // 'fwid'
		HalfForms                          = 0x666c6168, // 'half'
		HalantForms                        = 0x6e6c6168, // 'haln'
		AlternateHalfWidth                = 0x746c6168, // 'halt'
		HistoricalForms                    = 0x74736968, // 'hist'
		HorizontalKanaAlternates          = 0x616e6b68, // 'hkna'
		HistoricalLigatures                = 0x67696c68, // 'hlig'
		HalfWidth                          = 0x64697768, // 'hwid'
		HojoKanjiForms                    = 0x6f6a6f68, // 'hojo'
		Jis04Forms                         = 0x3430706a, // 'jp04'
		Jis78Forms                         = 0x3837706a, // 'jp78'
		Jis83Forms                         = 0x3338706a, // 'jp83'
		Jis90Forms                         = 0x3039706a, // 'jp90'
		Kerning                             = 0x6e72656b, // 'kern'
		StandardLigatures                  = 0x6167696c, // 'liga'
		LiningFigures                      = 0x6d756e6c, // 'lnum'
		LocalizedForms                     = 0x6c636f6c, // 'locl'
		MarkPositioning                    = 0x6b72616d, // 'mark'
		MathematicalGreek                  = 0x6b72676d, // 'mgrk'
		MarkToMarkPositioning            = 0x6b6d6b6d, // 'mkmk'
		AlternateAnnotationForms          = 0x746c616e, // 'nalt'
		NlcKanjiForms                     = 0x6b636c6e, // 'nlck'
		OldStyleFigures                   = 0x6d756e6f, // 'onum'
		Ordinals                            = 0x6e64726f, // 'ordn'
		ProportionalAlternateWidth        = 0x746c6170, // 'palt'
		PetiteCapitals                     = 0x70616370, // 'pcap'
		ProportionalFigures                = 0x6d756e70, // 'pnum'
		ProportionalWidths                 = 0x64697770, // 'pwid'
		QuarterWidths                      = 0x64697771, // 'qwid'
		RequiredLigatures                  = 0x67696c72, // 'rlig'
		RubyNotationForms                 = 0x79627572, // 'ruby'
		StylisticAlternates                = 0x746c6173, // 'salt'
		ScientificInferiors                = 0x666e6973, // 'sinf'
		SmallCapitals                      = 0x70636d73, // 'smcp'
		SimplifiedForms                    = 0x6c706d73, // 'smpl'
		StylisticSet1                     = 0x31307373, // 'ss01'
		StylisticSet2                     = 0x32307373, // 'ss02'
		StylisticSet3                     = 0x33307373, // 'ss03'
		StylisticSet4                     = 0x34307373, // 'ss04'
		StylisticSet5                     = 0x35307373, // 'ss05'
		StylisticSet6                     = 0x36307373, // 'ss06'
		StylisticSet7                     = 0x37307373, // 'ss07'
		StylisticSet8                     = 0x38307373, // 'ss08'
		StylisticSet9                     = 0x39307373, // 'ss09'
		StylisticSet10                    = 0x30317373, // 'ss10'
		StylisticSet11                    = 0x31317373, // 'ss11'
		StylisticSet12                    = 0x32317373, // 'ss12'
		StylisticSet13                    = 0x33317373, // 'ss13'
		StylisticSet14                    = 0x34317373, // 'ss14'
		StylisticSet15                    = 0x35317373, // 'ss15'
		StylisticSet16                    = 0x36317373, // 'ss16'
		StylisticSet17                    = 0x37317373, // 'ss17'
		StylisticSet18                    = 0x38317373, // 'ss18'
		StylisticSet19                    = 0x39317373, // 'ss19'
		StylisticSet20                    = 0x30327373, // 'ss20'
		Subscript                           = 0x73627573, // 'subs'
		Superscript                         = 0x73707573, // 'sups'
		Swash                               = 0x68737773, // 'swsh'
		Titling                             = 0x6c746974, // 'titl'
		TraditionalNameForms              = 0x6d616e74, // 'tnam'
		TabularFigures                     = 0x6d756e74, // 'tnum'
		TraditionalForms                   = 0x64617274, // 'trad'
		ThirdWidths                        = 0x64697774, // 'twid'
		Unicase                             = 0x63696e75, // 'unic'
		SlashedZero                        = 0x6f72657a, // 'zero'
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct GlyphOffset
	{
	private:
		Single _advanceOffset;
		Single _ascenderOffset;
	public:
		GlyphOffset(Single advanceOffset, Single ascenderOffset)
		{
			_advanceOffset = advanceOffset;
			_ascenderOffset = ascenderOffset;
		}

		property Single AdvanceOffset { Single get() { return _advanceOffset; } }
		property Single AscenderOffset { Single get() { return _ascenderOffset; } }
	};

	public enum class LineSpacingMethod 
	{
		Default = DWRITE_LINE_SPACING_METHOD_DEFAULT,
		Uniform = DWRITE_LINE_SPACING_METHOD_UNIFORM 
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct LineSpacing
	{
	private:
		LineSpacingMethod _lineSpacingMethod;
		Single _height;
		Single _baseLine;
	public:
		LineSpacing(LineSpacingMethod lineSpacingMethod, Single height, Single baseLine)
		{
			_lineSpacingMethod = lineSpacingMethod;
			_height = height;
			_baseLine = baseLine;
		}

		property LineSpacingMethod Method
		{
			LineSpacingMethod get() { return _lineSpacingMethod; }
			void set(LineSpacingMethod value) { _lineSpacingMethod = value; }
		}

		property Single Height
		{
			Single get() { return _height; }
			void set(Single value) { _height = value; }
		}

		property Single BaseLine
		{
			Single get() { return _baseLine; }
			void set(Single value) { _baseLine = value; }
		}
	};

	public enum class TrimmingGranularity 
	{
		None = DWRITE_TRIMMING_GRANULARITY_NONE,
		Character = DWRITE_TRIMMING_GRANULARITY_CHARACTER,
		Word = DWRITE_TRIMMING_GRANULARITY_WORD 
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct Trimming
	{
	private:
		DWRITE_TRIMMING_GRANULARITY _granularity;
		UINT32                      _delimiter;
		UINT32                      _delimiterCount;
	public:
		Trimming(TrimmingGranularity granularity, UInt32 delimiter, UInt32 delimiterCount)
		{
			_granularity = (DWRITE_TRIMMING_GRANULARITY)granularity;
			_delimiter = delimiter;
			_delimiterCount = delimiterCount;
		}

		property TrimmingGranularity Granularity
		{
			TrimmingGranularity get() { return (TrimmingGranularity)_granularity; }
			void set(TrimmingGranularity value) { _granularity = (DWRITE_TRIMMING_GRANULARITY)value; }
		}

		property UInt32 Delimiter
		{
			UInt32 get() { return _delimiter; }
			void set(UInt32 value) { _delimiter = value; }
		}

		property UInt32 DelimiterCount
		{
			UInt32 get() { return _delimiterCount; }
			void set(UInt32 value) { _delimiterCount = value; }
		}
	};

	public enum class WordWrapping 
	{
		Wrap = DWRITE_WORD_WRAPPING_WRAP,
		NoWrap = DWRITE_WORD_WRAPPING_NO_WRAP 
	};

	public enum class PixelGeometry
	{
		Flat = DWRITE_PIXEL_GEOMETRY_FLAT,
		Rgb = DWRITE_PIXEL_GEOMETRY_RGB,
		Brg = DWRITE_PIXEL_GEOMETRY_BGR 
	};

	public enum class RenderingMode 
	{
		Default = DWRITE_RENDERING_MODE_DEFAULT,
		Aliased = DWRITE_RENDERING_MODE_ALIASED,
		CleartypeGdiClassic = DWRITE_RENDERING_MODE_CLEARTYPE_GDI_CLASSIC,
		CleartypeGdiNatural =  DWRITE_RENDERING_MODE_CLEARTYPE_GDI_NATURAL,
		CleartypeNatural = DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL,
		CleartypeNaturalSymmetric = DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL_SYMMETRIC,
		Outline = DWRITE_RENDERING_MODE_OUTLINE 
	};

	public enum class FontFaceType
	{
		Cff = DWRITE_FONT_FACE_TYPE_CFF,
		Truetype = DWRITE_FONT_FACE_TYPE_TRUETYPE,
		TruetypeCollection = DWRITE_FONT_FACE_TYPE_TRUETYPE_COLLECTION,
		Type1 = DWRITE_FONT_FACE_TYPE_TYPE1,
		Vector = DWRITE_FONT_FACE_TYPE_VECTOR,
		Bitmap = DWRITE_FONT_FACE_TYPE_BITMAP,
		Unknown = DWRITE_FONT_FACE_TYPE_UNKNOWN 
	};

	public enum class FontSimulations 
	{
		None		= 0x0000,
		Bold		= 0x0001,
		Oblique		= 0x0002 
	};

	public enum class NumberSubstitutionMethod 
	{
		FromCulture = DWRITE_NUMBER_SUBSTITUTION_METHOD_FROM_CULTURE,
		Contextual = DWRITE_NUMBER_SUBSTITUTION_METHOD_CONTEXTUAL,
		None = DWRITE_NUMBER_SUBSTITUTION_METHOD_NONE,
		National = DWRITE_NUMBER_SUBSTITUTION_METHOD_NATIONAL,
		Traditional = DWRITE_NUMBER_SUBSTITUTION_METHOD_TRADITIONAL 
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct InlineObjectMetrics
	{
	private:
		FLOAT _width;
		FLOAT _height;
		FLOAT _baseline;
		BOOL _supportsSideways;
	public:
		InlineObjectMetrics(Single width, Single height, Single baseline, Boolean supportsSideways)
		{
			_width = width;
			_height = height;
			_baseline = baseline;
			_supportsSideways = supportsSideways;
		}

		property Single Width
		{
			Single get() { return _width; }
		}

		property Single Height
		{
			Single get() { return _height; }
		}

		property Single Baseline
		{
			Single get() { return _baseline; }
		}

		property Boolean SupportsSideways
		{
			Boolean get() { return _supportsSideways != 0; }
		}
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct OverhangMetrics
	{
	private:
		FLOAT _left;
		FLOAT _top;
		FLOAT _right;
		FLOAT _bottom;
	public:
		OverhangMetrics(Single left, Single top, Single right, Single bottom)
		{
			_left = left;
			_top = top;
			_right = right;
			_bottom = bottom;
		}
		property Single Left
		{
			Single get() { return _left; }
		}

		property Single Top
		{
			Single get() { return _top; }
		}

		property Single Right
		{
			Single get() { return _right; }
		}

		property Single Bottom
		{
			Single get() { return _bottom; }
		}
	};

	public enum class BreakCondition 
	{
		Neutral         = 0,
		CanBreak        = 1,
		MayNotBreak     = 2,
		MustBreak       = 3 
	};


}}}