//Вариант 5
#include <iostream> 
using namespace std;
const int N = 4; //Количество городов
//Здесь храним итоговый путь торговца
int final_path[N + 1];
//Здесь храним все посещенные города в данном пути
bool visited[N];
//Здесь храним ответ - минимальную длительность пути 
int final_res = INT_MAX;
//Сохраняем временный путь(ответ) в итоговый
void copyToFinal(int curr_path[])
{
	for (int i = 0; i < N; i++)
		final_path[i] = curr_path[i];
	final_path[N] = curr_path[0];
}
//Находим минимальную стоимость перехода с концом в городе i
int firstMin(int adj[N][N], int i)
{
	int min = INT_MAX;
	for (int k = 0; k < N; k++)
		if (adj[i][k] < min && i != k)
			min = adj[i][k];
	return min;
}
//Находим еще одну минимальную стоимость перехода с концом в городе i  
int secondMin(int adj[N][N], int i)
{
	int first = INT_MAX, second = INT_MAX;
	for (int j = 0; j < N; j++)
	{
		if (i == j)
			continue;

		if (adj[i][j] <= first)
		{
			second = first;
			first = adj[i][j];
		}
		else if (adj[i][j] <= second &&
			adj[i][j] != first)
			second = adj[i][j];
	}
	return second;
}

// curr_bound -> нижняя граница корня
// curr_weight-> стоимость пути на данный момент
// level-> шаг
// curr_path[] -> временный путь
void TSPRec(int adj[N][N], int curr_bound, int curr_weight,
	int level, int curr_path[])
{
	//базовый случай, когда мы прошли по всем узлам
	if (level == N)
	{
		//проверяем есть ли путь от последней точки нашего пути в начало
		if (adj[curr_path[level - 1]][curr_path[0]] != 0)
		{
			//записываем текущий результат
			int curr_res = curr_weight +
				adj[curr_path[level - 1]][curr_path[0]];
			//обновляем итоговый вариант если текущий лучше 
			if (curr_res < final_res)
			{
				copyToFinal(curr_path);
				final_res = curr_res;
			}
		}
		return;
	}

	// если обошли не все вершины, строим дерево поиска 
	for (int i = 0; i < N; i++)
	{
		//проверяем, что узел не посещяли и это узел на который можно перейти с данного
		if (adj[curr_path[level - 1]][i] != 0 &&
			visited[i] == false)
		{
			int temp = curr_bound;
			curr_weight += adj[curr_path[level - 1]][i];

			//используем разные формулы в случае если шаг 1 или нет
			if (level == 1)
				curr_bound -= ((firstMin(adj, curr_path[level - 1]) +
					firstMin(adj, i)) / 2);
			else
				curr_bound -= ((secondMin(adj, curr_path[level - 1]) +
					firstMin(adj, i)) / 2);

			//если данный случай меньше уже имеющегося
			if (curr_bound + curr_weight < final_res)
			{
				curr_path[level] = i;
				visited[i] = true;
				//расчитываем результат для следующего шага
				TSPRec(adj, curr_bound, curr_weight, level + 1,
					curr_path);
			}
			//иначе вырезаем данный узел из решения и возвращаем старые значения веса и нижней границы
			curr_weight -= adj[curr_path[level - 1]][i];
			curr_bound = temp;
			// Восстанавливаем список посещенныйх узлов
			memset(visited, false, sizeof(visited));
			for (int j = 0; j <= level - 1; j++)
				visited[curr_path[j]] = true;
		}
	}
}

// Данная функция выдает нам наш результат 
void TSP(int adj[N][N])
{
	int curr_path[N + 1];
	int curr_bound = 0;
	//инициализируем массивы пути и посещенных узлов
	memset(curr_path, -1, sizeof(curr_path));
	memset(visited, 0, sizeof(curr_path));

	//высчитываем нижнюю границу. ниже найти нельзя
	for (int i = 0; i < N; i++)
		curr_bound += (firstMin(adj, i) +
			secondMin(adj, i));
	curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 :
		curr_bound / 2;
	//устанавливаем первым посещенный узлом узел 0
	visited[0] = true;
	curr_path[0] = 0;
	//начинаем расчет
	TSPRec(adj, curr_bound, 0, 1, curr_path);
}

 
int main()
{
	int adj[N][N] = { 
		{0, 10, 15, 20},
		{10, 0, 35, 25},
		{15, 35, 0, 30},
		{20, 25, 30, 0}
	};

	TSP(adj);

	printf("Minimum cost : %d\n", final_res);
	printf("Path Taken : ");
	for (int i = 0; i <= N; i++)
		printf("%d ", final_path[i]);

	return 0;
}
