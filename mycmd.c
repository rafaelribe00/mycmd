#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main(char *argv[], int argc) {
    DIR *dir;
    struct dirent *entry;
    const char *proc_directory = "/proc";
    const char *target_file = "loadavg";

    // Open the /proc directory
    dir = opendir(proc_directory);
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    // Loop through the directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Find the target file (loadavg) in the /proc directory
        if (strcmp(entry->d_name, target_file) == 0) {
            char file_path[256];
            sprintf(file_path, "%s/%s", proc_directory, target_file);

            // Read the load average information
            FILE *file = fopen(file_path, "r");
            if (file == NULL) {
                perror("Error opening file");
                closedir(dir);
                return 1;
            }

            // Read and print the load average values
            char buffer[1024];
            if (fgets(buffer, sizeof(buffer), file) != NULL) {
                float loadavg_1min, loadavg_5min, loadavg_15min;
                sscanf(buffer, "%f %f %f", &loadavg_1min, &loadavg_5min, &loadavg_15min);

                printf("Load Average (1 minute): %.2f\n", loadavg_1min);
                printf("Load Average (5 minutes): %.2f\n", loadavg_5min);
                printf("Load Average (15 minutes): %.2f\n", loadavg_15min);
            } else {
                printf("Error reading file\n");
            }

            // Close the file
            fclose(file);
            break;
        }
    }

    // Close the directory
    closedir(dir);

    return 0;
}
