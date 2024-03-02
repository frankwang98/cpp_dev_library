#include <iostream>
#include "hello.h"
#include "openssl_code.h"

using namespace std;

int main()
{
    cout << "=== Test common_cpp_so!" << endl;

    hello();
    int result = add(1, 2);
    cout << "add(1, 2) = " << result << endl;

    string str = "Hello, World!";

    // crc32
    uint32_t crc = calculateCRC32(str);
    std::cout << "CRC32: " << std::hex << crc << std::endl;

    // sha256
    std::string sha256 = calculateSHA256(str);
    std::cout << "SHA256: " << sha256 << std::endl;

    // sm3
    std::string sm3 = calculateSM3(str);
    std::cout << "SM3: " << sm3 << std::endl;

    // aes128
    std::string key = "uaYBHtznvMU45n43";
    std::string aes_ciphertext = aesEncrypt(str, key);
    std::cout << "aesEncrypt: " << aes_ciphertext << std::endl;
    std::string aes_decrypted = aesDecrypt(aes_ciphertext, key);
    std::cout << "aesDecrypt: " << aes_decrypted << std::endl;

    // sm4
    std::string iv = "1234567812345678";
    std::string sm4_ciphertext = sm4Encrypt(str, key, iv);
    std::cout << "sm4Encrypt: " << sm4_ciphertext << std::endl;
    std::string sm4_decrypted = sm4Decrypt(sm4_ciphertext, key, iv);
    std::cout << "sm4Decrypt: " << sm4_decrypted << std::endl;

    cout << "=== Test end!" << endl;

    return 0;
}