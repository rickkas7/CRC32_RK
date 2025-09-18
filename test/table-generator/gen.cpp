#include <stdio.h>
#include <stdint.h>

// Global or static lookup table for CRC values
uint32_t crc_table[256];

void make_crc_table(void);

int main() {

    make_crc_table();

    printf("const uint32_t crcTable[256] = {\n    ");
    for(int ii = 0; ii < 256; ) {
        for(int kk = 0; kk < 8; kk++) {            
            printf("0x%08x", crc_table[ii++]);
            if (kk < 7) {
                printf(", ");
            }
        }
        if (ii < 256) {
            printf(",\n    ");
        }
        else {
            printf("\n");
        }
    }
    printf("};\n");

    return 0;
}



void make_crc_table(void) {
    uint32_t c;
    int n, k;
    uint32_t poly = 0xEDB88320L; // Standard CRC-32 polynomial

    for (n = 0; n < 256; n++) {
        c = (uint32_t)n;
        for (k = 0; k < 8; k++) {
            if (c & 1) {
                c = poly ^ (c >> 1);
            } else {
                c = c >> 1;
            }
        }
        crc_table[n] = c;
    }
}