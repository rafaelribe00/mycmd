#include <stdio.h>

int main() {
    FILE *file;
    char buffer[1024]; // Buffer to store data read from /proc/loadavg
    const char *file_path = "/proc/loadavg"; // Path to loadavg file

    // Open the file in read mode
    file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the load average information
    if (fgets(buffer, sizeof(buffer), file) != NULL) {
        float loadavg_1min, loadavg_5min, loadavg_15min;
        sscanf(buffer, "%f %f %f", &loadavg_1min, &loadavg_5min, &loadavg_15min);

        // Print the load average values
        printf("Load Average (1 minute): %.2f\n", loadavg_1min);
        printf("Load Average (5 minutes): %.2f\n", loadavg_5min);
        printf("Load Average (15 minutes): %.2f\n", loadavg_15min);
    } else {
        printf("Error reading file\n");
    }

    // Close the file
    fclose(file);

    return 0;
}