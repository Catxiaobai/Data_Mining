#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<cctype>
#include<ctime>

using namespace std;
const int min_sup=400;
int Prin[6]={0,0,0,0,0,0};
struct HeadNode//表头项节点
{
    int Id;
    int Co;
    HeadNode()
    {
        Id=0;
        Co=0;
    }
    HeadNode(int I,int C)
    {
        Id=I;
        Co=C;
    }
};

struct FPtreeNode//FP-tree节点
{
    int Id;
    int Co;
    int Parent;//父节点
    FPtreeNode()
    {
        Id=0;
        Co=0;
        Parent=0;
    }
};

int Change(vector<int> v,int a)
{
    for(int i=0;i<v.size();i++)
    {
        if(a==v[i])
            return i;
    }
    return -1;
}

int Firitem(vector<int> &v)//寻找数据集中最大数
{
    ifstream infile("retail.dat");
	int temp=0;
    while(infile>>temp){
        v.push_back(temp);
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    infile.close();
    return v.size()+5;
}

int Cin(vector<vector<HeadNode> > &arr,vector<int> &a,vector<int> Fir)//读入二维数组，同时计算每一个项出现次数
{
    ifstream fin("retail.dat");
    int num;
    char p;
    vector<HeadNode> temp_line;
    HeadNode h=HeadNode();
    while (fin.get(p))
	{
		do
		{
			if (p == '\n')
			{
				arr.push_back(temp_line);
				temp_line.clear();
			}
		} while (isspace((int)p) && fin.get(p));
		if (!fin)
			break;
		fin.putback(p);  //将读取到的数据返回到输入流中，供下面的fin>>num可以继续读取数据
		fin >> num;
		a[num]++;
		h.Id=num;
		h.Co=1;
		temp_line.push_back(h);

	}
    cout<<"第一次扫描数据库完成"<<endl;
	fin.close();
	return 0;
}

int Simplify(vector<vector<HeadNode> > &arr,vector<int> a,vector<int> Fir)//将非频繁一项集的数移除数据库
{
    vector<vector<HeadNode> > sim;
    vector<HeadNode> temp;
    HeadNode h=HeadNode();
    for(int i=0;i<arr.size();i++)
    {
        for(int j=0;j<arr[i].size();j++)
        {
            int c=Change(Fir,arr[i][j].Id);
            if(a[c]>=min_sup)
            {
                h.Id=arr[i][j].Id;
                h.Co=arr[i][j].Co;
                temp.push_back(h);
            }
        }
        if(temp.size())
            sim.push_back(temp);
            temp.clear();
    }

    for(int i=0;i<sim.size();i++)
    {
        for(int m=0;m<sim[i].size();m++)
        {
            for(int n=0;n<sim[i].size()-m-1;n++)
            {
                int c1=Change(Fir,sim[i][n].Id);
                int c2=Change(Fir,sim[i][n+1].Id);
                if(a[c1]<a[c2])
                {
                    HeadNode temp;
                    temp.Id=sim[i][n].Id;
                    temp.Co=sim[i][n].Co;
                    sim[i][n].Id=sim[i][n+1].Id;
                    sim[i][n].Co=sim[i][n+1].Co;
                    sim[i][n+1].Id=temp.Id;
                    sim[i][n+1].Co=temp.Co;
                }
            }
        }
    }
    arr=sim;
    return 0;
}
int Simplify(vector<vector<HeadNode> > &arr,vector<int> a)//将非频繁一项集的数移除数据库
{
    vector<vector<HeadNode> > sim;
    vector<HeadNode> temp;
    HeadNode h=HeadNode();
    for(int i=0;i<arr.size();i++)
    {
        for(int j=0;j<arr[i].size();j++)
        {
            int c=arr[i][j].Id;
            if(a[c]>=min_sup)
            {
                h.Id=arr[i][j].Id;
                h.Co=arr[i][j].Co;
                temp.push_back(h);
            }
        }
        if(temp.size())
            sim.push_back(temp);
            temp.clear();
    }
    for(int i=0;i<sim.size();i++)
    {
        for(int m=0;m<sim[i].size();m++)
        {
            for(int n=0;n<sim[i].size()-m-1;n++)
            {
                int c1=sim[i][n].Id;
                int c2=sim[i][n+1].Id;
                if(a[c1]<a[c2])
                {
                    HeadNode temp;
                    temp.Id=sim[i][n].Id;
                    temp.Co=sim[i][n].Co;
                    sim[i][n].Id=sim[i][n+1].Id;
                    sim[i][n].Co=sim[i][n+1].Co;
                    sim[i][n+1].Id=temp.Id;
                    sim[i][n+1].Co=temp.Co;
                }
            }
        }
    }
    arr=sim;
    return 0;
}
vector<HeadNode> BuildHead(vector<int> a,vector<int> Fir)//准备
{
    vector<HeadNode> Head;
    Head.clear();
    HeadNode temp=HeadNode();
    for(int i=0;i<Fir.size();i++)
    {
        if(a[i]>=min_sup)
        {
            temp.Id=Fir[i];
            temp.Co=a[i];
            Head.push_back(temp);
        }
    }
       for(int i=0;i<Head.size();i++)
    {
        for(int j=0;j<Head.size()-1-i;j++)
        {
            if(Head[j].Co<Head[j+1].Co)
            {
                HeadNode temp;
                temp.Id=Head[j].Id;
                temp.Co=Head[j].Co;
                Head[j].Id=Head[j+1].Id;
                Head[j].Co=Head[j+1].Co;
                Head[j+1].Id=temp.Id;
                Head[j+1].Co=temp.Co;
            }
        }
    }
    return Head;
}

int Change(vector<HeadNode> Head,int a)
{
    for(int i=0;i<Head.size();i++)
    {
        if(Head[i].Id==a)
            return i;
    }
    return -1;
}

vector<FPtreeNode> CreateTree(vector<vector<HeadNode> > arr,vector<HeadNode> Head)
{
    vector<FPtreeNode> FPtree;
    FPtree.clear();
    FPtreeNode temp=FPtreeNode();
    FPtree.push_back(temp);
    vector<vector<int> > Tree(arr.size()*5);
    for (int i=0;i<Tree.size();i++)
    Tree[i].resize(Head.size());
    int Count=1;//记录FP树的节点树
    for(int i=0;i<arr.size();i++)
    {
        int u=0;//根节点
        //cout<<i<<endl;
        for(int j=0;j<arr[i].size();j++)
        {
            int c=Change(Head,arr[i][j].Id);
            if(Tree[u][c]==0)
            {
                FPtreeNode temp=FPtreeNode();
                temp.Id=arr[i][j].Id;
                temp.Co=arr[i][j].Co;
                temp.Parent=u;
                FPtree.push_back(temp);
                Tree[u][c]=Count;
                Count++;
            }
            else
            {
                FPtree[Tree[u][c]].Co+=arr[i][j].Co;
            }
            u=Tree[u][c];
        }
    }
    return FPtree;
}
void FPGrowth(vector<FPtreeNode> FPTree,HeadNode H,vector<HeadNode> &Result)
{
    HeadNode t0=HeadNode();
    vector<vector<HeadNode> > t;//数据库
    vector<HeadNode> t1;
    vector<int> t3;
    for(int i=0;i<FPTree.size();i++)
    {
        if(H.Id==FPTree[i].Id&&FPTree[i].Parent!=0)
        {
            for(int j=FPTree[i].Parent;j!=0;j=FPTree[j].Parent)
            {
                t0.Id=FPTree[j].Id;
                t0.Co=FPTree[i].Co;
                t1.push_back(t0);
            }
            t.push_back(t1);
            t1.clear();
        }
    }
    if(t.size()==0)
    {
        if(Result.size()>1)
        Result.pop_back();
        return;
    }
    int Max=0,lo=0;
    for(int i=0;i<t.size();i++)
    {
        if(t[i].size()>Max)
        {
            Max=t[i].size();
            lo=i;
        }
    }
    if(t[lo].size()-1!=39)
    {
        t3.push_back(39);
        Max++;
    }
    for(int i=t[lo].size()-1;i>=0;i--)
    {
        t3.push_back(t[lo][i].Id);
    }
    vector<int> b(Max,0);
    for(int i=0;i<t.size();i++)
    {
        for(int j=0;j<t[i].size();j++)
        {
            int c=Change(t3,t[i][j].Id);
            if(c>=0)
            b[c]+=t[i][j].Co;
        }
    }
    vector<HeadNode> NewHead=BuildHead(b,t3);
    if(Result.size()==0){
        for(int i=0;i<NewHead.size();i++)
        {
            Prin[2]++;
            cout<<"{"<<NewHead[i].Id<<" "<<H.Id<<"}: "<<NewHead[i].Co<<endl;
        }
          Result.push_back(HeadNode(H.Id,H.Co));
    }
    else if(Result.size()>0){
        if(NewHead.size()>0){
        for(int i=0;i<NewHead.size();i++)
        {           cout<<"{";
            for(int i=0;i<Result.size();i++)
            {
                cout<<Result[i].Id<<" ";
            }
            cout<<NewHead[i].Id<<" "<<H.Id<<"}: "<<NewHead[i].Co<<endl;
            int qw=Result.size()+2;
            Prin[qw]++;
        }
        if(NewHead.size()>1)
            Result.push_back(HeadNode(H.Id,H.Co));
        }
    }
    if(NewHead.size()==1)
    {
        if(Result.size()>1)
        Result.pop_back();
        return;
    }
    else{
    Simplify(t,b,t3);
    vector<FPtreeNode> NewFPTree;
    NewFPTree=CreateTree(t,NewHead);
    if(NewFPTree.size()>1)
    {
        for(int i=NewHead.size()-1;i>=0;i--)
    {
        FPGrowth(NewFPTree,NewHead[i],Result);
    }
    }
    }
}
int main()
{

    int start=clock();
    vector<vector<HeadNode> > arr;//原始数据集
    vector<int> Fir;
    int Firlen=Firitem(Fir);//一项集可能的数目16469
    vector<int> a(Firlen);//记录原始数据集每一个项的出现次数
    Cin(arr,a,Fir);
    Simplify(arr,a);
    int Line=arr.size();//sim简化数据集共有多少项,即多少行
    vector<HeadNode> Head=BuildHead(a,Fir);//表头项
    int FirItem=Head.size();
    vector<FPtreeNode> FP=CreateTree(arr,Head);
    for(int i=Head.size()-1;i>=0;i--)
    {
        vector<HeadNode> Result;
        Result.clear();
        cout<<"{"<<Head[i].Id<<"}："<<Head[i].Co<<endl;
        Prin[1]++;
        FPGrowth(FP,Head[i],Result);
    }

    cout<<endl;
    for(int i=1;i<6;i++)
    {
        if(Prin[i]>0)
            cout<<i<<"项集个数："<<Prin[i]<<endl;
    }
    int sum=0;
    for(int i=1;i<6;i++)
    {
        sum+=Prin[i];
    }
    cout<<"总数："<<sum<<endl;
    cout<<"最小支持度为："<<min_sup<<"时寻找频繁项集用时："<<double(clock()-start)/CLOCKS_PER_SEC<<endl;
    return 0;
}
