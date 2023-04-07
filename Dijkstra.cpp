// C++ Code implementation for Dijkstra
#include <iostream> // cout 
#include <queue> // FIFO queue 
#include <array>
#include <map> // dictionary

// debugging output to the screen
#include <conio.h> //
#include <thread>
#include <chrono>

using namespace std;

int step_counter = 0;

// outputing 
const bool verbose_output = false; // To see the expansion or the exploration step by step, amek this variable true
const bool break_output = false; // if true the user must hit the keyboard after each step
const bool slow_output = true; // if true wait_period of time is put between each 2 explorations 
const int wait_period = 250;// wait time between 2 explorations in milliseconds 

//#define Dijkstra_algo true

// comparison 
// Example	Dikstra			BFS
//          cost / steps	cost / steps
// 1		5	 / 9		1004	/ 9
// 2		1016 / 78		2015	/ 79
// 3		21	 / 90		1016	/ 94
// 4		24	 / 79		1017	/ 79
// 5		6	 / 32		4000	/ 29
// 6		7	 / 32		104		/ 32	
// 7		5	 / 26		1000	/ 11	
// 8		inf	 / 21		inf		/ 21	


// choose the map by definting the corresponding Example. For example if you want Example 3, change Example_# in below to Example_3
#define Example_3 true

