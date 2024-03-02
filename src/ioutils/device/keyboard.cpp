#include <Windows.h>

// 检测键盘输入的函数
bool isKeyPressed(int keyCode) {
    return GetAsyncKeyState(keyCode) & 0x8000; // 提取当前按键状态
}

void readKeyboard() {
    while (true) {
        // 检测WASD按键
        if (isKeyPressed('W') || isKeyPressed('w')) {
        std::cout << "W key pressed" << std::endl;
        Sleep(100);
        }
        if (isKeyPressed('A') || isKeyPressed('a')) {
        std::cout << "A key pressed" << std::endl;
        Sleep(100);
        }
        if (isKeyPressed('S') || isKeyPressed('s')) {
        std::cout << "S key pressed" << std::endl;
        Sleep(100);
        }
        if (isKeyPressed('D') || isKeyPressed('d')) {
        std::cout << "D key pressed" << std::endl;
        Sleep(100);
        }

        // 在这里可以进行其他操作或逻辑

        // 退出循环的条件
        if (isKeyPressed('Q') || isKeyPressed('q')) {
            break;
        }
    }
}