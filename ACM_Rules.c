#include <stdio.h>
#include <string.h>

typedef struct problem {
	char name[21];
	int solve, debug;
} prob;

prob problem[10];

/*
	answer[] saves the temperary result
	solved[] is a boolean list to flag if the prob i has been solved
	key[] saves the best solution so far
*/
int answer[10], solved[10], key[10], maxCount, minT, h, n, read;

void record(int count, int t)
{
	/*
		update the maxCount and minTime
		copy answer[] to key[] for printing
	*/
	maxCount = count;
	minT = t;

	int i;

	for (i = 0; i < count; i++)
		key[i] = answer[i];
}

int getTime(int index, int t, int *debugTimes)
{
	/*
		calculate the debugtimes and the realtime it will cost when start doing problem[index] at time t
	*/
	int firstTime;

		dfs(0, read, 0);
		printf("Total Time = %d\n", minT);
		for (i = 0; i < maxCount; i++)
			printf("%s\n", problem[key[i]].name);
		scanf("%d", &h);
	}
}