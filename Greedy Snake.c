#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>
#include<time.h>
#define maphigh 28
#define mapwide 84

unsigned short Snake_size = 500, Snake_speed = 150, Snake_lenth = 3, key = 'w';
int Scores = 0, fruitBonus = 3, BigfruitBonus = 24, coodr = 12;
char vertion[15] = "V1.4";
struct fruit
{
    int number;
    int x;
    int y;
}fruit;
struct Bigfruit
{
    int number;
    int x;
    int y;
}Bigfruit;
struct snake
{
    int x[500];
    int y[500];
    int len;
    int speed;
}snake;

int snakestatus();
void Menu();
void Game();
void VertionInformation();
void WindowsInterface();
void gotoxy(int x,int y);
void drawmenu();
void drawmap();
void ClearMenu();
void ClearGames();
void control();
void Initialize();
void creatfruit();
void CreatBigFruit();
void Score();



int main()
{
    WindowsInterface();
    Menu();
    return 0;
}


// 游戏主程序
void Game()
{
    Initialize();
    for(;;)
    {
        system("cls");
        drawmap();
        getch();
        for(;;)
        {
            control();
            creatfruit();
            Score();
            Sleep(Snake_speed);     //void sleep(int seconds),参数 seconds 为要暂停的毫秒数。
            if (!snakestatus())     //死亡时snakestatus = 0
            {
                gotoxy(mapwide/2,maphigh/2);
                printf("GAME OVER!!!");
                getchar();
                break;
            }
        }
    }
}


// CMD图形界面设置
void WindowsInterface()
{
    system("color 87");
    system("title Greedy Snake V1.4");
    system("mode con:cols=120 lines=29");
}


// 初始化
void Initialize()
{
	fruit.number = 0;
	Bigfruit.number = 0;
}


// 光标定位
void gotoxy(int x,int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    //取句柄
    COORD coord;    //设置光标
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(handle, coord); //定位到handle这个窗口，把光标移到coord坐标
}


// 绘制游戏界面
void drawmap()
{
    int i,k;

    //绘制地图
    for ( i = 0; i <= mapwide; i += 2)      //绘制上下边界
    {
        gotoxy(i, 0);
        printf("█");
        gotoxy(i, maphigh);
        printf("█");
    }
    for ( i = 0; i <= maphigh; i++)         //绘制左右边界
    {
        gotoxy(0,i);
        printf("█");
        gotoxy(mapwide,i);
        printf("█");
    }


    //绘制蛇
    snake.len = Snake_lenth;
    snake.speed = Snake_speed;
    snake.x[0] = mapwide/2;
    snake.y[0] = maphigh/2;

    gotoxy(snake.x[0],snake.y[0]);          //蛇头
    printf("█");
    for ( k = 1; k < snake.len; k++)        //蛇身
    {
        snake.x[k] = snake.x[k - 1] + 2;
        snake.y[k] = snake.y[k - 1];
        gotoxy(snake.x[k],snake.y[k]);
        printf("█");
    }

    srand((unsigned int)time(NULL));        //随机生成食物位置
    while(1)
    {
        fruit.x = rand() % (mapwide - 4 ) + 1;       // + 1 与 * 所占的字符有关
        fruit.y = rand() % (maphigh - 2 ) + 1;
        if (fruit.x % 2 == 0)
            break;
    }
    gotoxy(fruit.x,fruit.y);
    printf("*");

    //右侧标注
    gotoxy(mapwide + 8, 6);
	printf(" W");
	gotoxy(mapwide + 6, 8);
	printf("A  S  D    进行控制");
    gotoxy(mapwide + 6, 12);
	printf("按 '空格' 以暂停");
    gotoxy(mapwide + 6, 18);
	printf("Scores : %d",Scores);
}


// 刷新游戏
void ClearGames()
{
    int i,k;
    system("cls");
    for ( i = 0; i <= mapwide; i += 2)      //绘制边界
    {
        gotoxy(i, 0);
        printf("█");
        gotoxy(i, maphigh);
        printf("█");
    }
    for ( i = 0; i <= maphigh; i++)
    {
        gotoxy(0,i);
        printf("█");
        gotoxy(mapwide,i);
        printf("█");
    }

    gotoxy(snake.x[0],snake.y[0]);          //绘制蛇
    printf("█");
    for ( k = 1; k < snake.len; k++)
    {
        gotoxy(snake.x[k],snake.y[k]);
        printf("█");
    }

    gotoxy(fruit.x,fruit.y);                //绘制果子
    printf("*");

    gotoxy(mapwide + 8, 6);                 //绘制右侧信息
	printf(" W");
	gotoxy(mapwide + 6, 8);
	printf("A  S  D    进行控制");
    gotoxy(mapwide + 6, 12);
	printf("按 '空格' 以暂停");
    gotoxy(mapwide + 6, 18);
	printf("Scores : %d",Scores);
}


