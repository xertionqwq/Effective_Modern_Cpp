#include<iostream>
#include<unordered_map>
#include<functional>
#include<vector>
#include<map>

template <typename It>
void dwim(It b, It c) {
    while (b != c) {
        // typename std::iterator_traits<It>::value_type current_val = *b;
        auto current_val = *b;
        std::cout << current_val << std::endl;
        b++;
    }
}

struct Widget{
    int windowSize = 10;
};

int main() {
    int a = 10;
    const float &b = a;

    std::vector<int> vec = {1, 2, 3, 4};
    // dwim(vec.cbegin(), vec.cend());

    // auto fun = [](const std::unique_ptr<int> &p1,
    //               const std::unique_ptr<int> &p2)
    // {
    //     return *p1 < *p2;
    // };
    auto fun = [](const auto &p1,
                  const auto &p2)
    {
        return *p1 < *p2;
    };
    int *p1 = new int(91);
    int *p2 = new int(69);
    std::cout << fun(p1, p2) << std::endl;
    // std::function<bool(const std::unique_ptr<int> &, const std::unique_ptr<int> &)> Fun;

    std::vector<int> v(10);
    unsigned sz = v.size();
    // std::cout << sizeof(sz) << std::endl;    //unsigned的大小比size_t小，数据可能溢出
    // std::cout << sizeof(size_t) << std::endl;

    std::unordered_map<std::string, int> testmap = {
        { "Yes", 2 },
        { "No", 3 },
        { "None", 4 }
    };
    for (const std::pair<std::string, int> &p : testmap) {

    }//该处的p的string没有const，所以出现了复制
    for (const auto &p : testmap) {

    }//该处的p的string有const，避免了复制

    std::cout
        << "return done" << std::endl;
    return 0;
}