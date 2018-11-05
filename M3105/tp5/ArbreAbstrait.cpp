#include <stdlib.h>
#include "ArbreAbstrait.h"
#include "Symbole.h"
#include "SymboleValue.h"
#include "Exceptions.h"

////////////////////////////////////////////////////////////////////////////////
// NoeudSeqInst
////////////////////////////////////////////////////////////////////////////////

NoeudSeqInst::NoeudSeqInst() : m_instructions() {
}

int NoeudSeqInst::executer() {
    for (unsigned int i = 0; i < m_instructions.size(); i++)
        m_instructions[i]->executer(); // on exécute chaque instruction de la séquence
    return 0; // La valeur renvoyée ne représente rien !
}

void NoeudSeqInst::ajoute(Noeud* instruction) {
    if (instruction != nullptr) m_instructions.push_back(instruction);
}

void NoeudSeqInst::traduitEncpp(ostream & cout, unsigned int indentation) const{
    for (unsigned int i = 0; i < m_instructions.size(); i++)
        m_instructions[i]->traduitEncpp(cout, indentation+1); // on exécute chaque instruction de la séquence
}


////////////////////////////////////////////////////////////////////////////////
// NoeudAffectation
////////////////////////////////////////////////////////////////////////////////

NoeudAffectation::NoeudAffectation(Noeud* variable, Noeud* expression)
: m_variable(variable), m_expression(expression) {
}

int NoeudAffectation::executer() {
    int valeur = m_expression->executer(); // On exécute (évalue) l'expression
    ((SymboleValue*) m_variable)->setValeur(valeur); // On affecte la variable
    return 0; // La valeur renvoyée ne représente rien !
}

void NoeudAffectation::traduitEncpp(ostream & cout, unsigned int indentation) const{
    m_variable->traduitEncpp(cout, 0);
    m_expression->traduitEncpp(cout, 0);
}

////////////////////////////////////////////////////////////////////////////////
// NoeudOperateurBinaire
////////////////////////////////////////////////////////////////////////////////

NoeudOperateurBinaire::NoeudOperateurBinaire(Symbole operateur, Noeud* operandeGauche, Noeud* operandeDroit)
: m_operateur(operateur), m_operandeGauche(operandeGauche), m_operandeDroit(operandeDroit) {
}

int NoeudOperateurBinaire::executer() {
    int og, od, valeur;
    if (m_operandeGauche != nullptr) og = m_operandeGauche->executer(); // On évalue l'opérande gauche
    if (m_operandeDroit != nullptr) od = m_operandeDroit->executer(); // On évalue l'opérande droit
    // Et on combine les deux opérandes en fonctions de l'opérateur
    if (this->m_operateur == "+") valeur = (og + od);
    else if (this->m_operateur == "-") valeur = (og - od);
    else if (this->m_operateur == "*") valeur = (og * od);
    else if (this->m_operateur == "==") valeur = (og == od);
    else if (this->m_operateur == "!=") valeur = (og != od);
    else if (this->m_operateur == "<") valeur = (og < od);
    else if (this->m_operateur == ">") valeur = (og > od);
    else if (this->m_operateur == "<=") valeur = (og <= od);
    else if (this->m_operateur == ">=") valeur = (og >= od);
    else if (this->m_operateur == "et") valeur = (og && od);
    else if (this->m_operateur == "ou") valeur = (og || od);
    else if (this->m_operateur == "non") valeur = (!og);
    else if (this->m_operateur == "/") {
        if (od == 0) throw DivParZeroException();
        valeur = og / od;
    }
    return valeur; // On retourne la valeur calculée
}

