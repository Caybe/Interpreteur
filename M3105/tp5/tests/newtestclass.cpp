/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass.cpp
 * Author: sulmontm
 *
 * Created on Nov 6, 2018, 3:35:58 PM
 */

#include "newtestclass.h"
#include "Interpreteur.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass);

newtestclass::newtestclass() {
}

newtestclass::~newtestclass() {
}

void newtestclass::setUp() {
}

void newtestclass::tearDown() {
}

void newtestclass::testTantQue() {
    Interpreteur interpreteur;
    interpreteur.analyse();
    
}

