#include "../src/cryptoutils/cryptoutils.hpp"
#include <iostream>
#include <time.h>

int main(int argc, char** argv)
{
    clock_t start,finish;
	start = clock();

    std::string srcText = "123456";

    // crc32
    uint32_t crc = calculateCRC32(srcText);
    std::cout << "CRC32: " << std::hex << crc << std::endl;
    // uLong crc32 = calculateCRC32(srcText);
    // std::cout << "CRC32: " << std::hex << crc32 << std::endl;

    // sha256
    std::string sha256 = calculateSHA256(srcText);
    std::cout << "SHA256: " << sha256 << std::endl;

    // sm3
    std::string sm3 = calculateSM3(srcText);
    std::cout << "SM3: " << sm3 << std::endl;

    // aes128
    std::string key = "uaYBHtznvMU45n43";
    std::string aes_ciphertext = aesEncrypt(srcText, key);
    std::cout << "aesEncrypt: " << aes_ciphertext << std::endl;
    std::string aes_decrypted = aesDecrypt(aes_ciphertext, key);
    std::cout << "aesDecrypt: " << aes_decrypted << std::endl;

    // sm4
    std::string iv = "1234567812345678";
    std::string sm4_ciphertext = sm4Encrypt(srcText, key, iv);
    std::cout << "sm4Encrypt: " << sm4_ciphertext << std::endl;
    std::string sm4_decrypted = sm4Decrypt(sm4_ciphertext, key, iv);
    std::cout << "sm4Decrypt: " << sm4_decrypted << std::endl;

    // 可配置加密方法
    std::string ciphertext = encrypt(srcText, key, 2);
    std::cout << "encrypt: " << ciphertext << std::endl;
    std::string decrypted = decrypt(ciphertext, key, 2);
    std::cout << "decrypt: " << decrypted << std::endl;

    finish = clock();
	std::cout << "the time cost is: " << double(finish - start) / CLOCKS_PER_SEC << std::endl;

    // base64
    char buf[20] = "Hello world!";
    std::string base64Str = Base64::encode(buf, sizeof(buf)); 
    std::cout << base64Str << std::endl;
    std::string buf2 = Base64::decode(base64Str);
    std::cout << buf2 << std::endl;

    return 0;
}