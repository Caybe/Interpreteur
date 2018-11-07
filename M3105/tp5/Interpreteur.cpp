#include "Interpreteur.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

Interpreteur::Interpreteur(ifstream & fichier) :
m_lecteur(fichier), m_table(), m_arbre(nullptr) {
}

void Interpreteur::analyse() {
    m_arbre = programme(); // on lance l'analyse de la première règle
    if (nbErreurs != 0) {
        m_arbre = nullptr;
        cerr << "Nombres d'erreurs : " << nbErreurs << endl;
    }
}

void Interpreteur::tester(const string & symboleAttendu) const throw (SyntaxeException) {
    // Teste si le symbole courant est égal au symboleAttendu... Si non, lève une exception
    static char messageWhat[256];
    if (m_lecteur.getSymbole() != symboleAttendu) {
        sprintf(messageWhat,
                "Ligne %d, Colonne %d - Erreur de syntaxe - Symbole attendu : %s - Symbole trouvé : %s",
                m_lecteur.getLigne(), m_lecteur.getColonne(),
                symboleAttendu.c_str(), m_lecteur.getSymbole().getChaine().c_str());
        throw SyntaxeException(messageWhat);
    }
}

void Interpreteur::testerEtAvancer(const string & symboleAttendu) throw (SyntaxeException) {
    // Teste si le symbole courant est égal au symboleAttendu... Si oui, avance, Sinon, lève une exception
    try {
        tester(symboleAttendu);
        m_lecteur.avancer();
    } catch (const SyntaxeException& e) {
        cerr << e.what() << endl;
        nbErreurs++;
        m_lecteur.avancer();
    }
}

void Interpreteur::erreur(const string & message) const throw (SyntaxeException) {
    // Lève une exception contenant le message et le symbole courant trouvé
    // Utilisé lorsqu'il y a plusieurs symboles attendus possibles...
    static char messageWhat[256];
    sprintf(messageWhat,
            "Ligne %d, Colonne %d - Erreur de syntaxe - %s - Symbole trouvé : %s",
            m_lecteur.getLigne(), m_lecteur.getColonne(), message.c_str(), m_lecteur.getSymbole().getChaine().c_str());
    throw SyntaxeException(messageWhat);
}

Noeud* Interpreteur::programme() {
    // <programme> ::= procedure principale() <seqInst> finproc FIN_FICHIER
    testerEtAvancer("procedure");
    testerEtAvancer("principale");
    testerEtAvancer("(");
    testerEtAvancer(")");
    Noeud* sequence = seqInst();
    testerEtAvancer("finproc");
    try {
        tester("<FINDEFICHIER>");
    } catch (const SyntaxeException& e) {
        cerr << e.what() << endl;
        nbErreurs++;
    }
    return sequence;
}

Noeud* Interpreteur::seqInst() {
    // <seqInst> ::= <inst> { <inst> }
    NoeudSeqInst* sequence = new NoeudSeqInst();
    do {
        sequence->ajoute(inst());
    } while (m_lecteur.getSymbole() == "<VARIABLE>" || m_lecteur.getSymbole() == "si" || m_lecteur.getSymbole() == "selon" || m_lecteur.getSymbole() == "tantque" || m_lecteur.getSymbole() == "repeter" || m_lecteur.getSymbole() == "pour" || m_lecteur.getSymbole() == "ecrire" || m_lecteur.getSymbole() == "lire");
    // Tant que le symbole courant est un début possible d'instruction...
    // Il faut compléter cette condition chaque fois qu'on rajoute une nouvelle instruction
    return sequence;
}

Noeud* Interpreteur::inst() {
    // <inst> ::= <affectation>  ; | <instSiRiche> | <instTantQue> | <instPour> | <ecrire> | <lire>
    if (m_lecteur.getSymbole() == "<VARIABLE>") {
        Noeud *affect = affectation();
        testerEtAvancer(";");
        return affect;
    } else if (m_lecteur.getSymbole() == "si")
        return instSiRiche();
    else if (m_lecteur.getSymbole() == "tantque")
        return instTantQue();
    else if (m_lecteur.getSymbole() == "pour")
        return instPour();
    else if (m_lecteur.getSymbole() == "repeter") {
        Noeud *repeter = instRepeter();
        testerEtAvancer(";");
        return repeter;
    } else if (m_lecteur.getSymbole() == "lire") {
        Noeud *lire = instLire();
        testerEtAvancer(";");
        return lire;
    } else if (m_lecteur.getSymbole() == "ecrire") {
        Noeud *ecrire = instEcrire();
        testerEtAvancer(";");
        return ecrire;
    } else if (m_lecteur.getSymbole() == "selon") {
        Noeud *selon = instSelon();
        return selon;
    }// Compléter les alternatives chaque fois qu'on rajoute une nouvelle instruction
    else erreur("Instruction incorrecte");

}

