#include<graphics.h>
#include<time.h>
#include<vector>
#include<stdio.h>

using namespace std;

vector<vector <int> > pix(2);
int size=pix[0].size();
int factor,value,maze_num;
int x,y,maxx,maxy;
char ch,lasthit;

class Pixel
{
    public:
    int x,y;

    void randomplot()
    {
            srand (time(NULL));
            x=10+rand()%600;
            y=60+rand()%350;

            if(false)
            {
                up:
                x+=6;
                y+=6;
            }

            for(int i=x;i<x+6;i++)
                for(int j=y;j<y+6;j++)
                    if(getpixel(i,j)==WHITE)
                        goto up;
    }


    void drawdot(int color=YELLOW)
    {
        const int side=6;
        for(int i=0;i<side;i++)
            for(int j=0;j<side;j++)
                putpixel(x+i,y+j,color);
    }

    int snakehit()
    {
        if(pix[0][size-1]>=x&&pix[0][size-1]<x+6)
            if(pix[1][size-1]>=y&&pix[1][size-1]<y+6)
                return true;
        return false;
    }
};

void Initialize()
{
    int gd=DETECT,gmode;
    initgraph(&gd,&gmode,"");
    setbkcolor(BLACK);
}

void upper_boundary()
{
    setfillstyle(SOLID_FILL, BLUE);
    bar(0, 0, maxx, 50);
}

void display(int x,int y, char text[],int size=1,int box=BLUE,int txt=WHITE)
{
    setbkcolor(box);
    setcolor(txt);
    settextstyle(GOTHIC_FONT,HORIZ_DIR,size);
    outtextxy(x,y,text);
    setbkcolor(BLACK);
}

void init_line(int x,int &y)
{
    for(int i=0;i<10;i++)
        {
            putpixel(x,y-i,WHITE);
            pix[0].push_back(x);
            pix[1].push_back(y-i);
            size++;
        }
        y-=9;
}

void erase()
{
     pix[0].erase(pix[0].begin(),pix[0].begin()+1);
     pix[1].erase(pix[1].begin(),pix[1].begin()+1);
}

void draw()
{
     for(int i=0;i<size;i++)
        putpixel(pix[0][i],pix[1][i],WHITE);

}

void welcome_screen()
{
    display(70,140,"WELCOME TO SNAKE",4);
    display(80,210,"Press any key to begin...",3);
    display(80,310,"Credits :");
    display(200,310,"Safal Pandita",1,YELLOW,BLACK);
    display(200,340,"Pulkit Kariryaa",1,YELLOW,BLACK);
    display(200,370,"Aditya Kathuria",1,YELLOW,BLACK);

    getch();
    cleardevice();
}

void update_score(int value)
{
    char arr[5];
    sprintf(arr,"%d",value);
    display(5,5,"Score : ");
    display(100,5,arr);
}

void menu()
{
    display(5,5,"Score : ");
    display(170,5,"Pause : P");
    display(340,5,"Restart : R");
    display(510,5,"Quit : Q");
}

void end_screen()
{
    delay(800);
    cleardevice();
    update_score(value);
    display(80,180,"GAME OVER",6);
    display(100,270,"Press any key to exit....",4);
    display(180,350,"Press 'R' to play again",1,YELLOW,BLACK);
}

void initial_values()
{
    cleardevice();
    pix[0].clear();
    pix[1].clear();
    value=0;size=0,factor=0,ch='w',lasthit='w';
    maxx=getmaxx();
    maxy=getmaxy();
    x=maxx/2;
    y=maxy/2;
}

void check_boundary()
{
        if(x>maxx)x=0;
        else if(x<0)x=maxx;
        else if(y>maxy)y=50;
        else if(y<50)y=maxy;
}

void maze1()
{
    setcolor(WHITE);
    line(0,51,maxx,51);
    line(maxx,51,maxx,(maxy-51)/3);
    line(maxx,((maxy-51)*2)/3,maxx,maxy);
    line(maxx,maxy,0,maxy);
    line(0,maxy,0,((maxy-51)*2)/3);
    line(0,(maxy-51)/3,0,51);
    line(maxx/3,(maxy-51)/3,(maxx*2)/3,(maxy-51)/3);
    line(maxx/3,((maxy-51)*2)/3,(maxx*2)/3,((maxy-51)*2)/3);

}
void maze2()
{
    setcolor(WHITE);
    line(50,101,maxx-50,maxy-50);
    line(50,maxy-50,maxx-50,101);
}

