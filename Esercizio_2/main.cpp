#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "SortingAlgorithm.hpp"
#include <iomanip>

using namespace std;
using namespace SortLibrary;
using namespace chrono;

int main(int argc, char **argv){

    unsigned int lunghezzaVettore = 0;

    if(argc != 2){
        cerr << "Errore: numero di argomenti passati da linea di comando diverso da due" << endl;
        cerr << "Oltre all'eseguibile (primo argomento passato da linea di comando) deve essere passato un secondo argomento da linea di comando: <lunghezza vettore>" << endl;
        return -1;
    }else{

        // ciclo for che controlla se il secondo argomento passato da linea di comando è un intero,
        // andando a verificare fino al terminatore di stringa \0 se tutti i caratteri sono cifre
        for(char *p = argv[1]; *p != '\0'; p++){
            if(!isdigit(*p)){

                // la condizione dell'if verifica se almeno un carattere non è un cifra
                // il programma termina e oltre a restituire -1 stampa anche un messaggio d'errore
                cerr << "Errore: il secondo argomento passato da linea di comando non e' un numero intero" << endl;
                return -1;
            }
        }

        lunghezzaVettore = stoi(argv[1]);
    }

    vector<unsigned int> arr(lunghezzaVettore);

    // Inizializzazione del vettore con valori casuali
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000);

    // Ripetizioni per calcolare statistiche
    const int numeroIterazioni = 54;  // Numero di esecuzioni da confrontare

    if(lunghezzaVettore > 1e+3 || numeroIterazioni > 1e+3){
        cerr << "Dimensione del vettore inserita da linea di comando o numero di iterazioni inserito troppo grande rischio crash del programma" << endl;
        cerr << "Lunghezza vettore: " << lunghezzaVettore << " numero di iterazioni: " << numeroIterazioni << endl;
        return -1;
    }

    vector<double> bubbleDur(numeroIterazioni);

    for(unsigned int i = 0; i < numeroIterazioni; i++){

        // Riempimento del vettore con numeri casuali
        for(unsigned int l = 0; l < lunghezzaVettore; l++){
            arr[l] = dis(gen);
        }

        // Misura del tempo per Bubble Sort
        auto inizioBubble = high_resolution_clock::now(); // misura il tempo di inizio dell'algoritmo        
        BubbleSort(arr); // chiamo l'algoritmo di Bubble Sort per il vettore // esegui Bubble Sort sull'array
        auto fineBubble = high_resolution_clock::now(); // misura il tempo di fine dell'algoritmo

        // calcolo la differenza tra il tempo di fine dell'algoritmo
        // e il tempo di inizio dell'algoritmo usando come unità di misura i microsecondi
        auto durataBubble = duration_cast<microseconds>(fineBubble - inizioBubble);

        // mi salvo nel vettore bubbleDur[i] quanto tempo ci ha messo l'algoritmo Bubble Sort
        // per ordinare il vettore ad ogni iterazione (numeroIterazioni)
        bubbleDur[i] = durataBubble.count();
    }

    // Calcolo della media delle durate per Bubble Sort
    double bubbleDurataMedia = 0;
    double bubbleSommaDurata = 0;
    for(unsigned int i = 0; i < numeroIterazioni; i++) {
        bubbleSommaDurata += bubbleDur[i];
    }
    // ho moltiplicato per 1e-3 in modo da non avere numeri troppo grandi espressi in microsecondi
    bubbleDurataMedia = (bubbleSommaDurata*1e-3)/numeroIterazioni;

    vector<double> mergeDur(numeroIterazioni);

    for(unsigned int i = 0; i < numeroIterazioni; i++){
        // Riempimento del vettore con numeri casuali
        for(unsigned int l = 0; l < lunghezzaVettore; l++){
            arr[l] = dis(gen);
        }

        // Misura del tempo per Merge Sort
        auto inizioMerge = high_resolution_clock::now(); // misura il tempo di inizio dell'algoritmo
        MergeSort(arr); // esegui Merge Sort sull'array
        auto fineMerge = high_resolution_clock::now(); // misura il tempo di fine dell'algoritmo

        // calcolo la differenza tra il tempo di fine dell'algoritmo
        // e il tempo di inizio dell'algoritmo usando come unità di misura i microsecondi
        auto durataMerge = duration_cast<microseconds>(fineMerge - inizioMerge);

        // mi salvo nel vettore mergeDur[i] quanto tempo ci ha messo l'algoritmo Merge Sort
        // per ordinare il vettore ad ogni iterazione (numeroIterazioni)
        mergeDur[i] = durataMerge.count();
    }

    // Calcolo della media delle durate per Merge Sort
    double mergeDurataMedia = 0;
    double mergeSommaDurata = 0;
    for(unsigned int i = 0; i < numeroIterazioni; i++){
        mergeSommaDurata += mergeDur[i];
    }
    // ho moltiplicato per 1e-3 in modo da non avere numeri troppo grandi espressi in microsecondi
    mergeDurataMedia = (mergeSommaDurata*1e-3)/numeroIterazioni;

    // Output dei risultati
    cout << "Lunghezza vettore: " << lunghezzaVettore << endl;
    if((bubbleDurataMedia*1e-3) > 1e-3 || (mergeDurataMedia*1e-3) > 1e-3){

        // se è soddisfatta la condizione dell'if e quindi la media del tempo del Bubble Sort o la media del tempo del Merge Sort
        // moltiplicati per 1e-3 sono maggiori di 1e-3 millisecondi cambio l'unità di misura in output da microsecondi a millisecondi
        cout << "Media tempo Bubble Sort su " << numeroIterazioni << " esecuzioni: "
             << fixed << scientific << setprecision(7) << bubbleDurataMedia << " millisecondi" << endl;
        cout << "Media tempo Merge Sort su " << numeroIterazioni << " esecuzioni: "
             << fixed << scientific << setprecision(7) << mergeDurataMedia << " millisecondi" << endl;
    }else{

        // se non è soddisfatta la condizione dell'if l'unità di misura in output rimane microsecondi
        cout << "Media tempo Bubble Sort su " << numeroIterazioni << " esecuzioni: " << fixed << scientific << setprecision(7) << bubbleDurataMedia << " microsecondi" << endl;
        cout << "Media tempo Merge Sort su " << numeroIterazioni << " esecuzioni: " << fixed << scientific << setprecision(7) << mergeDurataMedia << " microsecondi" << endl;
    }

    if(bubbleDurataMedia == 0){
        cout << "Tempo per il Bubble Sort pari a zero in microsecondi, dimensione del vettore inserita da linea di comando molto piccola cambiare dimensione"
                " o calcolare il tempo con un'unita' di misura piu' piccola dei microsecondi" << endl;
    }

    if(bubbleDurataMedia < mergeDurataMedia){
        cout << "L'algoritmo Bubble Sort e' piu' veloce dell'algoritmo Merge Sort per la lunghezza inserita" << endl;
    }else if(bubbleDurataMedia > mergeDurataMedia){
        cout << "L'algoritmo Bubble Sort e' piu' lento dell'algoritmo Merge Sort per la lunghezza inserita" << endl;
    }else if(bubbleDurataMedia == mergeDurataMedia){
        cout << "Gli algoritmi Bubble Sort e Merge Sort hanno la stessa durata per la lunghezza inserita" << endl;
    }

    return 0;
}

// Bubble Sort: algoritmo di ordinamento semplice ma inefficiente per grandi quantità di dati.
// La sua complessità computazionale è di O(n^2) dove n è la dimensione dell'array da ordinare
// questo significa che il tempo di esecuzione cresce quadraticamente con la dimensione dell'array
// ma questo lo rende poco efficiente per grandi quantità di dati.
// Per quantità di dati molto piccole il Bubble Sort risulta più veloce del Merge Sort

// Merge Sort: Merge Sort è un algoritmo di ordinamento più efficiente del Bubble Sort.
// La sua complessità computazionale è di O(n*log(n)) dove n è la dimensione dell'array da ordinare
// questo lo rende significativamente più veloce rispetto al Bubble Sort,
// specialmente quando si tratta di grandi quantità di dati.
