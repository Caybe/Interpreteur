/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass1.h
 * Author: sulmontm
 *
 * Created on Nov 6, 2018, 3:38:23 PM
 */

#ifndef NEWTESTCLASS1_H
#define NEWTESTCLASS1_H

#include <cppunit/extensions/HelperMacros.h>

class newtestclass1 : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(newtestclass1);

    CPPUNIT_TEST(testNoeudInstTantQue);
    CPPUNIT_TEST(testExecuter);
    CPPUNIT_TEST(testTraduitEncpp);

    CPPUNIT_TEST_SUITE_END();

public:
    newtestclass1();
    virtual ~newtestclass1();
    void setUp();
    void tearDown();

private:
    void testNoeudInstTantQue();
    void testExecuter();
    void testTraduitEncpp();

};

#endif /* NEWTESTCLASS1_H */

