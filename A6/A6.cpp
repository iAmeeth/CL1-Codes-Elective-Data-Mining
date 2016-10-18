#include<iostream>
#include<vector>
#include<math.h>
#include<fstream>
#include <sstream>
using namespace std;

int main()
{
ifstream inData("ip.csv");
char delim;
ofstream out;
cout<<"KMEANS\n";
int n,k;
cout<<"Enter total number of coordinates\n";
cin>>n;
double x[n];
double y[n];

for(int i=0;i<n;i++)
{
inData>>x[i]>>delim>>y[i];
}
/*
for(int i=0;i<n;i++)
{
cout<<"Enter X-Coordinate\n";
cin>>x[i];
cout<<"Enter Y-Coordinate\n";
cin>>y[i];
cout<<"------------------------------\n";
}*/




cout<<"Entered Co-ordinates are:\n";
for(int i=0;i<n;i++)
{
cout<<"X-Coordinate\t"<<x[i];
cout<<"Y-Coordinate\t"<<y[i];
}


cout<<"\nEnter k value for number of clusters\n";
cin>>k;

vector<double> *mean;
mean = new vector<double>[2];
////CHANGED TO INT
int tempx,tempy;
cout<<"Enter initial seeds\n";
for(int i=0;i<k;i++)
{
cout<<"Enter X-Coordinate\n";
cin>>tempx;
mean[0].push_back(tempx);
cout<<"Enter Y-Coordinate\n";
cin>>tempy;
mean[1].push_back(tempy);
cout<<"------------------------------\n";
}

vector<double> *omean;
omean = new vector<double>[2];

vector<int> *cluster;
cluster = new vector<int>[n];

while(1)
{
//Copy new mean values to old mean vector
for(int i=0;i<2;i++)
{
omean[i]=mean[i];
}

//Clear cluster
////Changed n to k
for(int i=0;i<k;i++)
{
cluster[i].erase(cluster[i].begin(),cluster[i].end());
}
//Find Distance and find minimum value
for(int i=0;i<n;i++)
{
	double min=99999;
	int place;
	for(int j=0;j<k;j++)
	{
		double dist = sqrt(  pow(  (x[i]-mean[0][j])   ,  2  )  +   pow(  (y[i]-mean[1][j])  ,2)    );
		if(dist<min)
		{
		min=dist;
		place=j;
		}
	}

cluster[place].push_back(i);
	
}


//Find mean values
for(int i=0;i<k;i++)
{
	double xsum=0;
	double ysum=0;
			for(int j=0;j<cluster[i].size();j++)
			{
				xsum+=x[cluster[i][j]];
				ysum+=y[cluster[i][j]];

			}
	mean[0][i]=xsum/cluster[i].size();
	mean[1][i]=ysum/cluster[i].size();
	
}



//Check for termination


if(omean[0]==mean[0] && omean[1]==mean[1])
{
break;
}


}

out.open("op.csv");
	for(int i=0;i<k;i++)
	{
		out<<"Cluster "<<i+1<<endl;
		out<<"Mean of cluster\n";
		out<<mean[0][i]<<","<<mean[1][i]<<endl;
		out<<"Cluster data\n";

		for(int j=0;j<cluster[i].size();j++)
		{
			int pos=cluster[i][j];		
			out<<x[pos]<<","<<y[pos]<<endl;
		}
		out<<endl;
			
		
	}

out.close();



return 0;
}
