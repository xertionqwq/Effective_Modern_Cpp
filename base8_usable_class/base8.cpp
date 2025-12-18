#include<iostream>
#include<memory>
#include<functional>
#include<map>
#include<string>
#include<vector>
#include <algorithm>

using Fun = int(int, int); // 函数类型：2个int参数，返回int

// 函数对象（重载()运算符）
struct divide{
    int operator()(int deno, int divi) const { // 加const：const对象可调用
        return deno / divi;
    }
};

// 普通函数：2个参数
int add (int a, int b) {
    return a + b;
}

// 辅助函数：字符串长度判断
bool isShorter(const std::string &a, int sz) {
    return a.size() > sz;
}

int main() {
    std::vector<std::string> word = {"Yes", "No", "None"};
    auto sz = 10;

    // 1. lambda实现闭包（捕获sz，参数数量匹配）
    auto wc = find_if(word.begin(), word.end(),
                      [sz](const std::string &a) {
                          return a.size() > sz;
                      });

    // 2. std::bind实现闭包（绑定_1为第一个参数，sz为第二个参数）
    using namespace std::placeholders;
    auto fun = std::bind(isShorter, _1, sz);
    auto wc2 = find_if(word.begin(), word.end(), fun);

    int mm = 0;
    // 修正1：有捕获的lambda（[mm]）无法转普通函数指针，仅可存到std::function
    auto mod_ = [mm](int a, int b) {
        return a % b;
    };
    // 无捕获的lambda：可隐式转函数指针
    Fun *mod = [](int a, int b) {
        return a % b;
    };

    // 修正2：std::bind参数数量匹配（add需要2个参数，绑定_1和_2即可）
    // 若想绑定mm作为固定参数，需调整逻辑（示例：add(a, mm)）
    auto bindAdd = std::bind(add, _1, _2); // 正确：2个参数匹配
    // 可选：绑定mm为第二个参数（调用时只需传第一个参数）
    auto bindAddWithMm = std::bind(add, _1, mm); 

    // 普通函数指针map：仅能存无捕获lambda/普通函数/函数指针
    std::map<std::string, int (*)(int, int)> funcMap;
    funcMap.insert({"+", add});
    funcMap.insert({"%", mod});
    // funcMap.insert({"%", mod_}); // 错误：mod_有捕获，无法转函数指针

    // std::function map：支持所有可调用对象（有捕获lambda/bind对象/函数对象等）
    std::map<std::string, std::function<int(int, int)>> funcMap2;
    funcMap2.insert({"+", add});
    funcMap2.insert({"%", mod});
    funcMap2.insert({"%_capture", mod_}); // 有捕获lambda：可存
    funcMap2.insert({"+_bind", bindAdd}); // bind对象：可存
    funcMap2.insert({"+_bind_mm", bindAddWithMm}); // 绑定固定参数的bind对象：可存

    // 初始化列表构建std::function map（支持函数/函数对象/无捕获lambda）
    std::map<std::string, std::function<int(int, int)>> binops = {
        {"+", add},          // 普通函数
        {"++", &add},        // 函数指针（和add等价）
        {"/", divide()},     // 函数对象（临时对象）
        {"*", [](int a, int b) { return a * b; }}, // 无捕获lambda
        {"%", mod}           // 函数指针（无捕获lambda转换）
    };

    // 测试调用（验证所有可调用对象）
    std::cout << "add(10,5) = " << funcMap["+"](10,5) << std::endl;
    std::cout << "mod(10,3) = " << funcMap["%"](10,3) << std::endl;
    std::cout << "mod_(10,3) = " << funcMap2["%_capture"](10,3) << std::endl;
    std::cout << "bindAdd(10,5) = " << funcMap2["+_bind"](10,5) << std::endl;
    // std::cout << "bindAddWithMm(10) = " << funcMap2["+_bind_mm"](10) << std::endl; // 第二个参数固定为mm=0
    std::cout << "divide(10,2) = " << binops["/"](10,2) << std::endl;
    std::cout << "multiply(10,5) = " << binops["*"](10,5) << std::endl;

    std::cout << "return done" << std::endl;
    return 0;
}