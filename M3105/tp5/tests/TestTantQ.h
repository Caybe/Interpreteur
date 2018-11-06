/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TestTantQ.h
 * Author: sulmontm
 *
 * Created on Nov 6, 2018, 4:39:47 PM
 */

#ifndef TESTTANTQ_H
#define TESTTANTQ_H

#include <cppunit/extensions/HelperMacros.h>

class TestTantQ : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(TestTantQ);

    CPPUNIT_TEST(testExecuter);
    CPPUNIT_TEST(testTraduitEncpp);

    CPPUNIT_TEST_SUITE_END();

public:
    TestTantQ();
    virtual ~TestTantQ();
    void setUp();
    void tearDown();

private:
    void testExecuter();
    void testTraduitEncpp();

};

#endif /* TESTTANTQ_H */

