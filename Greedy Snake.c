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


// ��Ϸ������
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
            Sleep(Snake_speed);     //void sleep(int seconds),���� seconds ΪҪ��ͣ�ĺ�������
            if (!snakestatus())     //����ʱsnakestatus = 0
            {
                gotoxy(mapwide/2,maphigh/2);
                printf("GAME OVER!!!");
                getchar();
                break;
            }
        }
    }
}


// CMDͼ�ν�������
void WindowsInterface()
{
    system("color 87");
    system("title Greedy Snake V1.4");
    system("mode con:cols=120 lines=29");
}


// ��ʼ��
void Initialize()
{
	fruit.number = 0;
	Bigfruit.number = 0;
}


// ��궨λ
void gotoxy(int x,int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    //ȡ���
    COORD coord;    //���ù��
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(handle, coord); //��λ��handle������ڣ��ѹ���Ƶ�coord����
}


// ������Ϸ����
void drawmap()
{
    int i,k;

    //���Ƶ�ͼ
    for ( i = 0; i <= mapwide; i += 2)      //�������±߽�
    {
        gotoxy(i, 0);
        printf("��");
        gotoxy(i, maphigh);
        printf("��");
    }
    for ( i = 0; i <= maphigh; i++)         //�������ұ߽�
    {
        gotoxy(0,i);
        printf("��");
        gotoxy(mapwide,i);
        printf("��");
    }


    //������
    snake.len = Snake_lenth;
    snake.speed = Snake_speed;
    snake.x[0] = mapwide/2;
    snake.y[0] = maphigh/2;

    gotoxy(snake.x[0],snake.y[0]);          //��ͷ
    printf("��");
    for ( k = 1; k < snake.len; k++)        //����
    {
        snake.x[k] = snake.x[k - 1] + 2;
        snake.y[k] = snake.y[k - 1];
        gotoxy(snake.x[k],snake.y[k]);
        printf("��");
    }

    srand((unsigned int)time(NULL));        //�������ʳ��λ��
    while(1)
    {
        fruit.x = rand() % (mapwide - 4 ) + 1;       // + 1 �� * ��ռ���ַ��й�
        fruit.y = rand() % (maphigh - 2 ) + 1;
        if (fruit.x % 2 == 0)
            break;
    }
    gotoxy(fruit.x,fruit.y);
    printf("*");

    //�Ҳ��ע
    gotoxy(mapwide + 8, 6);
	printf(" W");
	gotoxy(mapwide + 6, 8);
	printf("A  S  D    ���п���");
    gotoxy(mapwide + 6, 12);
	printf("�� '�ո�' ����ͣ");
    gotoxy(mapwide + 6, 18);
	printf("Scores : %d",Scores);
}


// ˢ����Ϸ
void ClearGames()
{
    int i,k;
    system("cls");
    for ( i = 0; i <= mapwide; i += 2)      //���Ʊ߽�
    {
        gotoxy(i, 0);
        printf("��");
        gotoxy(i, maphigh);
        printf("��");
    }
    for ( i = 0; i <= maphigh; i++)
    {
        gotoxy(0,i);
        printf("��");
        gotoxy(mapwide,i);
        printf("��");
    }

    gotoxy(snake.x[0],snake.y[0]);          //������
    printf("��");
    for ( k = 1; k < snake.len; k++)
    {
        gotoxy(snake.x[k],snake.y[k]);
        printf("��");
    }

    gotoxy(fruit.x,fruit.y);                //���ƹ���
    printf("*");

    gotoxy(mapwide + 8, 6);                 //�����Ҳ���Ϣ
	printf(" W");
	gotoxy(mapwide + 6, 8);
	printf("A  S  D    ���п���");
    gotoxy(mapwide + 6, 12);
	printf("�� '�ո�' ����ͣ");
    gotoxy(mapwide + 6, 18);
	printf("Scores : %d",Scores);
}


// ���Ʋ˵�����
void drawmenu()
{
    int i;
    system("cls");
    for ( i = 0; i <= mapwide; i += 2)      //���Ʊ߽�
    {
        gotoxy(i, 0);
        printf("��");
        gotoxy(i, maphigh);
        printf("��");
    }
    for ( i = 0; i <= maphigh; i++)
    {
        gotoxy(0,i);
        printf("��");
        gotoxy(mapwide,i);
        printf("��");
    }

    gotoxy(mapwide + 9, 2);
    printf("Greedy Snake V1.4");
    gotoxy(mapwide + 8, 6);
	printf("�� W �� S ���п���.");
    gotoxy(mapwide + 9, 8);
    printf("�� �ո� ����ѡ��.");

    gotoxy(mapwide + 9, coodr);
    printf("->");
    gotoxy(mapwide + 13, coodr);
    printf("��ʼ��Ϸ");
    gotoxy(mapwide + 13, coodr + 3);
    printf("�汾��Ϣ");
    gotoxy(mapwide + 13, coodr + 6);
    printf("�˳���Ϸ");
}


