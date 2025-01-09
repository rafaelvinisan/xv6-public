#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    // Imprime o número inicial de páginas usadas.
    printf(1, "Número de páginas usadas: %d\n", num_pages());

    // Aloca memória para criar mais páginas.
    char *mem = sbrk(4096); // Aloca uma página (4 KB).

    if (mem == (char *)-1) {
        printf(1, "Falha ao alocar memória.\n");
        exit();
    }

    // Imprime o número de páginas após a alocação.
    printf(1, "Número de páginas após alocação: %d\n", num_pages());

    // Finaliza o programa.
    exit();
}
