#include <stdio.h>

#define MAX 10

typedef struct {
    int pid;
    int arrival;
    int burst;
    int waiting;
    int turnaround;
    int completed;
} Process;

void sortByArrival(Process p[], int n) {
    Process temp;
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(p[j].arrival > p[j+1].arrival) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

int main() {
    Process p[MAX];
    int n, completed = 0, current_time = 0;
    float total_waiting = 0, total_turnaround = 0;

    // Sample input
    n = 4;
    int arrival[] = {0, 2, 4, 5};
    int burst[] = {7, 4, 1, 4};

    for(int i = 0; i < n; i++) {
        p[i].pid = i+1;
        p[i].arrival = arrival[i];
        p[i].burst = burst[i];
        p[i].completed = 0;
    }

    sortByArrival(p, n);

    while(completed < n) {
        int idx = -1;
        int min_burst = 1e9;

        for(int i = 0; i < n; i++) {
            if(p[i].arrival <= current_time && !p[i].completed && p[i].burst < min_burst) {
                min_burst = p[i].burst;
                idx = i;
            }
        }

        if(idx != -1) {
            p[idx].waiting = current_time - p[idx].arrival;
            if(p[idx].waiting < 0) p[idx].waiting = 0;

            current_time += p[idx].burst;
            p[idx].turnaround = p[idx].waiting + p[idx].burst;
            p[idx].completed = 1;

            total_waiting += p[idx].waiting;
            total_turnaround += p[idx].turnaround;
            completed++;
        } else {
            current_time++; // No process is ready, so increment time
        }
    }

    // Displaying result
    printf("Process\tArrival\tBurst\tWaiting\tTurnaround\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
    }

    printf("\nAverage Waiting Time: %.2f", total_waiting / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround / n);

    return 0;
}
