#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
    pid_t pid_A;
    int status;

    pid_A = fork();

    if (pid_A == -1) {
        perror("Error al hacer fork");
        exit(EXIT_FAILURE);
    } else if (pid_A == 0) {
        // Proceso hijo
        exit(EXIT_SUCCESS);
    } else {
        // Proceso padre
        sleep(3); // Esperar 3 segundos

        // Modificar el código del proceso padre para ejecutar hello_world usando execl()
        int ret = execl("/home/davidmc26/Documents/hello_world.c", "", NULL);
        if (ret == -1) {
            perror("Error al ejecutar hello_world");
            exit(EXIT_FAILURE);
        }

        wait(&status);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            printf("El programa hijo se ha ejecutado exitosamente.\n");
        } else {
            printf("El programa hijo ha fallado.\n");
        }
    }

    return 0;
}