// 绘制菜单界面
void drawmenu()
{
    int i;
    system("cls");
    for ( i = 0; i <= mapwide; i += 2)      //绘制边界
    {
        gotoxy(i, 0);
        printf("█");
        gotoxy(i, maphigh);
        printf("█");
    }
    for ( i = 0; i <= maphigh; i++)
    {
        gotoxy(0,i);
        printf("█");
        gotoxy(mapwide,i);
        printf("█");
    }

    gotoxy(mapwide + 9, 2);
    printf("Greedy Snake V1.4");
    gotoxy(mapwide + 8, 6);
	printf("按 W 或 S 进行控制.");
    gotoxy(mapwide + 9, 8);
    printf("按 空格 进行选择.");

    gotoxy(mapwide + 9, coodr);
    printf("->");
    gotoxy(mapwide + 13, coodr);
    printf("开始游戏");
    gotoxy(mapwide + 13, coodr + 3);
    printf("版本信息");
    gotoxy(mapwide + 13, coodr + 6);
    printf("退出游戏");
}


// 刷新菜单
void ClearMenu()
{

    int i;
    system("cls");
    for ( i = 0; i <= mapwide; i += 2)      //绘制边界
    {
        gotoxy(i, 0);
        printf("█");
        gotoxy(i, maphigh);
        printf("█");
    }
    for ( i = 0; i <= maphigh; i++)
    {
        gotoxy(0,i);    
        printf("█");
        gotoxy(mapwide,i);
        printf("█");
    }

    gotoxy(mapwide + 9, 2);
    printf("Greedy Snake V1.4");
    gotoxy(mapwide + 8, 6);
	printf("按 W 或 S 进行控制.");
    gotoxy(mapwide + 9, 8);
    printf("按 空格 进行选择.");

    gotoxy(mapwide + 13, coodr);
    printf("开始游戏");
    gotoxy(mapwide + 13, coodr + 3);
    printf("版本信息");
    gotoxy(mapwide + 13, coodr + 6);
    printf("退出游戏");
}


// 菜单控制
void Menu()
{
    int i = 1, end = 3;
    int temp;

    drawmenu();         //绘制菜单

    for (;;)            //光标控制
    {
        if (_kbhit())
        {
            fflush(stdin);
            temp = _getch();

            if(temp == 'w' || temp == 'W')
            {
                if(i>1 && i<= end)
                {
                    ClearMenu();
                    i--;
                    gotoxy(mapwide + 7,coodr + 3*(i-1));
                    printf("  ");
                    printf("->");

                }
            }
            if(temp == 's' || temp == 'S')
            {
                if(i>=1 && i< end)
                {
                    ClearMenu();
                    i++;
                    gotoxy(mapwide + 7,coodr + 3*(i-1));
                    printf("  ");
                    printf("->");
                }
            }

            if(temp == ' ')         //空格选择
            {
                break;
            }
        }
    }

    switch (i)
    {
    case 1:
        Game();
        break;
    
    case 2:
        VertionInformation();
        return Menu();

    case 3:
        exit(0);
    }
}


// 生成新果子
void creatfruit()
{
    if(snake.x[0] == fruit.x && snake.y[0] == fruit.y)        //当蛇吃掉小果子
    {
        // printf("\a");                       //蜂鸣声
        snake.len++;
        fruit.number++;
        Bigfruit.x = 0;            //防止大果子一直存在(小果子被吃掉时大果子消失)
        Bigfruit.y = 0;
        if(fruit.number %5 == 0)
        {
            CreatBigFruit();
        }
        srand((unsigned)time(NULL));
        while(1)
        {
            int tag = 1;
            fruit.x = rand() % (mapwide - 4 ) + 1;
            fruit.y = rand() % (maphigh - 2 ) + 1;

            for (int k = 0; k < snake.len; k++)         //防止fruit生成在蛇身上
            {
                if (snake.x[k] == fruit.x && snake.y[k] == fruit.y)     //判断是否在蛇身上
                {
                    tag = 0;
                    break;
                }
            }

            if (tag == 1 && fruit.x %2 ==0)break;
        }
    }
    gotoxy(fruit.x,fruit.y);
    printf("*");

    if(snake.x[0] == Bigfruit.x && snake.y[0] == Bigfruit.y)        //当蛇吃大果子时
    {
        // printf("\a");
        snake.len+=2;
        Bigfruit.number++;
        ClearGames();           //防止果子被吃掉后仍残留在屏幕上
        Bigfruit.x = 0;
        Bigfruit.y = 0;
    }
}


