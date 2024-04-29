#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "SortingAlgorithm.hpp"

using namespace std;
using namespace SortLibrary;
using namespace chrono;

int main(int argc, char* argv[]){

    unsigned int lunghezzaVettore = 0;

    if((argc < 2) || (argc > 2)){
        cout << "Primo argomento linea di comando: " << argv[0] << endl;
        cout << "Inserisci il secondo argomento della linea di comando <lunghezza vettore>" << endl;
        return 1;
    }else{

        lunghezzaVettore = stoi(argv[1]);

    }

    if(lunghezzaVettore >= 1e+5){
        cerr << "Dimensione del vettore inserita da linea di comando troppo grande: " << lunghezzaVettore << endl;
        return -1;
    }

    vector<unsigned int> arr(lunghezzaVettore);

    // Inizializzazione del vettore con valori casuali
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000);

    // Ripetizioni per calcolare statistiche
    const int numeroIterazioni = 30;  // Numero di esecuzioni da confrontare
    vector<double> bubbleDur(numeroIterazioni);

    for(unsigned int n = 0; n < numeroIterazioni; n++){
        // Riempimento del vettore con numeri casuali
        for (unsigned int i = 0; i < lunghezzaVettore; i++) {
            arr[i] = dis(gen);
        }

        // Misura del tempo per Bubble Sort
        auto inizioBubble = high_resolution_clock::now();
        BubbleSort(arr);
        auto fineBubble = high_resolution_clock::now();
        auto durataBubble = duration_cast<microseconds>(fineBubble - inizioBubble);
        bubbleDur[n] = durataBubble.count();
    }

    // Calcolo della media delle durate per Bubble Sort
    double bubbleDurataMedia = 0;
    for(unsigned int i = 0; i < numeroIterazioni; i++) {
        bubbleDurataMedia += bubbleDur[i];
    }
    bubbleDurataMedia /= numeroIterazioni;

    vector<double> mergeDur(numeroIterazioni);

    for(unsigned int n = 0; n < numeroIterazioni; n++){
        // Riempimento del vettore con numeri casuali
        for(unsigned int i = 0; i < lunghezzaVettore; i++) {
            arr[i] = dis(gen);
        }

        // Misura del tempo per Bubble Sort
        auto inizioMerge = high_resolution_clock::now();
        MergeSort(arr);
        auto fineMerge = high_resolution_clock::now();
        auto durataMerge = duration_cast<microseconds>(fineMerge - inizioMerge);
        mergeDur[n] = durataMerge.count();
    }

    // Calcolo della media delle durate per Bubble Sort
    double mergeDurataMedia = 0;
    for(unsigned int i = 0; i < numeroIterazioni; i++) {
        mergeDurataMedia += mergeDur[i];
    }
    mergeDurataMedia /= numeroIterazioni;

    // Output dei risultati
    cout << "Lunghezza vettore: " << lunghezzaVettore << endl;
    cout << "Media tempo Bubble Sort su " << numeroIterazioni << " esecuzioni: " << bubbleDurataMedia << " microsecondi" << endl;
    cout << "Media tempo Merge Sort su " << numeroIterazioni << " esecuzioni: " << mergeDurataMedia << " microsecondi" << endl;
    cout << "Tempo Bubble Sort: " << bubbleDurataMedia << " microsecondi" << endl;
    cout << "Tempo Merge Sort: " << mergeDurataMedia << " microsecondi" << endl;

    if(bubbleDurataMedia < mergeDurataMedia){
        cout << "L'algoritmo Bubble Sort e' piu' veloce dell'algoritmo Merge Sort (lunghezza vettore: " << lunghezzaVettore << ")" << endl;
    }else if(bubbleDurataMedia > mergeDurataMedia){
        cout << "L'algoritmo Bubble Sort e' piu' lento dell'algoritmo Merge Sort (lunghezza vettore: " << lunghezzaVettore << ")" << endl;
    }else if(bubbleDurataMedia == mergeDurataMedia){
        cout << "Gli algoritmi Bubble Sort e Merge Sort hanno la stessa durata (lunghezza vettore: " << lunghezzaVettore << ")" << endl;
    }

    return 0;
}
