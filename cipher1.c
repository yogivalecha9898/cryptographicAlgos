// Name: YOGI JAYPRAKASH VALECHA
// Roll No: 201951181


#include<stdio.h>

int main() {

    // ########################################## ENCRYPTION ##########################################

    // ############ PLAINTEXT ############

    int len_pt; //length of plaintext to avoid unnecessary characters
    char plaintext[100];
    printf("\n\nInput the length of plaintext: ");
    scanf("%d", &len_pt);
    printf("Input the plaintext: ");
    scanf("%s", plaintext);

    printf("\n#### About Plaintext ####\n");
    printf("Original plaintext: %s\n", plaintext);
    char mod_pt[100];
    int idx = 0;
    for(int i = 0; i < len_pt; i++) plaintext[i] = plaintext[i] == 'j' ? 'i':plaintext[i];
    for(int i = 0; i < len_pt; i++) {
        // Adjusting plaintexts text as per playfair cipher rules
        if(i+1 >= len_pt) {
            mod_pt[idx++] = plaintext[i];
            if(idx%2 == 1) mod_pt[idx++] = 'x';//here x is the filler character
            mod_pt[idx] = '\0';
        }
        else {
            if(plaintext[i] == plaintext[i+1]) {
                mod_pt[idx] = plaintext[i];
                mod_pt[idx+1] = 'x';
                idx += 2;
            } else mod_pt[idx++] = plaintext[i];
        }
    }
    len_pt = idx;
    printf("Modified plaintext: %s\n\n", mod_pt);



    // ############ KEY1 ############
    int len_k;
    char key[100];
    printf("Input the length of key: ");
    scanf("%d", &len_k);
    printf("Input the key: ");
    scanf("%s", key);
    printf("\n#### About Key ####\n");
    printf("Original key: %s\n", key);
    for(int i = 0; i < len_k; i++) key[i] = key[i] == 'j' ? 'i':key[i];
    printf("Modified key: %s\n\n", key);



    // ############ KEY MATRIX ############
    int vis[26], row = 0, col = 0, where[26][2];
    //where 2D array will remember where each character is placed in key matrix
    // will help in encryption and decryption of playfair cipher
    for(int i = 0; i < 26; i++) vis[i] = 0;
    char key_mat[5][5];
    for(int i = 0; i < len_k; i++) {
        if(vis[key[i]-'a'] == 0) {
            key_mat[row][col] = key[i];
            where[key[i]-'a'][0] = row;
            where[key[i]-'a'][1] = col;
            col++;
            if(col == 5) {
                col = 0;
                row++;
            }
            vis[key[i]-'a'] = 1;
        }
    }//The key is adjusted in the key matrix

    for(int i = 0; i < 26; i++) {
        if(i == 9) continue;
        if(vis[i] == 0) {
            key_mat[row][col] = (char)(i + 'a');
            where[i][0] = row;
            where[i][1] = col;
            col++;
            if(col == 5) {
                col = 0;
                row++;
            }
            vis[i] = 1;
        }
    }//remaining characters are being adjusted

    printf("\n#### About key matrix ####\n");
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            printf("%c", key_mat[i][j]);
        }
        printf("\n");
    }

    // ############ PLAYFAIR CIPHER ENCRYPTION ############
    char encrypt[100];
    for(int i = 0; i < len_pt; i += 2) {
        char cur = mod_pt[i]-'a', next = mod_pt[i+1]-'a';
        char target_cur = 'a', target_next = 'a';
        if(where[cur][0] == where[next][0]) {
            target_cur = key_mat[where[cur][0]][(where[cur][1] + 1)%5];
            target_next = key_mat[where[cur][0]][(where[next][1] + 1)%5];
        } else if(where[cur][1] == where[next][1]) {
            target_cur = key_mat[(where[cur][0] + 1)%5][where[cur][1]];
            target_next = key_mat[(where[next][0] + 1)%5][where[cur][1]];
        } else {
            target_cur = key_mat[where[cur][0]][where[next][1]];
            target_next = key_mat[where[next][0]][where[cur][1]];
        }
        encrypt[i] = target_cur;
        encrypt[i+1] = target_next;
        if(i+2 >= len_pt) encrypt[i+2] = '\0';
    }// following the rules for digraphs with help of key matrix
    printf("\nThe plaintext after encryption using Playfair cipher is: %s", encrypt);

    // ############ CAESAR CIPHER ENCRYPTION ############
    int caesar_key = 3;
    for(int i = 0; i < len_pt; i++) encrypt[i] = (char)((encrypt[i] - 'a' + caesar_key)%26 + 'a');
    printf("\nThe plaintext after encryption using Playfair and Caesar cipher is: %s", encrypt);


    // ############ AFFINE CIPHER ENCRYPTION ############
    int affine_key[2] = {5, 7};
    for(int i = 0; i < len_pt; i++) encrypt[i] = (char)((affine_key[0]*(encrypt[i]-'a') + affine_key[1])%26 + 'a');
    printf("\nThe plaintext after encryption using Playfair, Caesar and Affine cipher is: %s\n", encrypt);




    // ########################################## DECRYPTION ##########################################

    // Decryption of affine cipher

    // Finding the mulitplicative modulo inverse of 5 where mod = 26, since gcd(5, 26) = 1 it is possible

    int inverse = 1, count = 0;
    while(++count < 24) inverse = (inverse * affine_key[0])%26;
    //Fermat's little theorem 

    for(int i = 0; i < len_pt; i++) {
        int cur = encrypt[i] - 'a';
        int diff = cur - affine_key[1];
        diff = ((diff * inverse)%26 + 26)%26;
        encrypt[i] = (char)(diff + 'a');
    }
    printf("The cipher text after decryption using Affine cipher is: %s\n", encrypt);

    for(int i = 0; i < len_pt; i++) {
        encrypt[i] = (char)(((encrypt[i] - 'a' - 3)%26 + 26)%26 + 'a');
    }
    printf("The cipher text after decryption using Affine and Caesar cipher is: %s\n", encrypt);

    for(int i = 0; i < len_pt; i += 2) {
        char cur = encrypt[i]-'a', next = encrypt[i+1]-'a';
        char target_cur = 'a', target_next = 'a';
        if(where[cur][0] == where[next][0]) {
            target_cur = key_mat[where[cur][0]][((where[cur][1] - 1)%5 + 5)%5];
            target_next = key_mat[where[cur][0]][((where[next][1] - 1)%5 + 5)%5];
        } else if(where[cur][1] == where[next][1]) {
            target_cur = key_mat[((where[cur][0] - 1)%5 + 5)%5][where[cur][1]];
            target_next = key_mat[((where[next][0] - 1)%5 + 5)%5][where[cur][1]];
        } else {
            target_cur = key_mat[where[cur][0]][where[next][1]];
            target_next = key_mat[where[next][0]][where[cur][1]];
        }
        encrypt[i] = target_cur;
        encrypt[i+1] = target_next;
    }
    printf("The cipher text after decryption using Affine, Caesar and Playfair cipher is: %s\n", encrypt);
    return 0;
}
