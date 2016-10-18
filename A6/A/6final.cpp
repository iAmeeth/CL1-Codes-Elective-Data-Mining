#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <math.h>

using namespace std;


vector<string> split(string str,char delimiter)
{
	vector<string> internal;
	stringstream ss(str);
	string tok;
	while(getline(ss,tok,delimiter))
	{
		internal.push_back(tok);
	}
	return internal;
}


/*bool check(vector<int> *src,vector<int> *dest,int k)
{
	int i;
	for(i=0;i<k;i++)
	{

		if(!(src[i]==dest[i]))
			return false;
	}
	return true;
	
}*/



int main()
{
	int n;
	cout<<"Enter no. of data items:";
	cin>>n;


	ifstream in("ip.csv");
	ofstream out;
	string s;
	vector<string> p;

	double x[n],y[n];
	int lol=0;
	
	while(in>>s)
	{
		//cout<<s<<endl;
		p=split(s,',');
		//cout<<p[0]<<" "<<p[1]<<endl;
		x[lol]=atof(p[0].c_str());
		y[lol]=atof(p[1].c_str());
		++lol;
	}

	/*for(int i=0;i<n;i++)
	{
		cout<<x[i]<<" "<<y[i]<<endl;
	}*/


	int k;
	cout<<"Enter number of clusters:";
	cin>>k;

	vector<double> *mean;
	mean=new vector<double>[2];

	//Enter first k entries from input dataset
	cout<<"Enter cluster means:\n";

	for(int i=0;i<k;i++)
	{
		int mx,my;
		cin>>mx>>my;
		mean[0].push_back(mx);
		mean[1].push_back(my);
	}
	

	vector<double> *omean;
	omean=new vector<double>[2];

	//stores position of data
	vector<int> *c;		//k clusters
	c=new vector<int>[n];	//each cluster of size n


//	lol=0;
	while(1)
	{

		//cout<<lol++<<endl;
		for(int i=0;i<2;i++)
			omean[i]=mean[i];

		//clear previous cluster
		for(int i=0;i<k;i++)
			c[i].erase(c[i].begin(),c[i].end());

		//Cluster the data
		for(int i=0;i<n;i++)
		{
			double min=99999;
			int pos;
			
			//Find cluster center with minimum difference 
			for(int j=0;j<k;j++)
			{

				double temp=sqrt(pow((x[i]-mean[0][j]),2)+pow((y[i]-mean[1][j]),2));
				if(temp<min)
				{
					min=temp;
					pos=j;
				}
			}

			c[pos].push_back(i);

		}

		/*if(check(oc,c,k))
			break;*/


		//Calculate new mean and copy cluster data
		for(int i=0;i<k;i++)
		{
			double xsum=0,ysum=0;
			//oc[i]=c[i];
			for(int j=0;j<c[i].size();j++)
			{
				xsum+=x[c[i][j]];
				ysum+=y[c[i][j]];

			}
			mean[0][i]=xsum/c[i].size();
			mean[1][i]=ysum/c[i].size();
		}

		if(omean[0]==mean[0] && omean[1]==mean[1])
			break;

		/*for(int i=0;i<k;i++)
		{
			cout<<"Cluster "<<i+1<<endl;
			cout<<"Mean of cluster\n";
			cout<<mean[0][i]<<","<<mean[1][i]<<endl;
			cout<<"Cluster data\n";

			for(int j=0;j<c[i].size();j++)
			{
				int pos=c[i][j];		
				cout<<x[pos]<<","<<y[pos]<<endl;
			}
		}
			cout<<endl;*/
	}


	out.open("op.csv");
	for(int i=0;i<k;i++)
	{
		out<<"Cluster "<<i+1<<endl;
		out<<"Mean of cluster\n";
		out<<mean[0][i]<<","<<mean[1][i]<<endl;
		out<<"Cluster data\n";

		for(int j=0;j<c[i].size();j++)
		{
			int pos=c[i][j];		
			out<<x[pos]<<","<<y[pos]<<endl;
		}
		out<<endl;
			
		
	}

	in.close();
	out.close();

	return 0;
}