#include<iostream>
#include<cstring>
using namespace std;
const int N=1e5+5;
struct node
{
    int id,prior,next;
}circle[N];         //��̬˫������
bool is_incircle[N];        //�����ж�x�Ƿ���������
int length,tail;        //length��¼�����ȣ�tail��¼β��
void init(int n)        //��ʼ��
{
    tail=length=n;
    for(int i=1;i<=n;i++)
    {
        circle[i].id=i;
        circle[i].prior=i-1;
        circle[i].next=i+1;
    }
    circle[1].prior=n;
    circle[n].next=1;          //�γɻ���˫������
    is_incircle[0]=false;
    memset(is_incircle+1,true,n);
    memset(is_incircle+1+n,false,sizeof(is_incircle+1+n));
}
int find_x(int x,int k)     //ģ��x��Ѱ��
{
    for(int i=1;i<=k;i++)
        x=circle[x].next;
    return x;
}
int find_y(int y,int m)     //ģ��y��Ѱ��
{
    for(int i=1;i<=m;i++)
        y=circle[y].prior;
    return y;
}
void insert(int x)          //���뺯��������Ҫ�����λ��
{
    int p=circle[x].prior,q=circle[x].next;
    while(!is_incircle[p])      //�ҵ�xǰ��������������λ��
        p=circle[p].prior;
    while(!is_incircle[q])      //�ҵ�x����������������λ��
        q=circle[q].next;
    tail++,length++;
    circle[tail].id=tail;
    circle[tail].prior=p,circle[tail].next=q;
    circle[p].next=tail,circle[q].prior=tail;
    is_incircle[tail]=true;
}
void delete_node(int x)         //ɾ�����
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
        while(!is_incircle[x]&&length)      //Ѱ��x�ĺ��
            x=circle[x].next;
        while(!is_incircle[y]&&length)      //Ѱ��y��ǰ��
            y=circle[y].prior;
    }
}
void solve_2(int n,int k,int m)     //��Ҫ����
{
    int x=1,y=n;
    int times=10;           //����ѭ����������еĴ���
    while(length>1)
    {
        if(times==0)
            throw (int)6;       //�����ľ��������쳣
        x=find_x(x,k-1),y=find_y(y,m-1);
        if(x==y)
        {
            if(k+m==length+1)       //������ѭ���ı�־
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
    cout<<"������n,k,m:"<<'\n';
    int n,k,m;
    cin>>n>>k>>m;
    init(n);
    cout<<"1.����1\n"<<"2.����2\n";
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
                cout<<'\n'<<"��ʼ�����������½�����ѭ����������ֹ"<<'\n';
        }
    }
    cout<<'\n';
    return 0;
}