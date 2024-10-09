# Efficient Matrix Management

Consolidated knowledge on pointer-use and dynamic memory allocation in order to effectively use stack and heap memory. The program has the following functionalities in handling matrices:

* Matrix Loading: The program loads matrices by doubling the memory if necessary (double_size_coll) and using read_matrix to allocate and read elements upon receiving the "L" command.
* Matrix Dimensions: Dimensions are retrieved using pre-stored vectors for rows and columns, and errors are thrown if the index is out of bounds.
* Matrix Display: The print_matrix function accesses and displays matrix elements using their saved indices, handling errors for invalid indices.
* Matrix Resizing: Matrices are resized by creating new vectors for selected rows and columns, constructing a new matrix, and replacing the original one (resize_matrix).
* Matrix Multiplication: Matrix multiplication (matrix_prod_in_coll) checks dimension compatibility, creates a result matrix, and stores it. If needed, memory is expanded dynamically.
* Matrix Sorting: Matrices are sorted by sum, using an auxiliary matrix to track indices and sums. A modified selection sort is applied to maintain relationships between sums and matrices (org_matrix).
* Matrix Transposition: The transposition function swaps rows and columns, constructing a new transposed matrix and replacing the original.
* Matrix Exponentiation: Matrices are raised to a power in logarithmic time using identity matrices, matrix multiplication, and a loop that checks the parity of the exponent (exp_matrix).
* Matrix Deletion: Matrices are deleted from memory using remove_matrix, which shifts the remaining matrices and reduces memory usage. If only half the buffer is used, it calls half_size_coll.
* Program Termination: The endgame function releases all resources by freeing matrices, collections, and vectors. The program exits once the main loop reads the "Q" command.


