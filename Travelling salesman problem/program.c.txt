#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_CITIES 100

// Structure to represent a city with (x, y) coordinates
struct City {
    int x, y;
};

// Function to calculate the Euclidean distance between two cities
double distance(struct City city1, struct City city2) {
    return sqrt(pow(city1.x - city2.x, 2) + pow(city1.y - city2.y, 2));
}

// Function to find the nearest neighbor of a city
int findNearestNeighbor(int currentCity, int numCities, struct City cities[], int visited[]) {
    int nearestCity = -1;
    double minDistance = -1;

    for (int i = 0; i < numCities; i++) {
        if (!visited[i] && (nearestCity == -1 || distance(cities[currentCity], cities[i]) < minDistance)) {
            nearestCity = i;
            minDistance = distance(cities[currentCity], cities[i]);
        }
    }

    return nearestCity;
}

// Function to solve TSP using the nearest neighbor algorithm
void solveTSP(int numCities, struct City cities[]) {
    int visited[MAX_CITIES] = {0};
    int tour[MAX_CITIES];
    int currentCity = 0;
    int nextCity;

    tour[0] = 0; // Start from the first city

    for (int i = 1; i < numCities; i++) {
        visited[currentCity] = 1;
        nextCity = findNearestNeighbor(currentCity, numCities, cities, visited);
        tour[i] = nextCity;
        currentCity = nextCity;
    }

    // Return to the starting city to complete the tour
    tour[numCities] = tour[0];

    // Print the tour
    printf("Optimal Tour: ");
    for (int i = 0; i <= numCities; i++) {
        printf("%d ", tour[i]);
    }

    // Calculate and print the total distance of the tour
    double totalDistance = 0;
    for (int i = 0; i < numCities; i++) {
        totalDistance += distance(cities[tour[i]], cities[tour[i + 1]]);
    }
    printf("\nTotal Distance: %.2lf\n", totalDistance);
}

int main() {
    int numCities;
    struct City cities[MAX_CITIES];

    printf("Enter the number of cities: ");
    scanf("%d", &numCities);

    printf("Enter the coordinates of cities:\n");
    for (int i = 0; i < numCities; i++) {
        printf("City %d (x y): ", i + 1);
        scanf("%d %d", &cities[i].x, &cities[i].y);
    }

    solveTSP(numCities, cities);

    return 0;
}
