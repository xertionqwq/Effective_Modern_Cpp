#include<iostream>
#include<string>
#include<vector>
using namespace std;

class BigDate{
public:
    static const int poolSize = 40960;

    BigDate() : pool(new char[poolSize]) {
        cout << "constract" << endl;
    }
    ~BigDate() {
        if (pool != nullptr) {
            delete[] pool;
        }
    }

    //移动构造
    BigDate(BigDate && other) {
        cout << "move" << endl;
        this->pool = other.pool;
        other.pool = nullptr;
    }

    //拷贝构造
    BigDate(const BigDate &other) {
        cout << "copy" << endl;
        this->pool = new char[poolSize];
        // memcpy(pool, other.pool, poolSize);
        this->pool = other.pool;
    }

private:
    char *pool = nullptr;
};


BigDate getPool() {
    BigDate memoryPool;
    return memoryPool;
}

BigDate getPool(const BigDate &aaa) {
    return aaa;
}

//函数返回值不做规定便是临时变量
int geta() {
    int a = 10;
    return a;
}

//即使定义了全局变量
int gA = 110;
int getgA() {
    return gA;
}

int main() {
    int x = 10;
    const int cx = 911;
    int &qx = x;
    const int &y = -10;
    // int &&rx = std::move(cx);

    //int *p0 = &x++;
    int *p1 = &++x;
    auto p2 = &"hello world";
    //函数返回值为临时变量，因此能用右值绑定
    int &&a = geta();
    int &&ga = getgA();

    //得到右值
    int rq = std::move(qx);
    int rq1 = static_cast<int &&>(x);
    int &&rq2 = 61;

    BigDate bbb = getPool();
    // BigDate aaa = std::move(bbb);//类中不实现移动，则此处为拷贝
    // BigDate ddd = std::move(bbb);
    BigDate &&eee = std::move(bbb);
    //BigDate ccc = getPool(bbb);

    cout << "return done";

    return 0;
}