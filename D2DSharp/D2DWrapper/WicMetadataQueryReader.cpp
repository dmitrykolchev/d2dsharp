/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"

#include "WicMetadataQueryReader.h"
#include "WicMetadataQueryWriter.h"

namespace Managed { namespace Graphics { namespace Imaging
{

	Guid WicMetadataQueryReader::ContainerFormat::get()
	{
		throw gcnew NotImplementedException();
	}

	String^ WicMetadataQueryReader::Location::get()
	{
		throw gcnew NotImplementedException();
	}

	Object^ WicMetadataQueryReader::GetMetadataByName(String^ name)
	{
		throw gcnew NotImplementedException();
	}

	void WicMetadataQueryWriter::RemoveMetadataByName(String^ name)
	{
		throw gcnew NotImplementedException();
	}

	void WicMetadataQueryWriter::SetMetadataByName(String^ name, Object^ value)
	{
		throw gcnew NotImplementedException();
	}

}}}
