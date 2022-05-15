// Name: YOGI JAYPRAKASH VALECHA
// Roll No: 201951181


#include<stdio.h>

int ip[64] = {
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7,
    56, 48, 40, 32, 24, 16, 8, 0,
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6
};

int expansion[48] = {
    31, 0, 1, 2, 3, 4, 
    3, 4, 5, 6, 7, 8,
    7, 8, 9, 10, 11, 12,
    11, 12, 13, 14, 15, 16,
    15, 16, 17, 18, 19, 20,
    19, 20, 21, 22, 23, 24,
    23, 24, 25, 26, 27, 28,
    27, 28, 29, 30, 31, 0
};

int pc1[56] = { 
    56, 48, 40, 32, 24, 16, 8, 
    0, 57, 49, 41, 33, 25, 17, 
    9, 1, 58, 50, 42, 34, 26,
    18, 10, 2, 59, 51, 43, 35, 
    62, 54, 46, 38, 30, 22, 14, 
    8, 61, 53, 45, 37, 29, 21, 
    13, 5, 60, 52, 44, 36, 28, 
    20, 12, 4, 27, 19, 11, 3
};

int pc2[48] = {
    13, 16, 10, 23, 0, 4, 
    2, 27, 14, 5, 20, 9, 
    22, 18, 11, 3, 25, 7, 
    15, 6, 26, 19, 12, 1,
    40, 51, 30, 36, 46, 54, 
    29, 39, 50, 44, 32, 47, 
    43, 48, 38, 55, 33, 52, 
    45, 41, 49, 35, 28, 31
};

