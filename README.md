# Oferta

 - Method: Dynamic Programming
 - Complexity:
   - Time: O(n * k)
      - Explanation: We have a for loop that goes up to n => O(n). In it there is another loop that goes up to k => O(k). After the k loop there is a function that can iterate up to 3*k => O(k). Finally, the complexity is O(n * k).
   - Space: O(n * k)
      - Explanation: dp -> dim = (n + 1) * (k + 1) => O(n * k). v_o0, v_o1, v_o2 -> dim = k + 1 => O(k).

 - We calculate all possible values for the first 3 products.
    - The value if there is 1 product is the price of that product.
    - The value if there are 2 products is the offer for those products or the sum of the separate products' prices.
    - The value if there are 3 products is the offer for 3 products or the offer for 2 products for the first 2 products or the offer for 2 products for the last 2 products or the sum of the separate products' prices.
 - For the rest of the products we calculate each offer if we add the current product. We store each offer in a separate vector (3 vectors) and repeat this process at most k times.
 - This way all 3 vectors will already be sorted (there can not be an offer smaller than the previous one when we add a new product for each vector).
 - Taking advantage of this, we interleave them, directly adding each minimum in the dp[i] line, excluding duplicates.
 - The final result will be the element on dp[n][k] or -1 if it doesn't exist.
