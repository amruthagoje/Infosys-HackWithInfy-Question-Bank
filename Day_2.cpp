/*1. You are given two arrays A and P, both of length n.
At each step i, you can either:
Pick A[i] and add it to the score, but subtract penalty P[i].
Skip the element.
Find the maximum possible score.
Constraints: 1≤n≤1051 \leq n \leq 10^51≤n≤105, 0≤A[i],P[i]≤1050 \leq A[i], P[i] \leq
10^50≤A[i],P[i]≤105*/

long long maxScore(vector<int>& A, vector<int>& P, int n) {
    long long total = 0;
    for (int i = 0; i < n; i++) {
        if (A[i] > P[i]) {
            total += (A[i] - P[i]);
        }
    }
    return total;
}

/*2. You have a robot with k battery cycles.
Given an array Tasks[] of size n representing energy required per task,
and each task must be either:
Skipped
Executed, which costs Tasks[i] battery
You can skip at most m tasks. Maximize number of completed tasks.*/

int maxTasks(vector<int>& Tasks, int k, int m) {
    sort(Tasks.begin(), Tasks.end());
    int count = 0;
    for (int cost : Tasks) {
        if (k >= cost) {
            k -= cost;
            count++;
        } else if (m > 0) {
            m--; 
        } else break;
    }
    return count;
}

/*3. You're climbing n steps with height array H[i].
Each step costs H[i] energy.
You have x energy and k magic potions. Each potion gives +10 energy.
Use potions wisely to climb as far as possible.*/

int climbSteps(vector<int>& H, int x, int k) {
    long long totalEnergy = x + (k * 10LL);
    int steps = 0;
    for (int h : H) {
        if (totalEnergy >= h) {
            totalEnergy -= h;
            steps++;
        } else break;
    }
    return steps;
}

/*4. Each day i, you have a job with profit P[i]. If you pick job i,
you must skip the next day due to cooldown.
Return the maximum profit you can earn.*/

int maxProfit(vector<int>& P, int n) {
    if (n == 0) return 0;
    if (n == 1) return P[0];
    vector<int> dp(n);
    dp[0] = P[0];
    dp[1] = max(P[0], P[1]);
    for (int i = 2; i < n; i++) {
        dp[i] = max(dp[i-1], P[i] + dp[i-2]);
    }
    return dp[n-1];
}

/*5. You have M money and K discount vouchers (each 50% off).
You're given prices array P[0..n-1].
You can use vouchers on any items (but one voucher per item).
Minimize total spending. Return maximum number of items you can buy.*/

int maxItems(vector<int>& P, int M, int K) {
    sort(P.begin(), P.end());
    int n = P.size();
    int count = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    long long currentSpend = 0;

    for (int i = 0; i < n; i++) {
        currentSpend += P[i];
        pq.push(P[i]);
        if (pq.size() > K) {
            pq.pop(); 
        }
      
        long long discount = 0;
        priority_queue<int, vector<int>, greater<int>> temp = pq;
        while(!temp.empty()) {
            discount += temp.top() / 2;
            temp.pop();
        }

        if (currentSpend - discount <= M) count = i + 1;
        else break;
    }
    return count;
}

/*6. You're given array A[], and can select elements up to k times total.
You must not pick the same element in consecutive positions.
Maximize the total sum selected.*/

long long maxSum(vector<int>& A, int k) {
    sort(A.rbegin(), A.rend());
    if (A.size() == 1) return A[0]; 
    long long first = A[0], second = A[1];
    return (long long)(k / 2) * (first + second) + (k % 2) * first;
}

/*7. You are given X total energy and n tasks.
Each task i requires e[i] energy and gives v[i] value.
Find the maximum value you can collect by choosing some subset of tasks.*/

int knapsack(int X, vector<int>& e, vector<int>& v, int n) {
    vector<int> dp(X + 1, 0);
    for (int i = 0; i < n; i++) {
        for (int j = X; j >= e[i]; j--) {
            dp[j] = max(dp[j], dp[j - e[i]] + v[i]);
        }
    }
    return dp[X];
}

/*8. Given arrays A[i] (priority) and B[i] (cost).
You have R resources.
For each task:
If R >= B[i], you can take it and get A[i] score.
Each task reduces R by B[i].
Choose tasks to maximize score.*/

int maximizePriority(vector<int>& A, vector<int>& B, int R) {
    int n = A.size();
    vector<int> dp(R + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int j = R; j >= B[i]; j--) {
            dp[j] = max(dp[j], dp[j - B[i]] + A[i]);
        }
    }

    return dp[R];
}

int main() {
    vector<int> priorities = {10, 40, 30, 50}; 
    vector<int> costs = {5, 10, 15, 20};      
    int resources = 30;                        

    cout << "Maximum Priority Score: " << maximizePriority(priorities, costs, resources) << endl;

    return 0;
}

/*9. You're given prices[] of stocks.
You can buy/sell at most once, but one day you can use a bonus to buy at half
price.
Maximize profit using that one-time bonus wisely.’*/

int maxStockProfit(vector<int>& prices) {
    int n = prices.size();
    if (n < 2) return 0;
    vector<int> max_after(n);
    max_after[n-1] = prices[n-1];
    for (int i = n-2; i >= 0; i--) 
        max_after[i] = max(prices[i], max_after[i+1]);

    int maxP = 0;
    for (int i = 0; i < n - 1; i++) {
        maxP = max(maxP, max_after[i+1] - (prices[i] / 2));
    }
    return maxP;
}

/*10. You have a binary array arr of 0s and 1s.
You are allowed to flip exactly one subarray (0->1 and 1->0).
Find the maximum number of 1s you can get after the flip.*/

int maxOnes(vector<int>& arr) {
    int onesCount = 0;
    int n = arr.size();
    vector<int> gain(n);
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            onesCount++;
            gain[i] = -1;
        } else gain[i] = 1;
    }
    int maxGain = 0, currentGain = 0;
    for (int g : gain) {
        currentGain += g;
        if (currentGain < 0) currentGain = 0;
        maxGain = max(maxGain, currentGain);
    }
    return onesCount + maxGain;
}

