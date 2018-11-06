/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass1.cpp
 * Author: sulmontm
 *
 * Created on Nov 6, 2018, 3:38:23 PM
 */

#include "newtestclass1.h"
#include "ArbreAbstrait.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass1);

newtestclass1::newtestclass1() {
}

newtestclass1::~newtestclass1() {
}

void newtestclass1::setUp() {
}

void newtestclass1::tearDown() {
}

void newtestclass1::testNoeudInstTantQue() {
    Noeud* condition;
    Noeud* sequence;
    NoeudInstTantQue noeudInstTantQue(condition, sequence);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void newtestclass1::testExecuter() {
    NoeudInstTantQue noeudInstTantQue;
    int result = noeudInstTantQue.executer();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void newtestclass1::testTraduitEncpp() {
    ostream& cout;
    unsigned int indentation;
    NoeudInstTantQue noeudInstTantQue;
    noeudInstTantQue.traduitEncpp(cout, indentation);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

