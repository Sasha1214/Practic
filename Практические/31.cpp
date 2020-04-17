#include <iostream>
#include <cctype>

using namespace std;
bool exitt = false; 

void lab( string* maze, int a, int b) {
	maze[a][b] = '*'; //помечаем где уже прошли

	if (isalpha(maze[a][b])) {
		exitt = true;
		cout << maze[a][b];
	}
	if (isalpha(maze[a-1][b])) {
		exitt = true;
		cout << maze[a-1][b];
	}
	if (isalpha(maze[a + 1][b])) {
		exitt = true;
		cout << maze[a + 1][b];
	}
	if (isalpha(maze[a][b-1])) {
		exitt = true;
		cout << maze[a][b-1];
	}
	if (isalpha(maze[a][b + 1])) {
		exitt = true;
		cout << maze[a][b + 1];
	}

	if (maze[a - 1][b] == ' ') {
		lab(maze, a - 1, b);
	}
	if (maze[a + 1][b] == ' ') {
		lab(maze, a + 1, b);
	}
	if (maze[a][b - 1] == ' ') {
		lab(maze, a, b - 1);
	}
	if (maze[a][b + 1] == ' ') {
		lab(maze, a, b + 1);
	}
}



int main()
{
	setlocale(LC_ALL, "rus");
	string maze[25] = {
	"####B######################",
	"# #       #   #      #    #",
	"# # # ###### #### ####### #",
	"# # # #       #   #       #",
	"#   # # ######### # ##### #",
	"# # # #   #       #     # #",
	"### ### ### ############# #",
	"# #   #     # #           #",
	"# # #   ####### ###########",
	"# # # #       # #         C",
	"# # ##### ### # # ####### #",
	"# # #     ### # #       # #",
	"#   ##### ### # ######### #",
	"######### ### #           #",
	"# ####### ### #############",
	"A           #   ###   #   #",
	"# ############# ### # # # #",
	"# ###       # # ### # # # #",
	"# ######### # # ### # # # F",
	"#       ### # #     # # # #",
	"# ######### # ##### # # # #",
	"# #######   #       #   # #",
	"# ####### ######### #######",
	"#         #########       #",
	"#######E############D######"
	};
	int a, b;
	cin >> a; //cтрока
	cin >> b; //столбец
	
	if (a > 24 || b > 26 || maze[b][a] == '#') {
		cout << "Error";
		return 0;
	}

	lab(maze, a, b);
	
	if (!exitt) {
		cout << "выхода нет";
	}
}
