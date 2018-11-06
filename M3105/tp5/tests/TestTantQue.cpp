/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TestTantQue.cpp
 * Author: sulmontm
 *
 * Created on Nov 6, 2018, 3:41:13 PM
 */

#include "TestTantQue.h"
#include <iostream>
#include "../Interpreteur.h"
using namespace std;
CPPUNIT_TEST_SUITE_REGISTRATION(TestTantQue);

TestTantQue::TestTantQue() {
}

TestTantQue::~TestTantQue() {
}

void TestTantQue::setUp() {
}

void TestTantQue::tearDown() {
}

void TestTantQue::testNoeudInstTantQue() {

}

void TestTantQue::testExecuter() {
    ifstream fichier("testTantQue");
    Interpreteur interpreteur(fichier);
    interpreteur.analyse();
    int i = 0;
    int res = 0;
    while (i < interpreteur.getTable().getTaille() && res == 0) {
        if (interpreteur.getTable()[i].getChaine() == "b") {
            res = interpreteur.getTable()[i].executer();
        }
    }
    CPPUNIT_ASSERT_MESSAGE("test 1 ", res == 1024);
}

void TestTantQue::testTraduitEncpp() {
    ostream& cout;
    unsigned int indentation;
    NoeudInstTantQue noeudInstTantQue;
    noeudInstTantQue.traduitEncpp(cout, indentation);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