Noeud* Interpreteur::affectation() {
    // <affectation> ::= <variable> = <expression> 
    try {
        tester("<VARIABLE>");
    } catch (const SyntaxeException& e) {
        cerr << e.what() << endl;
        nbErreurs++;
    }
    Noeud* var = m_table.chercheAjoute(m_lecteur.getSymbole()); // La variable est ajoutée à la table et on la mémorise
    m_lecteur.avancer();
    testerEtAvancer("=");
    Noeud* exp = expression(); // On mémorise l'expression trouvée
    return new NoeudAffectation(var, exp); // On renvoie un noeud affectation
}

Noeud* Interpreteur::expression() {
    // <expression> ::= <terme>  { + <terme>  | - <terme> }
    Noeud* term = terme();
    while (m_lecteur.getSymbole() == "+" || m_lecteur.getSymbole() == "-") {
        Symbole operateur = m_lecteur.getSymbole(); // On mémorise le symbole de l'opérateur
        m_lecteur.avancer();
        Noeud* termeDroit = terme(); // On mémorise l'opérande droit
        term = new NoeudOperateurBinaire(operateur, term, termeDroit); // Et on construuit un noeud opérateur binaire
    }
    return term; // On renvoie terme qui pointe sur la racine de l'expression
}

Noeud* Interpreteur::terme() {
    // <terme> ::= <facteur> { * <facteur> | / <facteur }
    Noeud* fact = facteur();
    while (m_lecteur.getSymbole() == "*" || m_lecteur.getSymbole() == "/") {
        Symbole operateur = m_lecteur.getSymbole(); // On mémorise le symbole de l'opérateur
        m_lecteur.avancer();
        Noeud* factDroit = facteur(); // On mémorise l'opérande droit
        fact = new NoeudOperateurBinaire(operateur, fact, factDroit); // Et on construuit un noeud opérateur binaire
    }
    return fact;
}

Noeud* Interpreteur::facteur() {
    // <facteur> ::= <entier> | <variable> | - <expBool> | non <expBool> | ( <expBool>  )
    Noeud* exprBool = nullptr;
    if (m_lecteur.getSymbole() == "<VARIABLE>" || m_lecteur.getSymbole() == "<ENTIER>") {
        exprBool = m_table.chercheAjoute(m_lecteur.getSymbole()); // on ajoute la variable ou l'entier à la table
        m_lecteur.avancer();
    } else if (m_lecteur.getSymbole() == "-") { // - <expBool>
        m_lecteur.avancer();
        // on représente le moins unaire (- expBool) par une soustraction binaire (0 - expBool)
        exprBool = new NoeudOperateurBinaire(Symbole("-"), m_table.chercheAjoute(Symbole("0")), expBool());
    } else if (m_lecteur.getSymbole() == "non") { // non <expBool>
        m_lecteur.avancer();
        // on représente le moins unaire (- expBool) par une soustractin binaire (0 - expBool)
        exprBool = new NoeudOperateurBinaire(Symbole("non"), expBool(), nullptr);
    } else if (m_lecteur.getSymbole() == "(") { // expression parenthésée
        m_lecteur.avancer();
        exprBool = expression();
        testerEtAvancer(")");
    } else
        erreur("Expression booléenne incorrect");
    return exprBool;
}

Noeud* Interpreteur::expBool() {
    // <expbool> ::= <relationET> { ou <relationEt> }
    Noeud* relEt = relationEt();
    while (m_lecteur.getSymbole() == "ou") {
        Symbole operateur = m_lecteur.getSymbole(); // On mémorise le symbole de l'opérateur
        m_lecteur.avancer();
        Noeud* relEtDroit = relationEt(); // On mémorise l'opérande droit
        relEt = new NoeudOperateurBinaire(operateur, relEt, relEtDroit); // Et on construuit un noeud opérateur binaire
    }
    return relEt;
}

Noeud* Interpreteur::relationEt() {
    // <relationET> ::= <relation> { et <relation> }
    Noeud* rel = relation();
    while (m_lecteur.getSymbole() == "et") {
        Symbole operateur = m_lecteur.getSymbole(); // On mémorise le symbole de l'opérateur
        m_lecteur.avancer();
        Noeud* relDroit = relation(); // On mémorise l'opérande droit
        rel = new NoeudOperateurBinaire(operateur, rel, relDroit); // Et on construuit un noeud opérateur binaire
    }
    return rel;
}

