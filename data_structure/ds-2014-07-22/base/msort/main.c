#include <stdio.h>
#include <string.h>

void merge(int arr1[], int n1, int arr2[], int n2, int tmp[])
{
	int ind_1, ind_2, ind_tmp;

	ind_1 = ind_2 = ind_tmp = 0;
	while (ind_1 < n1 && ind_2 < n2) {
		if (arr1[ind_1] < arr2[ind_2]) {
			tmp[ind_tmp] = arr1[ind_1];
			ind_1++;
		} else {
			tmp[ind_tmp] = arr2[ind_2];
                        ind_2++;
		}
		ind_tmp++;
	}

	for (; ind_1 < n1; ind_1++, ind_tmp++) {
		tmp[ind_tmp] = arr1[ind_1];
	}
	for (; ind_2 < n2; ind_2++, ind_tmp++) {
                tmp[ind_tmp] = arr2[ind_2];
        }
}

void msort(int data[], int tmp[], int n)
{
	int mid;

	if (n <= 1) {
		return;
	}

	mid = n / 2;

	msort(data, tmp, mid);
	msort(data + mid, tmp + mid, n - mid);

	merge(data, mid, data + mid, n - mid, tmp);
	memcpy(data, tmp, n * sizeof(int));
}

int main(void)
{
	int data[18] = {4,9,3,44,99,88,8,33,2,22,5,55,66,6,7,77,1,11,};
	int tmp[18];
	int i;

	msort(data, tmp, 18);

	for (i = 0; i < 18; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");

	return 0;
}
