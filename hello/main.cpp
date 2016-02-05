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
#include "printtuple.hpp"
#include "widget.h"

/*
template <typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params) {
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}
*/

/* c++ 14 version
class Person {
    std::string name;
public:
    template<
    typename T,
    typename = std::enable_if_t<
    !std::is_base_of<Person, std::decay_t<T>>::value
    &&
    !std::is_integral<std::remove_reference_t<T>>::value
    >
    >
    explicit Person(T&& n)
        : name(std::forward<T>(n))
    {
        // assert that a std::string can be created from a T object
        static_assert(
                      std::is_constructible<std::string, T>::value,
                      "Parameter n can't be used to construct a std::string"
                      );
    }
    
    explicit Person(int n)
    {
        std::ostringstream oss;
        oss << "name is " << n;
        name = oss.str();
    }
    
    std::string get_name() {
        return name;
    }
};
*/

// c++ 11 version
class Person {
    std::string name;
public:
    template<
    typename T,
    typename = typename std::enable_if<
    !std::is_base_of<Person, typename std::decay<T>::type>::value
    &&
    !std::is_integral<typename std::remove_reference<T>::type>::value
    >::type
    >
    explicit Person(T&& n)
    : name(std::forward<T>(n))
    {
        // assert that a std::string can be created from a T object
        static_assert(
                      std::is_constructible<std::string, T>::value,
                      "Parameter n can't be used to construct a std::string"
                      );
    }
    
    explicit Person(int n)
    {
        std::ostringstream oss;
        oss << "name is " << n;
        name = oss.str();
    }
    
    std::string get_name() {
        return name;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...

    std::tuple<int, std::string, double, std::string> t{1, "a", 2.2, "bb"};
    std::cout << t << std::endl;
    
    print(std::cout, 1, 1.2, 2.3, "abc", std::bitset<16>(377), "ddd");
    
    Widget w;
    Widget w2 = w;
    Widget w3(w2);
    Widget w4 = std::move(w);
    
    Person p("pppp");
    std::cout << p.get_name() << std::endl;
    Person pp2(12);
    std::cout << pp2.get_name() << std::endl;
    
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