// Based on the previous macro, only map is choosen
#ifdef Example_1
const int ROW_SIZE = 4;	
const int COL_SIZE = 4;
char grid[][COL_SIZE] = {
	{ '1', '0', '1', 'S' },
	{ '0', '1', '0', '0' },
	{ '1', '0', '0', '0' },
	{ 'G', '0', '0', '0' }
};
int cost[ROW_SIZE][COL_SIZE] = {
	{ 1, 1, 1,    0 },
	{ 1, 1, 1000, 1 },
	{ 1, 1, 1,    1 },
	{ 0, 1, 1,    1 }
};
#elif Example_2
const int ROW_SIZE = 10;
const int COL_SIZE = 10;
char grid[][COL_SIZE] = {
	{ 'S', '0', '0', '0', '0', '1', '1', '1', '1', '0' },
	{ '0', '0', '0', '0', '0', '1', '1', '1', '1', '0' },
	{ '0', '0', '0', '0', '0', '1', '1', '1', '1', '0' },
	{ '0', '0', '0', '0', '0', '1', '1', '1', '1', '0' },
	{ '0', '0', '0', '0', '0', '1', '1', '1', '1', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', 'G' }
};
int cost[][COL_SIZE] = {
	{ 0, 1000,  1000,	1, 1, 1, 1, 1, 1, 1 },
{  1000, 1000,  1000,	1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1000,	1000,	1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1,		1,		1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1,		1,		1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1,		1,		1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1,		1,		1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1,		1,		1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1,		1,		1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1,		1,		1, 1, 1, 1, 1, 1, 0 }
};
#elif Example_3
const int ROW_SIZE = 10;
const int COL_SIZE = 10;
char grid[][COL_SIZE] = {
	{ 'S', '0', '0', '0', '0', '0', '0', '0', '1', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '1', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '1', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '1', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '1', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', 'G' }
};
int cost[][COL_SIZE] = {
	{ 0, 1000, 1, 1, 1, 1, 1, 1, 1,    1 },
	{ 1, 1000, 1, 1, 1, 1, 1, 1, 1,    1 },
	{ 1, 1000, 1, 1, 1, 1, 1, 1, 1,    1 },
	{ 1, 1000, 1, 1, 1, 1, 1, 1, 1,    1 },
	{ 1, 1000, 1, 1, 1, 1, 1, 1, 1,    1 },
	{ 1, 1000, 1, 1, 1, 1, 1, 1, 1,    1 },
	{ 1, 1000, 1, 1, 1, 1, 1, 1, 1,    1 },
	{ 1, 1000, 1, 1, 1, 1, 1, 1, 1000, 1 },
	{ 1, 1,    1, 1, 1, 1, 1, 1, 1000, 1 },
	{ 1, 1,    1, 1, 1, 1, 1, 1, 1000, 0 }
};
#elif Example_4
const int ROW_SIZE = 10;
const int COL_SIZE = 10;
char grid[][COL_SIZE] = {
	{ 'S', '0', '0', '0', '0', '1', '1', '1', '1', 'G' },
	{ '0', '0', '0', '0', '0', '1', '1', '1', '1', '0' },
	{ '0', '0', '0', '0', '0', '1', '1', '1', '1', '0' },
	{ '0', '0', '0', '0', '0', '1', '1', '1', '1', '0' },
	{ '0', '0', '0', '0', '0', '1', '1', '1', '1', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
	{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' }
};
int cost[][COL_SIZE] = {
	{ 0, 1, 1, 1, 1, 1, 1, 1, 1,	0 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1,	1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1,	1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1,	1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1,	1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1000, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1000, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1000, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1,	1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1,	1 }
};
#elif Example_5
const int ROW_SIZE = 10;
const int COL_SIZE = 5;
char grid[][COL_SIZE] = {
	{ '0', '0', '0', '1', '1' },
	{ '1', '0', 'G', '1', '1' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', 'S', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '1', '1', '0', '0' }
};
int cost[][COL_SIZE] = {
	{ 1, 1, 1,		1, 1 },
	{ 1, 1, 0,		1, 1 },
	{ 1, 1, 1000,	1, 1 },
	{ 1, 1, 1000,	1, 1 },
	{ 1, 1, 1000,	1, 1 },
	{ 1, 1, 1000,	1, 1 },
	{ 1, 1, 0,		1, 1 },
	{ 1, 1, 1,		1, 1 },
	{ 1, 1, 1,		1, 1 },
	{ 1, 1, 1,		1, 1 }
};
#elif Example_6
const int ROW_SIZE = 10;
const int COL_SIZE = 5;
char grid[][COL_SIZE] = {
	{ '1', '0', '0', '0', '1' },
	{ '1', '0', '1', '0', '0' },
	{ '1', 'G', '1', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', 'S', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '1', '1', '0', '0' }
};
int cost[][COL_SIZE] = {
	{ 1, 1, 1,		1, 1 },
	{ 1, 1, 1,		1, 1 },
	{ 1, 0, 1,		1, 1 },
	{ 1, 1, 100,	1, 1 },
	{ 1, 1, 100,	1, 1 },
	{ 1, 1, 100,	1, 1 },
	{ 1, 1, 100,	0, 1 },
	{ 1, 1, 1,		1, 1 },
	{ 1, 1, 1,		1, 1 },
	{ 1, 1, 1,		1, 1 }
};
#elif Example_7
const int ROW_SIZE = 10;
const int COL_SIZE = 5;
char grid[][COL_SIZE] = {
	{ '1', '0', '0', '0', '1' },
	{ '1', '0', '1', '0', '0' },
	{ '1', '0', '1', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', 'S', '0', 'G', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '1', '1', '0', '0' }
};
int cost[][COL_SIZE] = {
	{ 1, 1, 1,		1, 1 },
	{ 1, 1, 1,		1, 1 },
	{ 1, 1, 1,		1, 1 },
	{ 1, 1, 1,		1, 1 },
	{ 1, 1, 1,		1, 1 },
	{ 1, 1, 1000,	1, 1 },
	{ 1, 0, 1000,	0, 1 },
	{ 1, 1, 1000,	1, 1 },
	{ 1, 1, 1,		1, 1 },
	{ 1, 1, 1,		1, 1 }
};
#elif Example_8
const int ROW_SIZE = 10;
const int COL_SIZE = 5;
char grid[][COL_SIZE] = {
	{ '1', '0', '0', '0', '1' },
	{ '1', '0', '1', '0', '0' },
	{ '1', 'G', '1', '0', '0' },
	{ '1', '1', '1', '1', '1' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', 'S', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '0', '0', '0', '0' },
	{ '1', '1', '1', '0', '0' }
};
int cost[][COL_SIZE] = {
	{ 1, 1, 1,		1, 1 },
	{ 1, 1, 1,		1, 1 },
	{ 1, 0, 1,		1, 1 },
	{ 1, 1, 1,		1, 1 },
	{ 1, 1, 1,		1, 1 },
	{ 1, 1, 1,		1, 1 },
	{ 1, 1, 1000,	0, 1 },
	{ 1, 1, 1,		1, 1 },
	{ 1, 1, 1,		1, 1 },
	{ 1, 1, 1,		1, 1 }
};
#endif // choose_map 

// The below function shows the map
void show_map(char input_map[ROW_SIZE][COL_SIZE]) {
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COL_SIZE; j++) {
			cout << input_map[i][j] << "\t"; // \t means space with length = 1 tap
		}
		cout << endl;
	}

	if (verbose_output) {
		cout << endl << "Notations:\n"
			"F: current frontier \t E: previously explored frontier \t S: start node \t G: goal node \n"
			"*: Descovered Node \t 0: free & unexplored node \t 1:obstacle" << endl;
	}

	if (break_output)
		_getch();

	if (slow_output)
		std::this_thread::sleep_for(std::chrono::milliseconds(wait_period));

}

// Initialize parent array with -1 (-1 means no parent or in otherwords the cell is not explored or descovered by any frontier)
void initialize_parents(int map_size, map<int, int> & parent) {
	for (int i = 0; i < map_size; i++) {
		parent.insert(pair<char, int>(i, -1)); //-1 means no parent
	}
}

// The below is defining the entry of each location in the queue. Each cell is defined by its col, row, id and real distance (real distance = exploration step BTW) 
// from start node
// QItem for current location and distance from start location
// Note: this data structure is used only in BFS
class QItem {
public:
	int row;
	int col;
	int id;
	int dist;

	QItem(int x, int y, int ID, int w)
		: row(x), col(y), id(ID), dist(w)
	{
	}
};

/********************************************************************************************************************************/
/***************************************************    BFS Algorithm     *******************************************************/
/********************************************************************************************************************************/
// Here is the real BFS function 
int BFS(char grid[ROW_SIZE][COL_SIZE], map<int, int> & parent, int & start_node_id, int & goal_node_id)
{
	QItem start(0, 0, 0, 0);

	// To keep track of visited QItems. Marking blocked cells as visited. By this we avoid extra check if cell is barrier or not
	// At the same time when we descover start or goal nodes we use their col and row indices to find ther ids (start_node_id and goal_node_id)
	bool visited[ROW_SIZE][COL_SIZE];
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COL_SIZE; j++)
		{
			if (grid[i][j] == '1') // if barrier
				visited[i][j] = true; // mark visited
			else
				visited[i][j] = false;

			// Finding start 
			if (grid[i][j] == 'S')
			{
				start.row = i;
				start.col = j;
				start.id = i + ROW_SIZE * j; 			// ID = row_index + row_size * col_index 
				start_node_id = i + ROW_SIZE * j;
			}

			// Finding goal 
			if (grid[i][j] == 'G')
			{
				goal_node_id = i + ROW_SIZE * j;
			}
		}
	}

	// applying BFS on matrix cells starting from start node
	queue<QItem> q;
	q.push(start);
	visited[start.row][start.col] = true;
	while (!q.empty()) {
		QItem p = q.front(); // p is the current Fronteir
		q.pop();

		//  goal found; 
		if (grid[p.row][p.col] == 'G') {
			return p.dist; // break the loop and return minimum hops = distance in uniform grid
		}

		if (verbose_output && grid[p.row][p.col] != 'S') {
			grid[p.row][p.col] = 'F';

			show_map(grid);
		}

		// moving up 
		if (p.row - 1 >= 0 &&
			visited[p.row - 1][p.col] == false) {
			int id = (p.row - 1) + ROW_SIZE * p.col;
			q.push(QItem(p.row - 1, p.col, id, p.dist + 1));
			parent[id] = p.id;
			visited[p.row - 1][p.col] = true;

			step_counter++;
			cout << endl << "current exploration step = " << step_counter << endl << endl;

			if (verbose_output) {
				if (grid[p.row - 1][p.col] != 'G')
					grid[p.row - 1][p.col] = '*';
				show_map(grid);
			}
		}

		// moving right 
		if (p.col + 1 < COL_SIZE &&
			visited[p.row][p.col + 1] == false) {
			int id = p.row + ROW_SIZE * (p.col + 1);
			q.push(QItem(p.row, p.col + 1, id, p.dist + 1));
			parent[id] = p.id;
			visited[p.row][p.col + 1] = true;

			step_counter++;
			cout << endl << "current exploration step = " << step_counter << endl << endl;

			if (verbose_output) {
				if (grid[p.row][p.col + 1] != 'G')
					grid[p.row][p.col + 1] = '*';
				show_map(grid);
			}
		}

		// moving left 
		if (p.col - 1 >= 0 &&
			visited[p.row][p.col - 1] == false) {
			int id = p.row + ROW_SIZE * (p.col - 1);
			q.push(QItem(p.row, p.col - 1, id, p.dist + 1));
			parent[id] = p.id;
			visited[p.row][p.col - 1] = true;

			step_counter++;
			cout << endl << "current exploration step = " << step_counter << endl << endl;

			if (verbose_output) {
				if (grid[p.row][p.col - 1] != 'G')
					grid[p.row][p.col - 1] = '*';
				show_map(grid);
			}
		}

		// moving down 
		if (p.row + 1 < ROW_SIZE &&
			visited[p.row + 1][p.col] == false) {
			int id = (p.row + 1) + ROW_SIZE * p.col;
			q.push(QItem(p.row + 1, p.col, id, p.dist + 1));
			parent[id] = p.id;
			visited[p.row + 1][p.col] = true;

			step_counter++;
			cout << endl << "current exploration step = " << step_counter << endl << endl;

			if (verbose_output) {
				if (grid[p.row + 1][p.col] != 'G')
					grid[p.row + 1][p.col] = '*';
				show_map(grid);
			}
		}

		if (grid[p.row][p.col] == 'F') {
			grid[p.row][p.col] = 'E';

			show_map(grid);
		}

	}

	// In case this line is reached, then that means no route between start and goal. We mark that by min distance = -1
	return -1;
}

/********************************************************************************************************************************/
/********************************************     Dijkstra'a Algorithm     ******************************************************/
/********************************************************************************************************************************/
// Here is the real Dijkstra function 
int Dijkstra(char grid[ROW_SIZE][COL_SIZE], map<int, int> & parent, int & start_node_id, int & goal_node_id)
{
	// To keep track of visited QItems. Marking blocked cells as visited. By this we avoid extra check if cell is barrier or not
	// At the same time when we descover start or goal nodes we use their col and row indices to find ther ids (start_node_id and goal_node_id)
	bool visited[ROW_SIZE][COL_SIZE];
	int start_row; // start row
	int start_col; // start col
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COL_SIZE; j++)
		{
			if (grid[i][j] == '1') // if barrier
				visited[i][j] = true; // mark visited
			else
				visited[i][j] = false;

			// Finding start 
			if (grid[i][j] == 'S')
			{
				start_node_id = i + ROW_SIZE * j;
				start_row = i; // start node row
				start_col = j; // start node col
			}

			// Finding goal 
			if (grid[i][j] == 'G')
			{
				goal_node_id = i + ROW_SIZE * j;
			}
		}
	}

	// applying Dijkstra on matrix cells starting from start node
	// the following data structure (priority_queue) will provide you with automatic ascending sorting, i.e. from min to max, based on first element = cost from start
	// so based on that we only need to pick the head node as our frontier which will have the min cost from start node as Dijkstra's requires
	priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>  > pq;

	// push the start node in the pq
	pq.push( make_pair(cost[start_row][start_col],start_node_id ));
	visited[start_row][start_col] = true;
	while (!pq.empty()) {
		// read the next frontier node which is the head of the pq therefore it will have the min cost as required by Dijkstra
		pair<int, int> top = pq.top(); 
		int f_cost = top.first; // f_cost cost of the frontier (cost from start node to that frontier node)
		int f_id = top.second; // f_id is the current Fronteir
		pq.pop();

		// get row and col of the frontier
		int row = f_id % ROW_SIZE; // frontier row
		int col = (f_id - row) / ROW_SIZE; // frontier col

		//  goal found; 
		if (grid[row][col] == 'G') {
			return f_cost; // break the loop and return the cost from start node (this is also the min cost to reach that goal)
		}

		if (verbose_output && grid[row][col] != 'S') {
			grid[row][col] = 'F';

			show_map(grid);
		}

		// moving up 
		if (row - 1 >= 0 &&
			visited[row - 1][col] == false) {
			int id = (row - 1) + ROW_SIZE * col;
			pq.push(make_pair(f_cost + cost[row - 1][col], id));
			parent[id] = f_id;
			visited[row - 1][col] = true;

			step_counter++;
			cout << endl << "current exploration step = " << step_counter << endl << endl;

			if (verbose_output) {
				if (grid[row - 1][col] != 'G')
					grid[row - 1][col] = '*';
				show_map(grid);
			}
		}

		// moving right 
		if (col + 1 < COL_SIZE &&
			visited[row][col + 1] == false) {
			int id = row + ROW_SIZE * (col + 1);
			pq.push(make_pair(f_cost + cost[row][col + 1], id));
			parent[id] = f_id;
			visited[row][col + 1] = true;

			step_counter++;
			cout << endl << "current exploration step = " << step_counter << endl << endl;

			if (verbose_output) {
				if (grid[row][col + 1] != 'G')
					grid[row][col + 1] = '*';
				show_map(grid);
			}
		}

		// moving left 
		if (col - 1 >= 0 &&
			visited[row][col - 1] == false) {
			int id = row + ROW_SIZE * (col - 1);
			pq.push(make_pair(f_cost + cost[row][col - 1], id));
			parent[id] = f_id;
			visited[row][col - 1] = true;

			step_counter++;
			cout << endl << "current exploration step = " << step_counter << endl << endl;

			if (verbose_output) {
				if (grid[row][col - 1] != 'G')
					grid[row][col - 1] = '*';
				show_map(grid);
			}
		}

		// moving down 
		if (row + 1 < ROW_SIZE &&
			visited[row + 1][col] == false) {
			int id = (row + 1) + ROW_SIZE * col;
			pq.push(make_pair(f_cost + cost[row + 1][col], id));
			parent[id] = f_id;
			visited[row + 1][col] = true;

			step_counter++;
			cout << endl << "current exploration step = " << step_counter << endl << endl;

			if (verbose_output) {
				if (grid[row + 1][col] != 'G')
					grid[row + 1][col] = '*';
				show_map(grid);
			}
		}

		if (grid[row][col] == 'F') {
			grid[row][col] = 'E';

			show_map(grid);
		}

	}

	// In case this line is reached, then that means no route between start and goal. 
	return -1;
}


// main function  
int main()
{
	int start_node_id, goal_node_id;
	char input_map[ROW_SIZE][COL_SIZE];

	// copy grid map into input_map 
	memcpy(input_map, grid, sizeof(grid));

	// create parent array where parent[i][j] = parent of node [i][j]
	map<int, int> parent;
	initialize_parents(ROW_SIZE*COL_SIZE, parent);

#ifndef Dijkstra_algo
	// explore the map to find shortest path using BFS
	int cost_BFS = 0;
	int min_dist = BFS(input_map, parent, start_node_id, goal_node_id);
	// if min_dist > 0, then the goal is reachable from the start node 

	if (min_dist > 0) {
		int parent_node = parent[goal_node_id];

		int row_current = goal_node_id % ROW_SIZE;
		int col_current = (goal_node_id - row_current) / ROW_SIZE;

		int row_parent, col_parent;
		row_parent = parent_node % ROW_SIZE;
		col_parent = (parent_node - row_parent) / ROW_SIZE;

		// show the route from start to goal
		cout << "Shortest Path: G <- ";

		while (parent_node != start_node_id) {
			cost_BFS += cost[row_parent][col_parent];

			cout << parent_node << " <- ";
#else // use Dijkstra algorithm
	// explore the map to find shortest path using Dijkstra
	int min_dist = Dijkstra(input_map, parent, start_node_id, goal_node_id);
	if (min_dist > -1) {
		cout << "min cost route to goal is " << min_dist << endl;
		int parent_node = parent[goal_node_id];

		int row_current = goal_node_id % ROW_SIZE;
		int col_current = (goal_node_id - row_current) / ROW_SIZE;

		int row_parent, col_parent;

		row_parent = parent_node % ROW_SIZE;
		col_parent = (parent_node - row_parent) / ROW_SIZE;

		cout << "Shortest Path: G <- ";

		while (parent_node != start_node_id) {
			// show the route from start to goal
			cout << parent_node << " <- ";
#endif 
		
			if (row_parent - row_current == -1) {
				input_map[row_parent][col_parent] = 'v';
			}
			else if (row_parent - row_current == 1) {
				input_map[row_parent][col_parent] = '^';
			}
			else if (col_parent - col_current == -1) {
				input_map[row_parent][col_parent] = '>';
			}
			else if (col_parent - col_current == 1) {
				input_map[row_parent][col_parent] = '<';
			}

			parent_node = parent[parent_node];
			row_current = row_parent;
			col_current = col_parent;

			row_parent = parent_node % ROW_SIZE;
			col_parent = (parent_node - row_parent) / ROW_SIZE;
		}
		cout << "S" << endl;

		// show map with marked shortest route 
		show_map(input_map);
	}
	else
		cout << "No Route from S to G" << endl;

#ifndef Dijkstra_algo
	if (min_dist > 0) {
		cout << endl << "cost route to goal is " << cost_BFS << endl;
	}
#endif
	return 0;
}