// 2DHeatTransfer.cpp : 2D steady-state finite-difference heat transfer solver
//

#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <chrono>

int main()
{
    // User inputs

    // 3x3 grid minimum for this to work
    const int imax = 10;
    const int jmax = 10;

    const int nIterations = 10000;

    char outputPath[] = "temperature.dat";

    // Boundary temperatures (deg.C)
    float initialTemp = 25.0;
    float topBoundary = 100.0;
    float leftBoundary = 50.0;
    float rightBoundary = 200.0;
    float bottomBoundary = 300.0;
    
    // Initialize temperature array
    float T[imax][jmax];
    for (int i = 0; i < imax; i++) {
        for (int j = 0; j < jmax; j++) {
            T[i][j] = initialTemp;
        }
    }
 
    // Set top/bottom boundaries
    for (int j = 0; j < jmax; j++) {
        T[0][j] = topBoundary;
        T[imax - 1][j] = bottomBoundary;
    }

    // Set left/right boundaries
    for (int i = 0; i < imax; i++) {
        T[i][0] = leftBoundary;
        T[i][jmax - 1] = rightBoundary;
    }

    // Start timing 
    auto begin = std::chrono::high_resolution_clock::now();

    // Steady-state solution is the average of the surrounding nodes
    for (int n = 0; n < nIterations; n++) {
        for (int i = 1; i < imax - 1; i++) {
            for (int j = 1; j < jmax - 1; j++) {
                T[i][j] = 0.25f * (T[i - 1][j] + T[i][j - 1] + T[i][j + 1] + T[i + 1][j]);
            }
        }
    }

    // Manually calculate the temperature at the corners
    T[0][0] = 0.5f * (T[1][0] + T[0][1]);  // Upper left
    T[imax - 1][0] = 0.5f * (T[imax-2][0] + T[imax-1][1]);  // Lower left
    T[0][jmax - 1] = 0.5f * (T[0][jmax-2] + T[1][jmax-1]);  // Upper right
    T[imax - 1][jmax - 1] = 0.5f * (T[imax-1][jmax-2] + T[imax - 2][jmax - 1]);

    // Stop timing
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    
    // Pretty print temperature field
    for (int i = 0; i < imax; i++) {
        for (int j = 0; j < jmax; j++) {
            printf("%.1f ", T[i][j]);
        }
        printf("\n");
    }

    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    // Write temperature data to a binary file
    //FILE* file = fopen(outputPath, "wb");
    //fwrite(&T, 4, imax*jmax, file);
    //fclose(file);

    return 0;
}
