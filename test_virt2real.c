#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    char *va = (char *)0x4000; // Endereço virtual de teste.
    char *pa = virt2real(va); // Obtém o endereço físico.

    if (pa) {
        printf(1, "Endereço físico de %p: %p\n", va, pa); // Inclua 1 como primeiro argumento.
    } else {
        printf(1, "Falha ao obter o endereço físico.\n"); // Inclua 1 como primeiro argumento.
    }

    exit();
}
