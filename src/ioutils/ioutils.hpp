// ioutils.hpp

#ifndef IO_UTILS_HPP
#define IO_UTILS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <map>
#include <dirent.h>
#include <vector>
#include <sys/types.h>

// 输入组件
class InputComponent {
public:
    void ReadFile(const std::string& filename) {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            throw std::runtime_error("Failed to open input file");
        }

        std::string line;
        while (std::getline(inputFile, line)) {
            std::cout << line << std::endl;
        }

        inputFile.close();
    }

    void GetFileNames(std::string path,std::vector<std::string>& filenames)
    {
        DIR *pDir;
        struct dirent* ptr;
        if(!(pDir = opendir(path.c_str())))
            return;
        while((ptr = readdir(pDir))!=0) {
            if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
                filenames.push_back(path + "/" + ptr->d_name);
        }
        closedir(pDir);
    }

    // 创建文件
    void createFile(const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            std::cout << "文件创建成功: " << filename << std::endl;
            file.close();
        } else {
            std::cerr << "无法创建文件: " << filename << std::endl;
        }
    }

    // 删除文件
    void deleteFile(const std::string& filename) {
        if (std::remove(filename.c_str()) == 0) {
            std::cout << "文件删除成功: " << filename << std::endl;
        } else {
            std::cerr << "无法删除文件: " << filename << std::endl;
        }
    }

    // 判断文件是否存在
    bool fileExists(const std::string& filename) {
        std::ifstream file(filename);
        return file.good();
    }

    // 向文件写入内容
    void writeFile(const std::string& filename, const std::string& content) {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << content;
            std::cout << "内容成功写入文件: " << filename << std::endl;
            file.close();
        } else {
            std::cerr << "无法打开文件进行写入: " << filename << std::endl;
        }
    }

    // 读取文件内容
    std::string readFile(const std::string& filename) {
        std::ifstream file(filename);
        std::stringstream buffer;
        if (file.is_open()) {
            buffer << file.rdbuf();
            file.close();
        } else {
            std::cerr << "无法打开文件进行读取: " << filename << std::endl;
        }
        return buffer.str();
    }

    // 修改文件内容
    void modifyFile(const std::string& filename, const std::string& newContent) {
        std::string content = readFile(filename);
        writeFile(filename, content + "\n" + newContent);
    }
};

// 输出组件
class OutputComponent {
public:
    void WriteFile(const std::string& filename, const std::string& content) {
        std::ofstream outputFile(filename);
        if (!outputFile.is_open()) {
            throw std::runtime_error("Failed to open output file");
        }

        outputFile << content;

        outputFile.close();
    }
};

class IniReader
{
private:
    std::map<std::string, std::map<std::string, std::string> >settings_;
    
public:
    IniReader(){}
    ~IniReader(){}

    bool ReadConfig(const std::string &filename)
    {
        settings_.clear();
        std::ifstream infile(filename.c_str()); //构造默认调用open,所以可以不调用open
        if (!infile) {
            return false;
        }
        std::string line, key, value, section;
        std::map<std::string, std::string> k_v;
        std::map<std::string, std::map<std::string, std::string> >::iterator it;
        while (getline(infile, line))
        {
            if (AnalyseLine(line, section, key, value))
            {
                it = settings_.find(section);
                if (it != settings_.end())
                {
                    k_v[key] = value;
                    it->second = k_v;
                }
                else
                {
                    k_v.clear();
                    settings_.insert(std::make_pair(section, k_v));
                }
            }
            key.clear();
            value.clear();
        }
        infile.close();
        return true;
    }

    std::string ReadString(const char* section, const char* item, const char* default_value)
    {
        std::string tmp_s(section);
        std::string tmp_i(item);
        std::string def(default_value);
        std::map<std::string, std::string> k_v;
        std::map<std::string, std::string>::iterator it_item;
        std::map<std::string, std::map<std::string, std::string> >::iterator it;
        it = settings_.find(tmp_s);
        if (it == settings_.end())
        {
            return def;
        }
        k_v = it->second;
        it_item = k_v.find(tmp_i);
        if (it_item == k_v.end())
        {
            return def;
        }
        return it_item->second;
    }

