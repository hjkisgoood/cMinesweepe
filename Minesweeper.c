#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ROW 24
#define MAX_COL 30
#define MAX_MINE 99

int rows, cols, mines, opcount; // 地雷区大小和地雷数量
char board[MAX_ROW][MAX_COL];   // 棋盘
int mine[MAX_ROW][MAX_COL];     // 地雷位置，1表示地雷，0表示空
int opened[MAX_ROW][MAX_COL];   // 棋盘是否被打开
int flagged[MAX_ROW][MAX_COL];  // 棋盘是否被标记，0无，1雷！，2不确定？

void init(int level);
// 根据游戏难度level初始化棋盘和地雷位置
// 如果是自定义难度，则需要读取行数、列数和地雷数量

int open(int row, int col);
// 打开指定位置的格子，返回该格子周围地雷的数量

void flag(int row, int col, int Flag); // 1为！，2为？
// 标记指定位置的格子为地雷或问题标记

void unflag(int row, int col);
// 取消指定位置的格子的标记

int chord(int row, int col);
// 对指定位置的格子进行双击操作，返回是否操作成功

int get_state();
// 返回当前游戏状态

void print_board();
// 打印当前棋盘状态

int main()
{
    int level;
    int test9;
    opcount = 0;
    scanf("%d", &level);

    init(level); // 初始化
    int row, col, op;
   
    /*for(int i =0;i<rows;i++){
    	for(int j=0;j<cols;j++){
    		printf("%d",mine[i][j]);
		}
		printf("\n");
	}*/
	
    while (get_state() == 0)
    {
    	//printf("操作室%d",opcount);

        scanf("%d%d%d", &op, &row, &col);
        switch (op)
        {
        case 1:
            open(row - 1, col - 1);

            break;
        case 2:
            flag(row-1, col-1, 2);
            break;
        case 3:
            flag(row-1, col-1, 3);
            break;
        case 4:
            unflag(row-1, col-1);
            break;
        case 9:
            chord(row-1, col-1);
            //test9 = chord(row-1, col-1);
            /*if (test9 == -4)
            {
                opcount++;
               // printf("Hit mine, you lose\n");
                //printf("%d %d\n", opcount, mines);
                //print_board();
                //getchar();
                
                //return 0;
            }*/
            break;
        default:
            break;
        }
        opcount++; // 操作数+1
        if (get_state ()== 0)
        {
            printf("Game in progress\n");
            printf("%d %d\n", opcount, mines);
            print_board();
        }
    }

    if (get_state() == 1)
    {
        printf("Game over, you win\n");
        
    }
    else if (get_state() == -1)
    {
        printf("Hit mine, you lose\n");
    }
    else
    {
    }
    printf("%d %d\n", opcount, mines);
    print_board();
    getchar();
    return 0;
}

void init(int level)
{
    int i, j, k;
    char c;

    // 根据游戏难度确定行数、列数和地雷数量
    switch (level)
    {
    case 1:
        rows = 9;
        cols = 9;
        mines = 10;
        break;
    case 2:
        rows = 16;
        cols = 16;
        mines = 40;
        break;
    case 3:
        rows = 16;
        cols = 30;
        mines = 99;
        break;
    case 4:
        
        scanf("%d %d %d", &rows, &cols, &mines);
        break;
    default:
        break;
    }

getchar();//吃掉第一个换行符
    // 初始化棋盘和地雷位置
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            scanf("%c", &c);
            board[i][j] = '.';
            mine[i][j] = 0;
            opened[i][j] = 0;
            if (c == '*')
            {
                mine[i][j] = 1;
            } // 读到雷给赋值1，后面把周围的1加起来就是雷的数目
            if (cols == j + 1)
            {
                getchar();
            } // 读到行最后字符吃一个换行
            
        }
        
    }
    //TEST
    //for(int i=0;i<rows;i++){
     //   for(int j=0;j<cols;j++){
    //        printf("%d",mine[i][j]);
     //   }
   //     printf("\n");
    //}
}

