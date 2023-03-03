#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
//#define lowbit(x) ((x)&-(x))
struct node
{
    string word;
    int row;
    int col;
    node(){};
    node(string w,int x,int y)
    {
        word=w;
        row=x;
        col=y;
    }
};
vector<string>words;
vector<node>article;
bool cmp(node a,node b)
{
    if(a.word<b.word)
        return true;
    else if(a.word>b.word)
        return false;
    else
    {
        if(a.row<b.row)
            return true;
        else if(a.row>b.row)
            return false;
        else
            return a.col<b.col;
    }
}
int binary_find(string s)
{
    int l=0,r=article.size()-1;
    while(l<r)
    {
        int mid=(l+r)>>1;
        if(article[mid].word<s)
        {
            l=mid+1;
        }
        else
            r=mid;
    }
    return r;
}
int main() {
    ios::sync_with_stdio(false);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        string tmp;
        cin>>tmp;
        words.push_back(tmp);
    }
    string line;
    for(int row=1;getline(cin,line);row++)
    {
        string word;
        int col=1;
        for(int i=0;i<line.length();i++)
        {
            if(isalpha(line[i]))
            {
                word+=line[i];
            }
            else
            {
                node tmp(word,row,col);
                article.push_back(tmp);
                col++;
                word.clear();
            }
            if(i==line.length()-1)
            {
                node tmp(word,row,col);
                article.push_back(tmp);
            }
        }
        line.clear();
    }
    sort(article.begin(),article.end(),cmp);
    for(int i=0;i<n;i++)
    {
        int pos=binary_find(words[i]);
        int beginning=pos,ending=pos;
        for(int j=pos;j>=0;j--)
        {
            if(article[j].word!=words[i])
            {
                beginning=j+1;
                break;
            }
        }
        for(int j=pos;j<article.size();j++)
        {
            if(article[j].word!=words[i])
            {
                ending=j-1;
                break;
            }
        }
        cout<<"单词"<<words[i]<<"出现了"<<max(ending-beginning+1,0)<<"次\t";
        for(int j=beginning;j<=ending;j++)
        {
            cout<<"第"<<article[j].row<<"行，第"<<article[j].col<<"列；";
        }
        cout<<'\n';
    }
    return 0;
}