/*
 * change.cc
 *
 *  Created on: Jul 26, 2015
 *      Author: root
 */

#include <stdio.h>
#include <string.h>

int price[5] = {50, 20, 10, 5, 100};
int c[1000 + 1];

void change(int m)
{
	memset(c, 0, sizeof(c));
	c[0] = 1;

	for (int i = 0; i < 5; ++i) {
		for (int j = price[i]; j <= m; ++j) {
			c[j] += c[j - price[i]];
		}
 	}

	printf("cost: %d\n", m);
	printf("total types: %d\n", c[m]);
}

int main()
{
	change(20);

	return 0;
}

