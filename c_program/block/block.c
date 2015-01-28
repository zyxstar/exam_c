#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include "block.h"
typedef struct itimerval LEVEL;
//一共多少个级别
static LEVEL level_00 = { {0,      0}, {0,      0} };
static LEVEL level_01 = { {1, 0}, {1,      0} };
static LEVEL level_02 = { {0, 500000}, {0, 500000} };
static LEVEL level_03 = { {0, 400000}, {0, 300000} };
static LEVEL level_04 = { {0, 300000}, {0, 300000} };
static LEVEL level_05 = { {0, 200000}, {0, 300000} };
static LEVEL level_06 = { {0, 150000}, {0, 300000} };
static LEVEL level_07 = { {0, 100000}, {0, 300000} };
static LEVEL level_08 = { {0, 80000}, {0, 300000} };
static LEVEL level_09 = { {0, 60000}, {0, 300000} };
char name[20];//存储的名字
int ch=0;//你玩游戏操作的按键(接受你的键盘按键)
int score=0;//分数
int level=1;//级别

//图形开始下落的初始化新坐标(随着下移这两个x,y不断变化中)
int x=11;
int y=3;

//图形移动前的老坐标(随着下移这两个x,y不断变化中) ==> a[save_y][save_x]
int save_x=10;//
int save_y=2;//save_y是代表的几行，所以为[][]的第一维

//通过num,mode来对图形进行变换
int num=0;
int mode=0;

int save_mode=0;//上一个图形的模式,第2维(因为在下落的时候，num肯定是不变的，都是一类的，你不可能通过通过变形按钮来改变整个num的类别)
		//加上这个的目的是，例如当你在落下的时候，进行变形了，那么相当与你的mode已经改变了，这样你再进行消除上一个无法找到了，因此这个需要进行保存)

int color=42;//初始化的颜色(随着图形的不同不断的变化)

//????下一次课需要问一下!!!
int row=0;
int col=0;

//在下面的程序中print_shape()函数中可以通过一个标识来判断是否擦除上一个图形
//例如如果落到底了，已经调用print_draw()相当于落实了，那么下一次图形下落的时候，就每必要再擦除第一个图形了，因此设置这个标识
int flag=0;

//目前整个游戏区域整体的坐标
int draw[Y][X] = { 0 };

//由于函数嵌套调用，因此这两个函数需要实现声明在这里
void print_score();
void e_shape();

//升级函数,其实就是改变整个闹钟信号timer的时间
void change_level(void)
{
	switch (level) {
	case 1:
		setitimer(ITIMER_REAL, &level_01, NULL);
		break;
	case 2:
		setitimer(ITIMER_REAL, &level_02, NULL);
		break;
	case 3:
		setitimer(ITIMER_REAL, &level_03, NULL);
		break;
	case 4:
		setitimer(ITIMER_REAL, &level_04, NULL);
		break;
	case 5:
		setitimer(ITIMER_REAL, &level_05, NULL);
		break;
	case 6:
		setitimer(ITIMER_REAL, &level_06, NULL);
		break;
	case 7:
		setitimer(ITIMER_REAL, &level_07, NULL);
		break;
	case 8:
		setitimer(ITIMER_REAL, &level_08, NULL);
		break;
	case 9:
		setitimer(ITIMER_REAL, &level_09, NULL);
		break;
	default:
		break;
	}
}

//消层的函数
void destroy(void)
{
	int i, j, full;
	int a, b, c;
	for (i = 0; i < Y; i++) {
		full = 1;
		for (j = 0; j < X; j++) {//通过draw数组找出当前的行中，通过这个X的循环，如果全都是0的话，那就已经满了
			if (draw[i][j] == 0) {
				full = 0;//这一行有一个为0,full就为0.
			}
		}
		//如果满了的话
		if (full == 1) {//那就首先开始进行数组的移位，也就是整体将draw数组整体下移
			for (a = 0; a < i; a++) {
				for (b = 0; b < X; b++) {
					draw[i - a][b] = draw[i - a - 1][b];	// 整体下移
				}
			}
			score=score+100;//加分
			level=score/100+1;//以100分为1级进行升级
			if(level>=9)//升级最大才到9
			{
				level=9;
			}
			change_level();//改变level级别，越来越快
			print_score();//打印分数
			print_draw();//最后根据你已经移动完的数组进行游戏区的全局刷新
		}
	}
}