    int ReadInt(const char* section, const char* item, const int& default_value)
    {
        std::string tmp_s(section);
        std::string tmp_i(item);
        std::map<std::string, std::string> k_v;
        std::map<std::string, std::string>::iterator it_item;
        std::map<std::string, std::map<std::string, std::string> >::iterator it;
        it = settings_.find(tmp_s);
        if (it == settings_.end())
        {
            return default_value;
        }
        k_v = it->second;
        it_item = k_v.find(tmp_i);
        if (it_item == k_v.end())
        {
            return default_value;
        }
        return atoi(it_item->second.c_str());
    }

    float ReadFloat(const char* section, const char* item, const float& default_value)
    {
        std::string tmp_s(section);
        std::string tmp_i(item);
        std::map<std::string, std::string> k_v;
        std::map<std::string, std::string>::iterator it_item;
        std::map<std::string, std::map<std::string, std::string> >::iterator it;
        it = settings_.find(tmp_s);
        if (it == settings_.end())
        {
            return default_value;
        }
        k_v = it->second;
        it_item = k_v.find(tmp_i);
        if (it_item == k_v.end())
        {
            return default_value;
        }
        return atof(it_item->second.c_str());
    }

private:
    bool IsSpace(char c)
    {
        if (' ' == c || '\t' == c)
            return true;
        return false;
    }
    
    bool IsCommentChar(char c)
    {
        switch (c) 
        {
        case '#':
            return true;
        default:
            return false;
        }
    }

    void Trim(std::string & str)
    {
        if (str.empty())
        {
            return;
        }
        int i, start_pos, end_pos;
        for (i = 0; i < str.size(); ++i) {
            if (!IsSpace(str[i])) {
                break;
            }
        }
        if (i == str.size())
        {
            str = "";
            return;
        }
        start_pos = i;
        for (i = str.size() - 1; i >= 0; --i) {
            if (!IsSpace(str[i])) {
                break;
            }
        }
        end_pos = i;
        str = str.substr(start_pos, end_pos - start_pos + 1);
    }

    bool AnalyseLine(const std::string & line, std::string& section, std::string & key, std::string & value)
    {
        if (line.empty())
            return false;
        int start_pos = 0, end_pos = line.size() - 1, pos, s_startpos, s_endpos;
        if ((pos = line.find("#")) != -1)
        {
            if (0 == pos)
            {
                return false;
            }
            end_pos = pos - 1;
        }
        if (((s_startpos = line.find("[")) != -1) && ((s_endpos = line.find("]"))) != -1)
        {
            section = line.substr(s_startpos + 1, s_endpos - 1);
            return true;
        }
        std::string new_line = line.substr(start_pos, start_pos + 1 - end_pos);
        if ((pos = new_line.find('=')) == -1)
            return false;
        key = new_line.substr(0, pos);
        value = new_line.substr(pos + 1, end_pos + 1 - (pos + 1));
        Trim(key);
        if (key.empty()) {
            return false;
        }
        Trim(value);
        if ((pos = value.find("\r")) > 0)
        {
            value.replace(pos, 1, "");
        }
        if ((pos = value.find("\n")) > 0)
        {
            value.replace(pos, 1, "");
        }
        return true;
    }

};

/**
 * @brief 一个简单的读取ini文件的类，可以将ini转化为map - zhangguangyan
 * @test auto ini = IniReader{INI_PATH} // 建议使用ros::package::getPath(node_path)创建绝对路径
 * @test TYPE param = ini.Get<TYPE>(Section, Name); // Section为ini文件中[]中的字符串，name为其下key值
*/
class IniReader2 {
  private:
    struct IniLine {
        std::string value;
        std::string comment;
    };

  private:
    std::map<std::string, std::map<std::string, IniReader2::IniLine>> ini_map_;
    std::map<std::string, std::map<std::string, std::string>>        description_map_;
    std::string                                                      file_name_;
    std::string                                                      option_comment_characters_;

