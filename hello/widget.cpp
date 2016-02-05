//
//  widget.cpp
//  hello
//
//  Created by xt on 15/11/26.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#include "widget.h"
#include <string>

struct Widget::Impl {
    int i;
    double d;
    std::string s;
};

Widget::Widget()
: m_i(std::make_unique<Impl>())
{}

Widget::~Widget() = default;

Widget::Widget(Widget&& w) = default;

Widget& Widget::operator=(Widget&& w) = default;

Widget::Widget(const Widget& w)
: m_i(std::make_unique<Impl>(*w.m_i))
{}

Widget& Widget::operator=(const Widget& w) {
    *m_i = *w.m_i;
    return *this;
}
