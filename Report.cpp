#include<fstream>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<iostream>
using namespace std;
class Report
{       
int pno;
	char destination[200];
	char time[50], pname[100];
	int max_seats;
	int booked;
	int fare;
	public:
	Report()
	{
	pno=0;
	max_seats=50;
	booked=0;
	fare=0;
	strcpy(time,"9:10am");
	strcpy(destination,"");
	}
	void input();
	void show();
	void display();
	int getid()
	{
	return pno;
	}
	void book()
	{
	booked++;
	}
	char* getpname()
	{
	    return pname;
	}
	char* getDestination()
	{
	return destination;
	}
	char* getTime()
	{
	return time;
	}
	int getBooked(){
	return booked;
	}
	int getMax(){
	return max_seats;
	}
	int getFare()
	{
		return fare;
	}
};
int main()
{
	int ch,id;
	int chk=0;
	fstream F,G;
	Report b;
	do
	{cout<<"\n\t\t~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout<<"\n\t\t                  HEALTH REPORT MANAGMENT                        \n";
    cout<<"\n\t\t~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout<<"\n\t\t\t******   YOU ARE WELCOME   *******\n";
    cout<<"\n\n\t\t\tMAIN MENU\n\n";
        cout<<"\t=========================================\n";
		cout<<"\t|\tPress 1 - Add a New Report\t|"<<endl;
		cout<<"\t|\tPress 2 - Display All Report\t|"<<endl;
		cout<<"\t|\tPress 3 - Delete a Report\t|"<<endl;
		cout<<"\t|\tPress 4 - Book a ticket \t|"<<endl;
		cout<<"\t|\tPress 5 - Display Booked Tickets|"<<endl;
		cout<<"\t|\tPress 6 - Exit\t\t\t| "<<endl;
		cout<<"\t=========================================\n";
		cout<<"\n\t\t\tEnter your choice ";
		cin>>ch;
		switch(ch)
		{
		case 1:
			F.open("Report.txt",ios::app | ios::binary);
			b.input();
			F.write((char*)&b, sizeof(b));
			F.close();
			cout<<"Report added Successfully "<<endl;
		break;



		case 2:
			F.open("Report.txt",ios::in | ios::binary);
			if(F.fail())
				cout<<"Can't open file "<<endl;
			else
			{
				while(F.read((char*)&b,sizeof(b)))
					b.display();
			}
			F.close();
			cout<<"Press a key to continue ";

		break;
		case 3:
			chk=0;
			cout<<"Enter the Report id to be deleted ";
			cin>>id;
			F.open("Report.txt",ios::in | ios::binary);
			G.open("temp.txt",ios::out | ios::binary);
			if(F.fail())
				cout<<"Can't open file "<<endl;
			else
			{
				while(F.read((char*)&b,sizeof(b)))
				{
					if(b.getid()!=id)
					{
					G.write((char*)&b,sizeof(b));
					}
					else
					{
						b.show();
						chk=1;

					}
				}
				if(chk==0)
					cout<<"Report not Found"<<endl;

				else
					cout<<"Report Deleted "<<endl;
			}
			F.close();
			G.close();
			remove("Report.txt");
			rename("temp.txt","Report.txt");
			break;
		case 4:
			char dest[70],cname[50];
			int pno;

			cout<<"Enter the destination ";
			gets(dest);
			F.open("Report.txt",ios::in | ios::out | ios::binary);
			if(F.fail())
				cout<<"Can't open file "<<endl;
			else
			{
				while(F.read((char*)&b,sizeof(b)))
				{
					if(strcmp(b.getDestination(),dest)==0)
					{
						b.show();
						chk=1;
						cout<<"Enter the customer name ";
						gets(cname);
						b.book();
						t.generate(cname,b);
						G.open("tickets.dat",ios::app | ios::binary);
						G.write((char*)&t,sizeof(t));
						G.close();
					F.seekp(F.tellg()-sizeof(b),ios::beg);

					F.write((char*)&b,sizeof(b));
					cout<<"Ticket booked"<<endl;
					getch();
					break;
					}
				}
				if(chk==0)
					cout<<"No Report Found"<<endl;

			}
			F.close();
			break;
		case 5:
			cout<<"Booked Tickets "<<endl;
			G.open("tickets.txt",ios::in | ios::binary);
			if(G.fail())
				cout<<"can't open file "<<endl;
			else
			{
				while(G.read((char*)&t,sizeof(t)))
				t.display();
			}

			G.close();
			cout<<"Press a key to continue ";
			getch();

		}
	}while(ch!=7);
}
