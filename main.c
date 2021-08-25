#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int g_Stock[] = {-1, 3, -9, 2, 2, -1, 2, -1, -5};
int g_StockLen = sizeof(g_Stock) / sizeof(int);

void find_optimal_stock_trade(int *stock, int stockLen, int *pBuyIndex, int *pSellIndex)
{
    int prevGreatest = 0;
    *pBuyIndex = 0;
    *pSellIndex = 0;
    for (int i = 0; i < stockLen; i++)
    {
        int gain = 0;
        for (int j = i + 1; j < stockLen; j++)
        {
            gain += stock[j];
            if (gain > prevGreatest)
            {
                *pBuyIndex = i;
                *pSellIndex = j;
                prevGreatest = gain;
            }
        }
    }
}

int main()
{
    int buyIndex, sellIndex;
    find_optimal_stock_trade(g_Stock, g_StockLen, &buyIndex, &sellIndex);
    printf("n^2: Optimal buy and sell day: (%d, %d)\n", buyIndex + 1, sellIndex + 1);

    for (int n = 3; n <= 5; n++)
    {
        int len = (int)powl(10, n);
        int *stock = (int *)malloc(len * sizeof(int));

        for (int i = 0; i < len; i++)
        {
            int value = (rand() - (RAND_MAX / 2)) % 500;
            stock[i] = value;
        }

        struct timespec start, end;
        if (clock_gettime(CLOCK_REALTIME, &start))
        {
            printf("gettime failure\n");
            return 1;
        }
        find_optimal_stock_trade(stock, len, &buyIndex, &sellIndex);
        if (clock_gettime(CLOCK_REALTIME, &end))
        {
            printf("gettime failure\n");
            return 1;
        }
        int ms = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;

        printf("%d iterations took %dms\n", len, ms);
        printf("Buy: %d, sell: %d\n", buyIndex + 1, sellIndex + 1);

        free(stock);
    }

    return 0;
}
