/*
 * knapsack3.cc
 *
 *  Created on: Jul 26, 2015
 *      Author: root
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

typedef struct Item {
	int weight;
	int cost;
} Item;

const int MAX_TYPES = 4;
const int N = 100, C = 100000;
const int W = 100000;
int cost[W + 1];
int c[N + 1][W + 1];

Item item[MAX_TYPES] = { {850, 400}, {300, 150}, {500, 150}, {200, 120} };

void knapsack(int n, int w)
{
	memset(cost, 0, sizeof(cost));

	for (int i = 0; i < n; ++i) {
		for (int j = w; j - item[i].weight >= 0; --j) {
			cost[j] = max(cost[j], cost[j - item[i].weight] + item[i].cost);
		}
	}


	printf("The highest value is %d\n", cost[w]);
}

int knapsack2(int n, int w)
{
	if (w < 0) return -1e9;
	if (n == 0) return 0;

	if (c[n][w]) return c[n][w];

	return c[n][w] = max(knapsack2(n - 1, w - item[n].weight) + item[n].cost,
			             knapsack2(n - 1, w));

}

void knapsack3(int n, int w)
{
	memset(c, 0, sizeof(c));

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= w; ++j) {
			if (j - item[i].weight < 0) {
				c[i + 1][j] = c[i][j];
			} else {
				c[i + 1][j] = max(c[i][j], c[i][j - item[i].weight] + item[i].cost);
			}
		}
	}

	printf("The highest value is %d\n", c[n][w]);
}


int main()
{
	for (int i = 0; i < MAX_TYPES; ++i) {
		printf("[%d]: weight: %d, cost: %d\n", i + 1, item[i].weight, item[i].cost);
	}
	knapsack(MAX_TYPES, 1000);
//	printf("The highest value is %d\n", knapsack2(MAX_TYPES, 1000));
//	knapsack3(MAX_TYPES, 1000);
	return 0;
}



