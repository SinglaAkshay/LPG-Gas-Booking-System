#include<iostream>
using namespace std;
#include<fstream>
#include<string.h>
#include<conio.h>
int status,p;
char a[3];
class start
{
	public:
	int ch;
	void startup()
	{
		cout<<"\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
		cout<<"^^^ENTER 1 FOR CUSTOMER DETAILS^^^"<<endl;
		cout<<"^^^^^ENTER 2 FOR GAS DETAILS^^^^^^"<<endl;
		cout<<"^^^ENTER 3 FOR BOOKING DETAILS^^^^"<<endl;
		cout<<"^^^^^^^^^ENTER 4 FOR EXIT^^^^^^^^^"<<endl;
		cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
		cin>>ch;
	}
	void start_1()
	{
		cout<<"\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
		cout<<"^^^^ENTER 1 FOR ADD NEW CUSTOMER^^^^"<<endl;
		cout<<"^ENTER 2 FOR VIEW CUSTOMER DETAILS^^"<<endl;
		cout<<"^^^^^^ENTER 3 FOR BACK TO MENU^^^^^^"<<endl;
		cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
		cin>>ch;
	}
	void start_2()
	{
		cout<<"\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
		cout<<"^^^ENTER 1 FOR ADD GAS IN GODOWN^^^"<<endl;
		cout<<"^^^ENTER 2 FOR VIEW GAS DETAILS^^^^"<<endl;
		cout<<"^^^^^ENTER 3 FOR BACK TO MENU^^^^^^"<<endl;
		cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
		cin>>ch;
	}
	void start_3()
	{
		cout<<"\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
		cout<<"^^^^^^ENTER 1 FOR NEW BOOKING^^^^^^"<<endl;
		cout<<"^^^^^^^ENTER 2 FOR ISSUE GAS^^^^^^^"<<endl;
		cout<<"^^ENTER 3 FOR VIEW BOOKING STATUS^^"<<endl;
		cout<<"^^^^^ENTER 4 FOR BACK TO MENU^^^^^^"<<endl;
		cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
		cin>>ch;
	}
};
class accept:public start
{
	public:
	char name[15],address[40],phone[12],PIN[6],word[6];
	int gas,booking;
	void accept_cust()
	{
		cout<<"\n#  ENTER CUSTOMER NAME  : ";
		cin.getline(name,15);
		cout<<"#  ENTER CUSTOMER ADDRESS  : ";
		cin.getline(address,40);
		cout<<"#  ENTER PHONE NUMBER  : ";
		cin.getline(phone,12);
		cout<<"#  ENTER YOUR 5 DIGIT PIN : ";
		cin.getline(PIN,6);
		ofstream ofobj;
		ofobj.open("Cyl_det.txt",ios::app|ios::out|ios::in);
		ofobj<<PIN<<endl;
		ofobj<<name<<endl;
		ofobj<<address<<endl;
		ofobj<<phone<<endl;
		cout<<"       ***ADDED SUCCESSFULLY***"<<endl;
		ofobj.close();
		status=0;
		ofstream book;
		book.open("Cyl_book.txt",ios::app|ios::out|ios::in);
		book<<PIN<<endl;
		book<<status<<endl;
		book.close();
	}
	void accept_gas()
	{
		int g=0;
		cout<<"\n   !!!ENTER NUMBER OF CYLINDERS!!!    : ";
		cin>>g;
		ifstream ifobj;
		ifobj.open("Cyl_gas.txt");
		ifobj>>gas;
		ifobj.close();
		ofstream ofobj;
		ofobj.open("Cyl_gas.txt");
		gas+=g;
		ofobj<<gas;
		cout<<"   ***ADDED IN GODOWN***  "<<endl;
		ofobj.close();
	}
	void accept_book()
	{
		cout<<"\n   *ENTER PIN* ";
		cin>>word;
		fstream book;
		book.open("Cyl_book.txt",ios::ate|ios::in|ios::out);
		book.seekg(0);
		p=0;
		while(book!=NULL)
		{
			book.getline(PIN,6);
			book>>status;
			if(strcmp(word,PIN)==0)
			{
				if(status==0)
				{
					book.seekp(book.tellp()-1);
					status=1;
					book<<status<<endl;
					cout<<"\nSUCCESSFULLY BOOKED"<<endl;
				}
				else
				cout<<"\nALREADY BOOKED!!!"<<endl;
				p++;
			}
			book.getline(a,3);
		}
		book.close();
		if(p==0)
		cout<<"\n!!!INVALID PIN!!!"<<endl;
	}
};
class display : public accept
{
	public:
	void display_cust()
	{
		cout<<"\nEnter your PIN:";
		cin.getline(word,6);
		p=0;
		ifstream ifobj;
		ifobj.open("Cyl_det.txt");
		while(ifobj!=NULL)
		{
			ifobj >> PIN;
			ifobj >> name;
			ifobj >> address;
			ifobj >> phone;
			if(strcmp(word,PIN)==0)
			{
				cout<<"PIN : "<<PIN<<endl;
				cout<<"NAME : "<<name<<endl;
				cout<<"ADDRESS : "<<address<<endl;
				cout<<"PHONE : "<<phone<<endl;
				p++;
				break;
			}
		}
		ifobj.close();
		if(p==0)
		cout<<"\n!!!INVALID PIN!!!"<<endl;
	}
	void display_gas()
	{
		ifstream ifobj;
		ifobj.open("Cyl_gas.txt");
		ifobj>>gas;
		cout<<"\n"<<gas<<" CYLINDERS ARE PRESENT IN GODOWN";
		ifobj.close();
	}
	void display_book()
	{
		cout<<"\nENTER PIN  :";
		cin.getline(word,6);
		p=0;
		ifstream book;
		book.open("Cyl_book.txt");
		while(book!=NULL)
		{
			book.getline(PIN,6);
			book>>status;
			if(strcmp(word,PIN)==0)
			{
				if(status==1)
				cout<<"\nBOOKED ALREADY"<<endl;
				else
				cout<<"\nNOT BOOKED"<<endl;
				p++;
			}
			book.getline(a,3);
		}
		book.close();
		if(p==0)
		cout<<"\n!!!INVALID PIN!!!"<<endl;
	}
};
class get : public display
{
	public:
	void issue()
	{
		cout<<"\nENTER PIN  :";
		cin>>word;
		p=0;
		fstream book;
		book.open("Cyl_book.txt",ios::ate|ios::in|ios::out);
		book.seekg(0);
		while(book!=NULL)
		{
			book.getline(PIN,6);
			book>>status;
			if(strcmp(word,PIN)==0)
			{
				if(status==0)
					cout<<"NOT BOOKED YET!!"<<endl;
				else
				{
					book.seekp(book.tellp()-1);
					status=0;
					book<<status<<endl;
					cout<<"\nSUCCESSFULLY ISSUED"<<endl;
					ifstream ifobj;
					ifobj.open("Cyl_gas.txt");
					ifobj>>gas;
					ifobj.close();
					ofstream ofobj;
					gas--;
					ofobj.open("Cyl_gas.txt");
					ofobj<<gas<<endl;
					ofobj.close();
				}
				p++;
			}
			book.getline(a,3);
		}
		if(p==0)
		cout<<"!!!INVALID PIN!!!"<<endl;
		book.close();
	}
};
int main()
{
	char more;
	get ob;
	ob.startup();
	switch(ob.ch)
	{
		case 1:
		{
			ob.start_1();
			switch(ob.ch)
			{
				case 1:
				{
					do
					{
						cin.getline(a,3);
						ob.accept_cust();
						cout<<"\nDO YOU WANT TO ADD MORE CUSTOMER? [Y/N]"<<endl;
						cin>>more;
					}
					while(more=='Y'||more=='y');
					main();
					break;
				}
				case 2:
				{
					do
					{
						cin.getline(a,3);
						ob.display_cust();
						cout<<"\nDO YOU WANT TO VIEW MORE CUSTOMER DETAILS? [Y/N]"<<endl;
						cin>>more;
					}
					while(more=='Y'||more=='y');
					main();
					break;
				}
				case 3:
				{
					main();
					break;
				}
				default:
		        {
					cout<<"\nINVALID KEY!"<<endl;

					main();
					break;
				}
			}
		break;
		}
		case 2:
		{
			ob.start_2();
			switch(ob.ch)
			{
				case 1:
				{
					do
					{
						cin.getline(a,3);
						ob.accept_gas();
						cout<<"\nDO YOU WANT TO ADD MORE GAS IN GODOWN? [Y/N]"<<endl;
						cin>>more;
					}
					while(more=='Y'||more=='y');
					main();
					break;
				}
				case 2:
				{
					ob.display_gas();
					cout<<"\nENTER ANY KEY!!"<<endl;
					main();
					break;
				}
				case 3:
				{
					main();
					break;
				}
				default:
				{
					cout<<"\n!!!INVALID KEY!!!"<<endl;
					main();
					break;
				}
			}
		break;
		}
		case 3:
		{
			ob.start_3();
			switch(ob.ch)
			{
				case 1:
				{
					do
					{
						cin.getline(a,3);
						ob.accept_book();
						cout<<"\nDO YOU WANT TO BOOK MORE? [Y/N]"<<endl;
						cin>>more;
					}
					while(more=='Y'||more=='y');
					main();
					break;
				}
				case 2:
				{
					do
					{
						cin.getline(a,3);
						ob.issue();
						cout<<"\nDO YOU WANT TO ISSUE MORE? [Y/N]"<<endl;
						cin>>more;
					}
					while(more=='Y'||more=='y');
					main();
					break;
				}
				case 3:
				{
					do
					{
						ob.display_book();
						cout<<"\nDO YOU WANT TO VIEW MORE BOOKING STATUS? [Y/N]"<<endl;
						cin>>more;
					}
					while(more=='Y'||more=='y');
					main();
					break;
				}
				case 4:
				{
					main();
					break;
				}
				default:
				{
					cout<<"\n!!!INVALID KEY!!!"<<endl;
					main();
					break;
				}
			}
		break;
		}
		case 4:
		{
	
			cout<<"\n***THANKS FOR USING***"<<endl;
			break;
		}
	}
	cout<<"Press Any Key For EXIT"<<endl;
}
