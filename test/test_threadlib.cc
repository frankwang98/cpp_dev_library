#include "../src/threadlib/threadlib.hpp"
#include <iostream>

count_down_latch latch(3);

void worker_thread(const std::string& name)
{
    std::cout << name << "正在干活..." << std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(3));
    latch.count_down();

    std::cout << name << "干完活了!" << std::endl;
}

void boss_thread()
{
    std::cout << "老板正在等所有的工人干完活..." << std::endl;

    latch.await();

    std::cout << "工人活都干完了，老板开始检查了!" << std::endl;
}

void print()
{
    std::cout << "hello world" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void test_task(const std::string& str)
{
    std::cout << "Current thread id: " << std::this_thread::get_id() << ", str: " << str << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

class Test1
{
public:
    void print(const std::string& str, int i)
    {
        std::cout << "Test: " << str << ", i: " << i << std::endl;
    }
};

class Test2
{
public:
    void operator()(const std::string& str, int i)
    {
        std::cout << "Test2: " << str << ", i: " << i << std::endl;
    }
};

int main(int argc, char **argv)
{
    /* 闭锁机制，老板等所有工人干完活 */
    std::thread b(boss_thread);

    std::thread w1([]{ worker_thread("张三"); });
    std::thread w2([]{ worker_thread("李四"); });
    std::thread w3([]{ worker_thread("王五"); });

    b.join();
    w1.join();
    w2.join();
    w3.join();

    /* 任务线程，1s执行一次，直到键盘输入 */
    auto t = std::make_shared<task_thread>(std::bind(print));
    std::cin.get();
    // t->stop();

    /* 线程池 */
    Test1 t1;
    Test2 t2;

    try
    {
        thread_pool pool;
        pool.init_thread_num(10);

        std::string str = "Hello world";

        for (int i = 0; i < 100; ++i)
        {
            pool.add_task([]{ std::cout << "Hello ThreadPool" << std::endl; });
            pool.add_task(test_task, str);
            pool.add_task(t2, str, i);
            pool.add_task(&Test1::print, &t1, str, i);
        }

        std::cin.get();
        std::cout << "##############END###################" << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}