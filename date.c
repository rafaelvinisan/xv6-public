#include "types.h"
#include "user.h"
#include "date.h"

int stdout = 1;
int stderr = 2;

int
main(int argc, char *argv[])
{
 date(); // Chama a syscall para imprimir a data.
 exit(); // Encerra o programa.
}