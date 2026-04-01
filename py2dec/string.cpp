#include "common.h"

char regular_printable[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ ";

char printable_map[256][4] = {0,};

void init_strings() {
    int i;
    for(i=0;i<sizeof(regular_printable)-1;i++) {
        
        printable_map[regular_printable[i]][0] = regular_printable[i];
        printable_map[regular_printable[i]][1] = 0;
    }
    strcpy(printable_map['\''],"\\'");
    strcpy(printable_map['\t'],"\\t");
    strcpy(printable_map['\n'],"\\n");
    strcpy(printable_map['\r'],"\\r");   
	strcpy(printable_map['\\'], "\\\\");
    
}

void escape_regular_string(char * dst, char * str) {
    char * t = str;
    char * t2 = dst;
	if (!*t) {
		*t2 = 0;
		return;
	}

    while(*t) {
		if (*t == '\n') {
			strcpy(t2, "\\n");
		}		
        else if (printable_map[*t][0]) {
            strcpy(t2,printable_map[*t]);            
        }
        else {
            sprintf(t2,"\\x%.2x",*t);
        }
        t2 += strlen(t2);
        t++;
    }
}