//碰撞函数
//判断你的坐标下左右的每一个边沿是否与draw[][]
int end()
{

	int i, a = 0, b = 0;//a代表遍历到第几行，b代表列的位置
	for (i = 0; i < 16; i++) {
		if (i / 4 >= shape[num][mode][16] && i % 4 == 0) {//当遍历运转到当前第一个行首的时候，行需要加1，列需要归0
			a++;
			b = 0;
		}
		if (i / 4 >= shape[num][mode][16] && i % 4 >= shape[num][mode][17]) {//当遍历不是行首的时候，看看碰撞到啥
			if (shape[num][mode][i] == 0) {//如果是0的，没有碰撞
				b = b + 2;
			}
			if (shape[num][mode][i] == 1) {//如果当前图形中有格的话
				if (draw[a + y - 3][b + x - 3] != 0)	//首先和draw数组 ==>也就是与保存现有走过的数组不为0数组中的图形
								        //和你现在的图形冲突，那么你就不能下走了。
				{
					return 1;//一旦碰撞了，直接返回1
				} else
					b = b + 2;//否则继续逐个格进行遍历
			}
		}
	}
}

/*
int end(){
	return 0;
}
*/

void init()
{
	srand(time(NULL));//初始化，让图形变成随机图形，首先需要设置种子
	num=rand()%7;
	mode=rand()%4;
}

void print_draw(void)
{
	int i, j, n = 0;
	for (i = 0; i < Y; i++) {
		printf("\33[%d;3H", i + 2);
		for (j = 0; j < X; j++) {
			if (draw[i][j] != 0) {
				n = (n + 1) % 2;//每次[]成对出现，所以，通过%2得到1 或0,从而决定打[还是]
				fprintf(stdout, "\33[%dm", draw[i][j]);
			//	printf("1");
				(n == 1) ? printf("[") : printf("]");

			}
			if (draw[i][j] == 0) {
				fprintf(stdout, "\33[0m");
				printf(" ");//画两个空格
			}
		}
	}
}

//这个时候是图形已经向下碰撞到真正的图形了，首先是不能走了，其次这个时候应该保存当前的save_x,save_y再保存到当前的走过的draw数组中
//因此，这个函数是保存坐标
void store(void)
{
	int i, a = 0, b = 0;
	for (i = 0; i < 16; i++) {
		if (i / 4 >= shape[num][mode][16] && i % 4 == 0) {
			a++;
			b = 0;
		}
		if (i / 4 >= shape[num][mode][16] && i % 4 >= shape[num][mode][17]) {
			if (shape[num][mode][i] == 0) {//保存上次的图形，因为本次图形可能按了改变按钮，但图形落到最后，是不能改变形状的。
				b = b + 2;//是0就移动2个，因为是[]这是两位存储的。
			}
			if (shape[num][mode][i] == 1) {//为1是需要进行保存的
				draw[save_y + a -3][save_x + b -3] = color;//是1,要保存两个坐标，［］是两位存储的。判断时多了一行，所以这里要-1;
				b++;
				draw[save_y + a -3][save_x + b -3] = color;//再存一个坐标。
				b++;
			}
		}
	}

}
void scan_key(void)
{
	int flag = 1;
	struct termios old,new;
	int ch;

	//首先先关回显，没有回显没法玩，这部分是屏蔽掉普通的按键输入
	tcgetattr(0,&old);
	tcgetattr(0,&new);

	new.c_lflag = new.c_lflag & ~(ICANON |ECHO);
	new.c_cc[VTIME] = 0;
	new.c_cc[VMIN] = 1;

	tcsetattr(0, TCSANOW ,&new);


		//思考这里这里下落为什么用到信号，用while循环可以做吗?
		//我们需要用到两个循环，一个是循环接受你的输入，对方块位置和图形进行控制，第二个循环是需要按时将图形下落
		//因此，定时下落最好方式就是用信号，而第一个循环就是你不想让你的图形发生变化，因为你的输入可能停止，这个循环就相当与阻塞了
		//因此，这肯定是两个循环来做，因此主循环这里可以用键盘输入阻塞，副循环可以使用定时器一类的东东，这里正好就可以用到信号代替就行了
		while (flag) {


			ch = getchar();

			if (ch == '\33') {
				ch = getchar();
				if (ch == '[') {
					ch = getchar();
					switch (ch) {
					case 'A':
						change_shape();
						break;
					case 'B':
						move_down();
						int i;
						for (i = 0; i < X; i++) {
						if (draw[3][i] != 0) {//最顶一行横坐标为1,这一行只要有一个不为0,程序结束。
							flag=0;
							break;
						}
						}
						break;
					case 'C':
						move_right();
						break;
					case 'D':
						move_left();
						break;
					}
				}
				//                        continue;
			}

			if (ch == 'q' || ch == 'Q') {
				flag = 0;
			}

		}

		tcsetattr(0, TCSANOW ,&old);

}

