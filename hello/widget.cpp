//
//  widget.cpp
//  hello
//
//  Created by xt on 15/11/26.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#include <string>
#include <iostream>
#include "widget.h"

struct Widget::Impl {
    Impl() { ++impl; std::cout << "++impl1" << std::endl; }
    Impl(const Impl& i) { ++impl; std::cout << "++impl2" << std::endl; }
    ~Impl() { --impl; std::cout << "--impl" << std::endl; }
    
    int i;
    double d;
    std::string s;
    static int impl;
};

int Widget::widget = 0;
int Widget::Impl::impl = 0;

Widget::Widget()
: m_i(std::make_unique<Impl>())
{
    ++widget;
    std::cout << "Widget::Widget(), widget=" << widget << ", m_i.impl=" << Impl::impl << std::endl;
}

Widget::~Widget() //= default;
{
    --widget;
    std::cout << "Widget::~Widget(), widget=" << widget << ", m_i.impl=" << Impl::impl << std::endl;
}

Widget::Widget(Widget&& w) //= default;
{
    ++widget;
    std::cout << "Widget::Widget(Widget&& w), widget=" << widget << ", m_i.impl=" << Impl::impl << std::endl;
    m_i = std::move(w.m_i);
    w.m_i = nullptr;
}

Widget& Widget::operator=(Widget&& w) //= default;
{
    std::cout << "Widget::operator=(Widget&& w), widget=" << widget << ", m_i.impl=" << Impl::impl << std::endl;
    m_i = std::move(w.m_i);
    w.m_i = nullptr;
    
    return *this;
}

Widget::Widget(const Widget& w)
: m_i(std::make_unique<Impl>(*w.m_i))
{
    ++widget;
    std::cout << "Widget::(const Widget& w), widget=" << widget << ", m_i.impl=" << Impl::impl << std::endl;
}

Widget& Widget::operator=(const Widget& w) {
    std::cout << "Widget::operator=(const Widget& w), widget=" << widget << ", m_i.impl=" << Impl::impl << std::endl;
    *m_i = *w.m_i;
    return *this;
}
