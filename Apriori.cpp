#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<cctype>
#include<ctime>
using namespace std;
int sum=0;
void Cin(vector<vector<int> > &arr,vector<int> &a,vector<int> &b,int Firlen)//�����ά����
{
    ifstream fin("retail.dat");
    int num;
    char p;
    vector<int> temp_line;
    while (fin.get(p))
	{
		do
		{
			if (p == '\n')
			{
				arr.push_back(temp_line);
				if(temp_line.size()>1){
				for(int i=0;i<temp_line.size()-1;i++)
                {
                    for(int j=1;j<temp_line.size();j++)
                    {
                        b[(temp_line[i]*Firlen+temp_line[j])%79999]++;
                    }
                }
				}
				temp_line.clear();
			}
		} while (isspace((int)p) && fin.get(p));
		if (!fin)
			break;
		fin.putback(p);  //����ȡ�������ݷ��ص��������У��������fin>>num���Լ�����ȡ����
		fin >> num;
		a[num]++;
		temp_line.push_back(num);
	}
	fin.close();
}

void ShowData(vector<vector<int> > arr)//���ȫ������
{
    cout<<"��������"<<arr.size()<<endl;
    cout << "All the Data: " << endl;
    for (int i = 0; i < arr.size(); i++)
    {
        for(int j = 0; j < arr[i].size(); j++)
            cout << arr[i][j] << " ";
        cout << endl;
    }
}

