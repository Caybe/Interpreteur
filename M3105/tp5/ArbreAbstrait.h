#ifndef ARBREABSTRAIT_H
#define ARBREABSTRAIT_H

// Contient toutes les déclarations de classes nécessaires
//  pour représenter l'arbre abstrait

#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;
#include <typeinfo>
#include "Symbole.h"
#include "Exceptions.h"

////////////////////////////////////////////////////////////////////////////////

class Noeud {
    // Classe abstraite dont dériveront toutes les classes servant à représenter l'arbre abstrait
    // Remarque : la classe ne contient aucun constructeur
public:
    virtual int executer() = 0; // Méthode pure (non implémentée) qui rend la classe abstraite

    virtual void ajoute(Noeud* instruction) {
        throw OperationInterditeException();
    }

    virtual void traduitEncpp(ostream & cout, unsigned int indentation) const = 0;

    virtual ~Noeud() {
    } // Présence d'un destructeur virtuel conseillée dans les classes abstraites
};

////////////////////////////////////////////////////////////////////////////////

class NoeudSeqInst : public Noeud {
    // Classe pour représenter un noeud "sequence d'instruction"
    //  qui a autant de fils que d'instructions dans la séquence
public:
    NoeudSeqInst(); // Construit une séquence d'instruction vide

    ~NoeudSeqInst() {
    } // A cause du destructeur virtuel de la classe Noeud
    int executer(); // Exécute chaque instruction de la séquence
    void ajoute(Noeud* instruction); // Ajoute une instruction à la séquence
    void traduitEncpp(ostream & cout, unsigned int indentation) const;
private:
    vector<Noeud *> m_instructions; // pour stocker les instructions de la séquence
};

////////////////////////////////////////////////////////////////////////////////

class NoeudAffectation : public Noeud {
    // Classe pour représenter un noeud "affectation"
    //  composé de 2 fils : la variable et l'expression qu'on lui affecte
public:
    NoeudAffectation(Noeud* variable, Noeud* expression); // construit une affectation

    ~NoeudAffectation() {
    } // A cause du destructeur virtuel de la classe Noeud
    int executer(); // Exécute (évalue) l'expression et affecte sa valeur à la variable
    void traduitEncpp(ostream & cout, unsigned int indentation) const;
private:
    Noeud* m_variable;
    Noeud* m_expression;
};

////////////////////////////////////////////////////////////////////////////////

class NoeudOperateurBinaire : public Noeud {
    // Classe pour représenter un noeud "opération binaire" composé d'un opérateur
    //  et de 2 fils : l'opérande gauche et l'opérande droit
public:
    NoeudOperateurBinaire(Symbole operateur, Noeud* operandeGauche, Noeud* operandeDroit);
    // Construit une opération binaire : operandeGauche operateur OperandeDroit

    ~NoeudOperateurBinaire() {
    } // A cause du destructeur virtuel de la classe Noeud
    int executer(); // Exécute (évalue) l'opération binaire)
    void traduitEncpp(ostream & cout, unsigned int indentation) const;
private:
    Symbole m_operateur;
    Noeud* m_operandeGauche;
    Noeud* m_operandeDroit;
};

////////////////////////////////////////////////////////////////////////////////

class NoeudInstSiRiche : public Noeud {
    // Classe pour représenter un noeud "instruction si"
    //  et ses 2 fils : la condition du si et la séquence d'instruction associée
public:
    NoeudInstSiRiche();
    // Construit une "instruction si" avec sa condition et sa séquence d'instruction

    ~NoeudInstSiRiche() {
    } // A cause du destructeur virtuel de la classe Noeud
    int executer(); // Exécute l'instruction si : si condition vraie on exécute la séquence
    void ajouterCond(Noeud* condition);
    void ajouterSeq(Noeud* sequence);
    void ajouterSinon(Noeud* sequence);
    void traduitEncpp(ostream & cout, unsigned int indentation) const;
private:
    vector<Noeud*> m_conditions;
    vector<Noeud*> m_sequences;
    Noeud* m_sinon;
};
////////////////////////////////////////////////////////////////////////////////

class NoeudInstTantQue : public Noeud {
    // Classe pour représenter un noeud "instruction tant que"
public:
    NoeudInstTantQue(Noeud* condition, Noeud* sequence);
    // Construit une "instruction tant que" avec sa condition et sa séquence d'instruction

    ~NoeudInstTantQue() {
    } // A cause du destructeur virtuel de la classe Noeud
    int executer(); // Exécute l'instruction tant que : si condition vraie on exécute la séquence
    void traduitEncpp(ostream & cout, unsigned int indentation) const;
private:
    Noeud* m_condition;
    Noeud* m_sequence;
};

////////////////////////////////////////////////////////////////////////////////

class NoeudInstRepeter : public Noeud {
public:
    NoeudInstRepeter(Noeud* condition, Noeud* sequence);
    
    ~NoeudInstRepeter() {
    }
    int executer();
    void traduitEncpp(ostream & cout, unsigned int indentation) const;
private:
    Noeud* m_condition;
    Noeud* m_sequence;
};

////////////////////////////////////////////////////////////////////////////////

class NoeudInstEcrire : public Noeud {
    // Classe pour représenter un noeud "instruction ecrire"
public:
    NoeudInstEcrire();

    ~NoeudInstEcrire() {
    } // A cause du destructeur virtuel de la classe Noeud
    void ajouterInstruction(Noeud* instruction);
    int executer(); // Exécute l'instruction ecrire
    void traduitEncpp(ostream & cout, unsigned int indentation) const;
private:
    vector<Noeud*> m_chaines;

};

////////////////////////////////////////////////////////////////////////////////

class NoeudInstPour : public Noeud {
public:

    NoeudInstPour();

    ~NoeudInstPour() {
    }
    int executer();
    
    inline void setSequence(Noeud * seq) {
        m_sequence = seq;
    }

    inline void setCondition(Noeud * cond) {
        m_condition = cond;
    }

    inline void setInit(Noeud * init) {
        m_init = init;
    }

    inline void setIncrement(Noeud * incr) {
        m_increment = incr;
    }
    void traduitEncpp(ostream & cout, unsigned int indentation) const;
private:
    Noeud* m_init;
    Noeud* m_condition;
    Noeud* m_increment;
    Noeud* m_sequence;
};

////////////////////////////////////////////////////////////////////////////////

class NoeudInstLire : public Noeud {
public:
    NoeudInstLire(Noeud* variable);

    ~NoeudInstLire() {
    }
    int executer();

    inline void ajoute(Noeud* variable) {
        m_variables.push_back(variable);
    }
    void traduitEncpp(ostream & cout, unsigned int indentation) const;
private:
    vector<Noeud*> m_variables;
};
#endif /* ARBREABSTRAIT_H */
