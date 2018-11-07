#include <iostream>

using namespace std;

int main() {
    int coups;
    int i;
    int nombre;
    int trouve;
    cout << "Entrez un nombre entre 1 et 100" << endl;
    do {
        cin >> nombre;
    } while (!(nombre >= 1 && nombre <= 100));
    trouve = 0;
    coups = 0;
    for (i = 0; i < 20; i = i + 1) {
        cout << "" << endl;
    }
    while (!trouve) {
        cout << "Entrez un nombre : " << endl;
        cin >> i;
        if (i == nombre) {
            trouve = 1;
        } else if (i > nombre) {
            cout << "plus petit" << endl;
        } else {
            cout << "plus grand" << endl;
        }
        coups = coups + 1;
    }

    cout << "Trouvé ! nombre de coup : " << coups << endl;
    return 0;
}
