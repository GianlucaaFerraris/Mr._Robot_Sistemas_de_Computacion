#include <stdio.h>

// La implementación está en gini_calc.s
extern int convertir_y_sumar(float valor);

int main() {
    float gini_2020 = 42.7f;
    float gini_2019 = 43.3f;
    float gini_2018 = 41.7f;

    int resultado1 = convertir_y_sumar(gini_2020);
    int resultado2 = convertir_y_sumar(gini_2019);
    int resultado3 = convertir_y_sumar(gini_2018);

    printf("GINI 2020: %.1f -> %d\n", gini_2020, resultado1);
    printf("GINI 2019: %.1f -> %d\n", gini_2019, resultado2);
    printf("GINI 2018: %.1f -> %d\n", gini_2018, resultado3);

    return 0;
}