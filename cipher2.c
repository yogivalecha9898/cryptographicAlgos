// Name: Yogi JayPrakash Valecha
// ID: 201951181

#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>
#include<stdlib.h>
#include<string.h>

#define uchar unsigned char
#define uint unsigned int

#define rotateRight(a,b) (((a) >> (b)) | ((a) << (32-(b))))
#define doubleAddition(a,b,c) if (a > 0xffffffff - (c)) ++b; a += c;
#define rotateLeft(a,b) (((a) << (b)) | ((a) >> (32-(b))))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (rotateRight(x,2) ^ rotateRight(x,13) ^ rotateRight(x,22))
#define EP1(x) (rotateRight(x,6) ^ rotateRight(x,11) ^ rotateRight(x,25))
#define SIG0(x) (rotateRight(x,7) ^ rotateRight(x,18) ^ ((x) >> 3))
#define SIG1(x) (rotateRight(x,17) ^ rotateRight(x,19) ^ ((x) >> 10))

typedef struct {
	uint bitlen[2];
	uint state[8];
	uchar data[64];
	uint datalen;
} shaPointer;

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

uint k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

void transformingSHA256(shaPointer *ctx, uchar data[]) {
	uint a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];
	for (i = 0, j = 0; i < 16; i++, j += 4) m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
	for (; i < 64; i++) m[i] = m[i - 7] + SIG0(m[i - 15]) + SIG1(m[i - 2]) + m[i - 16];
	a = ctx -> state[0];
	b = ctx -> state[1];
	c = ctx -> state[2];
	d = ctx -> state[3];
	e = ctx -> state[4];
	f = ctx -> state[5];
	g = ctx -> state[6];
	h = ctx -> state[7];
	for (i = 0; i < 64; i++) {
		t1 = h + EP1(e) + k[i] + CH(e, f, g) + m[i];
		t2 = MAJ(a, b, c) + EP0(a);
		h = g;
		g = f;
		f = e;
		e = d;
        e += t1;
		d = c;
		c = b;
		b = a;
		a = t1;
        a += t2;
	}
	ctx -> state[0] += a;
	ctx -> state[1] += b;
	ctx -> state[2] += c;
	ctx -> state[3] += d;
	ctx -> state[4] += e;
	ctx -> state[5] += f;
	ctx -> state[6] += g;
	ctx -> state[7] += h;
}

void initializingSHA256(shaPointer *ctx) {
	ctx -> datalen = 0;
	ctx -> bitlen[0] = 0;
	ctx -> bitlen[1] = 0;
	ctx -> state[0] = 0x6a09e667;
	ctx -> state[1] = 0xbb67ae85;
	ctx -> state[2] = 0x3c6ef372;
	ctx -> state[3] = 0xa54ff53a;
	ctx -> state[4] = 0x510e527f;
	ctx -> state[5] = 0x9b05688c;
	ctx -> state[6] = 0x1f83d9ab;
	ctx -> state[7] = 0x5be0cd19;
}

void updatingSHA256(shaPointer *ctx, uchar data[], uint len) {
	for (uint i = 0; i < len; i++) {
		ctx -> data[ctx -> datalen] = data[i];
		ctx -> datalen++;
		if (ctx -> datalen == 64) {
			transformingSHA256(ctx, ctx -> data);
			doubleAddition(ctx -> bitlen[0], ctx -> bitlen[1], 512);
			ctx -> datalen = 0;
		}
	}
}

