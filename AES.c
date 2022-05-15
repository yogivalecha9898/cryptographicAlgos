// Yogi JayPrakash Valecha
// 201951181


#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>

uint8_t sbox[16][16] = {
    {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
    {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
    {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
    {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
    {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
    {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
    {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
    {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
    {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
    {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
    {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
    {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}
};

uint8_t inv_sbox[16][16] = {
    {0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB},
    {0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB},
    {0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E},
    {0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25},
    {0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92},
    {0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84},
    {0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06},
    {0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B},
    {0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73},
    {0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E},
    {0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B},
    {0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4},
    {0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F},
    {0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF},
    {0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61},
    {0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D}
};

uint8_t times(uint8_t x) {
  return ((x<<1) ^ (((x>>7) & 1) * 0x1b));
}

uint8_t mul(uint8_t x, uint8_t y) {
    return (((y & 1) * x) ^
        ((y>>1 & 1) * times(x)) ^
        ((y>>2 & 1) * times(times(x))) ^
        ((y>>3 & 1) * times(times(times(x)))) ^
        ((y>>4 & 1) * times(times(times(times(x))))));
}

int main() {
    uint8_t plaintext[4][4],
            key[4][4] = {{0, 4, 8, 12},
                         {1, 5, 9, 13},
                         {2, 6, 10, 14},
                         {3, 7, 11, 15}}, 
            temp[4][4];

    uint8_t input[32];
    printf("Input the m1 || m2 that is the 256 bit input\n");
    scanf("%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx", &input[0], &input[1], &input[2], &input[3], &input[4], &input[5], &input[6], &input[7], &input[8], &input[9], &input[10], &input[11], &input[12], &input[13], &input[14], &input[15], &input[16], &input[17], &input[18], &input[19], &input[20], &input[21], &input[22], &input[23], &input[24], &input[25], &input[26], &input[27], &input[28], &input[29], &input[30], &input[31]);
    int idx = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            plaintext[j][i] = input[idx++];
        }
    }
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            key[j][i] = input[idx++];
        }
    }

    printf("Original Plaintext or the m1\n");
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) printf("%x ", plaintext[i][j]);
        printf("\n");
    }

    printf("\n\nOriginal Key or the m2\n");
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) printf("%x ", key[i][j]);
        printf("\n");
    }
    printf("\n");

    // addkeys
    uint8_t keys[11][4][4];
    uint32_t con[10] = {(uint32_t) 0x01000000, (uint32_t) 0x02000000, (uint32_t) 0x04000000, (uint32_t) 0x08000000, (uint32_t) 0x10000000, (uint32_t) 0x20000000, (uint32_t) 0x40000000, (uint32_t) 0x80000000, (uint32_t) 0x1B000000, (uint32_t) 0x36000000};
    for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) keys[0][i][j] = key[i][j];
    printf("\n");
    

    // ##################### Encryption using given key and plaintext ##################### 

    for(int itr = 0; itr <= 10; itr++) {

        // Generating the round keys for this round.....................................

        if(itr > 0) {
            uint8_t yahaKaTemp[4][1];
            int by = 24;
            for(int row = 0; row < 4; row++) {
                yahaKaTemp[row][0] = keys[itr - 1][(row + 1) % 4][3];
            }
            for(int row = 0; row < 4; row++) {
                uint8_t curValue = yahaKaTemp[row][0];
                uint8_t rowValue = curValue >> 4, colValue = curValue & 15;
                yahaKaTemp[row][0] = sbox[rowValue][colValue];
            }
            for(int row = 0; row < 4; row++) {
                uint8_t now = con[itr - 1] >> by;
                yahaKaTemp[row][0] ^= now;
                con[itr - 1] <<= 8;
            }
            for(int row = 0; row < 4; row++) {
                keys[itr][row][0] = keys[itr - 1][row][0] ^ yahaKaTemp[row][0];
            }
            for(int col = 1; col < 4; col++) {
                for(int row = 0; row < 4; row++) {
                    keys[itr][row][col] = keys[itr - 1][row][col] ^ keys[itr][row][col - 1];
                }
            }
            // Subbytes
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    uint8_t curValue = plaintext[i][j];
                    uint8_t rowValue = curValue >> 4, colValue = curValue & 15;
                    plaintext[i][j] = sbox[rowValue][colValue];
                }
            }

            // Shiftrows
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    temp[i][j] = plaintext[i][(j + i) % 4];
                }
            }
            for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) plaintext[i][j] = temp[i][j];

            // Mixcolums 
            if(itr < 10) {
                for(int j = 0; j < 4; j++) {
                    for(int i = 0; i < 4; i++) {
                        int one = plaintext[i][j] << 1, two = plaintext[(i + 1) % 4][j] << 1;

                        if((one >> 1) >> 7) one = one ^ 27;
                        if((two >> 1) >> 7) two = two ^ 27;

                        temp[i][j] = one;
                        temp[i][j] ^= two;
                        temp[i][j] ^= plaintext[(i + 1) % 4][j];
                        temp[i][j] ^= plaintext[(i + 2) % 4][j];
                        temp[i][j] ^= plaintext[(i + 3) % 4][j];
                    }
                }
                for(int i = 0; i < 4; i++) {
                    for(int j = 0; j < 4; j++) plaintext[i][j] = temp[i][j];
                }
            }

            // Generated the round key for this round.....................................
        }

        // Xoring the plaintext with the generated round key.....................................
        for(int col = 0; col < 4; col++) {
            for(int row = 0; row < 4; row++) {
                plaintext[row][col] ^= keys[itr][row][col];
            }
        }
    }

    for(int i = 0; i < 11; i++) {
        for(int row = 0; row < 4; row++) {
            for(int col = 0; col < 4; col++) printf("%02x ", keys[i][row][col]);
            printf("\n");
        }
        printf("\n");
    }

    // ##################### Cipher text #####################
    printf("\n##################### Cipher Text #####################\n");
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) printf("%02hhx", plaintext[j][i]);
    }

    int generated_plaintext[4][4];
    for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) generated_plaintext[i][j] = plaintext[i][j];
    

    // ##################### Decryption #####################   

    for(int itr = 10; itr >= 0; itr--) {

        // Add keys.....................................
        for(int col = 0; col < 4; col++) {
            for(int row = 0; row < 4; row++) {
                plaintext[row][col] ^= keys[itr][row][col];
            }
        }

        if(itr > 0) {
            // inv Mixcolums 
            if(itr < 10) {
                uint8_t a, b, c, d;
                for (int i = 0; i < 4; ++i) { 
                    a = plaintext[0][i];
                    b = plaintext[1][i];
                    c = plaintext[2][i];
                    d = plaintext[3][i];

                    plaintext[0][i] = mul(a, 0x0e) ^ mul(b, 0x0b) ^ mul(c, 0x0d) ^ mul(d, 0x09);
                    plaintext[1][i] = mul(a, 0x09) ^ mul(b, 0x0e) ^ mul(c, 0x0b) ^ mul(d, 0x0d);
                    plaintext[2][i] = mul(a, 0x0d) ^ mul(b, 0x09) ^ mul(c, 0x0e) ^ mul(d, 0x0b);
                    plaintext[3][i] = mul(a, 0x0b) ^ mul(b, 0x0d) ^ mul(c, 0x09) ^ mul(d, 0x0e);
                }
            }

            // inv Shiftrows
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    temp[i][j] = plaintext[i][((j - i) % 4 + 4) % 4];
                }
            }
            for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) plaintext[i][j] = temp[i][j];
            
            // inv Subbytes
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    uint8_t curValue = plaintext[i][j];
                    uint8_t rowValue = curValue >> 4, colValue = curValue & 15;
                    plaintext[i][j] = inv_sbox[rowValue][colValue];
                }
            }

        }
        
    }

    printf("\n\n\n##################### m1 / Plain Text obtained from decryption using the above cipher text or m1 from m2 #####################\n");
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) printf("%02hhx", plaintext[j][i]);
    }
    printf("\n\n");

    // ##################### Now decrypting using a random key #####################
    uint8_t random_key[4][4] = {
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1}
    }, random_keys[11][4][4];

    // Generating the round keys for the random key
    for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) random_keys[0][i][j] = random_key[i][j];
    for(int itr = 1; itr < 11; itr++) {
        uint8_t yahaKaTemp[4][1];
        int by = 24;
        for(int row = 0; row < 4; row++) {
            yahaKaTemp[row][0] = random_keys[itr - 1][(row + 1) % 4][3];
        }
        for(int row = 0; row < 4; row++) {
            uint8_t curValue = yahaKaTemp[row][0];
            uint8_t rowValue = curValue >> 4, colValue = curValue & 15;
            yahaKaTemp[row][0] = sbox[rowValue][colValue];
        }
        for(int row = 0; row < 4; row++) {
            uint8_t now = con[itr - 1] >> by;
            yahaKaTemp[row][0] ^= now;
            con[itr - 1] <<= 8;
        }
        for(int row = 0; row < 4; row++) {
            random_keys[itr][row][0] = random_keys[itr - 1][row][0] ^ yahaKaTemp[row][0];
        }
        for(int col = 1; col < 4; col++) {
            for(int row = 0; row < 4; row++) {
                random_keys[itr][row][col] = random_keys[itr - 1][row][col] ^ random_keys[itr][row][col - 1];
            }
        }
    }

    for(int itr = 10; itr >= 0; itr--) {

        // Add keys.....................................
        for(int col = 0; col < 4; col++) {
            for(int row = 0; row < 4; row++) {
                generated_plaintext[row][col] ^= random_keys[itr][row][col];
            }
        }

        if(itr > 0) {
            // inv Mixcolums 
            if(itr < 10) {
                uint8_t a, b, c, d;
                for (int i = 0; i < 4; ++i) { 
                    a = generated_plaintext[0][i];
                    b = generated_plaintext[1][i];
                    c = generated_plaintext[2][i];
                    d = generated_plaintext[3][i];

                    generated_plaintext[0][i] = mul(a, 0x0e) ^ mul(b, 0x0b) ^ mul(c, 0x0d) ^ mul(d, 0x09);
                    generated_plaintext[1][i] = mul(a, 0x09) ^ mul(b, 0x0e) ^ mul(c, 0x0b) ^ mul(d, 0x0d);
                    generated_plaintext[2][i] = mul(a, 0x0d) ^ mul(b, 0x09) ^ mul(c, 0x0e) ^ mul(d, 0x0b);
                    generated_plaintext[3][i] = mul(a, 0x0b) ^ mul(b, 0x0d) ^ mul(c, 0x09) ^ mul(d, 0x0e);
                }
            }

            // inv Shiftrows
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    temp[i][j] = generated_plaintext[i][((j - i) % 4 + 4) % 4];
                }
            }
            for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) generated_plaintext[i][j] = temp[i][j];
            
            // inv Subbytes
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    uint8_t curValue = generated_plaintext[i][j];
                    uint8_t rowValue = curValue >> 4, colValue = curValue & 15;
                    generated_plaintext[i][j] = inv_sbox[rowValue][colValue];
                }
            }

        }
        

    }
    printf("\n##################### m1' / Plain Text obtained using random key or for finding the preimage, using a different m2 / m2' #####################\n");
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) printf("%02hhx", generated_plaintext[j][i]);
    }
    printf("\n\n");



    for(int itr = 0; itr <= 10; itr++) {

        // Generating the round keys for this round.....................................

        if(itr > 0) {
            // Subbytes
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    uint8_t curValue = generated_plaintext[i][j];
                    uint8_t rowValue = curValue >> 4, colValue = curValue & 15;
                    generated_plaintext[i][j] = sbox[rowValue][colValue];
                }
            }

            // Shiftrows
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                    temp[i][j] = generated_plaintext[i][(j + i) % 4];
                }
            }
            for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) generated_plaintext[i][j] = temp[i][j];

            // Mixcolums 
            if(itr < 10) {
                for(int j = 0; j < 4; j++) {
                    for(int i = 0; i < 4; i++) {
                        int one = generated_plaintext[i][j] << 1, two = generated_plaintext[(i + 1) % 4][j] << 1;

                        if((one >> 1) >> 7) one = one ^ 27;
                        if((two >> 1) >> 7) two = two ^ 27;

                        temp[i][j] = one;
                        temp[i][j] ^= two;
                        temp[i][j] ^= generated_plaintext[(i + 1) % 4][j];
                        temp[i][j] ^= generated_plaintext[(i + 2) % 4][j];
                        temp[i][j] ^= generated_plaintext[(i + 3) % 4][j];
                    }
                }
                for(int i = 0; i < 4; i++) {
                    for(int j = 0; j < 4; j++) generated_plaintext[i][j] = temp[i][j];
                }
            }

            // Generated the round key for this round.....................................
        }

        // Xoring the plaintext with the generated round key.....................................
        for(int col = 0; col < 4; col++) {
            for(int row = 0; row < 4; row++) {
                generated_plaintext[row][col] ^= random_keys[itr][row][col];
            }
        }
    }

    printf("\n##################### Cipher text obtained using new plaintext / m1' from a random key / m2' #####################\n");
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) printf("%02hhx", generated_plaintext[j][i]);
    }
    printf("\n\n");
    return 0;
}