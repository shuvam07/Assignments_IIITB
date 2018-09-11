#include <stdio.h>
#include <unistd.h>
int main() {
    printf("ARG_MAX: %ld\n", sysconf(_SC_ARG_MAX));
    printf("SIMULATENOUS_PROCESS: %ld\n", sysconf(_SC_CHILD_MAX));
    printf("CLOCK_TICKS: %ld\n", sysconf(_SC_CLK_TCK));
    printf("MAX_OPEN_FILE: %ld\n", sysconf(_SC_OPEN_MAX));
    printf("TOTAL_PAGES: %ld\n", sysconf(_SC_PHYS_PAGES));
    printf("AVAILABLE_PAGES: %ld\n", sysconf(_SC_AVPHYS_PAGES));
}