  public:
    IniReader2(const std::string& file_name) : option_comment_characters_(";#") {
        if (file_name != "")
            if (not Load(file_name)) std::cerr << "Unable to open the file " + file_name << std::endl;
    }

    ~IniReader2() {
        Free();
    }

    auto GetMap() -> std::map<std::string, std::map<std::string, IniReader2::IniLine>> {
        return ini_map_;
    }

    void Free() {
        ini_map_.clear();
    }

    void ParasitCar(std::string& str) {
        size_t fin = str.size();
        if (fin < 1) return;
        if (str.at(fin - 1) < ' ') str.erase(fin - 1);
    }

    auto Trim(const std::string& str) -> std::string {
        auto deb = size_t{0};
        auto fin = str.size();
        auto chr = char{};
        while (deb < fin) {
            chr = str.at(deb);
            if ((chr != ' ') && (chr != '\t')) break;
            deb++;
        }
        while (fin > 0) {
            chr = str.at(fin - 1);
            if ((chr != ' ') && (chr != '\t')) break;
            fin--;
        }
        return str.substr(deb, fin - deb);
    }

    auto Load(const std::string& file_name) -> bool {
        auto pos    = size_t{};
        auto pos2   = size_t{};
        auto length = size_t{};

        auto line    = std::string{};
        auto section = std::string{};
        auto key     = std::string{};
        auto comment = std::string{};

        auto    file = std::ifstream{};
        IniLine iniLine;

        Free();
        file_name_ = file_name;

        // open the file
        file.open(file_name_.c_str(), std::ifstream::in);
        if (!file) return false;

        // read each line
        while (getline(file, line)) {
            ParasitCar(line);
            if (line.empty()) continue;
            length          = line.length();
            key             = "";
            iniLine.value   = "";
            iniLine.comment = "";
            // sections
            if (line.at(0) == '[') {
                pos = line.find_first_of(']');
                if (pos == std::string::npos) pos = line.length();
                section = Trim(line.substr(1, pos - 1));
                if (comment != "") {
                    description_map_[section][""] = comment;
                    comment                       = "";
                }
                continue;
            }
            // comments
            pos = std::string::npos;
            for (unsigned int i = 0; i < option_comment_characters_.length(); ++i) {
                pos2 = line.find_first_of(option_comment_characters_[i]);
                if (pos2 == std::string::npos) continue;
                if (pos == std::string::npos) {
                    pos = pos2;
                    continue;
                }
                if (pos > pos2) pos = pos2;
            }
            if (pos != std::string::npos) {
                if (pos > 0) {
                    iniLine.comment = line.substr(pos + 1, length - pos);
                    line.erase(pos, length - pos);
                } else {
                    if (comment != "") comment += '\n';
                    comment += line.substr(pos + 1, length - pos);
                    continue;
                }
            }
            // value
            pos = line.find_first_of('=');
            if (pos != std::string::npos) {
                iniLine.value = Trim(line.substr(pos + 1, length - pos));
                line.erase(pos, length - pos);
            }
            // save to map
            key                    = Trim(line);
            ini_map_[section][key] = iniLine;
            if (comment != "") {
                description_map_[section][key] = comment;
                comment                        = "";
            }
        }
        file.close();
        return true;
    }

    template <class T>
    auto Get(const std::string& section, const std::string& key) -> T {
        auto value      = std::string{";"};
        auto it_section = ini_map_.find(section);
        if (it_section != ini_map_.end()) {
            if (it_section->second.find(key) != it_section->second.end())
                value = it_section->second.find(key)->second.value;
            else
                std::cerr << "key " + key + " not found!" << std::endl;
        } else
            std::cerr << "section " + section + " not found!" << std::endl;

        auto result = T{};
        if (value != std::string(";")) {
            auto ss = std::stringstream{};
            ss << value;
            ss >> result;
        }
        return result;
    }

    auto GetComment(const std::string& section, const std::string& key) -> std::string {
        auto it_section = ini_map_.find(section);
        if (it_section == ini_map_.end()) return "";
        auto it_key = it_section->second.find(key);
        if (it_key == it_section->second.end()) return "";
        return it_key->second.comment;
    }

};


#endif