Noeud* Interpreteur::relation() {
    // <relation> ::= <expression> { <opRel> <expression> }
    Noeud* expr = expression();
    while (m_lecteur.getSymbole() == "==" || m_lecteur.getSymbole() == "!=" ||
            m_lecteur.getSymbole() == "<" || m_lecteur.getSymbole() == "<=" ||
            m_lecteur.getSymbole() == ">" || m_lecteur.getSymbole() == ">=") {
        Symbole op = opRel();
        Noeud* exprDroit = expression(); // On mémorise l'opérande droit
        expr = new NoeudOperateurBinaire(op, expr, exprDroit); // Et on construuit un noeud opérateur binaire
    }
    return expr;
}

Symbole Interpreteur::opRel() {
    if (m_lecteur.getSymbole() == "==" || m_lecteur.getSymbole() == "!=" ||
            m_lecteur.getSymbole() == "<" || m_lecteur.getSymbole() == "<=" ||
            m_lecteur.getSymbole() == ">" || m_lecteur.getSymbole() == ">=") {
        Symbole operateur = m_lecteur.getSymbole();
        m_lecteur.avancer();
        return operateur;
    } else {
        erreur("opérateur incorrect");
    }
}




//Noeud* Interpreteur::instSi() {
//  // <instSi> ::= si ( <expression> ) <seqInst> finsi
//  testerEtAvancer("si");
//  testerEtAvancer("(");
//  Noeud* condition = expression(); // On mémorise la condition
//  testerEtAvancer(")");
//  Noeud* sequence = seqInst();     // On mémorise la séquence d'instruction
//  testerEtAvancer("finsi");
//  return new NoeudInstSi(condition, sequence); // Et on renvoie un noeud Instruction Si
//}

Noeud* Interpreteur::instSiRiche() {
    //<instSiRiche> ::= si(<expression>)<seqInst> {sinon si(<expression>)<seqInst> }[sinon<seqInst>]finsi
    NoeudInstSiRiche* noeud = new NoeudInstSiRiche();
    testerEtAvancer("si");
    testerEtAvancer("(");
    noeud->ajouterCond(expBool());
    testerEtAvancer(")");
    noeud->ajouterSeq(seqInst());
    while (m_lecteur.getSymbole() == "sinonsi") {
        testerEtAvancer("sinonsi");
        testerEtAvancer("(");
        noeud->ajouterCond(expBool());
        testerEtAvancer(")");
        noeud->ajouterSeq(seqInst());
    }
    if (m_lecteur.getSymbole() == "sinon") {
        testerEtAvancer("sinon");
        noeud->ajouterSinon(seqInst());
    }
    testerEtAvancer("finsi");

    return noeud;

}

Noeud* Interpreteur::instTantQue() {
    testerEtAvancer("tantque");
    testerEtAvancer("(");
    Noeud* condition = expBool();
    testerEtAvancer(")");
    Noeud* sequence = seqInst();
    testerEtAvancer("fintantque");
    NoeudInstTantQue* noeud = new NoeudInstTantQue(condition, sequence);
    return noeud;
}

Noeud * Interpreteur::instRepeter() {
    testerEtAvancer("repeter");
    Noeud* sequence = seqInst();
    testerEtAvancer("jusqua");
    testerEtAvancer("(");
    Noeud* condition = expBool();
    testerEtAvancer(")");
    return new NoeudInstRepeter(condition, sequence);
}

Noeud* Interpreteur::instPour() {
    //<instPour>::= pour([<affectation>];<expression>;[<affectation>])< seqInst> finpour
    NoeudInstPour* noeud = new NoeudInstPour();

    testerEtAvancer("pour");


    testerEtAvancer("(");

    if (m_lecteur.getSymbole() != ";") {
        noeud->setInit(affectation());
    }

    testerEtAvancer(";");

    noeud->setCondition(expBool());

    testerEtAvancer(";");

    if (m_lecteur.getSymbole() != ")") {
        noeud->setIncrement(affectation());
    }

    testerEtAvancer(")");

    noeud->setSequence(seqInst());

    testerEtAvancer("finpour");


    return noeud;
}