int open(int row, int col)
{
	//printf("test is good");
    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        // 检查行列数是否越界
        return -1;
    }
    if (opened[row][col]||flagged[row][col]==1)
    {
        // 如果这个格子已经被打开过，或者标记为雷返回-2表示无法打开或者标记为雷
        return -2;
    }
    opened[row][col] = 1; // 标记为已经打开
    if (mine[row][col] == 1)
    {
        // 如果这个格子是地雷，返回-4表示失败

        return -4;
    }
    int count = 0; // 统计周围地雷的数量
    
    if (row > 0 && col > 0 && mine[row - 1][col - 1] == 1)
    {
        count++;
    }
    if (row > 0 && mine[row - 1][col] == 1)
    {
        count++;
    }
    if (row > 0 && col < cols - 1 && mine[row - 1][col + 1] == 1)
    {
        count++;
    }
    if (col > 0 && mine[row][col - 1] == 1)
    {
        count++;
    }
    if (col < cols - 1 && mine[row][col + 1] == 1)
    {
        count++;
    }
    if (row < rows - 1 && col > 0 && mine[row + 1][col - 1] == 1)
    {
        count++;
    }
    if (row < rows - 1 && mine[row + 1][col] == 1)
    {
        count++;
    }
    if (row < rows - 1 && col < cols - 1 && mine[row + 1][col + 1] == 1)
    {
        count++; 
    }
    if (count == 0&&mine[row][col]==0)
    {
        // 如果周围没有地雷，递归打开周围的格子
        open(row - 1, col - 1);
        open(row - 1, col);
        open(row - 1, col + 1);
        open(row, col - 1);
        open(row, col + 1);
        open(row + 1, col - 1);
        open(row + 1, col);
        open(row + 1, col + 1);
    }
    board[row][col] = count + '0'; // 给board赋字符型值
    return count;
}

int get_state()
{ // 游戏状态
    int i, j, count = 0;
    bool win = true;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (opened[i][j] == 0)
            {
                if (mine[i][j] == 0)
                {
                    win = false;
                }
            }
            else if (mine[i][j] == 1)
            {
                return -1;
            }
        }
    }
    if (win)
    {
        return 1;
    }
    return 0;
}
void flag(int row, int col, int Flag)
{
    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        // 检查行列数是否越界
        return;
    }
    if (opened[row][col])
    {
        // 如果这个格子已经被打开过，不能标记
        return;
    }
    if (flagged[row][col] == 0)
    {
        // 如果这个格子没有被标记
        if (Flag == 2)
        {
            flagged[row][col] = 1;
            board[row][col] = '!';
            mines--;
        }
        else
        {
            flagged[row][col] = 2;
            board[row][col] = '?';
        }
    }
    else if (flagged[row][col] == 1 && Flag == 3)
    {
        // 如果这个格子已经被标记为地雷标记，标记为问题标记
        flagged[row][col] = 2;
        board[row][col] = '?';
        mines++;
    }
    else if (flagged[row][col] == 2 && Flag == 2)
    {
        // 如果这个格子已经被标记为问题标记，标记为地雷
        flagged[row][col] = 1;
        board[row][col] = '!';
        mines--;
    }
}

void unflag(int row, int col)
{
    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        // 检查行列数是否越界
        return;
    }
    if (opened[row][col])
    {
        // 如果这个格子已经被打开过，不能取消标记
        return;
    }
    if (flagged[row][col] == 1)
    { // 如果是标记为雷则把雷数目加回去
        mines++;
    }
    flagged[row][col] = 0; // 取消标记
    board[row][col] = '.';
}

