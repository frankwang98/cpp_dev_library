#include "../src/dsutils/dsutils.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::array;
using std::vector;
using std::list;
using std::pair;
using std::string;

void array_ex()
{
    array<int, 5> myArray = {1, 2, 3, 4, 5};

    cout << "Array elements: ";
    for (int i = 0; i < myArray.size(); ++i) {
        cout << myArray[i] << " ";
    }
    cout << endl;

    myArray[2] = 10;
    cout << "Modified array elements: ";
    for (auto it = myArray.begin(); it != myArray.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Array elements using range-based for loop: ";
    for (const auto& element : myArray) {
        cout << element << " ";
    }
    cout << endl;

    cout << "Array size: " << myArray.size() << endl;

    cout << "Is array empty? " << (myArray.empty() ? "Yes" : "No") << endl;
}

void vector_ex()
{
    vector<int> vecNumbers;
    vecNumbers.assign(5, 42);
    cout << "assign_ex: ";
    for (int num : vecNumbers) {
        cout << num << " ";
    }
    cout << endl;

    vector<int> destination;
    destination.assign(vecNumbers.begin(), vecNumbers.end());
    cout << "assign destination: ";
    for (int num : destination) {
        cout << num << " ";
    }
    cout << endl;

    vector<int> myVector{1, 2, 3, 4, 5};
    cout << "myVector's size: " << myVector.size() << endl;
    cout << "The maximum capacity of myVector: " << myVector.capacity() << endl;
    cout << "myVector has: ";
    int* pos = myVector.data(); // pointer to the first element
    for (int i = 0; i < myVector.size(); i++) {
        cout << myVector.at(i) << " ";
        cout << *pos++ << " ";
    }
    cout << endl;

    int& lastEle = myVector.back();
    cout << "myVector.front(): " << myVector.front() << endl;
    cout << "myVector.back(): " << myVector.back() << endl;
    lastEle = 10;

    myVector.push_back(100);
    myVector.emplace_back(1000);
    myVector.emplace(myVector.begin(), -1);
    myVector.emplace(myVector.end(), -1000);
    myVector.erase(myVector.begin());
    myVector.erase(myVector.begin()+1, myVector.begin()+4);
    auto it = myVector.insert(myVector.begin(), -1);  
    cout << "myVector has: ";
    for (auto it = myVector.begin(); it != myVector.end(); it++) {
	    cout << *it << " ";
	}
    cout << endl;
    myVector.pop_back();    // delete last ele
    cout << "myVector reserved has: ";
    for (auto it = myVector.cend() - 1;  it >= myVector.begin(); --it){ 
        cout << *it << " "; 
    }
    cout << endl;
    myVector.clear();
    cout << "now myVector's size: " << myVector.size() << endl;
    if (myVector.empty()) {
        cout << "myVector is empty!" << endl;
    }
}

void list_ex()
{
    list<int> listNumbers;
    listNumbers.assign(5, 100);
    cout << "listNumbers: ";
    for (int itr : listNumbers) {
        cout << itr << " ";
    }
    cout << endl;

    listNumbers.push_back(10);
    listNumbers.push_back(1000);
    listNumbers.pop_back();
    listNumbers.pop_front();
    listNumbers.emplace_back(10);
    listNumbers.emplace_front(1);
    listNumbers.insert(listNumbers.begin(), 5);
    listNumbers.remove(100);
    cout << "now listNumbers: ";
    for (auto it = listNumbers.begin(); it != listNumbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    cout << "listNumbers last ele: " << listNumbers.back() << endl;
    auto itr = listNumbers.begin();
    cout << "listNumbers begin ele: " << *itr << endl;
    listNumbers.erase(itr);
    listNumbers.clear();
    if (listNumbers.empty()) {
        cout << "listNumbers is empty!" << endl;
    }

    list<int> listNumbers1 = {1, 3, 5, 7};
    list<int> listNumbers2 = {2, 4, 6};
    listNumbers2.merge(listNumbers1);
    cout << "Merge list: ";
    for (auto it : listNumbers2) {
        cout << it << " ";
    }
    cout << endl;

    list< pair<int,char> > listPair;
    listPair.emplace(listPair.begin(), 100, 'x');
    listPair.emplace(listPair.begin(), 200, 'y');
    cout << "listPair contains: ";
    for (auto& it : listPair) {
        cout << "(" << it.first << "," << it.second << ")";
    }
    cout << endl;
}

void string_ex()
{
    string strRandom = "Hello World!";
    cout << "str Length: " << strRandom.length() << endl;
    if (strRandom.empty()) {
        cout << "String is empty" << endl;
    } else {
        cout << "String is not empty" << endl;
    }

    cout << "First character: " << strRandom[0] << endl;
    cout << "Last character: " << strRandom[strRandom.length() - 1] << endl;

    strRandom[7] = 'C';
    cout << "Modified string: " << strRandom << endl;

    string str2 = " Welcome!";
    string combinedStr = strRandom + str2;
    cout << "Combined string: " << combinedStr << endl;

    string searchStr = "World";
    size_t found = strRandom.find(searchStr);
    if (found != string::npos) {
        cout << "Substring found at index: " << found << endl;
    } else {
        cout << "Substring not found" << endl;
    }
}

int main(int argc, char** argv)
{
    /* 类型转换 */
    std::string str = "1000";
    int n = 200;
    std::cout << lexical_cast<int>(str) << std::endl;
    std::cout << lexical_cast<std::string>(n) << std::endl;
    std::cout << lexical_cast<bool>(n) << std::endl;
    std::cout << lexical_cast<bool>(-1) << std::endl;

    std::cout << lexical_cast<std::string>(str) << std::endl;
    std::cout << lexical_cast<std::string>("hello") << std::endl;

    /* 部分示例 */
    array_ex();

    vector_ex();

    list_ex();

    string_ex();

    return 0;
}