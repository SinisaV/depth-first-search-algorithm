#include <iostream>
#include <fstream>
#include <stack>

struct Vozlisce {
    int predhodnik;
    int indeks;
    int dolzina;
    int status;
    std::string ime;
};

void grafSosednjosti(Vozlisce *&V, int *&C, int &steviloVozlisc) {
    std::ifstream file("graf.txt");

    int steviloPovezav;
    int v1, v2, cena;

    file >> steviloVozlisc; // preberemo stevilo vozlisc
    file >> steviloPovezav; // preberemo stevilo povezav
    C = new int[steviloVozlisc * steviloVozlisc]; // ustavarimo matriko sosednjosti 8 x 8
    V = new Vozlisce[steviloVozlisc]; // ustvarimo matriko kjer hranimo vozlisca

    for (int i = 0; i < steviloVozlisc; i++) {
        V[i].indeks = i;
        V[i].ime = std::to_string(i);
    }

    for (int j = 0; j < steviloVozlisc * steviloVozlisc; j++) { // celo matriko napolnimo z stevili 0
        C[j] = 0;
    }

    for (int k = 0; k < steviloPovezav; k++) { // vstavimo povezave v graf
        file >> v1 >> v2 >> cena;
        C[(steviloVozlisc * (v1-1)) + (v2-1)] = 1; // steviloVozlisc=8 * 0 + 1 = pozicija[1]
        C[(steviloVozlisc * (v2-1)) + (v1-1)] = 1; // steviloVozlisc=8 * 1 + 0 = pozicija[8]
    }

    std::cout << "MATRIKA SOSEDNJOSTI" << "\n";
    std::cout << "-------------------" << "\n";

    for (int k = 0; k < steviloVozlisc * steviloVozlisc; k++) { // izpisemo matriko sosednjosti
            std:: cout << C[k] << " ";
            if (k == 7 || k == 15 || k == 23 || k == 31 || k == 39 || k == 47 || k == 55 || k == 63 || k == 71 || k == 79) {
                std::cout << "\n";
            }
    }
}

void iskanjeVGlobino(Vozlisce *&V, int s, int *&C, int &steviloVozlisc) {
    //int velikost = sizeof(V); // dolocimo velikost vozlisc
    std::stack<int> stack; // ustvarimo si spremenljivko stack

    for (int i = 0; i < steviloVozlisc; i++) {
        if (s > steviloVozlisc) {
            std::cout << "Vozlisce je vecje od pricakovanega!" << "\n";
            return;
        }
    }
    for(int v = 0; v < steviloVozlisc; v++) { // steviloVozlisc = 8
        V[v].status = 0; // nepregledano
        V[v].dolzina = INT_MAX; // dolzino nastavimo na veliko stevilo
        V[v].predhodnik = -1; // nima predhodnika
    }
    // s ki smo ga vstavili
    V[s].status = 1; // v obdelavi
    V[s].dolzina = 0; // trenutna dolzina je 0
    V[s].predhodnik = -1; // se vedno nima predhodnika
    stack.push(s); // vstavi na vrh sklada

    int v;
    while(!stack.empty()) { // preglejujemo ce sklad ni prazen in jemljemo z njega
        v = stack.top(); // vrh sklada si shranimo v spremenljivko v
        stack.pop(); // sklad zmanjsamo za ena

        for(int u = 0; u < steviloVozlisc; u++) {
            if(V[u].status == 0 && C[steviloVozlisc * v + u] == 1) { // nepregledano in iscemo povezave
                V[u].status = 1; // status je v obdelavi
                V[u].dolzina = V[v].dolzina + 1; // ko se pomikamo med vozlisci povecujemo dolzino
                V[u].predhodnik = V[v].indeks; // predhodnik postane indeks od prejsnjega vozlisca
                stack.push(u); // vstavi na vrh sklada
            }
            V[v].status = 2; // razvito
        }
    }
}

void izpis(Vozlisce *&V, int &steviloVozlisc) {

    //int velikost = sizeof(V);

    for (int i = 0; i < steviloVozlisc; i++) {
        std::cout << "VOZLISCE " << i << " Ime: " << V[i].ime << " Indeks: " << V[i].indeks
        << " Dolzina poti: " << V[i].dolzina << " Predhodnik: " << V[i].predhodnik << "\n";
    }
}

void izpisPoti(Vozlisce *&V, int s, int v, int &steviloVozlisc) {

    //int velikost = sizeof(V);
    for (int i = 0; i < steviloVozlisc; i++) {
        if (s > steviloVozlisc || v > steviloVozlisc) {
            std::cout << "Vozlisci sta vecji od pricakovanega!" << "\n";
            return;
        }
    }

    if (v == s) {
        std::cout << "Pot vozlisca je: " + V[v].ime + " ";
    }

    else {
        if (V[v].predhodnik == -1) {
            std::cout << "Med " + V[s].ime + " in " + V[v].ime + " ni poti! ";
        }
        else {
            izpisPoti(V, s, V[v].predhodnik, steviloVozlisc);
            std::cout << V[v].ime + " ";
        }
    }
}

void meni() {
    std::cout << "Iskanje v globino - izbira:" << "\n";
    std::cout << "1) Preberi graf iz datoteke" << "\n";
    std::cout << "2) Pozeni iskanje iz vozlisca s" << "\n";
    std::cout << "3) Izpis seznama vozlisc in njihovih podatkov" << "\n";
    std::cout << "4) Izpis poti med vozliscema s in d" << "\n";
    std::cout << "5) Konec" << "\n";
    std::cout << "Vasa izbira: ";
}
int main() {

    Vozlisce *V = nullptr;
    int *C = nullptr;
    int steviloVozlisc = 0;

    int s, v;

    bool running = true;
    int selection;

    bool case1 = false;

    do {
        meni();
        std::cin >> selection;
        switch (selection) {
            case 1:
                std::cout << "\n";
                grafSosednjosti(V, C, steviloVozlisc);
                case1 = true;
                break;
            case 2:
                if(case1) {
                    std::cout << "Vnesi vozlisce s katerega boste tvorili iskano drevo: ";
                    std::cin >> s;
                    iskanjeVGlobino(V, s, C, steviloVozlisc);
                    case1 = true;
                    break;
                }
                std::cout << "Prvo generiraj graf!" << "\n";
                case1 = false;
                break;
            case 3:
                if(case1) {
                    izpis(V, steviloVozlisc);
                    case1 = true;
                    break;
                }
                std::cout << "Prvo generiraj graf!" << "\n";
                case1 = false;
                break;
            case 4:
                if(case1) {
                    std::cout << "Vnesi vozlisce s katerega boste iskali: ";
                    std::cin >> s;
                    std::cout << "Vnesi vozlisce katerega boste iskali: ";
                    std::cin >> v;
                    izpisPoti(V, s, v, steviloVozlisc);
                    case1 = true;
                    break;
                }
                std::cout << "Prvo generiraj graf!" << "\n";
                case1 = false;
                break;
            case 5:
                running = false;
                break;
            default:
                std::cout << "Napacna izbira! \n";
                break;
        }
        std::cout << "\n";
    } while(running);

    delete [] V;
    delete [] C;

    return 0;
}
