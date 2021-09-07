#include <stdio.h>
#include <string.h>
#define blockSize 20
#define firstFive 5

void make_new_name(char *new_name, char *original_name){
    new_name = strcat(new_name, original_name);
}

int length_of_password(char *password){
    return strlen(password);
}

int is_alpha(char c){
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        return 1;
    }
    return 0;
}

int is_digit(char c){
    if ((c >= '0') && (c <= '9')){
        return 1;
    }
    return 0;
}

int is_valid_password(char *password){
    int count = length_of_password(password);
    int minimumOneAlpha = 0, minimumOneDigit = 0, i = 0;
    while (password[i] != '\0'){
        char c = password[i];
        if (is_alpha(c))
            minimumOneAlpha++;
        if (is_digit(c))
            minimumOneDigit++;
        i++;
    }

    if (count >= 8 && count <= 15 && minimumOneAlpha > 0 && minimumOneDigit > 0)
        return 1;
    if (count < 8)
        printf("The password needs to have at least 8 characters.\n");
    if (minimumOneAlpha == 0)
        printf("The password needs to contain at least 1 alphabetical character.\n");
    if (minimumOneDigit == 0)
        printf("The password needs to contain at least 1 digit.\n");
    return 0;
}

void perform_XOR(char *input_filename, char *output_filename, char *password){
    FILE *file, *newFile;
    int passLength = length_of_password(password);
    char block[blockSize];
    int i, numBytes;

    file = fopen(input_filename, "rb");
    newFile = fopen(output_filename, "wb");

    do {
        numBytes = fread(block, 1, passLength, file);
        for (i=0; i<numBytes; i++){
            block[i] = block[i]^password[i];
        }
        // write the result of XOR to the output file
        fwrite(block, 1, numBytes, newFile);
    } while (numBytes == passLength);
    fclose(newFile); fclose(file);
}

void print_first_five(char *filename)
{
	FILE *file = fopen(filename, "rb");
	unsigned char block[5];

	fread(block, 1, 5, file);

	for (int i = 0; i < 5; i++){
		printf("%02x\n", block[i]);
    }

	fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3){
        printf("Usage: ./A2 filename password\n");
    }
    else {
        char* filename = argv[1];
        char* password = argv[2];
        char new_filename[50] = "new-";

        make_new_name(new_filename, filename);
        printf("New filename = %s\n", new_filename);
        printf("Password length = %d\n", length_of_password(password));

        if (is_valid_password(password) == 1){
            perform_XOR(filename, new_filename, password);
            print_first_five(new_filename);
        }
    }
}
