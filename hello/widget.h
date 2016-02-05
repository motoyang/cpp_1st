//
//  widget.h
//  hello
//
//  Created by xt on 15/11/26.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#ifndef __hello__widget__
#define __hello__widget__

#include <memory>

class Widget {
    struct Impl;
    std::unique_ptr<Impl> m_i;
    
public:
    Widget();
    ~Widget();
    
    Widget(Widget&& w);
    Widget& operator= (Widget&& w);
    
    Widget(const Widget& w);
    Widget& operator= (const Widget& w);
};

#endif /* defined(__hello__widget__) */