void NoeudOperateurBinaire::traduitEncpp(ostream & cout, unsigned int indentation) const {
    if (m_operandeGauche != nullptr) m_operandeGauche->traduitEncpp(cout, indentation+1);
    if (m_operandeDroit != nullptr) m_operandeDroit->traduitEncpp(cout, indentation+1);
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstSi
////////////////////////////////////////////////////////////////////////////////

NoeudInstSiRiche::NoeudInstSiRiche() {
}

int NoeudInstSiRiche::executer() {
    bool b = true;
    for (int i = 0; i < m_conditions.size() && b; i++) {
        if (m_conditions[i]->executer()) {
            m_sequences[i]->executer();
            b = false;
        };
    }
    if (b) {
        m_sinon->executer();
    }
    return 0; // La valeur renvoyée ne représente rien !
}

void NoeudInstSiRiche::ajouterCond(Noeud* condition) {
    m_conditions.push_back(condition);
}

void NoeudInstSiRiche::ajouterSeq(Noeud* sequence) {
    m_sequences.push_back(sequence);
}

void NoeudInstSiRiche::ajouterSinon(Noeud* sequence) {
    m_sinon = sequence;
}

void NoeudInstSiRiche::traduitEncpp(ostream & cout, unsigned int indentation) const {

    cout << setw(4 * indentation) << "" << "if (";
    for (int i = 0; i < m_conditions.size(); i++) {
        m_conditions[i]->traduitEncpp(cout, 0);
        cout << setw(4 * indentation) << "" << ")";
        cout << setw(4 * indentation) << "" << "{";
        m_sequences[i]->traduitEncpp(cout, 0);
        cout << setw(4 * indentation) << "" << "}";
        if (i < m_conditions.size() - 1) {
            cout << setw(4 * indentation) << "" << "else if (";
        }
    }
    if (m_sinon != nullptr) {
        cout << setw(4 * indentation) << "" << "else {";
        m_sinon->traduitEncpp(cout, indentation+1);
        cout << setw(4 * indentation) << "" << "}";
    }

}


////////////////////////////////////////////////////////////////////////////////
// NoeudInstTantQue
////////////////////////////////////////////////////////////////////////////////

NoeudInstTantQue::NoeudInstTantQue(Noeud* condition, Noeud* sequence) : m_condition(condition), m_sequence(sequence) {
}

int NoeudInstTantQue::executer() {
    while (m_condition->executer()) {
        m_sequence->executer();
    }
    return 0;
}

void NoeudInstTantQue::traduitEncpp(ostream& cout, unsigned int indentation) const{
    cout << setw(4 * indentation) << "" << "while (";
    m_condition->traduitEncpp(cout,0);
    cout << ") {"<<endl;
    m_sequence->traduitEncpp(cout, indentation+1);
    cout<< setw(4*indentation) << "" << "}" << endl;
}



////////////////////////////////////////////////////////////////////////////////
// NoeudInstRepeter
////////////////////////////////////////////////////////////////////////////////

NoeudInstRepeter::NoeudInstRepeter(Noeud* condition, Noeud* sequence) : m_condition(condition), m_sequence(sequence) {
}

int NoeudInstRepeter::executer() {
    do {
        m_sequence->executer();
    } while (!m_condition->executer());
    return 0;
}
void NoeudInstRepeter::traduitEncpp(ostream& cout, unsigned int indentation) const{
    cout << setw(4 * indentation) << "" << "do {";
    m_sequence->traduitEncpp(cout,indentation+1);
    cout << setw(4*indentation) << "" << "} while (";
    m_condition->traduitEncpp(cout,0);
    cout << ");" << endl;
}
////////////////////////////////////////////////////////////////////////////////
// NoeudInstEcrire
////////////////////////////////////////////////////////////////////////////////

NoeudInstEcrire::NoeudInstEcrire() {
}

void NoeudInstEcrire::ajouterInstruction(Noeud* instruction) {
    m_chaines.push_back(instruction);
}

int NoeudInstEcrire::executer() {


    for (auto v : m_chaines) {
        if ((typeid (*v) == typeid (SymboleValue)) && *((SymboleValue*) v) == "<CHAINE>") {
            string chaine = ((SymboleValue*) v)->getChaine();
            chaine = chaine.substr(1, chaine.size() - 2);
            cout << chaine;
        } else {
            cout << v->executer();
        }
    }
    return 0;
}

void NoeudInstEcrire::traduitEncpp(ostream& cout, unsigned int indentation) const{
    cout<<setw(4*indentation)<<""<<"cout";
    for (auto v : m_chaines) {
        if ((typeid (*v) == typeid (SymboleValue)) && *((SymboleValue*) v) == "<CHAINE>") {
            string chaine = ((SymboleValue*) v)->getChaine();
            chaine = chaine.substr(1, chaine.size() - 2);
            cout << " << " << chaine;
            
        } else {
            cout << " << ";
            v->traduitEncpp(cout, 0);
        }
    }
    cout<<" << endl;";
}


////////////////////////////////////////////////////////////////////////////////
// NoeudInstPour
////////////////////////////////////////////////////////////////////////////////

NoeudInstPour::NoeudInstPour() {
}

int NoeudInstPour::executer() {
    if (m_init != nullptr) {
        m_init->executer();
    }
    while (m_condition->executer()) {
        m_sequence->executer();
        if (m_increment != nullptr) {
            m_increment->executer();
        }cout << " ; ";
    }
    return 0;
}

void NoeudInstPour::traduitEncpp(ostream& cout, unsigned int indentation) const{
    cout << setw(4*indentation) << "" << "for(int ";
    m_init->traduitEncpp(cout,0);
    cout << " ; ";
    m_condition->traduitEncpp(cout,0);
    cout << " ; ";
    m_increment->traduitEncpp(cout,0);
    cout<< " ) {" << endl;
    m_sequence->traduitEncpp(cout,indentation++);
    cout << setw(4*indentation) << "" << "}"<<endl;
    
}


////////////////////////////////////////////////////////////////////////////////
// NoeudInstLire
////////////////////////////////////////////////////////////////////////////////

NoeudInstLire::NoeudInstLire(Noeud* variable) {
    m_variables.push_back(variable);
}

int NoeudInstLire::executer() {
    int valeur;
    for (Noeud* var : m_variables) {
        cin >> valeur;
        ((SymboleValue*) var)->setValeur(valeur);
    }
    return 0;
}

void NoeudInstLire::traduitEncpp(ostream& cout, unsigned int indentation) const {
    cout<<setw(4*indentation)<<""<<"cin";
    
    for (Noeud* var : m_variables) {
        cout << " >> ";
        var->traduitEncpp(cout, 0);
    }
    cout<<setw(4*indentation)<<""<<";";
}

