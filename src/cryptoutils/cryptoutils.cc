#include "cryptoutils.hpp"

uint32_t calculateCRC32(const std::string& data)
{
    boost::crc_32_type crc;
    crc.process_bytes(data.c_str(), data.length());

    return crc.checksum();
}

std::string calculateSHA256(const std::string& data)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data.c_str(), data.length());
    SHA256_Final(hash, &sha256);

    std::string sha256Str;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
    {
        char buf[3];
        std::sprintf(buf, "%02x", hash[i]);
        sha256Str += buf;
    }

    return sha256Str;
}

std::string calculateSM3(const std::string& message)
{
    const int SM3_DIGEST_LENGTH = 32;
    EVP_MD_CTX* mdctx;
    const EVP_MD* md;
    unsigned char md_value[SM3_DIGEST_LENGTH];
    unsigned int md_len;

    OpenSSL_add_all_digests();
    md = EVP_sm3();

    if (!(mdctx = EVP_MD_CTX_new()))
    {
        ERR_print_errors_fp(stderr);
        exit(1);
    }

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL))
    {
        ERR_print_errors_fp(stderr);
        exit(1);
    }

    if (1 != EVP_DigestUpdate(mdctx, message.c_str(), message.length()))
    {
        ERR_print_errors_fp(stderr);
        exit(1);
    }

    if (1 != EVP_DigestFinal_ex(mdctx, md_value, &md_len))
    {
        ERR_print_errors_fp(stderr);
        exit(1);
    }

    EVP_MD_CTX_free(mdctx);

    // 将摘要值转换为十六进制字符串
    char hex_string[(SM3_DIGEST_LENGTH * 2) + 1];
    for (int i = 0; i < SM3_DIGEST_LENGTH; ++i)
        sprintf(hex_string + (i * 2), "%02x", md_value[i]);

    return std::string(hex_string);
}

std::string hex_encode(const std::string& input)
{
    std::ostringstream oss;
    for (unsigned char c : input) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    }
    return oss.str();
}

std::string hex_decode(const std::string& input)
{
    std::string output;
    for (std::size_t i = 0; i < input.length(); i += 2) {
        int n;
        std::istringstream iss(input.substr(i, 2));
        iss >> std::hex >> n;
        output.push_back(static_cast<unsigned char>(n));
    }
    return output;
}

std::string aesEncrypt(const std::string& plaintext, const std::string& key)
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), nullptr,
                       reinterpret_cast<const unsigned char*>(key.c_str()), nullptr);

    int ciphertext_len = 0;
    int len;

    // 分配足够大的缓冲区来容纳加密后的数据
    std::string ciphertext(plaintext.length() + EVP_MAX_BLOCK_LENGTH, '\0');

    EVP_EncryptUpdate(ctx, const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(ciphertext.data())), &len,
                      reinterpret_cast<const unsigned char*>(plaintext.data()), plaintext.length());
    ciphertext_len += len;

    EVP_EncryptFinal_ex(ctx, const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(ciphertext.data())) + ciphertext_len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    ciphertext.resize(ciphertext_len);

    return hex_encode(ciphertext);
}

std::string aesDecrypt(const std::string& ciphertext, const std::string& key)
{
    std::string decoded_ciphertext = hex_decode(ciphertext);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), nullptr,
                       reinterpret_cast<const unsigned char*>(key.c_str()), nullptr);

    int plaintext_len = 0;
    int len;

    // 分配足够大的缓冲区来容纳解密后的数据
    std::string plaintext(decoded_ciphertext.length(), '\0');

    EVP_DecryptUpdate(ctx, const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(plaintext.data())), &len,
                      reinterpret_cast<const unsigned char*>(decoded_ciphertext.data()), decoded_ciphertext.length());
    plaintext_len += len;

    EVP_DecryptFinal_ex(ctx, const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(plaintext.data())) + plaintext_len, &len);
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    plaintext.resize(plaintext_len);

    return plaintext;
}

std::string sm4Encrypt(const std::string& plaintext, const std::string& key, const std::string& iv)
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_sm4_ofb(), nullptr,
                       reinterpret_cast<const unsigned char*>(key.c_str()),
                       reinterpret_cast<const unsigned char*>(iv.c_str()));

    int ciphertext_len = 0;
    int len;

    std::string ciphertext(plaintext.length(), '\0');

    EVP_EncryptUpdate(ctx, const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(ciphertext.data())), &len,
                      reinterpret_cast<const unsigned char*>(plaintext.data()), plaintext.length());
    ciphertext_len += len;

    EVP_EncryptFinal_ex(ctx, const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(ciphertext.data())) + ciphertext_len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    ciphertext.resize(ciphertext_len);

    return hex_encode(ciphertext);
}

std::string sm4Decrypt(const std::string& ciphertext, const std::string& key, const std::string& iv)
{
    std::string decoded_ciphertext = hex_decode(ciphertext);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_sm4_ofb(), nullptr,
                       reinterpret_cast<const unsigned char*>(key.c_str()),
                       reinterpret_cast<const unsigned char*>(iv.c_str()));

    int plaintext_len = 0;
    int len;

    std::string plaintext(decoded_ciphertext.length(), '\0');

    EVP_DecryptUpdate(ctx, const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(plaintext.data())), &len,
                      reinterpret_cast<const unsigned char*>(decoded_ciphertext.data()), decoded_ciphertext.length());
    plaintext_len += len;

    EVP_DecryptFinal_ex(ctx, const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(plaintext.data())) + plaintext_len, &len);
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    plaintext.resize(plaintext_len);

    return plaintext;
}

std::string encrypt(const std::string& plaintext, const std::string& key, const int method)
{
    std::string iv = "1234567812345678";
    switch (method)
    {
        case 0:
            return plaintext;
        case 1:
            return aesEncrypt(plaintext, key);
        case 2:
            return sm4Encrypt(plaintext, key, iv);
        default:
            return 0;
    }
}

std::string decrypt(const std::string& ciphertext, const std::string& key, const int method)
{
    std::string iv = "1234567812345678";
    switch (method)
    {
        case 0:
            return ciphertext;
        case 1:
            return aesDecrypt(ciphertext, key);
        case 2:
            return sm4Decrypt(ciphertext, key, iv);
        default:
            return 0;
    }
}
