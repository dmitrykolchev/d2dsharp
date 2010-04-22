/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"


using namespace Managed::Graphics::DirectWrite;

Int32 LocalizedStrings::FindCulture(System::Globalization::CultureInfo^ culture)
{
	pin_ptr<const wchar_t> localeName = PtrToStringChars(culture->Name);
	UINT32 index;
	BOOL exists;

	ComUtils::CheckResult(
		GetNative()->FindLocaleName(
			localeName,
			&index,
			&exists));
	
	if(exists)
		return (Int32)index;
	return -1;
}

Int32 LocalizedStrings::Count::get()
{
	return (Int32)GetNative()->GetCount();
}

System::Globalization::CultureInfo^ LocalizedStrings::GetCulture(Int32 index)
{
	UINT32 length;
	ComUtils::CheckResult(GetNative()->GetLocaleNameLength(index, &length));

	wchar_t *localeName = new wchar_t[length + 1];
	try
	{
		ComUtils::CheckResult(GetNative()->GetLocaleName(index, localeName, length + 1));
		return gcnew System::Globalization::CultureInfo(gcnew String(localeName));
	}
	finally
	{
		delete localeName;
	}
}

String^ LocalizedStrings::default::get(Int32 index)
{
	UINT32 length;
	ComUtils::CheckResult(GetNative()->GetStringLength(index, &length));

	wchar_t *text = new wchar_t[length + 1];
	try
	{
		ComUtils::CheckResult(GetNative()->GetString(index, text, length + 1));
		return gcnew String(text);
	}
	finally
	{
		delete text;
	}
}
