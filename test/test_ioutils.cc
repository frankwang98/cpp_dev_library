#include "../src/ioutils/ioutils.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    InputComponent input;
    OutputComponent output;

    try {
        /* 读取文件 */
        input.ReadFile("./test/log.txt");

        /* 获取目录下的文件名，类似tree */
        std::vector<std::string> file_name;
        std::string path = ".";
    
        input.GetFileNames(path, file_name);
    
        for(int i = 0; i <file_name.size(); i++)
        {
            std::cout << file_name[i] << std::endl;
        }

        std::string data = "Hello, world!";
        /* 写入文件 */
        output.WriteFile("./test/output.txt", data);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    /* 读取ini配置 */
    IniReader config;
	bool ret = config.ReadConfig("./test/config.ini");
	if (ret == false) 
    {
		printf("ReadConfig is Error, filename=%s", "config.ini");
		return 1;
	}

	std::string HostName = config.ReadString("g1", "name", "");
	std::string IP = config.ReadString("g1", "IP", "");
	int Port = config.ReadInt("g1", "port", 0);
 
	std::cout << "HostName=" << HostName << std::endl;
	std::cout << "IP=" << IP << std::endl;
	std::cout << "Port=" << Port << std::endl;

    auto ini = IniReader2("./test/config.ini");
	int test_port = ini.Get<int>("g1", "port");
	std::cout << "test_port=" << test_port << std::endl;

    return 0;
}