#include <string.h>
#include "common.h"

int bsize(int b) {
	if ((b & 0x80) == 0) return 1;
	if ((b & 0xE0) == 0xC0) return 2;		
	if ((b & 0xF0) == 0xE0) return 3;
	if ((b & 0xF8) == 0xF0) return 4;
	py_assert(0, "Invalid unicode byte found");
	return -1;
}

uint32 get_unicode_repr(uint32 b) {
	uint32 mask = (b <= 0x00EFBFBF) ? 0x000F0000 : 0x003F0000;
	uint32 c = ((b & 0x07000000) >> 6) |
		((b & mask) >> 4) |
		((b & 0x00003F00) >> 2) |
		(b & 0x0000003F);


	return c;
}

void unicode_to_ascii(char * out, char * bytes) {
	int i;
	int k = 0;
	int ts = strlen(bytes);
	if (ts == 0) {
		out[0] = 0;
		return;
	}
	unsigned char * bb = (unsigned char *) bytes;
	for (i = 0; i < ts; i++) {
		
		uint32 b = bb[i];
		int size = bsize(b);
		if (size > 1) {
			
			uint32 cc;
			if (size == 2) {
				cc = (b << 8) | (bb[i+1]);				
			}
			else if (size == 3) {
				cc = (b << 16) | (bb[i + 1] << 8) | (bb[i+2]);				
			}
			else if (size == 4) {
				cc = (b << 24) | (bb[i + 1] << 16) | (bb[i + 2] << 8) | bb[i+3];				
			}
			else {
				py_assert(0, "Unsupported unicode size: %i",size);
			}
			uint32 uni = get_unicode_repr(cc);
			if (uni > 0xFFFF) {
				sprintf(out + k, "\\U%.8X", (uint32)uni);
			}
			else {
				sprintf(out + k, "\\u%.4X", (uint32)uni);
			}
			k += strlen(out + k);
			
			
			i += (size-1);
		}
		else {
			out[k++] = b;
		}

		
	}
	out[k++] = 0;
	

}