void finalizingSHA256(shaPointer *ctx, uchar hash[]) {
	uint i = ctx -> datalen;
	if (ctx->datalen < 56) {
		ctx->data[i++] = 0x80;
		while (i < 56) {
			ctx -> data[i] = 0x00;
            i++;
        }
	}
	else {
		ctx -> data[i] = 0x80;
        i++;
		while (i < 64)
			ctx -> data[i++] = 0x00;
		transformingSHA256(ctx, ctx->data);
		memset(ctx -> data, 0, 56);
	}
	doubleAddition(ctx -> bitlen[0], ctx -> bitlen[1], ctx -> datalen * 8);
	ctx->data[63] = ctx->bitlen[0];
	ctx->data[62] = ctx->bitlen[0] >> 8;
	ctx->data[61] = ctx->bitlen[0] >> 16;
	ctx->data[60] = ctx->bitlen[0] >> 24;
	ctx->data[59] = ctx->bitlen[1];
	ctx->data[58] = ctx->bitlen[1] >> 8;
	ctx->data[57] = ctx->bitlen[1] >> 16;
	ctx->data[56] = ctx->bitlen[1] >> 24;
	transformingSHA256(ctx, ctx->data);
	for (i = 0; i < 4; i++) {
		hash[i] = (ctx -> state[0] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4] = (ctx -> state[1] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8] = (ctx -> state[2] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (ctx -> state[3] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (ctx -> state[4] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 20] = (ctx -> state[5] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 24] = (ctx -> state[6] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 28] = (ctx -> state[7] >> (24 - i * 8)) & 0x000000ff;
	}
}

char* SHA256(char* data) {
	int strLen = strlen(data);
	shaPointer ctx;
	unsigned char hash[32];
	char* hashStr = malloc(65);
	strcpy(hashStr, "");
	initializingSHA256(&ctx);
	updatingSHA256(&ctx, data, strLen);
	finalizingSHA256(&ctx, hash);
	char s[3];
	for (int i = 0; i < 32; i++) {
		sprintf(s, "%02x", hash[i]);
		strcat(hashStr, s);
	}
	return hashStr;
}


int addInverse(int x, int mod) {
    return ((-x % mod) + mod) % mod; 
}

int mulInverse(int a, int m) {
    int x, y;
    int g = gcdExtended(a, m, &x, &y);
    int res = (x % m + m) % m;
    return res;
}

int gcdExtended(int a, int b, int* x, int* y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

int *expa(int *upd, int *p, int *q, int mod){
    //###################################### Formula for elliptic curve operation ###################################### 
    int rx = 0, ry = 1;
    if(p[0] != q[0] && p[1] != q[1]) {
        int m = (q[1] + addInverse(p[1], mod)) * (mulInverse(q[0] + addInverse(p[0], mod), mod)) % mod;
        rx = (m * m + addInverse(p[0] + q[0], mod)) % mod;
        ry = (p[1] + m * (rx + addInverse(p[0], mod))) % mod;
        ry = addInverse(ry, mod);
    } else if(p[0] == q[0] && p[1] == q[1]) {
        int m = ((3 * p[0] * p[0] + 1) * (mulInverse(2 * p[1], mod))) % mod;
        rx = ((m * m + addInverse(2 * p[0], mod))) % mod;
        ry = (p[1] + m * (rx + addInverse(p[0], mod))) % mod;
        ry = addInverse(ry, mod);
    }
    // printf("Rx = %d   Ry = %d\n", rx, ry);
    upd[0] = rx;
    upd[1] = ry;
    return upd;
}

int *ECC(int q, int *a) {
    ////###################################### Getting the alpha point //######################################
    for(int i = 0; i < q; i++) {
        for(int j = 0; j < q; j++) {
            int g = (i * i * i + 25 * i + 31) % q;
            int g1 = (j * j + addInverse(g, q) + q) % q;
            if(g1 == 0) {
                a[0] = i;
                a[1] = j;
                // printf("%d %d\n", i, j);
                return a;
            }
        }
    }
    return a; 
}

// Elliptic curve Defie Hellman key Exchange: ECDH
int *ECDH(int G[], int nA, int nB, int *a, int q) {
    int sec1[2] = {G[0], G[1]}, sec2[2] = {G[0], G[1]};
    //###################################### (naG)nb ######################################
    for(int i = 0; i < (nA + nB) % 7; i++) {
        int *now;
        now = expa(sec1, sec1, G, q);
        sec1[0] = now[0];
        sec1[1] = now[1];
    }
    printf("\n");
    //###################################### na(nbG) ######################################
    for(int i = 0; i < (nB + nA) % 7; i++) {
        int *now;
        now = expa(sec2, sec2, G, q);
        sec2[0] = now[0];
        sec2[1] = now[1];
    }
    G[0] = sec1[0];
    G[1] = sec1[1];
    return G;
}

char *binary(char *bin, int num) {
    //###################################### getting a binary value for a given decimal value ######################################
    for(int i = 0; i < 8; i++) bin[i] = '0';
    bin[8] = '\0';
    for(int i = 0; i < 8; i++) {
        int val = 1 << (8 - i - 1);
        if(val & num) bin[i] = '1';
    }
    return bin;
}

char reConvert(uint8_t val) {
    //###################################### For integer to character conversion ######################################
    if(val < 10) return (char) (val + '0');
    return (char) (val - 10 + 'a');
}

uint8_t convert(char val) {
    //###################################### For character to integer conversion ###################################### 
    if(val >= '0' && val <= '9') return val - '0';
    return val - 'a' + 10;
}

char *SHAed(char *ret, char *arr, uint8_t *pt) {
    //###################################### Generating the MAC ######################################
    char arrXor2[65], arrXor1[65];
    for(int i = 0; i < 64; i++) {
        arrXor1[i] = arr[i];
        arrXor2[i] = arr[i];
    }
    arrXor1[64] = '\0';
    arrXor2[64] = '\0';
    //###################################### KA/KB XOR 1 ###################################### 
    arrXor1[63] = reConvert(convert(arrXor1[63]) ^ 1);
    //###################################### KA/KB XOR 2 ###################################### 
    arrXor2[63] = reConvert(convert(arrXor2[63]) ^ 2);
    // printf("Xored: %s\n%s\n", arrXor1, arrXor2);

    char ptstr[65];
    //###################################### Getting the character array from hexadecimal array ######################################
    for(int i = 0; i < 32; i++) {
        uint8_t p1 = pt[i] >> 4, p2 = pt[i] & 15;
        // printf("%d %d\n", p1, p2);
        ptstr[2 * i] = reConvert(p1);
        ptstr[2 * i + 1] = reConvert(p2); 
    }
    // printf("concat: %s", ptstr);
    ptstr[64] = '\0';
    char arrConpt[129];
    //###################################### Concatenating the Xored KA/KB with Plaintext ######################################
    for(int i = 0; i < 64; i++) arrConpt[i] = arrXor2[i];
    for(int i = 64; i < 128; i++) arrConpt[i] = ptstr[i - 64];
    arrConpt[128] = '\0';
    // printf("%s\n", arrConpt);
    //###################################### Getting the inner hash value, SHA256
    char *arrpt = SHA256(arrConpt);
    // printf("%s\n", arrpt);
    //###################################### Again Concatenating ###################################### 
    for(int i = 0; i < 64; i++) arrConpt[i] = arrXor1[i];
    for(int i = 64; i < 128; i++) arrConpt[i] = arrpt[i - 64];
    arrpt = SHA256(arrConpt);
    // printf("%s", arrpt);
    //###################################### Returning the final hash value, SHA 256 ###################################### 
    ret = arrpt;
    return ret;
}

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

void encrypt(uint8_t pt[16], uint8_t rKeys[15][4][4]) {
    //###################################### Encrytion of AES ###################################### 
    uint8_t temp[4][4], key[4][8], plaintext[4][4];
    int idx = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            plaintext[j][i] = pt[idx++];
        }
    }

    // printf("\n\nOriginal Key or the m2\n");
    // for(int i = 0; i < 4; i++) {
    //     for(int j = 0; j < 8; j++) printf("%x ", key[i][j]);
    //     printf("\n");
    // }
    // printf("\n");

    // addkeys

    for(int itr = 0; itr <= 14; itr++) {

        if(itr > 0) {
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
            if(itr < 14) {
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
                plaintext[row][col] ^= rKeys[itr][row][col];
            }
        }
    }
    idx = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            pt[idx] = plaintext[j][i];
            idx++;
        }
    }
}

