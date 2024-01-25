/** TDDD95: Lab 1 - polymul2
 * Author: Axel Söderlind
 * Date:   2024-01-25
 * This problem is about multiplying two polynomials. We use the
 * Fast Fourier Transform to solve this problem. We first pad the
 * polynomials with zeroes to make their size a power of two. We
 * then convert the polynomials to complex numbers and perform
 * the FFT. We then multiply the resulting polynomials and perform
 * the inverse FFT to get the resulting polynomial.
 *
 * Complexity: O(nlogn) where n is the number of coefficients in the polynomials.
 * Space: O(n) where n is the number of coefficients in the polynomials.
 *
 */
#include <iostream>
#include <complex>
#include <vector>

using namespace std;

// For storing complex values of nth roots
// of unity we use complex<double>
typedef complex<double> cd;

// Recursive function of FFT
vector<cd> fft(vector<cd> &a, bool invert)
{
    int n = a.size();

    // if input contains just one element
    if (n == 1)
        return vector<cd>(1, a[0]);

    // For storing n complex nth roots of unity
    vector<cd> w(n);
    for (int i = 0; i < n; i++)
    {
        double alpha = -2 * M_PI * i / n * (invert ? -1 : 1);
        w[i] = cd(cos(alpha), sin(alpha));
    }

    vector<cd> A0(n / 2), A1(n / 2);
    for (int i = 0; i < n / 2; i++)
    {

        // even indexed coefficients
        A0[i] = a[i * 2];

        // odd indexed coefficients
        A1[i] = a[i * 2 + 1];
    }

    // Recursive call for even indexed coefficients
    vector<cd> y0 = fft(A0, invert);

    // Recursive call for odd indexed coefficients
    vector<cd> y1 = fft(A1, invert);

    // for storing values of y0, y1, y2, ..., yn-1.
    vector<cd> y(n);

    for (int k = 0; k < n / 2; k++)
    {
        y[k] = y0[k] + w[k] * y1[k];
        y[k + n / 2] = y0[k] - w[k] * y1[k];
        if (invert)
        {
            y[k] /= 2;
            y[k + n / 2] /= 2;
        }
    }
    return y;
}

vector<int> multiply(vector<cd> &fa, vector<cd> &fb)
{
    int n = 1;
    while (n < max(fa.size(), fb.size()))
        n <<= 1;
    n <<= 1;
    fa.resize(n), fb.resize(n);

    fa = fft(fa, false);
    fb = fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fa = fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}

int main()
{
    // Disable synchronization with C++ I/O streams and C streams for performance
    ios::sync_with_stdio(false);
    // Untie cin from cout for performance improvement
    cin.tie(NULL);

    int NUM_TEST_CASES;
    cin >> NUM_TEST_CASES;
    while (NUM_TEST_CASES--)
    {
        int degPoly1, degPoly2;
        cin >> degPoly1;
        degPoly1++;
        vector<cd> coeffPoly1(2 * degPoly1, 0);
        for (int i = 0; i < degPoly1; i++)
        {
            cin >> coeffPoly1[i];
        }

        cin >> degPoly2;
        degPoly2++;
        vector<cd> coeffPoly2(2 * degPoly2, 0);
        for (int i = 0; i < degPoly2; i++)
        {
            cin >> coeffPoly2[i];
        }

        vector<int> result = multiply(coeffPoly1, coeffPoly2);

        int degResult = result.size() - 1;
        while (degResult > 0 && result[degResult] == 0)
            degResult--; // Skip leading zeroes in output
        cout << degResult << "\n";

        // Output the coefficients of the resulting polynomial
        for (int i = 0; i <= degResult; i++)
        {
            cout << result[i] << (i < degResult ? " " : "\n");
        }
    }
    return 0;
}
