#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_task_wdt.h"

#define ITER_INT    11000000ULL
#define ITER_FLOAT   4700000ULL

void benchmark_integers(void)
{
    printf("\n[INT] Iniciando suma de enteros (%llu iteraciones)...\n", ITER_INT);
    int64_t t_start = esp_timer_get_time();

    volatile long long suma = 0;
    for (unsigned long long i = 0; i < ITER_INT; i++) {
        suma += i;
    }

    double elapsed = (esp_timer_get_time() - t_start) / 1e6;
    printf("[INT] Resultado: %lld\n", (long long)suma);
    printf("[INT] Tiempo: %.3f segundos\n", elapsed);
}

void benchmark_floats(void)
{
    printf("\n[FLT] Iniciando suma de floats (%llu iteraciones)...\n", ITER_FLOAT);
    int64_t t_start = esp_timer_get_time();

    volatile float suma = 0.0f;
    for (unsigned long long i = 0; i < ITER_FLOAT; i++) {
        suma += (float)i * 0.5f;
    }

    double elapsed = (esp_timer_get_time() - t_start) / 1e6;
    printf("[FLT] Resultado: %f\n", (double)suma);
    printf("[FLT] Tiempo: %.3f segundos\n", elapsed);
}

void app_main(void)
{
    // Desactivar el WDT completamente durante el benchmark
    esp_task_wdt_deinit();

    printf("=== Benchmark ESP-IDF: Enteros vs Floats ===\n");
    printf("CPU Freq: %d MHz\n\n", CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ);

    int64_t total_start = esp_timer_get_time();

    benchmark_integers();
    benchmark_floats();

    double total = (esp_timer_get_time() - total_start) / 1e6;
    printf("\n=== TOTAL: %.3f segundos ===\n", total);

    // Reactivar el WDT con configuración por defecto
    esp_task_wdt_config_t wdt_config = {
        .timeout_ms = 5000,
        .idle_core_mask = (1 << portNUM_PROCESSORS) - 1,
        .trigger_panic = false,
    };
    esp_task_wdt_init(&wdt_config);
}