void decrypt(uint8_t pt[16], uint8_t rKeys[15][4][4]) {
    //###################################### Decryption of AES ######################################
    uint8_t plaintext[4][4];
    int idx = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            plaintext[j][i] = pt[idx++];
        }
    }
    for(int itr = 14; itr >= 0; itr--) {

        // Add keys.....................................
        for(int col = 0; col < 4; col++) {
            for(int row = 0; row < 4; row++) {
                plaintext[row][col] ^= rKeys[itr][row][col];
            }
        }

        if(itr > 0) {
            // inv Mixcolums 
            if(itr < 14) {
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
            uint8_t temp[4][4];
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
    idx = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            pt[idx] = plaintext[j][i];
            idx++;
        }
    }
}


uint8_t *getHex(char *arr, uint8_t *ret) {
    //###################################### Getting the hexadecimal array from a character array ######################################
    for(int i = 0; i < 64; i += 2) {
        int val1 = convert(arr[i]), val2 = convert(arr[i + 1]), two = 128, value = 0;
        for(int i = 0; i < 4; i++) {
            int val = 1 << (3 - i);
            if(val & val1) value += two;
            two >>= 1;
        }
        for(int i = 0; i < 4; i++) {
            int val = 1 << (3 - i);
            if(val & val2) value += two;
            two >>= 1;
        }
        ret[i / 2] = value;
    }
    return ret;
}

