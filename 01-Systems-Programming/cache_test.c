#include <stdio.h> // For printf (output)
#include <time.h>   // For clock() (benchmarking)
#include <stdlib.h> // For standard utilities.
#include <assert.h> // For unit Testing.

//CONFIGURATION: 5000 x 5000 ints - ~100MB RAM
//We use defines so we can change the size in one place.

#define ROWS 5000
#define COLS 5000

// GLOBAL MEMORY: Declared outside main() to live in the Data Segment
// If we put this inside main(), it would blow up the Stack.

int array[ROWS][COLS];



// --- LOGIC 1: Row-Major (Hardware Friendly) ---
long fill_row_major() {
    long sum = 0;
    // Outer loop: Rows (i) - Moves slowly
    for (int i = 0; i < ROWS; i++) {
        // Inner loop: Cols (j) - Moves fast
        // We stay in Row 'i' and scan across all columns
        for (int j = 0; j < COLS; j++) {
            array[i][j] = 1;
            sum += array[i][j];
        }
    }
    return sum;
}

// --- LOGIC 2: Column-Major (Hardware Hostile) ---
long fill_col_major() {
    long sum = 0;
    // Outer loop: Cols (j) - Moves slowly
    for (int j = 0; j < COLS; j++) {
        // Inner loop: Rows (i) - Moves fast
        // We stay in Column 'j' and jump down rows
        for (int i = 0; i < ROWS; i++) {
            array[i][j] = 1;
            sum += array[i][j];
        }
    }
    return sum;
}


// --- THE INSPECTOR ---
void run_unit_tests(){
    printf("[TEST] Starting Unit Tests... \n");

    // 1. CLEANUP: Reset the entire array to 0
    // We use a nested loop to visit every cell and wipe it.

    for (int i=0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            array[i][j] = 0;
        }
    }

    //2. TEST: Check Row Major Logic
    printf("[TEST] Checking Row-Major logic... \n" );
    long result1 = fill_row_major();
    // This WILL fail right now because our stub returns 0
    assert(result1 == 25000000); 
    printf("[PASS] Row-Major logic is correct.\n");

    // 3. CLEANUP: Reset array again for the next test
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            array[i][j] = 0;
        }
    }

    // 4. TEST: Check Column Major Logic
    printf("[TEST] Checking Column-Major logic...\n");
    long result2 = fill_col_major();
    assert(result2 == 25000000);
    printf("[PASS] Column-Major logic is correct.\n");

    
}

int main() {
    // 1. SAFETY: Run tests first. 
    // If logic is wrong, we crash here and save time.
    run_unit_tests();

    // 2. BENCHMARK: The Physics Experiment
    clock_t start, end;
    double time_taken;

    printf("--- THE SOVEREIGN CACHE BENCHMARK ---\n");

    // Experiment A: The "Friendly" Loop
    start = clock();
    fill_row_major();
    end = clock();
    
    // Calculate seconds
    time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Row-Major (Fast):   %f seconds\n", time_taken);

    // Experiment B: The "Hostile" Loop
    start = clock();
    fill_col_major();
    end = clock();
    
    time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Column-Major (Slow): %f seconds\n", time_taken);

    return 0;
}