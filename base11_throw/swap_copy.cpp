#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // 用于 std::swap

class Buffer
{
private:
    unsigned char *_buf;
    int _capacity;
    int _length;

public:
    // 构造函数
    explicit Buffer(int capacity) : _capacity(capacity), _length(0)
    {
        std::cout << "Buffer(int capacity)" << std::endl;
        // throw std::invalid_argument("======"); // 构造函数执行到此处抛出异常,连对象都不会创建
        // 从而实现了强异常安全保证
        _buf = capacity == 0 ? nullptr : new unsigned char[capacity];
    }

    // 析构函数
    ~Buffer()
    {
        std::cout << "~Buffer()" << std::endl;
        delete[] _buf;
        // 置空指针，避免野指针
        _buf = nullptr;
        _capacity = 0;
        _length = 0;
    }

    // 拷贝构造函数
    Buffer(const Buffer &bfr)
    {
        std::cout << "Buffer (const Buffer &bfr)" << std::endl;
        this->_capacity = bfr._capacity;
        this->_length = bfr._length;
        // throw std::invalid_argument("======");  // 和拷贝构造同理,实现强异常安全保证
        // 只有涉及到内存申请,我们均抛出异常
        this->_buf = new unsigned char[_capacity];
        std::copy(bfr._buf, bfr._buf + bfr._capacity, this->_buf);
    }

    // 移动构造函数
    Buffer(Buffer &&bfr) noexcept // noexcept 是移动语义的最佳实践
    {
        std::cout << "Buffer (Buffer &&bfr)" << std::endl;
        this->_buf = bfr._buf;
        this->_capacity = bfr._capacity;
        this->_length = bfr._length;

        bfr._buf = nullptr;
        bfr._capacity = 0;
        bfr._length = 0;
    }

    Buffer &operator=(const Buffer &bfr)
    {
        std::cout << "Buffer operator=(const Buffer &bfr)" << std::endl;
        // 避免自赋值
        if (this != &bfr)
        {
            this->_capacity = bfr._capacity;
            this->_length = bfr._length;
            delete[] this->_buf;
            // 在申请内存前我们已经修改了this的内容
            // 而异常一旦抛出,已修改的内容无法挽回
            throw std::invalid_argument("======");
            this->_buf = new unsigned char[_capacity];
            std::copy(bfr._buf, bfr._buf + bfr._capacity, this->_buf);
        }
        return *this;
    }

    // 移动赋值运算符
    Buffer &operator=(Buffer &&bfr) noexcept
    {
        std::cout << "Buffer operator=(Buffer &&bfr)" << std::endl;
        // 避免自赋值
        if (this != &bfr)
        {
            // 接管源对象的资源
            this->_capacity = bfr._capacity;
            this->_length = bfr._length;
            delete[] this->_buf;
            this->_buf = bfr._buf;

            bfr._buf = nullptr;
            bfr._capacity = 0;
            bfr._length = 0;
        }
        return *this;
    }

    void setLength(int len) { _length = len; }
    bool write(unsigned char value)
    {
        if (_capacity == _length)
            return false;
        _buf[_length++] = value;
        return true;
    }
};

// 测试代码
int main()
{ // try{
    //     Buffer b1{10};
    // }
    // catch(...) {
    //     std::cout << "error" << std::endl;
    // }

    Buffer b{10};
    b.write(99);
    b.write(69);
    Buffer b1{99};
    b1.write(78);
    b1.write(45);
    try
    {
        b1 = b; // b1的存储的数据已经被修改且无法追回
    }
    catch (...)
    {
        std::cout << "error" << std::endl;
    }

    std::cout << "return done" << std::endl;
    return 0;
}