int Firitem(vector<int> &v)
{
    ifstream infile("retail.dat");
	int temp=0;
    while(infile>>temp){
        v.push_back(temp);
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    infile.close();
    return v.back();
}

void ShowFir(vector<int> a,int Min_sup)//���һ�
{
    int Co=0;
    cout<<"-------1�--------"<<endl;
     for(int i=0;i<a.size();i++)
     {
         if(a[i]>=Min_sup)
        {
            Co++;
            cout<<"{ "<<i<<" }: "<<a[i]<<endl;
        }
     }
     cout<<"1�������"<<Co<<endl;
     sum+=Co;
}

void Com(vector<vector<int> > &Ck,vector<int> a,int Min_sup)
{
    vector<int> t;
    for(int i=0;i<a.size();i++)
    {
        t.clear();
        if(a[i]>=Min_sup)
        {
            t.push_back(i);
        }
        else continue;
        Ck.push_back(t);
    }
}

void Link(vector<vector<int> > &Ck,vector<int> b,int Firlen,int Min_sup)
{
    vector<int> t1;
    vector<vector<int> > t2;
    if(Ck[0].size()==1)//���ɶ��
    {
        for(int i=0;i<Ck.size()-1;i++)
        {
            for(int j=i+1;j<Ck.size();j++)
            {
                if(b[(Ck[i][0]*Firlen+Ck[j][0])%79999]>=Min_sup)
                {
                    t1.push_back(Ck[i][0]);
                t1.push_back(Ck[j][0]);
                t1.push_back(0);
                t2.push_back(t1);
                t1.clear();
                }
            }
        }
        Ck=t2;
    }
    //���ɶ��
    else
    {
        int t;
        for(int i=0;i<Ck.size()-1;i++)
        {
            for(int j=i+1;j<Ck.size();j++)
            {
                for(t=0;t<Ck[0].size()-1;t++)
                {
                    if(Ck[i][t]==Ck[j][t])
                    {
                        t1.push_back(Ck[i][t]);
                    }
                    else break;
                }
                if(t==Ck[0].size()-1)
                {
                    t1.push_back(Ck[i][Ck[0].size()-1]);
                    t1.push_back(Ck[j][Ck[0].size()-1]);
                    t1.push_back(0);
                    t2.push_back(t1);
                    t1.clear();
                }
                else{
                    t1.clear();
                }
            }
        }
    }
    //�޼�
    if(t2.size()!=0&&t2[0].size()>=4)
    {
        vector<vector<int> > t3;
        vector<int> temp;
        for(int i=0;i<t2.size();i++)
        {
            temp.clear();
            for(int j=1;j<t2[0].size()-1;j++)
            {
                temp.push_back(t2[i][j]);
            }
            for(int k=0;k<Ck.size();k++)
            {
                int n=0;
                while(Ck[k][n]==temp[n])
                {
                    n++;
                    if(n==temp.size())
                    {
                    for(int q=0;q<t2[0].size();q++)
                    t1.push_back(t2[i][q]);
                    t3.push_back(t1);
                    t1.clear();
                    break;
                    }
                }
                if(n==temp.size()) break;
            }
        }
            Ck=t3;
    }
    else Ck=t2;
}

void TraData(vector<vector<int> > arr,vector<vector<int> > &Ck)//����
{
    for(int i=0;i<arr.size();i++)
    {
        int m=0;
        while(m<Ck.size())
        {
            if(Ck[m][1]<=arr[i][arr[i].size()-1])
            {
            int n=0;
            for(int j=0;j<arr[i].size();j++)
            {
             if(Ck[m][n]<arr[i][j]) break;
            else if(arr[i][j]==Ck[m][n])
            {

                n++;
                if(n==Ck[m].size()-1)
                {
                    Ck[m][n]++;
                    break;
                }
            }
            }
            }
             m++;
    }
    }
}

void ShowItem(vector<vector<int> > Ck,int Min_sup)
{
    int Co=0;
    cout<<"-------"<<Ck[0].size()-1<<"�--------"<<endl;
     for(int i=0;i<Ck.size();i++)
    {
        if(Ck[i].back()>=Min_sup)
        {
            Co++;
            cout<<"{ ";
            for(int j=0;j<Ck[i].size()-1;j++)
            {
                cout<<Ck[i][j]<<" ";
            }
            cout<<"}: "<<Ck[i].back()<<endl;
        }
    }
    cout<<Ck[0].size()-1<<"�����: "<<Co<<endl;
    sum+=Co;
}

void Delete(vector<vector<int> > &Ck,int Min_sup)
{
    vector<int> t1;
    vector<vector<int> > t2;
    for(int i=0;i<Ck.size();i++)
    {
        if(Ck[i].back()>=Min_sup)
        {
            for(int j=0;j<Ck[i].size()-1;j++)
            {
                t1.push_back(Ck[i][j]);
            }
        }
        else continue;
        t2.push_back(t1);
        t1.clear();
    }
    Ck=t2;
}

int main()
{
	vector<vector<int> > arr;//�洢Data���Ķ�ά����
	vector<int> Fir;
	vector<vector<int> > Ck;//��ѡ�
	int Min_sup;
	int Firlen;
    Firlen=Firitem(Fir);
    vector<int> a(Firlen);
    vector<int> b(79999);
    //cout<<"��������88162"<<endl;
    cout<<"������С֧�ֶ�Min_sup��";
    cin>>Min_sup;
    int start=clock();
    Cin(arr,a,b,Firlen); //��ȡdat�ļ���������,�õ���ѡһ�C1,�õ���ϣ��H2
    cout<<"��һ��ɨ�����ݿ���ʱ��"<<double(clock()-start)/CLOCKS_PER_SEC<<endl;

    Com(Ck,a,Min_sup);
    //ShowData(arr);//���ȫ������
    ShowFir(a,Min_sup);//���һ�
    cout<<"һ���ʱ��"<<double(clock()-start)/CLOCKS_PER_SEC<<endl;
    while(Ck.size()>1)
    {
        Link(Ck,b,Firlen,Min_sup);//��ѡ�
        if(Ck.size()==0) break;
        TraData(arr,Ck);
        ShowItem(Ck,Min_sup);
        cout<<Ck[0].size()-1<<"���ʱ��"<<double(clock()-start)/CLOCKS_PER_SEC<<endl;
        Delete(Ck,Min_sup);
    }
    cout<<"������"<<sum<<endl;
    cout<<"��С֧�ֶ�Ϊ��"<<Min_sup<<"ʱѰ��Ƶ�����ʱ��"<<double(clock()-start)/CLOCKS_PER_SEC<<endl;
	return 0;
}
