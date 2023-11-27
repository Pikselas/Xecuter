#include <iostream>
#include "Xecutor.h"

int main()
{

    std::mutex mtx;

    auto func = [&]()
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Hello World!" << std::endl;

    };
    
    Xecutor xecutor;
    xecutor.execute(func);
    xecutor.execute(func);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    xecutor.execute(func);
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    xecutor.execute(func);

    std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    return 0;
}