Noeud* Interpreteur::instEcrire() {
    //<instEcrire>  ::= ecrire(<expression> |<chaine> {,<exp(string)expression->executer();ression> | <chaine> })
    testerEtAvancer("ecrire");
    testerEtAvancer("(");
    NoeudInstEcrire* noeud = new NoeudInstEcrire();
    bool premierPassage = true;

    do {
        if (!premierPassage) {
            testerEtAvancer(",");
        }
        if (m_lecteur.getSymbole() == "<CHAINE>") {
            Noeud* chaine = m_table.chercheAjoute(m_lecteur.getSymbole()); // La variable est ajoutée à la table et on la mémorise   
            noeud->ajouterInstruction(chaine);
            testerEtAvancer("<CHAINE>");

        } else {
            Noeud* instru = expBool();
            noeud->ajouterInstruction(instru);
        }
        premierPassage = false;

    } while (m_lecteur.getSymbole() != ")");

    testerEtAvancer(")");
    return noeud;
}

Noeud* Interpreteur::instLire() {
    //<instLire> ::=lire( <variable> {,<variable> })
    testerEtAvancer("lire");
    testerEtAvancer("(");
    try {
        tester("<VARIABLE>");
    } catch (const SyntaxeException& e) {
        cerr << e.what() << endl;
        nbErreurs++;
    }
    Noeud* var = m_table.chercheAjoute(m_lecteur.getSymbole());
    Noeud* noeud = new NoeudInstLire(var);
    m_lecteur.avancer();
    while (m_lecteur.getSymbole() != ")") {
        testerEtAvancer(",");
        try {
            tester("<VARIABLE>");
        } catch (const SyntaxeException& e) {
            cerr << e.what() << endl;
            nbErreurs++;
        }
        var = m_table.chercheAjoute(m_lecteur.getSymbole());
        noeud->ajoute(var);
        m_lecteur.avancer();
    }
    testerEtAvancer(")");
    return noeud;
}

void Interpreteur::traduitEncpp(ostream & cout, unsigned int indentation) const {
    cout << "#include <iostream>" << endl << endl;
    cout << "using namespace std;" << endl << endl;
    cout << setw(4 * indentation) << "" << "int main() {" << endl;
    for (int i = 0; i < m_table.getTaille(); i++) {
        if (m_table[i] == "<VARIABLE>") {
            cout << setw(4 * (indentation + 1)) << "" << "int " << m_table[i].getChaine() << ";" << endl;
        }
    }
    getArbre()->traduitEncpp(cout, indentation + 1);
    cout << setw(4 * (indentation + 1)) << "" << "return 0;" << endl;
    cout << setw(4 * indentation) << "}" << endl;
}

Noeud* Interpreteur::instSelon() {
    NoeudInstSelon* noeud = new NoeudInstSelon();
    testerEtAvancer("selon");
    testerEtAvancer("(");
    testerEtAvancer(",");
    try {
        tester("<VARIABLE>");
    } catch (const SyntaxeException& e) {
        cerr << e.what() << endl;
        nbErreurs++;
    }
    Noeud* var = m_table.chercheAjoute(m_lecteur.getSymbole());
    noeud->ajouterVar(var);
    m_lecteur.avancer();
    while (m_lecteur.getSymbole() == "cas") {
        testerEtAvancer("cas");
        try {
            tester("<ENTIER>");
        } catch (const SyntaxeException& e) {
            cerr << e.what() << endl;
            nbErreurs++;
        }
        Noeud* cas = m_table.chercheAjoute(m_lecteur.getSymbole());
        noeud->ajouterCas(cas);
        m_lecteur.avancer();
        testerEtAvancer(":");
        noeud->ajouterSeq(seqInst());
    }
    testerEtAvancer("defaut :");
        noeud->ajouterSeqDef(seqInst());
        testerEtAvancer("finselon");
    return noeud;
}


//procedure
//
//Noeud* Interpreteur::instProcedure() {
//    testerEtAvancer("procedure");
//    testerEtAvancer("(");
//    if (m_lecteur.getSymbole() == "<VARIABLE") {
//        m_table.chercheAjoute(m_lecteur.getSymbole()); // La variable est ajoutée à la table et on la mémorise
//        m_lecteur.avancer();
//        while (m_lecteur.getSymbole() == ",") {
//            m_table.chercheAjoute(m_lecteur.getSymbole()); // La variable est ajoutée à la table et on la mémorise
//            m_lecteur.avancer();
//        }
//    }
//
//
//    NoeudProc* noeud = new NoeudProc(seqInst);
//    return noeud;
//}

//Noeud* Interpreteur::instAppel(){
//    
//}

