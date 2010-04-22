/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"


using namespace Managed::Graphics::DirectWrite;

TextAnalysisSource::TextAnalysisSource(String^ text)
{
	_text = text;
	_native = new TextAnalysisSourceNative(this, text);
}

TextAnalysisSource::~TextAnalysisSource()
{
	this->!TextAnalysisSource();
}

TextAnalysisSource::!TextAnalysisSource()
{
	if(_native)
	{
		_native->Release();
		_native = NULL;
	}
}


HRESULT STDMETHODCALLTYPE TextAnalysisSourceNative::GetTextAtPosition(
	UINT32 textPosition,
	__out WCHAR const** textString,
	__out UINT32* textLength
	)
{
	if(textPosition >= _length)
	{
		*textString = NULL;
		*textLength = 0;
	}
	else
	{
		*textString = &_text[textPosition];
		*textLength = _length - textPosition;
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TextAnalysisSourceNative::GetTextBeforePosition(
	UINT32 textPosition,
	__out WCHAR const** textString,
	__out UINT32* textLength
	)
{
	if(textPosition == 0 || textPosition > _length)
	{
		*textString = NULL;
		*textLength = 0;
	}
	else
	{
		*textString = &_text[0];
		*textLength = textPosition;
	}
	return S_OK;
}

DWRITE_READING_DIRECTION STDMETHODCALLTYPE TextAnalysisSourceNative::GetParagraphReadingDirection()
{
	return (DWRITE_READING_DIRECTION)_managed->ReadingDirection;
}

HRESULT STDMETHODCALLTYPE TextAnalysisSourceNative::GetLocaleName(
	UINT32 textPosition,
	__out UINT32* textLength,
	__out_z WCHAR const** localeName
	)
{
	UInt32 length;
	System::Globalization::CultureInfo^ culture = _managed->GetCulture(textPosition, length);
	
	if(_localeName)
		LocalFree(_localeName);

	_localeName = (wchar_t*)Marshal::StringToHGlobalUni(culture->Name).ToPointer();

	*textLength = length;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TextAnalysisSourceNative::GetNumberSubstitution(
	UINT32 textPosition,
	__out UINT32* textLength,
	__out IDWriteNumberSubstitution** numberSubstitution
	)
{
	try
	{
		UInt32 length;
		NumberSubstitution^ numberSubstitutionManaged = _managed->GetNumberSubstitution(textPosition, length);
		*textLength = length;

		if(numberSubstitutionManaged != nullptr)
		{
			IDWriteNumberSubstitution* native = numberSubstitutionManaged->GetNative();
			if(native)
				native->AddRef();
			*numberSubstitution = native;
		}
		else
		{
			*numberSubstitution = NULL;
		}
	}
	catch(Exception^)
	{
		return E_FAIL;
	}
	return S_OK;
}


unsigned long STDMETHODCALLTYPE TextAnalysisSourceNative::AddRef()
{
    return InterlockedIncrement(&_refCount);
}

unsigned long STDMETHODCALLTYPE TextAnalysisSourceNative::Release()
{
    if (InterlockedDecrement(&_refCount) == 0)
    {
        delete this;
        return 0;
    }
    return _refCount;
}

HRESULT STDMETHODCALLTYPE TextAnalysisSourceNative::QueryInterface(IID const& riid, void** ppvObject)
{
	if(__uuidof(IDWriteTextAnalysisSource) == riid)
	{
		*ppvObject = static_cast<IDWriteTextAnalysisSource*>(this);
	}
	else if (__uuidof(IUnknown) == riid)
    {
        *ppvObject = static_cast<IUnknown*>(this);
    }
    else
    {
        *ppvObject = NULL;
        return E_FAIL;
    }
    return S_OK;
}