//变形函数
void change_shape()
{
	if((x+col==27 && row>col)|| (y+row==26 && row<col))//?算法还需要研究一下，但是这句话的意思是当区域位置不能变形
							   //例如，你来一个棍，只有三个空间，你怎么变形都还保持原样，也就在这里还是print_shape();
	{
		print_shape();//这一行注释掉了，相当与变形没有任何的约束
	}
	else
	{
		//变形的mode发生变化
		int mode_save=mode;
		mode++;
		if(mode==4)
		{
		mode=0;
		}

		//当变形之后发生碰撞了，那么就还是不能变形，使用上一个的情况进行赋值
		if(end()==1)
		{

		   mode=mode_save;
		}

		//变形最后的打印，因为mode都已经记录下来了，因此最终打印一把就行了
		print_shape();
	}
}

//向下移动函数
void move_down()
{
	y++;//首先让坐标向下移动一位

	if(y+row<=26)//在游戏区中正常进行，调用print_shape函数打印当前图形，并消除掉
	{
		print_shape();
	}
	else//这个判断条件就是这个时候，已经无障碍下到最下底的了，那么这里相当与碰撞到最底下了，也就是最终的条件了
	{
		y--;//坐标往上移动一位把
		print_shape();//打印一次图形(实际上这一次打不打都无关紧要了，因为print_draw()马上要将store()存入的draw数组挨个进行打印)
                store();//这个时候由于已经到最底下了，这个已经可以放到全局的draw[][]数组中了
		//到这个时候,游戏区这一次图块下块阶段，告一段落了
		print_draw();//这个时候，将draw数组中的值逐个进行打印，相当于全部

		//下面这一段代码就是重置下一次开始下落方块的初始状态
		x=11;//初始位置，为3行11列开始往下落
		y=3;
		num=rand()%7;//num,mode就是下落的图形进行随机的匹配
		mode=rand()%4;
		color=color+1;//color颜色每一次都+1，都变一个颜色，
		if(color>46)//一直到46，再从41开始来
		{
			color=41;
		}
		flag=1;//flag非0的话，就是在print_shape不要消除上一个图形，因为你的方块已经落实了，下一次还是就是进入上面的if(y+row<=26)的循环了
		       //这个是一个连续的过程，因此这个地方应该将flag设置成1，然后下一次执行过print_shape后，自动在最后将flag置成了0
		//print_shape();//这句话可以省略掉，因为你前面已经print_draw()过了，相当与已经将整个游戏区刷新一遍了，
				//没有必要再进行打印图形了，你加上这句话，也是将前面的图形给覆盖掉
		return;

	}

	//与draw数组发生碰准了，进入到这个判断中说明在下落的过程中，碰到了其它的方块了
	if(end()==1)
	{
		//下面这段代码和上面是一模一样的，这里就不再缀余数
		y--;
		print_shape();
                store();
		print_draw();
		x=11;
		y=3;
		num=rand()%7;
		mode=rand()%4;
		color=color+1;
		if(color>46)
		{
			color=41;
		}

		flag=1;
		//print_shape();
	}

	//如果执行到这里，那么相当与已经是发生与其它的块进行碰撞了，这个时候就可以考虑消层了
	destroy();//进行消层

}






//向左移动函数
void move_left()//和向右移动一样，这个函数就不做注释了
{

	x=x-2;
	if(end()==1)
	{
              x=x+2;
		print_shape();
	//	return;
	}
	if(x>=2)
	{
		print_shape();
	}
	else
	{
		x=x+2;
		print_shape();

	}
}

//向右移动
void move_right()
{
	x=x+2;
	if(end()==1)//如果与原来的draw[][]走过的数组碰撞了，相当与没有变化
	{
		x=x-2;//最开始的x=x+2,现在搞成x=x-2,当前坐标相当与没有发生变化
		print_shape();

	}
	if(x+col<=27)//如果没到游戏区的右边界，按照最开始的x=x+2来走，这个判断是正常的逻辑
	{
		print_shape();
	}
	else//当发现已经达到游戏区的右边界了，那么执行和碰撞一样的内容，x=x-2
	{
		x=x-2;
		print_shape();

	}
}

