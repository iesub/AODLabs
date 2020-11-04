#include <iostream>
#include <vector>

using namespace std;

int main()
{
		vector<vector<int>> cost;
		vector<int> visited;
		int first_node = 0, second_node = 0, node_count, minimum_cost = 0, check_nodes_count = 0;
		setlocale(LC_ALL, "Russian");
		cout << "Введи количество вершин  "; cin >> node_count;
		cout << "Введи матрицу смежности\n";


		for (int i = 0; i < node_count; i++) { //вводим матрицу смежности(матрица с расстояниями между узлами)
			cost.push_back(vector<int>());         //    1  2  3
			visited.push_back(0);                  // 1  0  2  4
			for (int j = 0; j < node_count; j++)   // 2  2  0  2
			{                                      // 3  4  2  0
				int length;
				cin >> length;
				cost[i].push_back(length);
				if (cost[i][j] == 0)
					cost[i][j] = -1;
			}
		}
		
		visited[0] = 1;
		cout << "\n";
		int min = -1;

		while (check_nodes_count != node_count)
		{
			check_nodes_count = 0;
			for (int i = 0; i < node_count; i++) { // проходим дерево. если мы прошли по узлу, ищем самый короткий путь от него к другим узлам
				for (int j = 0; j < node_count; j++) {
					if (min == -1 && cost[i][j] != -1) min = cost[i][j];
					if (cost[i][j] <= min && cost[i][j] != -1) {
						if (visited[i] != 0) {
							min = cost[i][j];
							first_node = i;
							second_node = j;
						}
					}
				}
			}
			if (visited[first_node] == 0 || visited[second_node] == 0) { //найденный узел помечаем как пройденный и приплюсовываем к общему пути
				cout <<"\n"<< first_node+1 << "-->" << second_node+1 << ": " << min;
				minimum_cost += min;
				visited[second_node] = 1;
			}
			min = -1;
			cost[first_node][second_node] = cost[second_node][first_node] = -1; //проверяем все узлы пройдены. если да, то цикл прервется
			for (int i = 0; i < visited.size(); i++)
				if (visited[i] == 1) {
					check_nodes_count++;
				}
		}
		cout << "\nМинимальная стоимость: " <<  minimum_cost;
}

