//
//  main.cpp
//  hello
//
//  Created by xt on 15/11/25.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include <cassert>
#include "printtuple.hpp"
#include "widget.h"
#include "person.h"
#include "boost/anyshow.hpp"
#include "boost/optional.hpp"

/*
 template <typename T, typename... Ts>
 std::unique_ptr<T> make_unique(Ts&&... params) {
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
 }
 */

int main(int argc, const char * argv[]) {

    // 验证boost/any特性
    std::tuple<int, std::string, double, std::string> t1 {111, "string2", 2.3333, "string3"};
    std::vector<int> vi {111, 222, 333, 444, 555};
    xtyang::any a1(1), a2(std::string("string")), a3(1.3333), a4(t1), a5(vi);
    std::cout << t1 << std::endl;
    std::cout << vi << std::endl;
    std::cout << a1 << ", "
        << a2 << ", "
        << a3 << ", "
        << a4 << ", "
        << a5 << std::endl;
    
    // 验证printtuple
    std::tuple<int, std::string, double, std::string> t{1, "a", 2.2, "bb"};
    std::cout << t << std::endl;
    
    // 验证print多个不同类型参数
    print(std::cout, 1, 1.2, 2.3, "abc", std::bitset<16>(377), "ddd");
    
    // 验证Widget中的impl方式
    Widget w;
    Widget w2 = w;
    Widget w3(w2);
    Widget w4 = std::move(w);
    
    // 验证Person的类定义
    Person p("pppp");
    std::cout << p.get_name() << std::endl;
    Person pp2(12);
    std::cout << pp2.get_name() << std::endl;
    
    // 验证unique_ptr管理原始指针
    auto up1 = std::make_unique<char[]>(20);
    char* cp1 = up1.get();
    strcpy(cp1, "hello, wwwww!");
    for (int i = 0; i < 20; i++) {
        up1[i]=8;
    }
    
    // 验证vector管理存储buffer
    std::vector<char> vp1 {1, 2, 3, 4, 5, 6};
    std::for_each(std::begin(vp1), std::end(vp1), [](char c) { c = 8; });
    vp1.resize(20);
    char* cp2 = vp1.data();
    strcpy(cp2, "wowwww, yes");
    
    auto ptr = std::make_shared<int>(10);
    auto p2 = std::make_unique<std::string>("aaaaa");
//    std::cout << (*ptr);
//    std::cout << *p2;
    
    std::cout << *ptr << std::endl << *p2 << std::endl;
    
    std::vector<std::unique_ptr<std::string>> vs;
    vs.push_back(std::move(p2));
    auto p3 = std::make_unique<std::string>("bbbbb");
    vs.push_back(std::move(p3));
    vs.emplace_back(std::make_unique<std::string>("ccccc"));

    for (auto const& s : vs) {
        std::cout << *s << std::endl;
    }
    
    std::for_each(vs.cbegin(), vs.cend(), [] (auto const& s) {
        std::cout << "1 " << *s << std::endl;
    });
    
    for (auto bi = vs.cbegin(); bi != vs.cend(); ++bi) {
        (*bi)->append("1");
        std::cout << **bi << (*bi)->c_str() << std::endl;
    }
    
    for (auto const& s : vs) {
        std::cout << s->c_str() << std::endl;
    }
    

    if (p2 && p3) {
        std::cout << p2->c_str() << *p3 << std::endl;
    }
    
    std::cout << "Hello, World!\n";
    return 0;


}
