//
//  person.h
//  hello
//
//  Created by xt on 16/2/15.
//  Copyright © 2016年 xt. All rights reserved.
//

#ifndef person_h
#define person_h

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


#endif /* person_h */
