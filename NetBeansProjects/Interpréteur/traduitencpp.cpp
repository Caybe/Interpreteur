#include <iostream>

using namespace std;

int main() {
    int i;
    int j;
    int k;
    cout << "Test de la priorité des opérateurs" << endl;
    cout << "*********************************" << endl;
    cout << " " << endl;
    cout << "* Priorité de la multiplication :" << endl;
    cout << "    i = 2 + 4 * 6" << endl;
    cout << " Résultat attendu : " << endl;
    cout << "    i = 26 (et non i = 36 sans priorité des opérateurs) " << endl;
    cout << " Résultat : " << endl;
    i = 2 + 4 * 6;
    cout << "    i= " << i << endl;
    cout << "" << endl;
    cout << "* Priorité des parenthèses :" << endl;
    cout << "    j = (2 + 4) * 6" << endl;
    cout << " Résultat attendu : " << endl;
    cout << "    j = 36 (et non i = 26 sans priorité des opérateurs) " << endl;
    cout << " Résultat : " << endl;
    j = 2 + 4 * 6;
    cout << "    j= " << j << endl;
    if (j > 30 && i < 30) {
        k = 1;
    } else {
        k = 0;
    }
    cout << "" << endl;
    cout << "* Test des opérateurs < , > , et" << endl;
    cout << " si( j > 30 et i < 30) " << endl;
    cout << "   k = 1" << endl;
    cout << " sinon" << endl;
    cout << "   k = 0" << endl;
    cout << " finsi" << endl;
    cout << "Résultat attendu :" << endl;
    cout << "    k = 1 " << endl;
    cout << "Résultat : " << endl;
    cout << "    k = " << k << endl;
    if (j > 30 && i < 30) {
        k = 1;
    } else {
        k = 0;
    }
    cout << "" << endl;
    cout << "* Test des opérateurs ou , <= , >=" << endl;
    cout << " si( j >= 37 ou i <= 26) " << endl;
    cout << "   k = 1" << endl;
    cout << " sinon" << endl;
    cout << "   k = 0" << endl;
    cout << " finsi" << endl;
    cout << "Résultat attendu :" << endl;
    cout << "    k = 1 " << endl;
    cout << "Résultat : " << endl;
    cout << "    k = " << k << endl;
    return 0;
}
