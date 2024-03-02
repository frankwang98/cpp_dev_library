const crypto = require('crypto');
const crc32 = require('crc32'); // npm install crc32
const sm4 = require('sm-crypto').sm4; // npm install sm-crypto

function generateMD5(input) {
    // 创建 MD5 哈希对象
    const md5Hash = crypto.createHash('md5');

    // 更新哈希对象的数据
    md5Hash.update(input);

    // 计算哈希值并以十六进制字符串形式返回
    const md5Value = md5Hash.digest('hex');

    return md5Value;
}

function generateCRC32(input) {
    // 使用 crc32 模块计算 CRC32 值
    const crc32Value = crc32(input);

    return crc32Value;
}

function generateSHA256(input) {
    // 创建 SHA-256 哈希对象
    const sha256Hash = crypto.createHash('sha256');

    // 更新哈希对象的数据
    sha256Hash.update(input);

    // 计算哈希值并以十六进制字符串形式返回
    const sha256Value = sha256Hash.digest('hex');

    return sha256Value;
}


// 生成随机的 256 位密钥和 16 位初始化向量 (IV)
const secretKey = crypto.randomBytes(32); // 256 位密钥
const iv = crypto.randomBytes(16); // 16 位 IV

function aesencrypt(text, key, initializationVector) {
    const cipher = crypto.createCipheriv('aes-256-cbc', key, initializationVector);
    let encrypted = cipher.update(text, 'utf-8', 'hex');
    encrypted += cipher.final('hex');
    return encrypted;
}

function aesdecrypt(encryptedText, key, initializationVector) {
    const decipher = crypto.createDecipheriv('aes-256-cbc', key, initializationVector);
    let decrypted = decipher.update(encryptedText, 'hex', 'utf-8');
    decrypted += decipher.final('utf-8');
    return decrypted;
}

// 生成随机的 128 位密钥
const sm4secretKey = '0123456789abcdeffedcba9876543210';

function sm4encrypt(text, key) {
    const cipherText = sm4.encrypt(text, key);
    return cipherText;
}

function sm4decrypt(cipherText, key) {
    const plainText = sm4.decrypt(cipherText, key);
    return plainText;
}

// nodejs 加密示例
const inputString = 'Hello, Nodejs!';
const md5Result = generateMD5(inputString);
const crc32Result = generateCRC32(inputString);
const sha256Result = generateSHA256(inputString);
const aesenCrypted = aesencrypt(inputString, secretKey, iv);
const aesdeCrypted = aesdecrypt(aesenCrypted, secretKey, iv);
const sm4cipherText = sm4encrypt(inputString, sm4secretKey);
const sm4decryptedText = sm4decrypt(sm4cipherText, sm4secretKey);

console.log(`Input: ${inputString}`);
console.log(`MD5: ${md5Result}`);
console.log(`CRC32: ${crc32Result}`);
console.log(`SHA-256: ${sha256Result}`);
console.log(`Encrypted AES: ${aesenCrypted}`);
console.log(`Decrypted AES: ${aesdeCrypted}`);
console.log(`Cipher SM4: ${sm4cipherText}`);
console.log(`Decrypted SM4: ${sm4decryptedText}`);
