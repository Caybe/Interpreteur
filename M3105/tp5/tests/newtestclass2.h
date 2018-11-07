/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass2.h
 * Author: sulmontm
 *
 * Created on Nov 7, 2018, 11:44:13 AM
 */

#ifndef NEWTESTCLASS2_H
#define NEWTESTCLASS2_H

#include <cppunit/extensions/HelperMacros.h>

class newtestclass2 : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(newtestclass2);

    CPPUNIT_TEST(testNoeudInstTantQue);
    CPPUNIT_TEST(testExecuter);
    CPPUNIT_TEST(testTraduitEncpp);

    CPPUNIT_TEST_SUITE_END();

public:
    newtestclass2();
    virtual ~newtestclass2();
    void setUp();
    void tearDown();

private:
    void testNoeudInstTantQue();
    void testExecuter();
    void testTraduitEncpp();

};

#endif /* NEWTESTCLASS2_H */

