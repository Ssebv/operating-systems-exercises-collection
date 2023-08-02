#include <fcntl.h>
#include <stdio.h>

/*
 * This is an example of file usage in the UNIX style.
 * This program reads a file provided by argv[1] and copies it
 * with the name provided by argv[2].
 */

int main(int argc, char *argv[]) {
    int source, destination, length;
    char buffer[256];

    source = open(argv[1], O_RDONLY);
    destination = open(argv[2], O_RDWR | O_CREAT, 0755);

    length = read(source, buffer, sizeof(buffer));
    while (length > 0) {
        write(destination, buffer, length);
        length = read(source, buffer, sizeof(buffer));
    }

    close(source);
    close(destination);
    return 0;
}
