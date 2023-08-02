#include <dirent.h>
#include <stdio.h>

int main(void) {
    DIR *directory_descriptor;
    struct dirent *directory_entry;

    /* Open the current directory to read its content */
    directory_descriptor = opendir(".");

    /* Read a directory entry and store it in the directory_entry structure
       If it can't continue reading, the assignment will result in NULL
    */
    while ((directory_entry = readdir(directory_descriptor)) != NULL) {
        /* Print the name of the entry as a string */
        printf("%s\n", directory_entry->d_name);
    }

    /* Close the directory */
    closedir(directory_descriptor);
    return 0;
}
