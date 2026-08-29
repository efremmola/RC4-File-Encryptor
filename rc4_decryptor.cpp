#include <iostream>
#include <cstdio>
#include <cstdlib>

void swapBytes(unsigned char &a, unsigned char &b)
{
    unsigned char temp = a;
    a = b;
    b = temp;
}

void KSA(unsigned char *S, unsigned char *key, int keyLength)
{
    int j = 0;

    for (int i = 0; i < 256; i++)
    {
        S[i] = i;
    }

    for (int i = 0; i < 256; i++)
    {
        j = (j + S[i] + key[i % keyLength]) % 256;
        swapBytes(S[i], S[j]);
    }
}

unsigned char *PRGA(unsigned char *S, unsigned int length)
{
    int i = 0;
    int j = 0;

    unsigned char *keystream =
        (unsigned char *)malloc(length);

    if (keystream == NULL)
    {
        return NULL;
    }

    for (unsigned int k = 0; k < length; k++)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;

        swapBytes(S[i], S[j]);

        keystream[k] =
            S[(S[i] + S[j]) % 256];
    }

    return keystream;
}

int main()
{
    // Open encrypted file for reading and writing
    FILE *file = fopen("file.txt", "r+b");

    if (file == NULL)
    {
        std::cout << "Error: Could not open file.txt\n";
        return 1;
    }

    // Find file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    std::cout << "Encrypted file size: "
              << file_size
              << " bytes\n";

    // Allocate memory
    unsigned char *buffer =
        (unsigned char *)malloc(file_size);

    if (buffer == NULL)
    {
        std::cout << "Error: Could not allocate memory\n";
        fclose(file);
        return 1;
    }

    // Read encrypted data
    size_t bytes_read =
        fread(buffer, 1, file_size, file);

    std::cout << "Bytes read: "
              << bytes_read
              << "\n";

    // SAME KEY used by the encryptor
    unsigned char key[] = {
        0x13, 0x37, 0xBE, 0xEF
    };

    // RC4 state array
    unsigned char S[256];

    // Initialize RC4 state
    KSA(S, key, sizeof(key));

    std::cout << "KSA completed successfully.\n";

    // Generate the same keystream
    unsigned char *keystream =
        PRGA(S, file_size);

    if (keystream == NULL)
    {
        std::cout << "Error: Could not generate keystream\n";
        free(buffer);
        fclose(file);
        return 1;
    }

    std::cout << "PRGA completed successfully.\n";

    // XOR encrypted data with keystream
    for (long i = 0; i < file_size; i++)
    {
        buffer[i] = buffer[i] ^ keystream[i];
    }

    std::cout << "Decryption completed successfully.\n";

    // Go back to beginning
    rewind(file);

    // Write decrypted data back
    size_t bytes_written =
        fwrite(buffer, 1, file_size, file);

    if (bytes_written == (size_t)file_size)
    {
        std::cout << "Original data restored to file.txt.\n";
    }
    else
    {
        std::cout << "Error: Could not write all decrypted bytes.\n";
    }

    // Clean up
    free(keystream);
    free(buffer);
    fclose(file);

    return 0;
}
