/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass2.cpp
 * Author: sulmontm
 *
 * Created on Nov 7, 2018, 11:44:13 AM
 */

#include "newtestclass2.h"
#include "ArbreAbstrait.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass2);

newtestclass2::newtestclass2() {
}

newtestclass2::~newtestclass2() {
}

void newtestclass2::setUp() {
}

void newtestclass2::tearDown() {
}

void newtestclass2::testNoeudInstTantQue() {
    Noeud* condition;
    Noeud* sequence;
    NoeudInstTantQue noeudInstTantQue(condition, sequence);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void newtestclass2::testExecuter() {
    NoeudInstTantQue noeudInstTantQue;
    int result = noeudInstTantQue.executer();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void newtestclass2::testTraduitEncpp() {
    ostream& cout;
    unsigned int indentation;
    NoeudInstTantQue noeudInstTantQue;
    noeudInstTantQue.traduitEncpp(cout, indentation);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

