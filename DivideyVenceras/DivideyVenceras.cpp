#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>

// almaceno los resultados y las OE en una estructura
struct Result {
    long long result;
    int oe;
};

// Función potencia3
long long potencia3_aux(int a, int n, int& oe) {
    if (n == 0) {
        oe++;
        return 1;
    }
    else if (n % 2 == 0) { // n es par
        long long halfPower = potencia3_aux(a, n / 2, oe);
        oe++; // Conteo la OE por multiplicación
        return halfPower * halfPower;
    }
    else { // n es impar
        long long halfPower = potencia3_aux(a, (n - 1) / 2, oe);
        oe += 2; // Conteo 2 OE por multiplicación
        return halfPower * halfPower * a;
    }
}

// Función potencia3 inicializa OE's y llama a funcion auxiliar
Result potencia3(int a, int n) {
    Result res;
    res.oe = 0; // inicializo OE's a 0
    res.result = potencia3_aux(a, n, res.oe);
    return res;
}

int main() {
    //creamos un excel
    std::ofstream archivo("resultados2.csv");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }
    std::mt19937 rng(42); // Generador de números aleatorios con semilla 42
    std::uniform_int_distribution<int> dist(1, 15); // dsitribuyo del 1 al 15

    archivo << std::fixed << std::setprecision(6); // Fijamos precisión decimal
    archivo << "Base ;Exponente ;resultado ;Operaciones elementales ;Tiempo de ejecucion (ms) " << std::endl;

    // Realizamos 25 pruebas
    for (int i = 0; i < 25; ++i) {
        int a = dist(rng); // "a" aleatoria
        int n = dist(rng); // "n" aleatoria

        // Mido el tiempo de ejecución
        auto start = std::chrono::high_resolution_clock::now();
        Result result = potencia3(a, n);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        // Imprimo resultados por pantalla para mayor eficiencia
        std::cout << "Prueba " << i + 1 << ": " << std::endl;
        std::cout << "a (base): " << a << std::endl;
        std::cout << "n (exponente): " << n << std::endl;
        std::cout << "resultado: " << result.result << std::endl;
        std::cout << "operaciones elementales: " << result.oe << std::endl;
        std::cout << "tiempo de ejecución: " << duration.count() << " ms" << std::endl;
        std::cout << "------------------------" << std::endl;
        archivo << a << "; " << n << "; " << result.result << ";" << result.oe << ";" ";" << duration.count() << ";" << std::endl;

    }
    archivo.close();
    std::cout << "Los resultados se han guardado en el archivo 'resultados.csv'." << std::endl;

    return 0;
}
