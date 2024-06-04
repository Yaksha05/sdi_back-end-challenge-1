#include <stdio.h>

typedef struct {
    char size;
    int capacity;
    int cost;
} CarType;

void calculate_optimized_cost(int seats) {
    CarType car_types[] = {
        {'S', 5, 5000},
        {'M', 10, 8000},
        {'L', 15, 12000}
    };

    int num_car_types = sizeof(car_types) / sizeof(car_types[0]);

    int min_cost = 0;
    int optimal_counts[num_car_types];
    int possible_results[100][num_car_types]; // Assume there won't be more than 100 possible results
    int result_count = 0;

    for (int i = 0; i <= seats / car_types[2].capacity + 1; ++i) {
        for (int j = 0; j <= seats / car_types[1].capacity + 1; ++j) {
            for (int k = 0; k <= seats / car_types[0].capacity + 1; ++k) {
                int total_seats = i * car_types[2].capacity + j * car_types[1].capacity + k * car_types[0].capacity;
                int total_cost = i * car_types[2].cost + j * car_types[1].cost + k * car_types[0].cost;

                if (total_seats >= seats) {
                    if (result_count == 0 || total_cost < min_cost) {
                        min_cost = total_cost;
                        result_count = 0;
                    }
                    if (total_cost == min_cost) {
                        possible_results[result_count][0] = k;
                        possible_results[result_count][1] = j;
                        possible_results[result_count][2] = i;
                        result_count++;
                    }
                }
            }
        }
    }

    // Print only the first possible solution
    printf("\nBest Solution:\n");
    if (possible_results[0][0] > 0) printf("%c x %d\n", car_types[0].size, possible_results[0][0]);
    if (possible_results[0][1] > 0) printf("%c x %d\n", car_types[1].size, possible_results[0][1]);
    if (possible_results[0][2] > 0) printf("%c x %d\n", car_types[2].size, possible_results[0][2]);
    printf("Total = PHP %d\n", min_cost);
}


int main() {
    int seats;
    char continue_program = 'Y';

    while (continue_program == 'Y' || continue_program == 'y') {
        printf("Please input number (seat): ");
        scanf("%d", &seats);

        calculate_optimized_cost(seats);

        printf("\nDo you want to continue? (Y/N): ");
        scanf(" %c", &continue_program);
    }

    return 0;
}
