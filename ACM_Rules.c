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

	firstTime = t + problem[index].solve;
	*debugTimes = firstTime % 60 ? firstTime / 60 : firstTime / 60 - 1; //consider the critical condition

	return problem[index].solve + problem[index].debug * *debugTimes;
}

void dfs(int count, int t, int totalTime)
{
	/*
		so far the number of the problems we have solved is count
		now the time is t
	*/
	if ((count > maxCount) || (count == maxCount && totalTime < minT)){
		/*
			update the best solution when:
			present solved problems is more than best solution's or
			present solved problems is equal to best solution's but totaltime is less
		*/
		record(count, totalTime);
	}

	int i, realTime, debugTimes;

	for (i = 0; i < n; i++){
		if (!solved[i]){
			realTime = getTime(i, t, &debugTimes);
			if (t + realTime <= h){
				/*
					if we have enough time to solve problem[i]
					then try to solve it and update totaltime and answer[]
				*/
				solved[i] = 1;
				totalTime += t + realTime + 20 * debugTimes;
				answer[count++] = i;
				dfs(count, t + realTime, totalTime);
				/*
					undo the change
				*/
				count--;
				totalTime -= t + realTime + 20 * debugTimes;
				solved[i] = 0;
			}
		}
	}
}

int main()
{
	int i;

	scanf("%d", &h);
	while (h >= 0){
		scanf("%d%d", &n, &read);
		for (i = 0; i < n; i++){
			scanf("%s%d%d", problem[i].name, &problem[i].solve, &problem[i].debug);
			solved[i] = answer[i] = key[i] = 0;
		}
		h *= 60;
		maxCount = -1;
		minT = 32767;
		/*
			at the very begining we have solved nothing
			already takes read time
			totaltime is zero
		*/
		dfs(0, read, 0);
		printf("Total Time = %d\n", minT);
		for (i = 0; i < maxCount; i++)
			printf("%s\n", problem[key[i]].name);
		scanf("%d", &h);
	}
}