// ˢ�²˵�
void ClearMenu()
{

    int i;
    system("cls");
    for ( i = 0; i <= mapwide; i += 2)      //���Ʊ߽�
    {
        gotoxy(i, 0);
        printf("��");
        gotoxy(i, maphigh);
        printf("��");
    }
    for ( i = 0; i <= maphigh; i++)
    {
        gotoxy(0,i);    
        printf("��");
        gotoxy(mapwide,i);
        printf("��");
    }

    gotoxy(mapwide + 9, 2);
    printf("Greedy Snake V1.4");
    gotoxy(mapwide + 8, 6);
	printf("�� W �� S ���п���.");
    gotoxy(mapwide + 9, 8);
    printf("�� �ո� ����ѡ��.");

    gotoxy(mapwide + 13, coodr);
    printf("��ʼ��Ϸ");
    gotoxy(mapwide + 13, coodr + 3);
    printf("�汾��Ϣ");
    gotoxy(mapwide + 13, coodr + 6);
    printf("�˳���Ϸ");
}


// �˵�����
void Menu()
{
    int i = 1, end = 3;
    int temp;

    drawmenu();         //���Ʋ˵�

    for (;;)            //������
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

            if(temp == ' ')         //�ո�ѡ��
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


// �����¹���
void creatfruit()
{
    if(snake.x[0] == fruit.x && snake.y[0] == fruit.y)        //���߳Ե�С����
    {
        // printf("\a");                       //������
        snake.len++;
        fruit.number++;
        Bigfruit.x = 0;            //��ֹ�����һֱ����(С���ӱ��Ե�ʱ�������ʧ)
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

            for (int k = 0; k < snake.len; k++)         //��ֹfruit������������
            {
                if (snake.x[k] == fruit.x && snake.y[k] == fruit.y)     //�ж��Ƿ���������
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

    if(snake.x[0] == Bigfruit.x && snake.y[0] == Bigfruit.y)        //���߳Դ����ʱ
    {
        // printf("\a");
        snake.len+=2;
        Bigfruit.number++;
        ClearGames();           //��ֹ���ӱ��Ե����Բ�������Ļ��
        Bigfruit.x = 0;
        Bigfruit.y = 0;
    }
}


// ���ɽ��������
void CreatBigFruit()
{
    int ret = 1;
    srand((unsigned)time(NULL));
        while(1)
        {
            Bigfruit.x = rand() % (mapwide- 8) + 2;
            Bigfruit.y = rand() % (maphigh- 4) + 2;

            for (int k = 0; k < snake.len; k++)         //��ֹfruit������������
            {
                if (snake.x[k] == Bigfruit.x && snake.y[k] == Bigfruit.y)     //�ж��Ƿ���������
                {
                    ret = 0;
                    break;
                }
            }

            if (ret == 1 && Bigfruit.x %2 ==0)break;
        }
    gotoxy(Bigfruit.x,Bigfruit.y);
    printf("��");
}


// ����ģ��
void control()
{
    int i,temp;
    if (_kbhit())           //kbhit������鵱ǰ�Ƿ��м������룬�����򷵻�һ����0ֵ�����򷵻�0
    {
        fflush(stdin);      //��ջ�����
        temp = _getch();
        if((temp == 'a' || temp == 'A') && (key !='D' && key !='d'))        //��ֹ����������ɱ
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

    gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);     //ɾȥ���һ��
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
    printf("��");
    gotoxy(mapwide + 2,0);          //���߹��
}


// �ж���������
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


// ����ϵͳ
void Score()
{
    Scores = fruit.number *fruitBonus + Bigfruit.number*BigfruitBonus;
    gotoxy(mapwide + 6, 18);
	printf("Scores : %d",Scores);
}


// �汾��Ϣ
void VertionInformation()
{
    ClearMenu();

    gotoxy(28,6);
    printf("\tGreedy Snake");
    gotoxy(28,9);
    printf("���ߣ���");
    gotoxy(28,12);
    printf("����ʱ�䣺2020.11.29");
    gotoxy(28,15);
    printf("�汾��V1.4");
    gotoxy(28,18);
    printf("�汾˵��: 1.���³�ʼ�˵�����");
    gotoxy(28,20);
    printf("\t      2.�޸���������һֱ���ڵ�BUG");

    getch();
}























/*
==============================================================
    ���ߣ�ɭ��Cci (223467140@qq.com)
    ʱ�䣺2020.11.26
    �����GreedySnake
    �汾��V1.1
    �汾˵��:1.�����Ҳ�ע����
            2.���¿�����ͣ
            3.�޸�����50��fruit��ֹͣ��BUG
            
==============================================================
    ���ߣ�ɭ��Cci (223467140@qq.com)
    ʱ�䣺2020.11.26
    �����GreedySnake
    �汾��V1.2
    �汾˵��:1.���·���ϵͳ
            2.�޸��Ҳ���libgcc.dll�޷����д����BUG
            3.�Ż���Ϸ������������Ϸ������"�س�"���¿�ʼ

==============================================================
    ���ߣ�ɭ��Cci (223467140@qq.com)
    ʱ�䣺2020.11.27
    �����GreedySnake
    �汾��V1.3
    �汾˵��:1.���°� ���ո� ��ͣ��Ϸ
            2.���ӽ������ӣ�Bigfruit.

==============================================================
    ���ߣ�ɭ��Cci (223467140@qq.com)
    ʱ�䣺2020.11.29
    �����GreedySnake
    �汾��V1.4
    �汾˵��: 1.���³�ʼ�˵�����.
             2.�޸������һֱ���ڵ�BUG


==============================================================
*/










