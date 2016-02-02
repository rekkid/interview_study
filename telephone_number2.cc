/*
 * telephone_number2.cc
 *
 *  Created on: Jan 16, 2016
 *      Author: root
 */

#include#include

#define N 4 //电话号码个数

using namespace std;

char c[][10] = { "", "", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV",
		"WXYZ" }; //存储各个数字所能代表的字符
int number[N] = { 2, 4, 7, 9 }; //存储电话号码
int total[10] = { 0, 0, 3, 3, 3, 3, 3, 4, 3, 4 }; //各个数组所能代表的字符总数
int answer[N]; //数字目前所代表的字符在其所能代表的字符集中的位置,初始为0

void Search(int *number, int n); //非递归的办法
void RecursiveSearch(int *number, int cur, char *ps, int n); //递归的办法
int main() {
	//Search(number, N);
	char ps[N + 1] = { 0 };
	RecursiveSearch(number, 0, ps, N);
	return 0;
}

void Search(int *number, int n) {
	int i;
	while (1) {
		for(i=0; i<n; ++i)="" printf("%c",="" c[number[i]][answer[i]]);="" printf("\n");="" int="" k="n-1;" 用k和while循环来解决扩展性问题,模拟了递归="" while(k="">= 0)
		{
			</n;>

			<n; ++i)="" printf("%c",="" c[number[i]][answer[i]]);="" printf("\n");="" int="" k="n-1;" 用k和while循环来解决扩展性问题,模拟了递归="" while(k=""> if(answer[k] < total[number[k]]-1) {++answer[k]; break;} else {answer[k] = 0; --k;}}if (k
				< 0)
			break;
	}
} /*递归的解法: number为存储电话号码的数组,pos为当前处理的数字在number中的下标,初始为0 *ps为一外部数组,用于存放字母,n代表电话号码的长度(个数) * 此递归的方法好理解,比上面非递归的办法好写易懂 * */


<n; ++i)="" printf("%c",="" c[number[i]][answer[i]]);="" printf("\n");="" int="" k="n-1;" 用k和while循环来解决扩展性问题,模拟了递归="" while(k="">
</n;>
void RecursiveSearch(int *number, int pos, char *ps, int n)
{
	int i;
	for(i=0; i<total[number[pos]]; ++i)
	{
		ps[pos] = c[number[pos]][i];
		if(pos == n-1)
		cout<<ps<<endl;
		else
		RecursiveSearch(number, pos+1, ps, n);
	}
}

