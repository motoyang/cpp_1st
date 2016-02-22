//
//  printtuple.hpp
//  hello
//
//  Created by xt on 15/12/23.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#ifndef hello_printtuple_hpp
#define hello_printtuple_hpp

#include <tuple>
#include <iostream>

// ----------------------------
// 输出tuple
// ----------------------------
template <int IDX, int MAX, typename... Args>
struct PRINT_TUPLE {
    static void print(std::ostream& strm, const std::tuple<Args...>& t) {
        strm << std::get<IDX>(t) << (IDX+1 == MAX ? "" : ", ");
        PRINT_TUPLE<IDX+1, MAX, Args...>::print(strm, t);
    }
};

template <int MAX, typename... Args>
struct PRINT_TUPLE<MAX, MAX, Args...> {
    static void print(std::ostream& strm, const std::tuple<Args...>& t) {}
};

template <typename... Args>
std::ostream& operator<< (std::ostream& strm, const std::tuple<Args...>& t) {
    strm << "(";
    PRINT_TUPLE<0, sizeof...(Args), Args...>::print(strm, t);
    return strm << ")";
}

// ----------------------------
// 输出不同类型的多个参数
// ----------------------------
void print(std::ostream& strm)
{
    strm << std::endl;
}

template<typename T, typename... Types>
void print(std::ostream& strm, const T& firstArg, const Types&... args)
{
    strm << firstArg << (sizeof...(args) > 0 ? ", " : "");
    print(strm, args...);
}

// ----------------------------
// 输出stl的vector容器
// ----------------------------
template <typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& v) {
    o << "[";
    for (auto i = v.cbegin(); i < v.cend(); ++i) {
        o << *i;
        if (i+1 != v.cend()) {
            o << ",";
        }
    }
    return o << "]";
}

#endif
