/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TestTantQue.h
 * Author: sulmontm
 *
 * Created on Nov 6, 2018, 3:41:13 PM
 */

#ifndef TESTTANTQUE_H
#define TESTTANTQUE_H

#include <cppunit/extensions/HelperMacros.h>

class TestTantQue : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(TestTantQue);

    CPPUNIT_TEST(testNoeudInstTantQue);
    CPPUNIT_TEST(testExecuter);
    CPPUNIT_TEST(testTraduitEncpp);

    CPPUNIT_TEST_SUITE_END();

public:
    TestTantQue();
    virtual ~TestTantQue();
    void setUp();
    void tearDown();

private:
    void testNoeudInstTantQue();
    void testExecuter();
    void testTraduitEncpp();

};

#endif /* TESTTANTQUE_H */

