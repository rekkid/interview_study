/*
 * knapsack2.cc
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
int c[W + 1];

Item item[MAX_TYPES] = { {850, 400}, {300, 150}, {500, 150}, {200, 120} };

void knapsack(int n, int w)
{
	memset(c, 0x80, sizeof(c));
	c[0] = 0;

	for (int i = 0; i < n; ++i) {
		for (int j = w; j - item[i].weight >= 0; --j) {
			c[j] = max(c[j], c[j - item[i].weight] + item[i].cost);
		}
	}

	int bestw = 0;
	for (int i = 1; i <= w; ++i) {
		if (c[i] > c[bestw]) {
			bestw = i;
		}
	}

	printf("Highest value is %d\n", c[bestw]);

	for (int minw = 0; minw <= w; ++minw) {
		if (c[minw] == c[bestw]) {
			printf("Lightest is %d\n", minw);
			break;
		}
	}

	for (int maxw = w; maxw >= 0; --maxw) {
		if (c[maxw] == c[bestw]) {
			printf("Heaviest is %d\n", maxw);
			break;
		}
	}
}

int main()
{
	for (int i = 0; i < MAX_TYPES; ++i) {
		printf("[%d]: weight: %d, cost: %d\n", i + 1, item[i].weight, item[i].cost);
	}
	knapsack(MAX_TYPES, 1000);
	return 0;
}

