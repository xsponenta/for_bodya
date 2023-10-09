#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief implementation of grade school multiplication algorithm
 *
 * @param s1 - string, which represents the first number
 * @param s2 - string, which represents the second number
 *
 * @return string, which represents multiplication of @param s1 and @param
 * s2
 *
 * Constraints:
 *      1 <= s1.size(), s2.size() <= 10^5
 *      s1 and s2 contains only ascii digits
 *
 * @note @param s1 and @param s2 may contain trailing zeros
 * @note returned value should not contain trailing zeros
 */


string reverseString(const string &str) {
    string reversed;
    for (int i = str.size() - 1; i >= 0; i--) {
        reversed += str[i];
    }
    return reversed;
}


string numMultiplication(const string &s1, const string &s2)
{
    // TODO: implement
    int n1 = s1.size();
    int n2 = s2.size();

    // Check for zero inputs
    if (n1 == 0 || n2 == 0) {
        return "0";
    }

    vector<int> result(n1 + n2, 0);

    // Reverse the input strings
    string rev_s1 = reverseString(s1);
    string rev_s2 = reverseString(s2);

        for (int i = 0; i < n1; i++) {
        int carry = 0;
        int digit1 = rev_s1[i] - '0';

        for (int j = 0; j < n2; j++) {
            int digit2 = rev_s2[j] - '0';
            int product = digit1 * digit2 + result[i + j] + carry;

            carry = product / 10;
            result[i + j] = product % 10;
        }

        if (carry > 0) {
            result[i + n2] += carry;
        }
    }

    int i = n1 + n2 - 1;
    while (i >= 0 && result[i] == 0) {
        i--;
    }

    if (i == -1) {
        return "0";
    }

    string final_result;
    while (i >= 0) {
        final_result += to_string(result[i]);
        i--;
    }

    return final_result;
}

// ns to benchmark (feel free to change)
const vector<long long> Ns{ 100000, 1000000 };

// uniform distribution of digits in s1 and s2 (feel free to change)
const int digitMin = 0;
const int digitMax = 9;

// don't touch
#include "utils/num-multiplication.h"
