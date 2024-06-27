#include <bits/stdc++.h>
using namespace std;

/* Compare function for sort (descending compare) */
bool compareDesc(double a, double b) {
    return a > b;
}

/*
 * Function that fills a line in the dp matrix.
 * Parameters: 3 sorted vectors, their lengths, the dp line and k.
 * Takes the minimum value of the 3 vectors and adds it in the result,
 * eliminating duplicates. If there are more elements than k, stops at k.
 */
void fillDPLine(vector<double> v1,
                vector<double> v2,
                vector<double> v3,
                int len0, int len1, int len2,
                vector<double> &result, int k) {
    int i = 1, j = 1, l = 1, x = 1;

    // While there are elements in the vectors
    while (i <= len0 || j <= len1 || l <= len2) {
        double min_val = INFINITY;

        // Calculate the minimum value
        if (i <= len0) {
            min_val = min(min_val, v1[i]);
        }
        if (j <= len1) {
            min_val = min(min_val, v2[j]);
        }
        if (l <= len2) {
            min_val = min(min_val, v3[l]);
        }

        /* Add the minimum value to result if the vector is not already full
        or it is a duplicate */
        if (x <= k) {
            if (min_val != result[x - 1]) {
                result[x++] = min_val;
            }
        } else {
            // The result vector is full so we return.
            return;
        }

        // Going to the next element.
        if (i <= len0 && v1[i] == min_val) {
            i++;
        } else if (j <= len1 && v2[j] == min_val) {
            j++;
        } else {
            l++;
        }
    }
}

class Task {
 public:
    /* Function that runs the code */
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, k;
    vector<int> prices;

    /* Reading function */
    void read_input() {
        ifstream fin("oferta.in");
        fin >> n >> k;

        prices.push_back(-1);
        for (int i = 1, price; i <= n; i++) {
            fin >> price;
            prices.push_back(price);
        }

        fin.close();
    }

    /* Function that calculates the result */
    double get_result() {
        vector<vector<double>> dp(n + 1, vector<double>(k + 1, 0));
        /* dp - holds the solutions for each "smaller problem" resulting
        in the final solution */

        // Base cases
        // 1 product
        dp[1][1] = prices[1];

        // 2 products
        if (n > 1) {
            dp[2][1] = prices[1] < prices[2] ?
                        prices[1] / 2.0 + prices[2] :
                        prices[2] / 2.0 + prices[1];
            if (k >= 2) {
                dp[2][2] = prices[1] + prices[2];
            }
        }

        // 3 products
        if (n > 2) {
            vector<double> v;
            v.push_back(prices[1] + prices[2] + prices[3] -
                        min({prices[1], prices[2], prices[3]}));
            v.push_back(prices[3] + (prices[1] < prices[2] ?
                                    prices[1] / 2.0 + prices[2] :
                                    prices[2] / 2.0 + prices[1]));
            v.push_back(prices[1] + (prices[3] < prices[2] ?
                                    prices[3] / 2.0 + prices[2] :
                                    prices[2] / 2.0 + prices[3]));
            v.push_back(prices[1] + prices[2] + prices[3]);
            sort(v.begin(), v.end());

            int vlen = v.size(), len = vlen > k ? k : vlen;
            for (int j = 0; j < len; j++) {
                dp[3][j + 1] = v[j];
            }
        }

        /* For the rest of the products we calculate each offer and store
         * them in 3 vectors.
         * v_o0 - no offer, just add the product to the rest
         * v_o1 - offer 1 between the current and previous product
         * v_o2 - offer 2 between the current and previous 2 products
         */
        vector<double> v_o0(k + 1, 0), v_o1(k + 1, 0), v_o2(k + 1, 0);

        for (int i = 4; i <= n; i++) {
            int len0 = 0, len1 = 0, len2 = 0;

            for (int j = 1; j <= k; j++) {
                // Checking if the offers can be applied
                if (dp[i - 1][j]) {
                    v_o0[j] = dp[i - 1][j] + prices[i];
                    len0++;
                }
                if (dp[i - 2][j]) {
                    v_o1[j] = dp[i - 2][j] + (prices[i - 1] < prices[i] ?
                                            prices[i - 1] / 2.0 + prices[i] :
                                            prices[i] / 2.0 + prices[i - 1]);
                    len1++;
                }
                if (dp[i - 3][j]) {
                    v_o2[j] = dp[i - 3][j] +
                            prices[i - 2] + prices[i - 1] + prices[i] -
                            min({prices[i - 2], prices[i - 1], prices[i]});
                    len2++;
                }
            }
            fillDPLine(v_o0, v_o1, v_o2, len0, len1, len2, dp[i], k);
        }
        return dp[n][k] == 0 ? -1 : dp[n][k];
    }

    /* Printing function */
    void print_output(double result) {
        ofstream fout("oferta.out");
        fout << setprecision(1) << fixed << result;
        fout.close();
    }
};

int main() {
    auto* task = new (nothrow) Task();
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
