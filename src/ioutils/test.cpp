const std::string filename = "example.txt";
    
// 创建文件
createFile(filename);

// 写入内容
writeFile(filename, "Hello, File!");

// 读取并输出内容
std::cout << "文件内容: " << readFile(filename) << std::endl;

// 修改文件内容
modifyFile(filename, "Appended Text");

// 读取并输出修改后的内容
std::cout << "修改后的文件内容: " << readFile(filename) << std::endl;

// 删除文件
deleteFile(filename);