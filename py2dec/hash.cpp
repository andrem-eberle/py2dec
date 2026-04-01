#include "hash.h"



uint32 hash_fn(uint64 key) {
	uint32 size = 8;
	uint64 out = 2166136261;
	uint32 n = size / 8;
	int j;
	char * data = (char*)&key;
	
	for (uint32 i = 0; i < n; i++) {
		
		uint32 grain = 0;
		for (j = 0; j < 8; j++) {
			uint32 lshift = 8*j;			
			grain |= (uint64)data[j] << lshift;
		}
		out ^= grain;
		out *= 0xbf58476d1ce4e5b9;
		data += 8;
	}

	uint64 last = size & 0xff;
	for (j = size % 8; j > 0; j--) {
		uint32 lshift = (j) * 8;
		last |= (uint64)data[j-1] << lshift;
	}
	out = (out ^last) * 0xd6e8feb86659fd93;

	return (uint32)(out ^ out >> 32);
}