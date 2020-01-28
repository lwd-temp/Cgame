#include<windows.h>
#include<conio.h>
int T, root, c, i, j, k, map[250] = { 0 }, node[28][4] = {//形状&方向，输入&循环变量，ijk循环变量，地图，节点
	-1,0,1,-11,10,0,-10,-9,11,-1,0,1,9,10,0,-10, -1,0,1,-9,10,11,0,-10,9,-1,0,1,
	10,0,-10,-11, 9,10,0,1,11,0,1,-10,9,10,0,1,11,0,1,-10, 10,11,-1,0,10,0,1,-9,
	10,11,-1,0,10,0,1,-9,-1,0,1,-10,10,0,1,-10,10,-1,0,1,10,-1,0,-10,20,10,0,-10,
	-1,0,1,2,20,10,0,-10,-1,0,1,2,10,11,0,1,10,11,0,1,10,11,0,1,10,11,0,1	};
int move(int* v, int l) {//移动，如果新位置合理返回1，不合理返回0
	for (*v += l, i = 0; i < 4 && (j = (node[T][i] & 0x8000 ? 
		(node[T][i] - 2) % 10 + 2 : (node[T][i] + 2) % 10 - 2) + root % 10, 1); i++)//依次遍历四个节点，j为节点的横坐标
		if ((j < 0 || 9 < j || 249 < node[T][i] + root ||
			map[node[T][i] + root]) && (*v -= l, 1))return 0;//判断节点是否越界或有方块，是则复位
	return 1;
}
void down(){
	if (move(&root, 10))return;//向下移动1格，如果没触发碰撞则直接返回
	if (root / 10 < 2)exit(!_getch());//如果当前根纵坐标小于2，则判断结束
	for (i = 0; i < 4 && (map[node[T][i] + root] = 1); i++);//当前每个节点固定方块
	for (i = 240; i > 0 || (c = 0);) {//消行，从下依次往上
		for (k = 0, j = 0; j < 10; k += map[i + j++]);//累计当前行的方块数
		if (k != 10 && (i -= 10))continue;//如果不是全方块则跳到上面一行
		for (j = i + 9; j > 9; map[j] = map[j - 10], j--);//整体往下移，覆盖当前行实现消行
	}
}
int main(){
	srand((unsigned)malloc(!system("mode con: cols=20 lines=25")));//初始化随机数种子，修改窗口大小
	while (T = rand() % 7 * 4, (c = 1))//重置形状
		for (root = 14; c;down(), Sleep(150)) {//重置位置，下降，延迟
			if (_kbhit() && (c = _getch())) {//检测输入
				if (c == 'd' || c == 'D')(root % 10 - 9) && move(&root, 1);//向右
				else if (c == 'a' || c == 'A')root % 10 && move(&root, -1);//向左
				else if (c == 'w' || c == 'W')move(&T, (T % 4) < 3 ? 1 : -3);//旋转
				else if (c == 's' || c == 'S')while (down(), c);//直接下降到固定为止
			}
			for (system("cls"),i = 0; i < 4 && (map[node[T][i] + root] = -1); i++);//临时把4个节点赋值为-1,清屏
			for (i = 0; i < 250; i++)_cputs(map[i] ? "[]" : "  "), map[i] += map[i] < 0;//打印,4个节点复位
		}
}