// 生成奖励大果子
void CreatBigFruit()
{
    int ret = 1;
    srand((unsigned)time(NULL));
        while(1)
        {
            Bigfruit.x = rand() % (mapwide- 8) + 2;
            Bigfruit.y = rand() % (maphigh- 4) + 2;

            for (int k = 0; k < snake.len; k++)         //防止fruit生成在蛇身上
            {
                if (snake.x[k] == Bigfruit.x && snake.y[k] == Bigfruit.y)     //判断是否在蛇身上
                {
                    ret = 0;
                    break;
                }
            }

            if (ret == 1 && Bigfruit.x %2 ==0)break;
        }
    gotoxy(Bigfruit.x,Bigfruit.y);
    printf("★");
}


// 控制模块
void control()
{
    int i,temp;
    if (_kbhit())           //kbhit函数检查当前是否有键盘输入，若有则返回一个非0值，否则返回0
    {
        fflush(stdin);      //清空缓冲区
        temp = _getch();
        if((temp == 'a' || temp == 'A') && (key !='D' && key !='d'))        //防止反方向导致自杀
        {
            key = temp;
        }
        if((temp == 'd' || temp == 'D') && (key !='a' && key !='A'))
        {
            key = temp;
        }
        if((temp == 'w' || temp == 'W') && (key !='S' && key !='s'))
        {
            key = temp;
        }
        if((temp == 's' || temp == 'S') && (key !='w' && key !='W'))
        {
            key = temp;
        }
        if((temp == ' '))
        {
            getch();
        }
    }

    gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);     //删去最后一节
    printf("  ");

    for ( i = snake.len-1 ; i>0 ; i-- )
    {
        snake.x[i] = snake.x[i-1];
        snake.y[i] = snake.y[i-1];
    }

    switch (key)
    {
        case 'w':
        case 'W':
            snake.y[0]--;
            break;

        case 's':
        case 'S':
            snake.y[0]++;
            break;

        case 'a':
        case 'A':
            snake.x[0]-=2;
            break;

        case 'd':
        case 'D':
            snake.x[0]+=2;
            break;
    }

    gotoxy(snake.x[0],snake.y[0]);
    printf("█");
    gotoxy(mapwide + 2,0);          //移走光标
}


// 判断死亡条件
int snakestatus()
{
    int ret;
    if ((snake.x[0] == 0 || snake.x[0] == mapwide) || (snake.y[0] == 0 || snake.y[0] == maphigh))
        return 0;
        
    for (int i = 1; i < snake.len; i++)
    {
        if(snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i])
            return 0;
    }
    return 1;
}


// 分数系统
void Score()
{
    Scores = fruit.number *fruitBonus + Bigfruit.number*BigfruitBonus;
    gotoxy(mapwide + 6, 18);
	printf("Scores : %d",Scores);
}


// 版本信息
void VertionInformation()
{
    ClearMenu();

    gotoxy(28,6);
    printf("\tGreedy Snake");
    gotoxy(28,9);
    printf("作者：北");
    gotoxy(28,12);
    printf("更新时间：2020.11.29");
    gotoxy(28,15);
    printf("版本：V1.4");
    gotoxy(28,18);
    printf("版本说明: 1.更新初始菜单界面");
    gotoxy(28,20);
    printf("\t      2.修复奖励果子一直存在的BUG");

    getch();
}























/*
==============================================================
    作者：森屿Cci (223467140@qq.com)
    时间：2020.11.26
    软件：GreedySnake
    版本：V1.1
    版本说明:1.更新右侧注释栏
            2.更新开局暂停
            3.修复吃满50个fruit就停止的BUG
            
==============================================================
    作者：森屿Cci (223467140@qq.com)
    时间：2020.11.26
    软件：GreedySnake
    版本：V1.2
    版本说明:1.更新分数系统
            2.修复找不到libgcc.dll无法运行代码的BUG
            3.优化游戏结束交互，游戏结束后按"回车"重新开始

==============================================================
    作者：森屿Cci (223467140@qq.com)
    时间：2020.11.27
    软件：GreedySnake
    版本：V1.3
    版本说明:1.更新按 ‘空格’ 暂停游戏
            2.增加奖励果子：Bigfruit.

==============================================================
    作者：森屿Cci (223467140@qq.com)
    时间：2020.11.29
    软件：GreedySnake
    版本：V1.4
    版本说明: 1.更新初始菜单界面.
             2.修复大果子一直存在的BUG


==============================================================
*/










