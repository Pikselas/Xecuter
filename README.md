# Xecuter
Sample implementation for threadpool in C++
```C++
auto func = [&]()
{
    std::cout << "Hello World!" << std::endl;
};

Xecutor xecutor;
xecutor.execute(func);
xecutor.execute(func);

std::this_thread::sleep_for(std::chrono::milliseconds(200));
xecutor.execute(func);
std::this_thread::sleep_for(std::chrono::milliseconds(400));
xecutor.execute(func);

std::this_thread::sleep_for(std::chrono::milliseconds(2000));
```
