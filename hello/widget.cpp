//
//  widget.cpp
//  hello
//
//  Created by xt on 15/11/26.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#include "widget.h"
#include <string>
#include <iostream>

struct Widget::Impl {
    Impl() { ++ref; std::cout << "++ref1" << std::endl; }
    Impl(const Impl& i) { ++ref; std::cout << "++ref2" << std::endl; }
    ~Impl() { --ref; std::cout << "--ref" << std::endl; }
    
    int i;
    double d;
    std::string s;
    static int ref;
};

int Widget::m_count = 0;
int Widget::Impl::ref = 0;

Widget::Widget()
: m_i(std::make_unique<Impl>())
{
    ++m_count;
    std::cout << "Widget::Widget(), m_count=" << m_count << ", m_i.ref=" << Impl::ref << std::endl;
}

Widget::~Widget() //= default;
{
//    if (m_i) --m_count;
//    else std::cout << "Keep m_count!!!" << std::endl;
    
    --m_count;
    std::cout << "Widget::~Widget(), m_count=" << m_count << ", m_i.ref=" << Impl::ref << std::endl;
}

Widget::Widget(Widget&& w) //= default;
{
    ++m_count;
    std::cout << "Widget::Widget(Widget&& w), m_count=" << m_count << ", m_i.ref=" << Impl::ref << std::endl;
    m_i = std::move(w.m_i);
    w.m_i = nullptr;
}

Widget& Widget::operator=(Widget&& w) //= default;
{
    std::cout << "Widget::operator=(Widget&& w), m_count=" << m_count << ", m_i.ref=" << Impl::ref << std::endl;
    m_i = std::move(w.m_i);
    w.m_i = nullptr;
    
    return *this;
}

Widget::Widget(const Widget& w)
: m_i(std::make_unique<Impl>(*w.m_i))
{
    ++m_count;
    std::cout << "Widget::(const Widget& w), m_count=" << m_count << ", m_i.ref=" << Impl::ref << std::endl;
}

Widget& Widget::operator=(const Widget& w) {
    std::cout << "Widget::operator=(const Widget& w), m_count=" << m_count << ", m_i.ref=" << Impl::ref << std::endl;
    *m_i = *w.m_i;
    return *this;
}
