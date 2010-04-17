// Copyright (c) Microsoft Corporation.  All rights reserved.

#include "stdafx.h"

#include "StreamWrapper.h"

using namespace Managed::Runtime::InteropServices;

StreamWrapper::StreamWrapper( Stream^ stream )
{
    if (stream == nullptr)
        throw gcnew ArgumentNullException("stream");
    _stream = stream;
}

void StreamWrapper::Clone( System::Runtime::InteropServices::ComTypes::IStream^% ppstm )
{ 
    ppstm = nullptr;
}

void StreamWrapper::Commit(int grfCommitFlags)
{
}

void StreamWrapper::CopyTo( System::Runtime::InteropServices::ComTypes::IStream^ pstm, __int64 cb, IntPtr pcbRead, IntPtr pcbWritten)
{
}

void StreamWrapper::LockRegion( __int64 libOffset, __int64 cb, int dwLockType )
{
}

void StreamWrapper::Read( cli::array<unsigned char>^ pv, int cb, System::IntPtr pcbRead)
{
    Marshal::WriteInt64( pcbRead, (System::Int64) _stream->Read(pv, 0, cb) );
}

void StreamWrapper::Revert( )
{
}

void StreamWrapper::Seek( __int64 dlibMove, int dwOrigin, IntPtr plibNewPosition)
{
    __int64* pNewPosition = (__int64*)plibNewPosition.ToPointer();
    __int64 newPosition = _stream->Seek( dlibMove, (System::IO::SeekOrigin)dwOrigin );
    if( pNewPosition != NULL )
        *(pNewPosition) = newPosition;
}

void StreamWrapper::SetSize(__int64 libNewSize)
{
}

void StreamWrapper::Stat( System::Runtime::InteropServices::ComTypes::STATSTG% pstatstg, int grfStatFlag )
{
    if( (grfStatFlag & STATFLAG_NONAME ) == 0 )
    {
        pstatstg.pwcsName = gcnew String( L"no name" );
    }
    pstatstg.type = STGTY_STREAM;
    pstatstg.cbSize = _stream->Length;
    pstatstg.mtime.dwHighDateTime = 0;
    pstatstg.mtime.dwLowDateTime = 0;
    pstatstg.atime.dwHighDateTime = 0;
    pstatstg.atime.dwLowDateTime = 0;
    pstatstg.grfMode = 0;
    pstatstg.grfLocksSupported = 0;
    pstatstg.clsid = Guid( 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 );
    pstatstg.grfStateBits = 0;
}

void StreamWrapper::UnlockRegion( __int64 libOffset, __int64 cb, int dwLockType )
{
}

void StreamWrapper::Write( cli::array<unsigned char>^ pv, int cb, IntPtr pcbWritten)
{
}
