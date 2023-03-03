#include<iostream>
#include<cstring>
using namespace std;
const int N=1e5+5;
struct node
{
    int id,prior,next;
}circle[N];         //静态双向链表
bool is_incircle[N];        //用于判断x是否在链表内
int length,tail;        //length记录链表长度，tail记录尾部
void init(int n)        //初始化
{
    tail=length=n;
    for(int i=1;i<=n;i++)
    {
        circle[i].id=i;
        circle[i].prior=i-1;
        circle[i].next=i+1;
    }
    circle[1].prior=n;
    circle[n].next=1;          //形成环形双向链表
    is_incircle[0]=false;
    memset(is_incircle+1,true,n);
    memset(is_incircle+1+n,false,sizeof(is_incircle+1+n));
}
int find_x(int x,int k)     //模拟x的寻找
{
    for(int i=1;i<=k;i++)
        x=circle[x].next;
    return x;
}
int find_y(int y,int m)     //模拟y的寻找
{
    for(int i=1;i<=m;i++)
        y=circle[y].prior;
    return y;
}
void insert(int x)          //插入函数，传入要插入的位置
{
    int p=circle[x].prior,q=circle[x].next;
    while(!is_incircle[p])      //找到x前在链表内最近结点位置
        p=circle[p].prior;
    while(!is_incircle[q])      //找到x后在链表内最近结点位置
        q=circle[q].next;
    tail++,length++;
    circle[tail].id=tail;
    circle[tail].prior=p,circle[tail].next=q;
    circle[p].next=tail,circle[q].prior=tail;
    is_incircle[tail]=true;
}
void delete_node(int x)         //删除结点
{
    int p=circle[x].prior,q=circle[x].next;
    circle[p].next=q;
    circle[q].prior=p;
    length--;
    is_incircle[x]=false;
}
void solve_1(int n,int k,int m)
{
    int x=1,y=n;
    while(length)
    {
        x=find_x(x,k-1),y=find_y(y,m-1);
        if(x==y)
        {
            delete_node(x);
            cout<<x<<';';
        }
        else
        {
            delete_node(x),delete_node(y);
            cout<<x<<','<<y<<';';
        }
        while(!is_incircle[x]&&length)      //寻找x的后继
            x=circle[x].next;
        while(!is_incircle[y]&&length)      //寻找y的前驱
            y=circle[y].prior;
    }
}
void solve_2(int n,int k,int m)     //主要函数
{
    int x=1,y=n;
    int times=10;           //陷入循环后继续进行的次数
    while(length>1)
    {
        if(times==0)
            throw (int)6;       //次数耗尽，抛掷异常
        x=find_x(x,k-1),y=find_y(y,m-1);
        if(x==y)
        {
            if(k+m==length+1)       //出现死循环的标志
                times--;
            delete_node(x);
            cout<<x<<';';
            if(length==0)
                break;
            while(!is_incircle[y])
                y=circle[y].prior;
            insert(x);
        }
        else
        {
            delete_node(x),delete_node(y);
            cout<<x<<','<<y<<';';
            if(length==0)
                break;
            while(!is_incircle[y])
                y=circle[y].prior;
            insert(x);
        }
        x=tail;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cout<<"请输入n,k,m:"<<'\n';
    int n,k,m;
    cin>>n>>k>>m;
    init(n);
    cout<<"1.面试1\n"<<"2.面试2\n";
    int c;
    cin>>c;
    if(c==1)
        solve_1(n,k,m);
    else
    {
        try
        {
            solve_2(n,k,m);
        }
        catch(int hah)
        {
            if(hah==6)
                cout<<'\n'<<"初始数据在题意下进入死循环，程序中止"<<'\n';
        }
    }
    cout<<'\n';
    return 0;
}