int sbox[8][4][16] = {
    { 
        { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
        { 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
        { 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
        { 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 } 
    },
    { 
        { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
        { 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
        { 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
        { 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 } 
    },
    { 
        { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
        { 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
        { 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
        { 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 } 
    },
    { 
        { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
        { 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
        { 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
        { 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 } 
    },
    { 
        { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
        { 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
        { 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
        { 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 } 
    },
    { 
        { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
        { 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
        { 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },
        { 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 } 
    },
    { 
        { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
        { 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
        { 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
        { 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 } 
    },
    { 
        { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
        { 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
        { 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
        { 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } 
    }
};

int perm[32] = { 
    15, 6, 19, 20, 
    28, 11, 27, 16, 
    0, 14, 22, 25, 
    4, 17, 30, 9, 
    1, 7, 23, 13, 
    31, 26, 2, 8, 
    18, 12, 29, 5,
    21, 10, 3, 24 
};

int ip_inv[64] = { 
    39, 7, 47, 15, 55, 23, 63, 31, 
    38, 6, 46, 14, 54, 22, 62, 30, 
    37, 5, 45, 13, 53, 21, 61, 29, 
    36, 4, 44, 12, 52, 20, 60, 28, 
    35, 3, 43, 11, 51, 19, 59, 27, 
    34, 2, 42, 10, 50, 18, 58, 26, 
    33, 1, 41, 9, 49, 17, 57, 25, 
    32, 0, 40, 8, 48, 16, 56, 24
};

// Above are the utilities for DES, because the algorithm says so...

unsigned long long getValue(int arr[], int what) {
    unsigned long long temp = 0;
    for(int i = 0; i < what; i++) {
        unsigned long long val = 1ULL << i;
        temp += val * arr[what - i - 1];
    }
    return temp;
} // Random function for binary to decimal conversion

int main() {
    unsigned long long plaintext, key;
    printf("Enter the plaintext that is between 0 to 2^64 - 1\n");
    scanf("%llu", &plaintext);
    printf("Enter the key that is between 0 to 2^56 - 1\n");
    scanf("%llu", &key);

    // Now I have the key and the plaintext, 
    // I will convert both of them to an integer array of 0 and 1 only so the calculations become easy
    // Basically converting them to binary representation

    int pt[64], k[56];
    for(int i = 0; i < 64; i++) {
        pt[i] = 0;
        if(i <= 55) k[i] = 0;
    }

    // The 0-th bit is on the right side while 63-th/55-th bit is on the left side
    for(int i = 0; i < 64; i++) {
        unsigned long long cur = (1ULL << i);
        pt[63 - i] = (cur & plaintext) ? 1 : 0;
    }

    for(int i = 0; i < 56; i++) {
        unsigned long long cur = (1ULL << i);
        k[55 - i] = (cur & key) ? 1 : 0;
    }

    // Applying the initial permutation on plaintext
    int temp_pt[64];
    for(int i = 0; i < 64; i++) temp_pt[i] = pt[ip[i]];
    for(int i = 0; i < 64; i++) pt[i] = temp_pt[i];
    // for(int i = 0; i < 64; i++) printf("%d", pt[i]);
    // printf("\n%llu\n", getValue(pt, 64));
    

    // First letting the key go through PC1
    int temp_k[56];
    for(int i = 0; i < 56; i++) temp_k[i] = k[pc1[i] - pc1[i] / 8]; // Compressing the to_be_64_bit_key to the given 56 bit key
    for(int i = 0; i < 56; i++) k[i] = temp_k[i];

    // I think generating the 16 keys first will help very much or no, maybe, but definitely helps understanding the code

    // Now the rounds
    int keys[16][48]; // For storing the keys generated in each of 16 rounds
    for(int i = 0; i < 16; i++) {

        // The shifting to the 'Left Circularly' phase of 28 and 28 bits of a 56 bit key
        int shift_by = 2;
        if(i == 0 || i == 1 || i == 8 || i == 15) shift_by = 1; // Because the algorithm says so
        for(int by = 1; by <= shift_by; by++) {
            int remember1 = k[0], remember2 = k[28];
            for(int j = 0; j < 27; j++) {
                k[j] = k[j + 1];
                k[j + 28] = k[j + 28 + 1];
            } 
            k[27] = remember1;
            k[55] = remember2;
        }
        // Shifting was done for C0 and D0 parallelly
        // Now going through PC2

        for(int j = 0; j < 48; j++) keys[i][j] = k[pc2[j]];
        // printf("%llu\n", getValue(keys[i], 48));
    }

    // Since all the 16 keys have been generated, now it is time to supply this keys to the round function
    for(int i = 0; i < 16; i++) {

        int exp[48], xored[48], sub[32], per[32], xor_again[32];
        
        // First the Second half bits of plaintext will go through the expansion 
        for(int j = 0; j < 48; j++) exp[j] = pt[32 + expansion[j]];

        // Xoring the expanded with the round key
        for(int j = 0; j < 48; j++) xored[j] = exp[j] ^ keys[i][j];

        // Now through the substitution
        for(int j = 0; j < 48; j += 6) {
            int box = j / 6;
            int row = 2 * xored[j] + xored[j + 5];
            int col = 8 * xored[j + 1] + 4 * xored[j + 2] + 2 * xored[j + 3] + xored[j + 4];
            int value = sbox[box][row][col];
            for(int itr = 0; itr < 4; itr++) {
                int val = 1 << itr;
                sub[3 - itr + ((j / 6) * 4)] = (val & value) ? 1 : 0;
            }
        }

        // Now through the permuation box
        for(int j = 0; j < 32; j++) per[j] = sub[perm[j]];

        // Here I have got the function value, now supplying it to Li to be xored again
        for(int j = 0; j < 32; j++) xor_again[j] = per[j] ^ pt[j];

        // Now getting the pt for the next round
        int temp_round_pt[64];
        // First giving the right half as it is to the next left half
        for(int j = 0; j < 32; j++) temp_round_pt[j] = pt[32 + j];
        // Next giving the xor_again value to the right half
        for(int j = 0; j < 32; j++) temp_round_pt[j + 32] = xor_again[j];
        for(int j = 0; j < 64; j++) pt[j] = temp_round_pt[j];

        if(i == 15) {
            // Swapping the left and right half bits, because the algorithm says so....
            for(int i = 0; i < 32; i++) {
                int temp_bit = pt[i];
                pt[i] = pt[i+32];
                pt[i+32] = temp_bit;
            }
        }

    }

    int final_pt[64];
    for(int i = 0; i < 64; i++) final_pt[i] = pt[ip_inv[i]];
    for(int i = 0; i < 64; i++) pt[i] = final_pt[i];
    printf("Encrypted plain text / Cipher text: %llu\n", getValue(pt, 64));
    // Done with the encryption
    



    // for the decryption
    for(int i = 0; i < 64; i++) temp_pt[i] = pt[ip[i]];
    for(int i = 0; i < 64; i++) pt[i] = temp_pt[i];
    for(int i = 0; i < 16; i++) {

        int exp[48], xored[48], sub[32], per[32], xor_again[32];
        
        // First the Second half bits of plaintext will go through the expansion 
        for(int j = 0; j < 48; j++) exp[j] = pt[32 + expansion[j]];

        // Xoring the expanded with the round key
        for(int j = 0; j < 48; j++) xored[j] = exp[j] ^ keys[15 - i][j];

        // Now through the substitution
        for(int j = 0; j < 48; j += 6) {
            int box = j / 6;
            int row = 2 * xored[j] + xored[j + 5];
            int col = 8 * xored[j + 1] + 4 * xored[j + 2] + 2 * xored[j + 3] + xored[j + 4];
            int value = sbox[box][row][col];
            for(int itr = 0; itr < 4; itr++) {
                int val = 1 << itr;
                sub[3 - itr + ((j / 6) * 4)] = (val & value) ? 1 : 0;
            }
        }

        // Now through the permuation box
        for(int j = 0; j < 32; j++) per[j] = sub[perm[j]];

        // Here I have got the function value, now supplying it to Li to be xored again
        for(int j = 0; j < 32; j++) xor_again[j] = per[j] ^ pt[j];

        // Now getting the pt for the next round
        int temp_round_pt[64];
        // First giving the right half as it is to the next left half
        for(int j = 0; j < 32; j++) temp_round_pt[j] = pt[32 + j];
        // Next giving the xor_again value to the right half
        for(int j = 0; j < 32; j++) temp_round_pt[j + 32] = xor_again[j];
        for(int j = 0; j < 64; j++) pt[j] = temp_round_pt[j];

        if(i == 15) {
            // Swapping the left and right half bits, because the algorithm says so....
            for(int i = 0; i < 32; i++) {
                int temp_bit = pt[i];
                pt[i] = pt[i+32];
                pt[i+32] = temp_bit;
            }
        }

    }

    for(int i = 0; i < 64; i++) final_pt[i] = pt[ip_inv[i]];
    for(int i = 0; i < 64; i++) pt[i] = final_pt[i];
    printf("Decrypted cipher text / Plain text: %llu\n", getValue(pt, 64));
    return 0;
}
