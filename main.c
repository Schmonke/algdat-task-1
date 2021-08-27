#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

const int ITERATION_EXPONENT_START = 3;
const int ITERATION_EXPONENT_END = 5;

int g_Stock[] = {-1, 3, -9, 2, 2, -1, 2, -1, -5};
int g_StockLen = sizeof(g_Stock) / sizeof(g_Stock[0]);

typedef struct Trade
{
    int buyIndex, sellIndex;
} Trade;

struct Trade find_optimal_stock_trade(int *stock, int stockLen)
{
    int maxProfit = 0;
    Trade trade;

    // Iterate over all buy indices.
    for (int i = 0; i < stockLen; i++)
    {
        int gain = 0;
        // Iterate over all possible sell indices relative to the buy indices.
        for (int j = i + 1; j < stockLen; j++)
        {
            gain += stock[j];
            if (gain > maxProfit)
            {
                trade.buyIndex = i;
                trade.sellIndex = j;
                maxProfit = gain;
            }
        }
    }

    return trade;
}

int main()
{
    // Run algorithm for the stock prices given in the task.
    struct Trade trade = find_optimal_stock_trade(g_Stock, g_StockLen);
    printf("n^2: Optimal buy and sell day: (%d, %d)\n", trade.buyIndex + 1, trade.sellIndex + 1);

    printf("\n### Performance measurement ###\n");
    for (int n = ITERATION_EXPONENT_START; n <= ITERATION_EXPONENT_END; n++)
    {
        // Generate a random array with 10^n values
        int len = (int)powl(10, n);
        int *stock = (int *)malloc(len * sizeof(int));
        for (int i = 0; i < len; i++)
        {
            int value = (rand() - (RAND_MAX / 2)) % 500;
            stock[i] = value;
        }

        // Find the optimal stock trade while measuring the time.
        struct timespec start, end;
        if (clock_gettime(CLOCK_REALTIME, &start))
        {
            printf("gettime failure\n");
            return 1;
        }
        trade = find_optimal_stock_trade(stock, len);
        if (clock_gettime(CLOCK_REALTIME, &end))
        {
            printf("gettime failure\n");
            return 1;
        }

        // Print out the time.
        int ms = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
        printf("%d iterations took %dms\n", len, ms);
        printf("Buy: %d, sell: %d\n\n", trade.buyIndex + 1, trade.sellIndex + 1);

        free(stock);
    }

    return 0;
}
