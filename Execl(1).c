#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main() {
    pid_t pid;
    int status, fd;

    // Crear proceso hijo
    pid = fork();
    if (pid == -1) {
        perror("Error al hacer fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Proceso hijo
        fd = open("datos.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (fd == -1) {
            perror("Error al abrir archivo");
            exit(EXIT_FAILURE);
        }
        write(fd, "1 2 3 4 5", strlen("1 2 3 4 5"));
        close(fd);
        exit(EXIT_SUCCESS);
    } else {
        // Proceso padre
        sleep(3); // Esperar 3 segundos
        fd = open("datos.txt", O_RDONLY);
        if (fd == -1) {
            perror("Error al abrir archivo");
            exit(EXIT_FAILURE);
        }
        char buffer[256];
        int nbytes;
        while ((nbytes = read(fd, buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, nbytes);
        }
        close(fd);

        // Esperar a que el proceso hijo complete
        wait(&status);
    }

    return 0;
}


