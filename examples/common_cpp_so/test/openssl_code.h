/**
 * @file openssl_code.h
 * @author wangzf (wangzhifeng@wicri.org)
 * @brief 
 * @version 1.0
 * @date 2023-10-09
 * 
 * Copyright (c) 2023 wicri.cn. All rights reserved.
 * 
 */
#ifndef OPENSSL_CODE_H
#define OPENSSL_CODE_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <boost/crc.hpp>

/*
Usage: g++ -o main main.cpp -lssl -lcrypto -lboost_system
*/

uint32_t calculateCRC32(const std::string& data);

std::string calculateSHA256(const std::string& data);

std::string calculateSM3(const std::string& message);

std::string hex_encode(const std::string& input);

std::string hex_decode(const std::string& input);

std::string aesEncrypt(const std::string& plaintext, const std::string& key);

std::string aesDecrypt(const std::string& ciphertext, const std::string& key);

std::string sm4Encrypt(const std::string& plaintext, const std::string& key, const std::string& iv);

std::string sm4Decrypt(const std::string& ciphertext, const std::string& key, const std::string& iv);

std::string encrypt(const std::string& plaintext, const std::string& key, const int method);

std::string decrypt(const std::string& ciphertext, const std::string& key, const int method);

#endif