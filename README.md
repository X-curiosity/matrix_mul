# Matrix Multiplication Benchmark

This project compares matrix multiplication in C with a NumPy reference implementation.

## What was done

- Implemented row-major matrix multiplication in C.
- Generated compatible rectangular matrix sizes.
- Measured C execution time at `-O0`, `-O2`, and `-O3`.
- Computed a NumPy reference using `@`.
- Saved benchmark results as JSON and generated comparison figures.

## Possible improvements

- Add numerical correctness checks between C and NumPy.
- Use a monotonic wall-clock timer and repeat each measurement.
- Add OpenMP and compare performance across thread counts.
- Improve cache usage with loop reordering or blocking.
- Add compiler warnings and memory-safety checks with sanitizers.
- Extend the benchmark to SIMD or GPU implementations.
