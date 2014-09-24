/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"

#include "WicColorContext.h"

namespace Managed { namespace Graphics { namespace Imaging
{

	array<Byte>^ WicColorContext::GetProfileBytes()
	{
		IWICColorContext* pContext = GetNative<IWICColorContext>();
		UINT cbActual;
		ComUtils::CheckResult(pContext->GetProfileBytes(0, NULL, &cbActual));
		array<Byte>^ buffer = gcnew array<Byte>(cbActual);
		pin_ptr<Byte> pBuffer = &buffer[0];
		ComUtils::CheckResult(pContext->GetProfileBytes(cbActual, pBuffer, &cbActual));
		return buffer;
	}

}}}