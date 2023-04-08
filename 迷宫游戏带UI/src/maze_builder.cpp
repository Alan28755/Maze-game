#include"maze_builder.h"
static int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
typedef struct node
{
	int i, j;
}node;
void buildMaze(char** map, int n)
{
	/*map = (char**)malloc(n * sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		map[i] = (char*)malloc(n * sizeof(char));
		memset(map[i], 0, n);

	}*/

	srand((unsigned int)time(NULL));
	map[n-2][1] = 1;
	int currentI = n-2, currentJ = 1;
	int ti1, tj1;
	int ti2, tj2;
	node tnode;
	int t;
	list l;
	newList(&l, sizeof(struct node));
	for (int i = 0; i < 4; i++)
	{
		ti2 = currentI + dir[i][0]*2;
		tj2 = currentJ + dir[i][1]*2;
		if (ti2 < 0 || ti2 >= n  || tj2 < 0 || tj2 >= n)
		{
			continue;
		}
		if (map[ti2][tj2])
			continue;
		tnode = { ti2,tj2 };
		l_push_back(&l, &tnode);
	}
	int ti[4], tj[4], count;
	while (!l_empty(&l))
	{
		t = Rand(l.len);
		l_visit_erase(&l, &tnode, t);
		if (map[tnode.i][tnode.j])
			continue;
		map[tnode.i][tnode.j] = 1;
		currentI = tnode.i;
		currentJ = tnode.j;
		count = 0;
		for (int i = 0; i < 4; i++)
		{
			ti1 = currentI + dir[i][0];
			tj1 = currentJ + dir[i][1];
			ti2 = currentI + dir[i][0] * 2;
			tj2 = currentJ + dir[i][1] * 2;
			
			if (ti2 < 0 || ti2 >= n || tj2 < 0 || tj2 >= n)
				continue;
			if (map[ti1][tj1] == 0 && map[ti2][tj2] == 1)
			{
				ti[count] = ti1;
				tj[count] = tj1;
				count++;
			}
			if (map[ti1][tj1] == 0 && map[ti2][tj2] == 0)
			{
				tnode = { ti2,tj2 };
				l_push_back(&l, &tnode);
			}
		}
		count = Rand(count);
		map[ti[count]][tj[count]] = 1;
		/*for (int i = 0; i < 4; i++)
		{
			ti1 = currentI + dir[i][0];
			tj1 = currentJ + dir[i][1];
			ti2 = currentI + dir[i][0] * 2;
			tj2 = currentJ + dir[i][1] * 2;
			if (map[ti2][tj2])
				continue;
			if (ti2 < 0 || ti2 >= n || tj2 < 0 || tj2 >= n)
				continue;
			if (map[ti1][tj1] == 0 && map[ti2][tj2] == 0)
			{
				tnode = { ti2,tj2 };
				l_push_back(&l, &tnode);
			}

		}*/
	}
	map[1][n - 2] = 3;
	/*for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}*/
}
int Rand(int max)
{
	return rand() % max;
}