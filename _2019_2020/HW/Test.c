#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int main() {
	int n;
	//int mays = 0;
	while(scanf("%d", &n) != EOF) {
		int mays1 = 0;
		int mays2_sum = 0;
		int mays2[n];
		if(n%2 == 0) {
			for (int i = 0;i <= n;) {
				mays1++;
				i = i+2;
			}
			mays1 = mays1*((n/2 + 1) - 1);
			//mays = mays*2;
			for (int i = 1;i < n;) {
				mays2[i] = 0;
				if ((i+1)%2 == 0) {
					for (int j = 0;j <= n-i+1;) {
						mays2[i]++;
						j = j+2;
					}
					mays2[i] = mays2[i]*((n/2 + 1) - 1);
				}
				else {
					for (int j = 1;j <= n-i+1;) {
						mays2[i]++;
						j = j+2;
					}
					mays2[i] = mays2[i]*((n+1)/2) - 1;
				}
				mays2_sum += mays2[i];
				i++;
			}
		}
		else {
			for (int i = 1;i <= n;) {
				mays1++;
				i = i+2;
			}
			mays1 = mays1*((n+1)/2) - 1;
			//printf("%d\n", mays1);
			if (n == 1)
				mays1 = 1;
			for (int i = 1;i < n;) {
				mays2[i] = 0;
				if ((i+1)%2 == 0) {
					for (int j = 1;j <= n-i+1;) {
						mays2[i]++;
						j = j+2;
					}
					mays2[i] = mays2[i]*((n+1)/2) - 1;	
				//printf("%d\n", mays2[i]);
				}
				else {
					for (int j = 0;j <= n-i+1;) {
						mays2[i]++;
						j = j+2;
					}
					mays2[i] = mays2[i]*((n/2 + 1) - 1);
				//printf("%d\n", mays2[i]);
				}
			mays2_sum += mays2[i];
			i++;
			//printf("%d\n", mays2_sum);
			}
		}

		printf("%d\n", mays1+mays2_sum);
	}
	return 0;
}











































































































































































































































































































































































































































































































































/*字符去重按ACILL码排序
先冒泡排序，再去重，去重思路如下
a[n];//排好序了
b[n];
b[0] = a[0];
k =1;
exist = 0;
for (int i = 0;i<n;i++) {
	for (int j= 0;j<k)
		if (b[j] == a[i]) {exist = 1;break;}
	if (exist == 0 ) {b[k] = a[i];k++;}
	else exist = 0;
}
*/

/*连续字符长度排序
先将连续
a[n];
b[n];
b[0] = a[0];
k =1;
exist = 0;
for (int i = 0;i<n;i++) {
	for (int j= 0;j<k)
		if (b[j] == a[i]) {exist = 1;break;}
	if (exist == 0 ) {b[k] = a[i];k++;}
	else exist = 0;
}
*/	