int chord(int row, int col)
{
    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        // 检查行列数是否越界
        return 0; 
    }
    if (!opened[row][col])
    {
        // 如果这个格子没有被打开过，返回0表示无法操作
        return 0;
    }

    int flag_count = 0; // 统计周围的标记数量
    for (int i = row - 1; i <= row + 1; i++)
    {
        for (int j = col - 1; j <= col + 1; j++)
        {
            if (i < 0 || i >= rows || j < 0 || j >= cols || (i == row && j == col))
            {
                // 如果超出边界或者是当前格子，则跳过
                continue;
            }
            if (opened[i][j]==0&&flagged[i][j] == 1)
            {
                // 如果是标记为地雷，则统计数量
                flag_count++;
            }
        }
    }
    

    if (flag_count == (board[row][col]-'0'))
    {
        // 如果周围的标记数量等于当前格子的地雷数量，则打开未打开的格子
       
        for (int i = row - 1; i <= row + 1; i++)//这个for循环查看双击是否点到雷
        {
            for (int j = col - 1; j <= col + 1; j++)
            {
                if (i < 0 || i >= rows || j < 0 || j >= cols || (i == row && j == col) || opened[i][j]||flagged[i][j]==1)
                {
                    // 如果超出边界或者是当前格子或者已经被打开过，则跳过
                    continue;
                }
                else if (mine[i][j]==1)
                {
                    open(i,j);
                    // 如果打开失败，则直接返回失败
                    return -1;
                }
                
            }
        }
        //打开周围8格
        
        for (int i = row - 1; i <= row + 1; i++)//如果没有点到雷那就正常双击
        {
            for (int j = col - 1; j <= col + 1; j++)
            {
                if (i < 0 || i >= rows || j < 0 || j >= cols || (i == row && j == col) || opened[i][j]||flagged[i][j]==1)
                {
                    // 如果超出边界或者是当前格子或者已经被打开过，则跳过
                    continue;
                }
                open(i, j);
              
            }
        }
        return 1; // 返回成功
    }
    else
    {
        return -3; // 返回表示操作失败
    }
}

void print_board()
{
    int flagOut = 0,flagSuc=0;
    // 游戏结束的打印
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (opened[i][j] == 1 && mine[i][j] == 1) // 打开的地雷表示游戏结束
            {
                flagOut = 1;
            }
            if(opened[i][j]==1&&mine[i][j]==0){
                flagSuc++;
            }
            if(mine[i][j]==1){
                flagSuc++;
            }
        }
    }

    if (flagOut == 1||flagSuc==rows*cols)
    { // 游戏结束的打印
    for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (opened[i][j] == 0)
                {
                    if(mine[i][j]==1){//如果是雷输出雷
                        printf("*");
                    }
                    // 如果不是雷且这个格子没有被打开
                    else if (flagged[i][j] == 0)
                    {
                        // 如果这个格子没有被标记
                        printf(".");
                    }
                    else if (flagged[i][j] == 1)
                    {
                        // 如果这个格子被标记为地雷
                        printf("!");
                    }
                    else if (flagged[i][j] == 2)
                    {
                        // 如果这个格子被标记为问号
                        printf("?");
                    }
                }
                else // 如果这个格子被打开了
                {
                    if(mine[i][j]==1){//如果这是点开爆炸的那个雷
                        printf("*");
                    }
                    else{
                         printf("%c", board[i][j]);
                    }
                   
                }
            }
            if(i==rows-1){
                
                //printf("");
                continue;
            }
            printf("\n");
        }
     //   printf("whatareyou doing");
        getchar();
        
       
    }
    else
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (opened[i][j] == 0)
                {
                    // 如果这个格子没有被打开
                    if (flagged[i][j] == 0)
                    {
                        // 如果这个格子没有被标记
                        printf(".");
                    }
                    else if (flagged[i][j] == 1)
                    {
                        // 如果这个格子被标记为地雷
                        printf("!");
                    }
                    else if (flagged[i][j] == 2)
                    {
                        // 如果这个格子被标记为问号
                        printf("?");
                    }
                }
                else // 如果这个格子被打开了
                {
                    printf("%c", board[i][j]);
                }
            }
            
            printf("\n");
        }
        
    }
}
