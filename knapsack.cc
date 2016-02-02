/*
 * knapsack.cc
 *
 *  Created on: Jul 25, 2015
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
int weight[C + 1];

Item item[MAX_TYPES] = { {850, 400}, {300, 150}, {500, 150}, {200, 120} };

void knapsack(int n, int w)
{
	memset(weight, 0x7f, sizeof(weight));
	weight[0] = 0;

	for (int i = 0; i < n; ++i) {
		for (int j = C; j - item[i].cost >= 0; --j) {
			weight[j] = min(weight[j], weight[j - item[i].cost]) + item[i].weight;
		}
	}

	int c = C;
	while (weight[c] > w) c--;
	printf("The highest value is %d\n", c);
}

int main()
{
	for (int i = 0; i < MAX_TYPES; ++i) {
		printf("[%d]: weight: %d, cost: %d\n", i + 1, item[i].weight, item[i].cost);
	}
	knapsack(MAX_TYPES, 1000);
	return 0;
}

