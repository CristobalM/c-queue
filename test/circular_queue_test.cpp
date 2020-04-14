#include <gtest/gtest.h>

#include "circular_queue_wrapper.h"


#include <iostream>

using namespace std;


template<class T>
CircularStackWrapper<T> buildCS(uint capacity){
    return CircularStackWrapper<T>(capacity);
}

template<class T>
static inline void testCSPopFront(CircularStackWrapper<T> &cs, string msg=""){
    for(int i = 0; i < cs.capacity(); i++){
        cs.push((T)i);
    }

    for(int i = 0; i < cs.capacity(); i++){
        ASSERT_EQ(cs.pop_front(), (T)i) << "testCSPopFront fails at i=" << i << ", msg = " << msg;
    }
}

template<class T>
static inline void testCSPopBack(CircularStackWrapper<T> &cs, string msg=""){
    for(int i = 0; i < cs.capacity(); i++){
        cs.push((T)i);
    }

    for(int i = 0; i < cs.capacity(); i++){
        ASSERT_EQ(cs.pop_back(), (T)(cs.capacity()-1-i)) << "testCSPopBack fails at i=" << i << ", msg = " << msg;
    }
}



TEST(some_circular_queue_test_s, pop_front_test_1){
    auto csint = buildCS<int>(1000);
    auto csfloat = buildCS<float>(1000);
    auto cschar = buildCS<char>(1000);
    auto csdouble = buildCS<double>(1000);

    testCSPopFront(csint, "int");
    testCSPopFront(csfloat, "float");
    testCSPopFront(cschar, "char");
    testCSPopFront(csdouble, "double");

}


TEST(some_circular_queue_test_s, pop_back_test_1){
    auto csint = buildCS<int>(1000);
    auto csfloat = buildCS<float>(1000);
    auto cschar = buildCS<char>(1000);
    auto csdouble = buildCS<double>(1000);

    testCSPopBack(csint, "int");
    testCSPopBack(csfloat, "float");
    testCSPopBack(cschar, "char");
    testCSPopBack(csdouble, "double");
}


class SomeTestClass{
    public:
    int a;
    float b;
    double c;
    unsigned char d;
    
    SomeTestClass(int a, float b, double c, unsigned char d) : a(a), b(b), c(c), d(d) {}
    SomeTestClass() : SomeTestClass(0, 0 ,0, 0){}
    bool operator==(SomeTestClass const &rhs) const{
        return a == rhs.a && b == rhs.b && c == rhs.c && d == rhs.d;
    }
};

TEST(some_circular_queue_test_s, pop_front_test_1_stc){
    auto csstc = CircularStackWrapper<SomeTestClass>(1000);
    for(int i = 0; i < csstc.capacity(); i++){
        csstc.push(SomeTestClass(i, i, i, i));
    }

    for(int i = 0; i < csstc.capacity(); i++){
        ASSERT_EQ(csstc.pop_front(), SomeTestClass(i, i, i, i)) << "testCSPopFront fails at i=" << i << ", msg = " << "SomeTestClass";
    }
}


TEST(some_circular_queue_test_s, pop_back_test_1_stc){
    auto csstc = CircularStackWrapper<SomeTestClass>(1000);
    for(int i = 0; i < csstc.capacity(); i++){
        csstc.push(SomeTestClass(i, i, i, i));
    }

    int cap = csstc.capacity();
    for(int i = 0; i < csstc.capacity(); i++){
        int tc = cap - 1- i;
        ASSERT_EQ(csstc.pop_back(), SomeTestClass(tc, tc, tc, tc)) << "testCSPopFront fails at i=" << i << ", msg = " << "SomeTestClass";
    }
}

TEST(some_circular_queue_test_s, capacity_overflow_test){
    auto csint = buildCS<int>(10);

    try{
        for(int i = 0; i < 20; i++){
            csint.push(i);
        }

        FAIL() << "Expected cant_add_more_exception";
    }
    catch(cant_add_more_exception const & err){
        EXPECT_EQ(err.what(), std::string("Cant add more elements"));
    }
    catch(...){
        FAIL() << "Expected cant_add_more_exception";
    }


}
