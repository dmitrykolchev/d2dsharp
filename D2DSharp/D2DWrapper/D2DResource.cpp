#include "stdafx.h"

#include "D2DResource.h"

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	Direct2DFactory^ D2DResource::GetFactory()
	{
		ID2D1Factory *factory;
		GetNative()->GetFactory(&factory);
		return gcnew Direct2DFactory(factory);
	}
}}}
