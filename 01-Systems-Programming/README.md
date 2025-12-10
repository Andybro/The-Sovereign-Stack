# Systems Programming & Hardware Physics

This module contains tools and benchmarks that validate how software interacts with the physical CPU and Memory. The objective is to prove that "Abstraction is not free" and that understanding hardware constraints leads to performant code.

## Projects

### 1. The Sovereign Bit Inspector (`bit_inspector.c`)
A command-line interface (CLI) diagnostic tool designed to visualize the raw binary representation of integers in system memory.

**Problem Statement:**
High-level languages abstract away the internal representation of numbers, hiding critical details like Integer Overflow risks and Two's Complement storage for negative numbers.

**Solution:**
A C-based utility that:
1.  Accepts integer input via CLI arguments.
2.  Performs robust input validation (using `strtol` to catch non-numeric input and integer overflows).
3.  Manually traverses the bit-field using bitwise Shift (`>>`) and Mask (`&`) operations to render the binary state.
4.  Displays the Decimal, Hexadecimal, and Binary representations simultaneously.

**Usage:**
```bash
./bit_inspector -50
# Output verifies Two's Complement (Sign Bit 1)


### 2. Cache Locality Benchmark (`cache_test.c`)
An empirical benchmark demonstrating the impact of CPU Cache Lines on software performance.

**Experiment:**
The program performs an identical mathematical summation on a 5000x5000 integer matrix using two different traversal patterns:
* **Row-Major Traversal:** Accessing memory sequentially (`array[0][0], array[0][1]...`).
* **Column-Major Traversal:** Accessing memory by jumping rows (`array[0][0], array[1][0]...`).

**Results:**
* **Row-Major:** ~0.03 seconds (**Cache Hit optimized**).
* **Column-Major:** ~0.11 seconds (**~400% slower** due to Cache Misses).

**Conclusion:**
This project validates that memory is not a 2D grid, but a linear 1D array. Respecting the "Stride" of the CPU pre-fetcher is critical for high-performance applications.

## Technical Learnings
* **Bitwise Mechanics:** Utilizing `&`, `|`, and `>>` for data packing and inspection.
* **Input Hygiene:** Differentiating between `atoi` (unsafe) and `strtol` (safe) for production-grade CLI tools.
* **Hardware Latency:** Understanding the cost of L1/L2 Cache misses in tight loops.