# RC4-File-Encryptor
A simple RC4-based file encryptor and decryptor implemented in C++.
# RC4 File Encryptor and Decryptor

  Objective

This project demonstrates file encryption and decryption using the RC4 stream cipher in C++.

   Files

* `rc4_encryptor.cpp` — Encrypts the contents of `file.txt` using RC4.
* `rc4_decryptor.cpp` — Decrypts the encrypted contents using the same RC4 key.

## How It Works

The encryptor:

1. Opens `file.txt` in binary mode.
2. Reads the file contents into memory.
3. Initializes the RC4 state using the Key Scheduling Algorithm (KSA).
4. Generates the RC4 keystream using the Pseudo-Random Generation Algorithm (PRGA).
5. XORs the file bytes with the keystream.
6. Writes the encrypted bytes back to `file.txt`.

The decryptor performs the same RC4 process using the same key. Because RC4 uses XOR, applying the same keystream to the encrypted data restores the original contents.

## Expected Result

After encryption, `file.txt` contains encrypted binary data that cannot be read as the original text.

After running the decryptor with the correct key, the original file contents are restored exactly.

## Verification

The encryption and decryption process was tested by encrypting `file.txt` and then decrypting it using the same key. The decrypted file matched the original contents.
