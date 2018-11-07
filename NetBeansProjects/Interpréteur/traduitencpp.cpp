#include <iostream>

using namespace std;

int main() {
    int i;
    int nbcoups;
    int nombre;
    int trouve;
    cout << "entrer un nombre entre 1 et 100" << endl;
    do {
        cin >> nombre;
    } while (!(nombre >= 1 && nombre <= 100));
    trouve = 0;
    nbcoups = 0;
    while (!trouve) {
        cout << "trouver le nombre  : " << endl;
        cin >> i;
        if (i == nombre) {
            trouve = 1;
        } else if (i > nombre) {
            cout << "plus petit" << endl;
        } else {
            cout << "plus grand" << endl;
        }
        nbcoups = nbcoups + 1;
    }

    cout << "nombre de coup : " << nbcoups << endl;
    return 0;
}