//打印图形
void print_shape()
{
	//消除原来的图形
	if(flag==0)
	{
		e_shape();//e_shape就是消除原来的图形的函数
	}

	//下面是打印整个的图形
	int j=0;
	int x1=0;
	int y1=0;
	int n=0;
	x1=x;
	printf("\33[%dm",color);
for (j = 0, n = 0; j < 16; j++)	//
	{			//
		if (j / 4 >= shape[num][mode][16] && j % 4 == 0)	//
		{		//
			y1 = y + n;	//从顶坐标向下移动4行
			printf("\33[%d;%dH", y1, x1);	//
			n++;
		}
		if (j / 4 >= shape[num][mode][16] && j % 4 >= shape[num][mode][17])	//
		{		//
			if (shape[num][mode][j] == 0)	//
			{	//
				printf("\33[2C");	//
			}
			if (shape[num][mode][j] == 1) {
				printf("[]");
			}
		}

		fflush(NULL);
	}
	save_x=x;//记录上一个图形位移的位置x
	save_y=y;//记录上一个图形位移的位置y
	save_mode=mode;//记录上一个图形的mode，用于当发生不能变形的时候，还得回到原来的形状，因此这里需要记录一下

	row=4-shape[num][mode][16];//???
	col=4-shape[num][mode][17];//???

	printf("\33[0m");

	fflush(NULL);
	flag=0;//注意将这个flag一定置0
}

//消除上一个图形位移的函数
void e_shape()
{
	int j=0;
	int x1=0;
	int y1=0;
	int n=0;
	x1=save_x;
	printf("\33[0m");
for (j = 0, n = 0; j < 16; j++)	//
	{			//
		if (j / 4 >= shape[num][save_mode][16] && j % 4 == 0)	//
		{		//
			y1 = save_y + n;	//从顶坐标向下移动4行
			printf("\33[%d;%dH", y1, x1);	//
			n++;
		}
		if (j / 4 >= shape[num][save_mode][16] && j % 4 >= shape[num][save_mode][17])	//
		{		//
			if (shape[num][save_mode][j] == 0)	//
			{	//
				printf("\33[2C");	//
			}
			if (shape[num][save_mode][j] == 1) {
				printf("  ");//和print_shape相比就是这个是不同的，每一个格[]占两个位置，所以这里需要改成两个空格
			}
		}

		fflush(NULL);
	}
	printf("\33[0m");
	fflush(NULL);
}

//打印初始化界面
void print_back()
{
	system("clear");//清屏
	int i=0;
	int j=0;
	for(i=0;i<28;i++)
	{
		for(j=0;j<50;j++)
		{
			if(back[i][j]=='=' || back[i][j]=='|')
			{
				printf("\33[42m");
			}
			if(back[i][j]=='[' || back[i][j]==']')
			{
				printf("\33[45m");
			}
			printf("%c",back[i][j]);
			printf("\33[0m");
		}
		printf("\n");

	}
	printf("\33[27;24H");
	scanf("%d",&ch);
	printf("\33[28;4H");
	printf("Input your name:");
	scanf("%s",name);
}

//打印清空界面(将上图的游戏区域进行清空)
void print_back1()
{
	system("clear");
	int i=0;
	int j=0;
	for(i=0;i<28;i++)
	{
		for(j=0;j<50;j++)
		{
			if(back1[i][j]=='=' || back1[i][j]=='|')
			{
				printf("\33[42m");
			}
			if(back1[i][j]=='[' || back1[i][j]==']')
			{
				printf("\33[45m");
			}
			printf("%c",back1[i][j]);
			printf("\33[0m");
		}
		printf("\n");
	}
	printf("\33[3;38H");
	printf("%s",name);
	printf("\33[5;40H");
	printf("%d",score);
	printf("\33[7;40H");
	printf("%d",level);
}

//在分数区域打印分数
 void print_score()
{

	printf("\33[5;40H");
	printf("%d",score);
	printf("\33[7;40H");
	printf("%d",level);
}


int main()
{
	init();
	print_back();
	print_back1();
	//思考这里为什么要用信号来做?因为主进程输入字符阻塞，这里我还不能等待
	signal(SIGALRM, move_down);
        setitimer(ITIMER_REAL, &level_01, NULL);
	//

        scan_key();
	/*int i=0;
	for(i=0;i<15;i++)
	{
		sleep(1);
		 print_shape();
		 y++;
	}*/

	return 0;
}
