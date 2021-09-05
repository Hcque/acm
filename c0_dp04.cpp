

int main()
{
    int n, w;
    scanf("%d %d", &n, &w);
    vector<int> dp[w+1]; // 0-w
    // dp[i] is the max value with weight i;
    while (n--){
        int value, weight;
        scanf("%d %d", &weight, &value);
        for (int wei_now = w-weight;wei_now>=0;wei_now--){
            dp[wei_now+weight] = max(dp[wei_now+weight], dp[wei_now]+value);
        }

        
    }
}