#include "lz4.h"

#define LLOG(x) // LOG(x)

namespace Upp {


void LZ4DecompressStream::Init()
{
	for(int i = 0; i < 16; i++)
		wb[i].Clear();
	ii = 0;
	count = 0;
	dlen = 0;
	pos = 0;
	eof = false;
	ptr = rdlim = NULL;
	xxh.Reset();
	ClearError();
}

bool LZ4DecompressStream::Open(Stream& in_)
{
	Init();

	in = &in_;
	String header_data = in->Get(7);
	if(header_data.GetCount() < 7) {
		SetError();
		return false;
	}

	if(Peek32le(~header_data) != LZ4F_MAGIC) {
		SetError();
		return false;
	}
	lz4hdr = header_data[4];
	if((lz4hdr & LZ4F_VERSIONMASK) != LZ4F_VERSION) {
		SetError();
		return false;
	}
	if(!(lz4hdr & LZ4F_BLOCKINDEPENDENCE)) { // dependent blocks not supported
		SetError();
		return false;
	}
	maxblock = header_data[5];
	maxblock = decode(maxblock & LZ4F_MAXSIZEMASK,
	                  LZ4F_MAXSIZE_64KB, 1024 * 64,
	                  LZ4F_MAXSIZE_256KB, 1024 * 256,
	                  LZ4F_MAXSIZE_1024KB, 1024 * 1024,
	                  LZ4F_MAXSIZE_4096KB, 1024 * 4096,
	                  -1);
	if(maxblock < 0) {
		SetError();
		return false;
	}
	
	if((lz4hdr & LZ4F_CONTENTSIZE) && in->Get(8).GetCount() != 8) {
		SetError();
		return false;
	}

	return true;
}

bool LZ4DecompressStream::Next()
{
	RTIMING("Next");
	if(ii < count) {
		pos += dlen;
		ptr = (byte *)~wb[ii].d;
		dlen = wb[ii].dlen;
		rdlim = ptr + dlen;
		ii++;
		return true;
	}
	return false;
}


void LZ4DecompressStream::Fetch()
{
	if(Next())
		return;
	if(eof)
		return;
#ifdef _MULTITHREADED
	CoWork co;
#endif
	bool   error = false;
	bool last = false;
	ii = 0;
	count = concurrent ? 16 : 1;
	for(int i = 0; i < count; i++) {
		Workblock& t = wb[i];
		int blksz = in->Get32le();
		if(blksz == 0) { // This is EOF
			last = true;
			count = i;
			break;
		}
		t.clen = blksz & 0x7fffffff;
		if(t.clen > maxblock) {
			SetError();
			return;
		}
		if(!t.c) {
			RTIMING("Alloc");
			t.c.Alloc(maxblock);
			t.d.Alloc(maxblock);
		}
		if(blksz & 0x80000000) { // block is not compressed
			t.dlen = t.clen;
			if(!in->GetAll(~t.d, t.clen)) {
				SetError();
				return;
			}
		}
		else {
			{ RTIMING("GetAll");
			if(!in->GetAll(~t.c, t.clen)) {
				SetError();
				return;
			}
			}
#ifdef _MULTITHREADED
			if(concurrent)
				co & [=, &error] {
					Workblock& t = wb[i];
					t.dlen = LZ4_decompress_safe(~t.c, ~t.d, t.clen, maxblock);
					CoWork::FinLock();
					if(t.dlen < 0)
						error = true;
				};
			else
#endif
			{
				RTIMING("LZ4 decompress");
				t.dlen = LZ4_decompress_safe(~t.c, ~t.d, t.clen, maxblock);
				if(t.dlen < 0)
					error = true;
			}
		}
		if(lz4hdr & LZ4F_BLOCKCHECKSUM)
			in->Get32le(); // just skip it
	}
#ifdef _MULTITHREADED
	if(concurrent)
		co.Finish();
#endif
	if(error)
		SetError();
	else {
		for(int i = 0; i < count; i++) {
			RTIMING("xxh");
			xxh.Put(wb[i].d, wb[i].dlen);
		}
		if(last) {
			if(in->Get32le() != xxh.Finish())
				SetError();
			eof = true;
		}
		Next();
	}
}

bool LZ4DecompressStream::IsOpen() const
{
	return in->IsOpen() && !IsError();
}

int LZ4DecompressStream::_Term()
{
	if(eof)
		return -1;
	Fetch();
	return ptr == rdlim ? -1 : *ptr;
}

int LZ4DecompressStream::_Get()
{
	if(eof)
		return -1;
	Fetch();
	return ptr == rdlim ? -1 : *ptr++;
}

dword LZ4DecompressStream::_Get(void *data, dword size)
{
	RTIMING("_Get");
	byte *t = (byte *)data;
	while(size) {
		if(IsError() || in->IsError() || ptr == rdlim && ii == count && eof)
			break;
		dword n = dword(rdlim - ptr);
		if(size < n) {
			RTIMING("memcpy1");
			memcpy(t, ptr, size);
			t += size;
			ptr += size;
			break;
		}
		else {
			{ RTIMING("memcpy2");
			memcpy(t, ptr, n); }
			t += n;
			size -= n;
			ptr = rdlim;
			Fetch();
		}
	}
	
	return dword(t - (byte *)data);
}

LZ4DecompressStream::LZ4DecompressStream()
{
	in = NULL;
	concurrent = false;
}

LZ4DecompressStream::~LZ4DecompressStream()
{
}

};
