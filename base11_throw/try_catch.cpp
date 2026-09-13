#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

void strcpy(char *dest, const char *source)
{
    // 存在空指针，抛出异常
    if (!dest || !source)
    {
        throw std::invalid_argument("Null Pointers pass to strcpy");
    } // 如果属实，函数调用栈解开,后面的语句不会执行
    while (*source)
    {
        *dest++ = *source;
    }
    *dest = '\0';
}

void func(int n)
{
    int x{42};
    int *p = new int[n];
}

template <typename T>
class Array
{
public:
    // try可写入构造函数里面
    Array(std::size_t n)
    try : m_size(n), m_data(new T[n])
    {
        std::cout << "Array(n)" << std::endl;
    }
    catch (const std::bad_alloc &ba)
    {
        std::cerr << "No enough memory" << std::endl;
        throw;
    }

private:
    size_t m_size;
    int *m_data;
};

void test(void *ptr) noexcept(true) {
    
}

int main()
{
    char *dest = nullptr;
    const char *source = "hello world";
    // try为尝试语句,如果存在异常,会将异常抛给后面的catch进行捕获
    try
    {
        strcpy(dest, source);
    }
    catch (const std::logic_error &e)
    {
        // 使用父类引用可以接子类
        std::cerr << "catch(logic): " << e.what() << std::endl;

        // 可继续抛出异常
        // throw std::runtime_error("test");
    }
    catch (...)
    {
        // (...)兜底,表示所有类型
        // cerr无缓冲,可以立即输出
        std::cerr << "catch(...): " << std::endl;
    }

    int size{9999999};
    try
    {
        func(size);
    }
    catch (...)
    {
    }

    std::cout << "return done" << std::endl;
    return 0;
}