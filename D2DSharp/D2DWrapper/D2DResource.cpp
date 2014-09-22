/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "stdafx.h"

#include "D2DResource.h"

namespace Managed { namespace Graphics { namespace Direct2D 
{
	Direct2DFactory^ D2DResource::GetFactory()
	{
		ID2D1Factory *factory;
		GetNative<ID2D1Resource>()->GetFactory(&factory);
		return gcnew Direct2DFactory(factory);
	}
}}}