int main() {
    //###################################### Getting the point alpha ######################################
    int p = 101;
    int tempEcPoint[2];
    int *ecPoint = ECC(p, tempEcPoint);
    printf("The point alpha: %d %d\n", ecPoint[0], ecPoint[1]);

    int nA, nB;
    printf("Input nA and nB: ");
    scanf("%d%d", &nA, &nB);
    printf("Input for nA and nB: %d %d\n", nA, nB);

    //###################################### Getting the secret key ######################################
    int tempSecPoint[2];
    int *secKey = ECDH(ecPoint, nA, nB, tempSecPoint, p);
    printf("The secret key: %d %d\n\n", secKey[0], secKey[1]);

    char bin1[9], bin2[9], bin3[17];
    char *ans1 = binary(bin1, secKey[0]), *ans2 = binary(bin2, secKey[1]);
    for(int i = 0; i < 16; i++) bin3[i] = '0';
    bin3[16] = '\0';
    for(int i = 0; i < 8; i++) bin3[i] = bin1[i];
    for(int i = 8; i < 16; i++) bin3[i] = bin2[i - 8];
    // printf("%s\n", bin3);

    char *kA = SHA256(bin3), *kB = SHA256(bin3);

    uint8_t tempMA[32], mA[32], forNow[32];
    printf("Input the plaintext (mA):\n");
    for(int i = 0; i < 32; i++) scanf("%02x", &mA[i]);
    for(int i = 0; i < 32; i++) tempMA[i] = mA[i];

    //###################################### Key Scheduling part for the encryption ######################################
    uint8_t *ka = getHex(kA, forNow), rKeys[15][4][4], keyHere[4][8];
    int idx = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 4; j++) {
            keyHere[j][i] = ka[idx++];
        }
    }
    
    uint8_t keys[15][4][8];
    uint32_t con[14] = {(uint32_t) 0x01000000, (uint32_t) 0x02000000, (uint32_t) 0x04000000, (uint32_t) 0x08000000, (uint32_t) 0x10000000, (uint32_t) 0x20000000, (uint32_t) 0x40000000, (uint32_t) 0x80000000, (uint32_t) 0x1B000000, (uint32_t) 0x36000000, (uint32_t) 0x6C000000, (uint32_t) 0xD8000000, (uint32_t) 0xAB000000, (uint32_t) 0x4D000000, (uint32_t) 0x9A000000};
    for(int i = 0; i < 4; i++) for(int j = 0; j < 8; j++) keys[0][i][j] = keyHere[i][j];

    for(int itr = 1; itr <= 14; itr++) {
        uint8_t yahaKaTemp[4][1];
        int by = 24;
        for(int row = 0; row < 4; row++) {
            yahaKaTemp[row][0] = keys[itr - 1][(row + 1) % 4][7];
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
        for(int col = 1; col < 8; col++) {
            if(col == 4) {
                for(int row = 0; row < 4; row++) {
                    uint8_t curValue = keys[itr][row][3];
                    uint8_t rowValue = curValue >> 4, colValue = curValue & 15;
                    keys[itr][row][4] = sbox[rowValue][colValue] ^ keys[itr - 1][row][4];
                }
                continue;
            }
            for(int row = 0; row < 4; row++) {
                keys[itr][row][col] = keys[itr - 1][row][col] ^ keys[itr][row][col - 1];
            }
        }
    }

    idx = 0;
    for(int i = 0; i < 7; i++) {
        for(int row = 0;  row < 4; row++) {
            for(int col = 0; col < 4; col++) {
                rKeys[idx][row][col] = keys[i][row][col];
            }
        }
        for(int row = 0;  row < 4; row++) {
            for(int col = 4; col < 8; col++) {
                rKeys[idx + 1][row][col - 4] = keys[i][row][col];
            }
        }
        idx += 2;
    }

    for(int row = 0;  row < 4; row++) {
        for(int col = 0; col < 4; col++) {
            rKeys[14][row][col] = keys[7][row][col];
        }
    }

    //###################################### key scheduling done over here ######################################

    // Initialization vector = 0, initially
    //###################################### Encrytion in CBC mode ######################################
    uint8_t iv[16];
    for(int i = 0; i < 16; i++) iv[i] = 0;
    for(int itr = 0; itr < 2; itr++) {
        for(int i = 0; i < 16; i++) {
            mA[16 * itr + i] = mA[16 * itr + i] ^ iv[i];
        }
        uint8_t toSend[16];
        for(int i = 0; i < 16; i++) toSend[i] = mA[16 * itr + i];
        encrypt(toSend, rKeys);
        for(int i = 0; i < 16; i++) mA[16 * itr + i] = toSend[i];
        for(int i = 0; i < 16; i++) iv[i] = mA[16 * itr + i]; 
    }

    //###################################### Printing the cipher text ######################################
    printf("\n\nThe cipher text (or the encrypted plaintext) cA:\n");
    for(int i = 0; i < 32; i++) printf("%02x ", mA[i]);
    printf("\n\n");

    //###################################### Getting the MAC ###################################### 
    char ret[33];
    ret[32] = '\0';
    char *shaedA = SHAed(ret, kA, tempMA);
    char *shaedB = SHAed(ret, kB, tempMA);

    //###################################### Decryption in CBC mode ######################################
    // for(int i = 0; i < 16; i++) iv[i] = 0;
    uint8_t prev[48];
    for(int i = 16; i < 48; i++) prev[i] = mA[i - 16];
    for(int i = 0; i < 16; i++) prev[i] = 0;
    for(int itr = 0; itr < 2; itr++) {
        uint8_t toSend[16];
        for(int i = 0; i < 16; i++) {
            toSend[i] = mA[16 * itr + i];
        }
        decrypt(toSend, rKeys);
        for(int i = 0; i < 16; i++) mA[16 * itr + i] = toSend[i] ^ prev[16 * itr + i];
    }

    //###################################### Printing the cipher text ######################################
    printf("\nThe plain text (or the decrypted cipher text) mB:\n");
    for(int i = 0; i < 32; i++) printf("%02x ", mA[i]);
    printf("\n\n");

    //###################################### Final answer ###################################### 
    printf("\nkA: ");
    for(int i = 0; i < 64; i += 2) printf("%c%c ", kA[i], kA[i + 1]);
    printf("\nkB: ");
    for(int i = 0; i < 64; i += 2) printf("%c%c ", kB[i], kB[i + 1]);
    printf("\n\nmA: ");
    for(int i = 0; i < 32; i++) printf("%02x ", tempMA[i]);
    printf("\nmB: ");
    for(int i = 0; i < 32; i++) printf("%02x ", mA[i]);
    printf("\n\nmacA: ");
    for(int i = 0; i < 64; i += 2) printf("%c%c ", shaedA[i], shaedA[i + 1]);
    printf("\nmacB: ");
    for(int i = 0; i < 64; i += 2) printf("%c%c ", shaedB[i], shaedB[i + 1]);


    // printf("\n");
    // for(int itr = 0; itr < 15; itr++) {
    //     for(int row = 0; row < 4; row++) {
    //         for(int col = 0; col < 4; col++) printf("%02x ", rKeys[itr][row][col]);
    //         printf("\n");
    //     }
    //     printf("\n");
    // }
    return 0;
}