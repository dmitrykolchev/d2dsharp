/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
* Copyright (C) 2010 Dmitry Kolchev
*
* This sourcecode is licenced under The GNU Lesser General Public License
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
* NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
* USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::IO;

namespace DykBits { namespace Runtime { namespace InteropServices
{
	ref class StreamWrapper:  public System::Runtime::InteropServices::ComTypes::IStream
	{
	public:
		StreamWrapper( Stream^ stream );
	protected:
		virtual void Clone( System::Runtime::InteropServices::ComTypes::IStream^% ppstm ) = IStream::Clone;
		virtual void Commit( int grfCommitFlags ) = IStream::Commit;
		virtual void CopyTo( System::Runtime::InteropServices::ComTypes::IStream^ pstm, __int64 cb, IntPtr pcbRead, IntPtr pcbWritten) = IStream::CopyTo;
		virtual void LockRegion( __int64 libOffset, __int64 cb, int dwLockType ) = IStream::LockRegion;
		virtual void Read( cli::array<unsigned char>^ pv, int cb, System::IntPtr pcbRead ) = IStream::Read;
		virtual void Revert( ) = IStream::Revert;
		virtual void Seek( __int64 dlibMove, int dwOrigin, IntPtr plibNewPosition ) = IStream::Seek;
		virtual void SetSize( __int64 libNewSize ) = IStream::SetSize;
		virtual void Stat( System::Runtime::InteropServices::ComTypes::STATSTG% pstatstg, int grfStatFlag ) = IStream::Stat;
		virtual void UnlockRegion( __int64 libOffset, __int64 cb, int dwLockType ) = IStream::UnlockRegion;
		virtual void Write( cli::array<unsigned char>^ pv, int cb, IntPtr pcbWritten ) = IStream::Write;
	private:
		Stream^ _stream;
	};
}}}