/**
 * @file EasyGeekBench.cpp 
 * @brief: EGB
 * @version:  0.1.0a
 * @copyright: Zerosoft Company
 * @author: Waterdrop142857
 * @date: 2023-06-26 13:31:03
 * 
 **/

#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>

using namespace std;

#define ld long double

#define Limit 800000000
#define R 10.0

ld f(ld x)
{
	return sqrt(R*R-x*x);
}

ld V=0;
long long Status=0,OldStatus=0;
long long ReadyCount=0;

ld Calc(ld l,ld r,long long lim,bool statistics)
{
	ld dx=(r-l)/lim;
	ld x=l;
	ld v;
	for(int i=0;i<lim;i++)
	{
		v=dx*f((x+x+dx)/2.0);
		x+=dx;
		V+=v;
		Status++;
		if((Status-OldStatus)==lim/10.0&&statistics)
		{
			char Text[1024];
			sprintf_s(Text,1024,"Finshed: %d %%\n",(int)(Status/(1.0*lim/100.0)));
			cout<<Text;
			OldStatus=Status;
		}
//		if(Status==Limit) break;
	}
	return V;
}

void About(){
	system("cls");
	cout<<"Made with CPP,build by GCC\n";
	cout<<"Developed by Waterdrop142857\n";
	cout<<"Copyright : Zerosoft Company\n";
	system("pause");
}

void SBM()
{
	system("cls");
	system("title EasyBenchMark - Single-thread Benchmark");
	cout<<"Preparing for work...\n";
	V=0;
	Status=0;
	OldStatus=0;
	cout<<"Start work\n";
	long long TickA=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	Calc(-R,R,Limit,1);
	long long TickB=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	long long Score=Limit/(TickB-TickA);
	cout<<"Your Score="<<Score<<endl;
	cout<<V*2.0<<endl;
	system("pause");
}

void ThreadWork(ld l,ld r,long long lim,int NowID,int CntThread)
{
	ReadyCount++;
	while(ReadyCount!=CntThread-1);
	Calc(l,r,lim,0);
}

void MBM()
{
	system("cls");
	system("title EasyBenchMark - Mutli-thread Benchmark");
	ReadyCount=0;V=0;
	Status=0;
	OldStatus=0;
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	int num=sysinfo.dwNumberOfProcessors;
	cout<<"Due to the poor technical skills of the developer, displaying progress is not supported when running multi-threaded benchmarks.\n";
	long long limOfThread=Limit/num;
	long long Fanwei=2*R/num;
	long long TickA=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	for(int i=1;i<num;i++)
	{
		thread a(ThreadWork,-R*1.0+Fanwei*(i-1)*1.0,-R*1.0+Fanwei*i*1.0,limOfThread,i,num);
		a.detach();
	}
	Calc(-R*1.0+Fanwei*(num-1)*1.0,R,Limit-limOfThread,0);
	long long TickB=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	long long Score=Limit/(TickB-TickA);
	cout<<"Your Score="<<Score<<endl;
	system("pause");
}

void CST()
{
	
}

int Menu()
{
	system("cls");
	system("title EasyBenchMark");
	cout<<"******************************\n"
		<<"*     EasyCPUGeekBench       *\n"
		<<"******************************\n"
		<<"*     1.SingleBenchMark      *\n"
		<<"*     2.MutliBenchMark       *\n"
		<<"*     3.CPUStabilityTest     *\n"
		<<"*         5.About            *\n"
		<<"*         0.Exit             *\n"
		<<"******************************\n"
	;
	char ch='a';
	while(ch<'0'||ch>'5')
	{
		ch=getch();
	}
	return (int)(ch-'0');
}

int main()
{
	
	bool flag=1;
	while(flag)
	{
		int choice=Menu();
		switch(choice)
		{
		case 1:
			SBM();
			break;
		case 2:
			MBM();
			break;
		case 3:
			
			break;
		case 4:
			
			break;
		case 5:
			About();
			break;
		case 0:
			flag=false;
			break;
		}
	}
	return 0;
}
