#include <stdexcept>
#include <string>
#include <vector>
#define HW1_METHOD_NAME_STR "Karatsuba"


using namespace std;

/**
 * @brief implementation of karatsuba multiplication algorithm
 *
 * @param s1 - string, which represents the first number
 * @param s2 - string, which represents the second number
 *
 * @return string, which represents multiplication of @param s1 and @param
 * s2
 *
 * Constraints:
 *      1 <= s1.size(), s2.size()
 *      s1 and s2 contains only ascii digits
 *
 * @note @param s1 and @param s2 may contain trailing zeros
 * @note returned value should not contain trailing zeros
 */

// Function to add two large numbers represented as strings
string add(const string &num1, const string &num2) {
    string result;
    int carry = 0;

    int i = num1.size() - 1;
    int j = num2.size() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int digit1 = (i >= 0) ? (num1[i] - '0') : 0;
        int digit2 = (j >= 0) ? (num2[j] - '0') : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        sum = sum % 10;

        result.insert(result.begin(), sum + '0');

        i--;
        j--;
    }

    if (carry) {
        result.insert(result.begin(), carry + '0');
    }

    return result;
}




// Function to subtract two large numbers represented as strings
string subtract(const string &num1, const string &num2) {
    string result;
    int borrow = 0;

    int i = num1.size() - 1;
    int j = num2.size() - 1;

    while (i >= 0) {
        int digit1 = (i >= 0) ? (num1[i] - '0') : 0;
        int digit2 = (j >= 0) ? (num2[j] - '0') : 0;

        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.insert(result.begin(), diff + '0');

        i--;
        j--;
    }

    // Remove leading zeros
    while (result.size() > 1 && result[0] == '0') {
        result.erase(0, 1);
    }

    return result;
}




string numMultiplication(const string &s1, const string &s2) {
    int n1 = s1.size();
    int n2 = s2.size();

    if (n1 == 1 || n2 == 1) {
        int product = stoi(s1) * stoi(s2);
        return to_string(product);
    }

    int n = max(n1, n2);
    int halfN = (n + 1) / 2;

    string a = (n1 > halfN) ? s1.substr(0, n1 - halfN) : "0";
    string b = (n1 > halfN) ? s1.substr(n1 - halfN) : s1;
    string c = (n2 > halfN) ? s2.substr(0, n2 - halfN) : "0";
    string d = (n2 > halfN) ? s2.substr(n2 - halfN) : s2;

    string ac = numMultiplication(a, c);
    string bd = numMultiplication(b, d);

    string aPlusb = add(a, b);
    string cPlusd = add(c, d);
    string abcd = numMultiplication(aPlusb, cPlusd);

    string adbc = subtract(subtract(abcd, ac), bd);

    string result = add(add(ac + string(2 * halfN, '0'), adbc + string(halfN, '0')), bd);

    // Remove leading zeros
    while (result.size() > 1 && result[0] == '0') {
        result.erase(0, 1);
    }

    return result;
}

// ns to benchmark (feel free to change)
const vector<long long> Ns{ 1, 5, 25, 125, 1024, 2048, 10000, 100000 };

// uniform distribution of digits in s1 and s2 (feel free to change)
const int digitMin = 0;
const int digitMax = 9;

// don't touch
#include "utils/num-multiplication.h"