void maze3()
{
    setcolor(WHITE);
    rectangle(0,51,maxx,maxy);
    rectangle(40,91,maxx-40,maxy-40);
    rectangle(80,111,maxx-80,maxy-80);
    rectangle(120,131,maxx-120,maxy-120);
    rectangle(160,151,maxx-160,maxy-160);
    setcolor(BLACK);
    int k;
    k=(maxy-40-91)/4;
    line(40,91+k,40,maxy-40-k);
    line(maxx-40,91+k,maxx-40,maxy-40-k);
    line(80,91+k,80,maxy-40-k);
    line(maxx-80,91+k,maxx-80,maxy-40-k);
    line(120,91+k,120,maxy-40-k);
    line(maxx-120,91+k,maxx-120,maxy-40-k);
    line(160,91+k,160,maxy-40-k);
    line(maxx-160,91+k,maxx-160,maxy-40-k);
}

void mazes (int number)
{
    if(number==49)return;
    else if (number==50)
        maze1();
    else if(number==51)
        maze2();
    else if(number==52)
        maze3();
    else return;
}

void select_maze()
{
    display(50,100,"Select any maze...",5);
    display(50,200,"1. No Maze ",3);
    display(50,240,"2. Easy Maze",3);
    display(50,280,"3. Medium Maze",3);
    display(50,320,"4. Hard Maze",3);
    display(70,390,"Use W,A,S,D to control the snake",2,YELLOW,BLACK);

    while(1)
    {
        maze_num=getch();
        if(maze_num>=49&&maze_num<=52)
            break;
    }
    cleardevice();
}

int main()
{
    Pixel p;
    Initialize();

    Start:

    initial_values();

    welcome_screen();
    select_maze();
    mazes(maze_num);

    upper_boundary();
    init_line(x,y);
    p.randomplot();
    p.drawdot();

    menu();
    update_score(0);

	while(1)
    {
        switch(ch)
        {
          case 'w':
                y--;
                break;

          case 's':
                y++;
                break;

          case 'a':
                x--;
                break;

          case 'd':
                x++;
                break;
        }

        check_boundary();

        if(getpixel(x,y)==WHITE)
        {
            end_screen();
            if(getch()=='r')
                goto Start;
            else
                break;
        }

        pix[0].push_back(x);
        pix[1].push_back(y);

        putpixel(x,y,WHITE);

        if(factor==0)
        {
            putpixel(pix[0][0],pix[1][0],BLACK);
            erase();
        }
        else
        {
            size++;
            factor--;
        }

        if(p.snakehit())
        {
            factor=15;
            p.drawdot(BLACK);
            draw();
            value+=10;
            update_score(value);
            p.randomplot();
            p.drawdot();
        }
        if (kbhit())
        {
            char temp;
            temp=getch();
            if(temp!=ch)
            {
                if((ch=='w'&&temp!='s')||(ch=='s'&&temp!='w')||(ch=='a'&&temp!='d')||(ch=='d'&&temp!='a'))
                {
                    if(temp=='w'||temp=='s'||temp=='a'||temp=='d')
                    {
                        lasthit=ch;
                        ch=temp;
                    }
                    else if(temp=='q')
                    {
                        end_screen();
                        if(getch()=='r')
                            goto Start;
                        else
                            break;
                    }
                    else if(temp=='p')
                    {
                        cleardevice();
                        display(maxx/2-90,maxy/2-55,"Paused...",5);
                        display(maxx/2-110,maxy/2-5,"Press any key to continue..",3);
                        getch();

                        cleardevice();
                        draw();
                        upper_boundary();
                        menu();
                        update_score(value);
                        mazes(maze_num);
                        p.drawdot();
                    }
                    else if(temp=='r')
                        goto Start;
                }
            }
        }
        delay(7);
    }

    return 0;
}

