#include  <stdio.h>

int binsearch(int arr[], int len, int num);





int main()
{
	int nums[6] = {13,25,123,253,456,879};
	printf("%d", binsearch(nums, 6, 456));
	return 0;
}




int binsearch(int arr[], int l, int n)
{
	int low, high, mid;

	low = 0;
	high = l-1;
	mid = (low + high)/2;
	while(low <= high && n != arr[mid]) {
		if(n<arr[mid])
			high = mid-1;
		else
			low = mid + 1;
		mid = (low + high)/2;
	}

	if(n == arr[mid])
		return mid;
	return -1;
}

		

