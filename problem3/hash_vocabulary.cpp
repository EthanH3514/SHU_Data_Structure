#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
//#define lowbit(x) ((x)&-(x))
unordered_map<string,vector<pair<int,int>>> mp;
vector<string> s;
int main() {
    ios::sync_with_stdio(false);
    ifstream inputFile("E:\\code\\C++\\in.txt");
    ofstream outputFile("E:\\code\\C++\\out.txt");
    if(!inputFile)
    {
        perror("Failed to open input file");
        return 1;
    }
    int n;
    inputFile>>n;
    for(int i=1;i<=n;i++)
    {
        string tmp;
        inputFile>>tmp;
        s.push_back(tmp);
    }
    string line;
    for(int row=1;getline(inputFile,line);row++)
    {
        int col=1;
        string word;
        for(int i=0;i<line.length();i++)
        {
            if(isalpha(line[i]))
            {
                word+=line[i];
            }
            else
            {
                mp[word].push_back({row,col});
                col++;
                word.clear();
            }
            if(i==line.length()-1)
                mp[word].push_back({row,col});
        }
        line.clear();
    }
    for(int i=0;i<n;i++)
    {
        outputFile<<"单词"<<s[i]<<"出现了"<<mp[s[i]].size()<<"次"<<'\t';
        for(int j=0;j<mp[s[i]].size();j++)
        {
            outputFile<<"第"<<mp[s[i]][j].first<<"行,第"<<mp[s[i]][j].second<<"列;";
        }
        outputFile<<'\n';
    }
    inputFile.close(),outputFile.close();
    return 0;
}