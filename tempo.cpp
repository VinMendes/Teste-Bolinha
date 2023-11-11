#include <stdio.h>
#include <sys\timeb.h>

int main() {
    struct timeb inicio_tempo, fim_tempo;
    int total_tempo;
    
    ftime(&inicio_tempo);

    ftime(&fim_tempo);
    total_tempo = 1000.0 * (fim_tempo.time - inicio_tempo.time) + (fim_tempo.millitm - inicio_tempo.millitm);

    total_tempo = total_tempo / (1000 * 60);

    return 0;
}
