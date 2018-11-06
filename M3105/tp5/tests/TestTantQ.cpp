/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TestTantQ.cpp
 * Author: sulmontm
 *
 * Created on Nov 6, 2018, 4:39:47 PM
 */

#include "TestTantQ.h"
#include "../ArbreAbstrait.h"


CPPUNIT_TEST_SUITE_REGISTRATION(TestTantQ);

TestTantQ::TestTantQ() {
}

TestTantQ::~TestTantQ() {
}

void TestTantQ::setUp() {
}

void TestTantQ::tearDown() {
}

void TestTantQ::testExecuter() {
    NoeudInstTantQue noeudInstTantQue;
    int result = noeudInstTantQue.executer();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void TestTantQ::testTraduitEncpp() {
    ostream& cout;
    unsigned int indentation;
    NoeudInstTantQue noeudInstTantQue;
    noeudInstTantQue.traduitEncpp(cout, indentation);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

