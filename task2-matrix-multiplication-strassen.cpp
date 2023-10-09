#include <stdexcept>
#include <vector>

using namespace std;

/**
 * @brief implementation of Strassen matrix multiplication
 *
 * @note matrix dimensions: @param a is (m x n) matrix,
 *                          @param b is (n x k) matrix,
 *                     result should be (m x k) matrix
 *
 * @param a representation of matrix a as 1d array
 * @param b representation of matrix b as 1d array
 *
 * For example, to get the entry of matrix a on row i and column j, you could write:
 * \code {.cpp}
 *  int &elem = a[i * n + j]
 * \endcode
 *
 * @return std::vector<int> representation of a dot b as 1d array
 *
 * Constraints:
 *      1 <= m,n,k
 *      no need to worry about int overflow in the entries of the resulting matrix
 */

// Helper function to add two matrices
std::vector<int> matrixAddition(const std::vector<int>& A, const std::vector<int>& B, int n) {
    std::vector<int> C(n * n);
    for (int i = 0; i < n * n; i++) {
        C[i] = A[i] + B[i];
    }
    return C;
}

// Helper function to subtract two matrices
std::vector<int> matrixSubtraction(const std::vector<int>& A, const std::vector<int>& B, int n) {
    std::vector<int> C(n * n);
    for (int i = 0; i < n * n; i++) {
        C[i] = A[i] - B[i];
    }
    return C;
}


std::vector<int> matrixMultiplication(
    int                     m,
    int                     n,
    int                     k,
    const std::vector<int> &a,
    const std::vector<int> &b)
{
    if (m <= 0 || n <= 0 || k <= 0) {
        throw std::invalid_argument("Invalid matrix dimensions");
    }

    // Pad matrices with zeros to make dimensions even if needed
    int newM = (m % 2 == 0) ? m : m + 1;
    int newN = (n % 2 == 0) ? n : n + 1;
    int newK = (k % 2 == 0) ? k : k + 1;

    // Create padded matrices with zeros using dynamic memory allocation with proper alignment
    std::vector<int> paddedA(newM * newN, 0);
    std::vector<int> paddedB(newN * newK, 0);

    // Copy original matrices to padded matrices
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            paddedA[i * newN + j] = a[i * n + j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            paddedB[i * newK + j] = b[i * k + j];
        }
    }

    if (m == 1 || n == 1 || k == 1) {
        // Base case: Use regular matrix multiplication
        std::vector<int> result(m * k, 0);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < k; j++) {
                for (int x = 0; x < n; x++) {
                    result[i * k + j] += a[i * n + x] * b[x * k + j];
                }
            }
        }
        return result;
    } else {
        // Divide matrices into submatrices
        int newM = m / 2;
        int newN = n / 2;
        int newK = k / 2;

        // Split matrices into 4 submatrices each
        std::vector<int> A11(newM * newN);
        std::vector<int> A12(newM * newN);
        std::vector<int> A21(newM * newN);
        std::vector<int> A22(newM * newN);
        std::vector<int> B11(newN * newK);
        std::vector<int> B12(newN * newK);
        std::vector<int> B21(newN * newK);
        std::vector<int> B22(newN * newK);

        for (int i = 0; i < newM; i++) {
            for (int j = 0; j < newN; j++) {
                A11[i * newN + j] = a[i * n + j];
                A12[i * newN + j] = a[i * n + j + newN];
                A21[i * newN + j] = a[(i + newM) * n + j];
                A22[i * newN + j] = a[(i + newM) * n + j + newN];

                B11[i * newK + j] = b[i * k + j];
                B12[i * newK + j] = b[i * k + j + newK];
                B21[i * newK + j] = b[(i + newN) * k + j];
                B22[i * newK + j] = b[(i + newN) * k + j + newK];
            }
        }

        // Compute 7 products recursively
        std::vector<int> P1 = matrixMultiplication(newM, newN, newK, A11, matrixSubtraction(B12, B22, newK));
        std::vector<int> P2 = matrixMultiplication(newM, newN, newK, matrixAddition(A11, A12, newN), B22);
        std::vector<int> P3 = matrixMultiplication(newM, newN, newK, matrixAddition(A21, A22, newN), B11);
        std::vector<int> P4 = matrixMultiplication(newM, newN, newK, A22, matrixSubtraction(B21, B11, newK));
        std::vector<int> P5 = matrixMultiplication(newM, newN, newK, matrixAddition(A11, A22, newN), matrixAddition(B11, B22, newK));
        std::vector<int> P6 = matrixMultiplication(newM, newN, newK, matrixSubtraction(A12, A22, newN), matrixAddition(B21, B22, newK));
        std::vector<int> P7 = matrixMultiplication(newM, newN, newK, matrixSubtraction(A11, A21, newN), matrixAddition(B11, B12, newK));

        // Compute the result matrices
        std::vector<int> C11 = matrixAddition(matrixSubtraction(matrixAddition(P5, P4, newK), P2, newK), P6, newK);
        std::vector<int> C12 = matrixAddition(P1, P2, newK);
        std::vector<int> C21 = matrixAddition(P3, P4, newK);
        std::vector<int> C22 = matrixSubtraction(matrixSubtraction(matrixAddition(P5, P1, newK), P3, newK), P7, newK);

        // Combine the result matrices into a single matrix
        std::vector<int> result(m * k, 0);
        for (int i = 0; i < newM; i++) {
            for (int j = 0; j < newK; j++) {
                result[i * k + j] = C11[i * newK + j];
                result[i * k + j + newK] = C12[i * newK + j];
                result[(i + newM) * k + j] = C21[i * newK + j];
                result[(i + newM) * k + j + newK] = C22[i * newK + j];
            }
        }

        return result;
}
}
// benchmark multiplication of squared matrices of size (N x N) (feel free to change)
const vector<long long> Ns{ 1, 5, 25, 128, 512 };

// uniform distribution of matrix entries (feel free to change)
const int entryMin = 0;
const int entryMax = 10;

// don't touch
const bool bT = false;
#include "utils/matrix-multiplication.h"
