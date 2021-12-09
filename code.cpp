

#include<fstream>
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<conio.h>

using namespace std;

class subject
{
	char subject_id[10], subname[20], type[20],group[20];
	int theory,prac;
	int year;

	public:
	void getdata();
	void showdata();

	char* retsubject_id()
	{
		return subject_id;
	}

	char* retname()
	{
		return subname;
	}

	char* rettype()
	{
		return type;
	}

	int retprac()
	{
		return prac;
	}
	char*retgroup()
	{
		return group;
	}
};

subject s1,s2;
fstream f,f1;

void subject::getdata()				//User interface to input data
{
	system("cls");;
	cout<<"\n\n";
	cout<<"----------------------------------------------------------------------------";
	cout<<"\n			User Data Input Screen";
	cout<<"\n----------------------------------------------------------------------------";
	cout<<"\n\n Enter subject id				:   ";
	cin>>subject_id;
	cout<<" Enter subject name				:   ";
	cin>>subname;
	cout<<" Enter type of subject				:   ";
	cin>>type;
	cout<<" Enter the Group (A group/B group/Common) :  "; 	//Science/Commerce/Humanities/All
	cin>>group;
	cout<<" Enter maximum practical marks			:   ";	//enter 0 if non practical subject else enter a non zero value
	cin>>prac;
	cout<<" Enter maximum theory marks			:   ";
	cin>>theory;
	cout<<" Enter year				:   ";
	cin>>year;
}

void subject::showdata()		//Show user the entered data
{
	cout<<"\n The subject id is		: ";
	cout<<subject_id;
	cout<<"\n The subject name is 		: ";
	cout<<subname;
	cout<<"\n The type of subject is 	: ";
	cout<<type;
	cout<<"\n The subject Group is		: ";
	cout<<group;
	cout<<"\n The maximum practical marks are : ";
	cout<<prac;
	cout<<"\n The maximum theory marks are	: ";
	cout<<theory;
	cout<<"\n The year of the student 	: ";
	cout<<year;
	cout<<"\n____________________________________________________________________________";
}

void create()				//Function to create and save data to binary file
{
	f.open("subject.dat",ios::out|ios::binary);
	char ans='y';
	while(ans=='y'||ans=='Y')
	{
		s1.getdata();
		f.write((char*)&s1,sizeof(s1));
		cout<<"\n  Do you want to continue (Y/N)? : ";
		cin>>ans;
	}
	f.close();
}

void showfile()				//Display input data
{
	f.open("subject.dat",ios::in|ios::binary);
	f.seekg(0);
	system("cls");
	cout<<"\n\n";
	cout<<"----------------------------------------------------------------------------";
	cout<<"\n			User Data Display Screen";
	cout<<"\n----------------------------------------------------------------------------";
	while(f.read((char*)&s1,sizeof(s1)))
	{
		s1.showdata();
	}
	f.close();
}

void search()				//Search function based on selected criteria
{
	f.open("subject.dat",ios::in|ios::binary);
	system("cls");
	cout<<"\n\n\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<"\t 			User Query Screen\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<" Search on the basis of \n 1: Subject id \n 2: Subject name \n 3: Subject type\n 4: Subject Group";
	int ch;
	cout<<"\n Enter Choice : ";
	cin>>ch;
	if(ch==1)
	{
		char searchid[20];
		cout<<" Enter subject id : ";
		cin>>searchid;
		while(f.read((char*)&s1,sizeof(s1)))
		{
			if(strcmp(s1.retsubject_id(),searchid)==0)
				s1.showdata();
		}
	}
	f.close();
	f.open("subject.dat",ios::in|ios::binary);

	if(ch==2)
	{
		char searchname[20];
		cout<<" Enter subject name : ";
		cin>>searchname;

		while(f.read((char*)&s1,sizeof(s1)))
		{
			if(strcmp(s1.retname(),searchname)==0)
			s1.showdata();
		}
	}
	f.close();
	f.open("subject.dat",ios::in|ios::binary);

	if(ch==3)
	{
		char searchtype[20];
		cout<<" Enter subject type : ";
		cin>>searchtype;

		while(f.read((char*)&s1,sizeof(s1)))
		{
			if(strcmp(s1.rettype(),searchtype)==0)
			s1.showdata();
		}
	}
	f.close();
	f.open("subject.dat",ios::in|ios::binary);
	if(ch==4)
	{
		char searchstr[20];
		cout<<" Enter subject group : ";
		cin>>searchstr;

		while(f.read((char*)&s1,sizeof(s1)))
		{
			if(strcmp(s1.retgroup(),searchstr)==0)
			s1.showdata();
		}
	}
	f.close();
}

void editn()					//Edit function based on record number
{
	f.open("subject.dat",ios::in|ios::binary);
	f1.open("temp.dat",ios::out|ios::binary);

	int r=0;
	int sr;
	int flag=0;
	cout<<"\n Enter record number to edit : ";
	cin>>sr;

	while(f.read((char*)&s1,sizeof(s1)))
	{
		r++;
		if(r==sr)
		{
//			cout<<"\n Enter new details ";
			s2.getdata();
			f1.write((char*)&s2,sizeof(s2));
			flag=1;
		}
		else
		f1.write((char*)&s1,sizeof(s1));
	}
	f1.close();
	f.close();

	remove("subject.dat");
	rename("temp.dat","subject.dat");
	system("cls");
	cout<<"\n\n\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<"\t 			User Update Screen\n";
	cout<<"----------------------------------------------------------------------------";
	if (flag==1)
		cout<<"\n Record edit was completed\n";
	else
		cout<<"\n Record not found\n";
}

void editid()					//Edit function based on subject id
{
	f.open("subject.dat",ios::in|ios::binary);
	f1.open("temp.dat",ios::out|ios::binary);
	char sid[20];
//	char ans;
	int flag=0;
	cout<< "\n Enter subject id to edit : ";
	cin>>sid;
	f.seekg(0);
	while(f.read((char*)&s1,sizeof(s1)))
	{
		if(strcmp(s1.retsubject_id(),sid)==0)
		{
//			cout<<"\n Taking you to Input screen for new details. Press any key";
//			cin>>ans;
			s2.getdata();
			f1.write((char*)&s2,sizeof(s2));
			flag=1;
		}
		else
			f1.write((char*)&s1,sizeof(s1));
	}
	f.close();
	f1.close();
	remove("subject.dat");
	rename("temp.dat","subject.dat");
	system("cls");
	cout<<"\n\n\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<"\t 			User Update Screen\n";
	cout<<"----------------------------------------------------------------------------";
	if (flag==1)
		cout<<"\n Record edit was completed\n";
	else
		cout<<"\n Record not found\n";
}

void editname()					//Edit function based on subject name
{
	f.open("subject.dat",ios::in|ios::binary);
	f1.open("temp.dat",ios::out|ios::binary);
	char sn[20];
	int flag=0;
	cout<< "\n Enter subject name to edit : ";
	cin>>sn;
	f.seekg(0);
	while(f.read((char*)&s1,sizeof(s1)))
	{
		if(strcmp(s1.retname(),sn)==0)
		{
//			cout<<"\n Enter new details";
			s2.getdata();
			f1.write((char*)&s2,sizeof(s2));
			flag=1;
		}
		else
			f1.write((char*)&s1,sizeof(s1));
	}
	f.close();
	f1.close();
	remove("subject.dat");
	rename("temp.dat","subject.dat");
	system("cls");
	cout<<"\n\n\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<"\t 			User Update Screen\n";
	cout<<"----------------------------------------------------------------------------";
	if (flag==1)
		cout<<"\n Record edit was completed\n";
	else
		cout<<"\n Record not found\n";
}

void delfst()					//Delete function for deleting first record stored in file
{
	f.open("subject.dat",ios::in|ios::binary);
	f1.open("temp.dat",ios::out|ios::binary);
	f.read((char*)&s2,sizeof(s2));
	while(f.read((char*)&s2,sizeof(s2)))
	{
		f1.write((char*)&s2,sizeof(s2));
	}
	f.close();
	f1.close();
	remove("subject.dat");
	rename("temp.dat","subject.dat");
	system("cls");
	cout<<"\n\n\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<"\t 			User Update Screen\n";
	cout<<"----------------------------------------------------------------------------";
	cout<<"\n Record deletion was completed\n";
}

void dellst()					//Delete function for deleting last record stored in file
{
	f.open("subjcet.dat",ios::in|ios::binary);
	f1.open("temp.dat",ios::out|ios::binary);
	f.seekg(0,ios::end);
	int ip=f.tellg();
	int s=sizeof(s1);
	int ir=ip/s;
	int r=1;
	cout<<"\n Number of records are "<<ir;
	f.seekg(0);
	while(f.read((char*)&s2,sizeof(s2)))
	{
		if(r!=ir)
			f1.write((char*)&s2,sizeof(s2));
			r++;
	}
	f.close();
	f1.close();
	remove("subject.dat");
	rename("temp.dat","subject.dat");
	system("cls");
	cout<<"\n\n\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<"\t 			User Update Screen\n";
	cout<<"----------------------------------------------------------------------------";
	cout<<"\n Record deletion was completed\n";
}

void deln()					//Delete function for deleting based on record number
{
	f.open("subject.dat",ios::in|ios::binary);
	f1.open("temp.dat",ios::out|ios::binary);
	int r=1;
	int dr;
	int flag=0;
	cout<<" Enter record number to delete : ";
	cin>>dr;
	f.seekg(0);
	while(f.read((char*)&s2,sizeof(s2)))
	{
		if(r==dr)
			flag=1;
		if(r!=dr)
			f1.write((char*)&s2,sizeof(s2));
			r++;
	}
	f.close();
	f1.close();
	remove("subject.dat");
	rename("temp.dat","subject.dat");
	system("cls");
	cout<<"\n\n\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<"\t 			User Update Screen\n";
	cout<<"----------------------------------------------------------------------------";
	if (flag==1)
		cout<<"\n Record deletion was completed\n";
	else
		cout<<"\n Record not found\n";
}

void delid()					//Delete function for deleting record based on subject id
{
	f.open("subject.dat",ios::in|ios::binary);
	f1.open("temp.dat",ios::out|ios::binary);
	char did[20];
	int flag=0;
	cout<<" Enter subject id to delete : ";
	cin>>did;
	f.seekg(0);
	while(f.read((char*)&s2,sizeof(s2)))
	{
		if(strcmp(s2.retsubject_id(),did)==0)
			flag=1;
		if(strcmp(s2.retsubject_id(),did)!=0)
			f1.write((char*)&s2,sizeof(s2));
	}
	f.close();
	f1.close();
	remove("subject.dat");
	rename("temp.dat","subject.dat");
	system("cls");
	cout<<"\n\n\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<"\t 			User Update Screen\n";
	cout<<"----------------------------------------------------------------------------";
	if (flag==1)
		cout<<"\n Record deletion was completed\n";
	else
		cout<<"\n Record not found\n";
}

void delname()					//Delete function for deleting record based on subject name
{
	f.open("subject.dat",ios::in|ios::binary);
	f1.open("temp.dat",ios::out|ios::binary);
	char dname[20];
	int flag=0;
	cout<<" Enter Subject name to delete : ";
	cin>>dname;
	f.seekg(0);
	while(f.read((char*)&s2,sizeof(s2)))
	{
		if(strcmp(s2.retname(),dname)!=0)
			flag=1;
		if(strcmp(s2.retname(),dname)!=0)
			f1.write((char*)&s2,sizeof(s2));
	}
	f.close();
	f1.close();
	remove("subject.dat");
	rename("temp.dat","subject.dat");
	system("cls");
	cout<<"\n\n\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<"\t 			User Update Screen\n";
	cout<<"----------------------------------------------------------------------------";
	if (flag==1)
		cout<<"\n Record deletion was completed\n";
	else
		cout<<"\n Record not found\n";
}

void insfst()					//Function for inserting record in file at first location
{
	f.open("subject.dat",ios::in|ios::binary);
	f1.open("temp.dat",ios::out|ios::binary);
	cout<<" Enter record to be inserted : ";
	s2.getdata();
	f.seekg(0);
	f1.write((char*)&s2,sizeof(s2));
	while(f.read((char*)&s1,sizeof(s1)))
	{
		f1.write((char*)&s1,sizeof(s1));
	}
	f.close();
	f1.close();
	remove("subject.dat");
	rename("temp.dat","subject.dat");
	system("cls");
	cout<<"\n\n\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<"\t 			User Update Screen\n";
	cout<<"----------------------------------------------------------------------------";
	cout<<"\n Record insertion at begining of file was completed\n";
}

void inslst()					//Function for inserting record in file at last location
{
	f.open("subject.dat",ios::in|ios::binary);
	f1.open("temp.dat",ios::out|ios::binary);
	cout<<" Enter record to be inserted : ";
	s2.getdata();
	while(f.read((char*)&s1,sizeof(s1)))
	{
		f1.write((char*)&s1,sizeof(s1));
	}
	f1.write((char*)&s2,sizeof(s2));
	f.close();
	f1.close();
	remove("subject.dat");
	rename("temp.dat","subject.dat");
	system("cls");
	cout<<"\n\n\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<"\t 			User Update Screen\n";
	cout<<"----------------------------------------------------------------------------";
	cout<<"\n Record insertion at end of file was completed\n";
}

void insnth()					//Function for inserting record in file after nth record
{
	f.open("subject.dat",ios::in|ios::binary);
	f1.open("temp.dat",ios::out|ios::binary);
	cout<<" Enter data to insert : ";
	s2.getdata();
	int flag=0;
	int r=0;
	int ir;
	cout<<"\n Enter record no after which you want to insert : ";
	cin>>ir;
	while(f.read((char*)&s1,sizeof(s1)))
	{
		f1.write((char*)&s1,sizeof(s1));
		r++;
		if(r==ir)
			f1.write((char*)&s2,sizeof(s2));
			flag=1;
	}

	f.close();
	f1.close();
	remove("subject.dat");
	rename("temp.dat","subject.dat");
	system("cls");
	cout<<"\n\n\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<"\t 			User Update Screen\n";
	cout<<"----------------------------------------------------------------------------";
	if (flag==1)
		cout<<"\n Record insertion was completed\n";
	else
		cout<<"\n Record not found\n";
}

void insid()					//Function for inserting record in file after selected subject id
{
	f.open("subject.dat",ios::in|ios::binary);
	f1.open("temp.dat",ios::out|ios::binary);
	cout<<" Enter data to insert : ";
	s2.getdata();
	char sid[20];
	int flag=0;
	cout<<"\n Enter id after which record has to be inserted : ";
	cin>>sid;
	f.seekg(0);
	while(f.read((char*)&s1,sizeof(s1)))
	{
		f1.write((char*)&s1,sizeof(s1));
		if(strcmp(s1.retsubject_id(),sid)==0)
			f1.write((char*)&s2,sizeof(s2));
			flag=1;
	}

	f.close();
	f1.close();
	remove("subject.dat");
	rename("temp.dat","subject.dat");
	system("cls");
	cout<<"\n\n\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<"\t 			User Update Screen\n";
	cout<<"----------------------------------------------------------------------------";
	if (flag==1)
		cout<<"\n Record insertion was completed\n";
	else
		cout<<"\n Record not found\n";
}

void insname()					//Function for inserting record in file after selected subject id
{
	f.open("subject.dat",ios::in|ios::binary);
	f1.open("temp.dat",ios::out|ios::binary);
	cout<<" Enter data to insert : ";
	s2.getdata();
	char sname[20];
	int flag=0;
	cout<<"\n Enter name after which record has to be inserted : ";
	cin>>sname;
	f.seekg(0);
	while(f.read((char*)&s1,sizeof(s1)))
	{
		f1.write((char*)&s1,sizeof(s1));
		if(strcmp(s1.retname(),sname)==0)
			f1.write((char*)&s2,sizeof(s2));
			flag=1;
	}

	f.close();
	f1.close();
	remove("subject.dat");
	rename("temp.dat","subject.dat");
	system("cls");
	cout<<"\n\n\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<"\t 			User Update Screen\n";
	cout<<"----------------------------------------------------------------------------";
	if (flag==1)
		cout<<"\n Record insertion was completed\n";
	else
		cout<<"\n Record not found\n";
}

void countsub()					//Function for counting number of subjects whose details are stored in the file
{
	f.open("subject.dat",ios::in|ios::binary);
	int ctr=0;
	while(f.read((char*)&s1,sizeof(s1)))
	{
		ctr++;
	}
	f.close();
	system("cls");
	cout<<"\n\n\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<"\t 			User Query Screen\n";
	cout<<"----------------------------------------------------------------------------";
	cout<<"\n The number of subjects are "<<ctr;
	cout<<"\n\n";
}

void countprac()				//Function for counting number of subjects with practical marks
{
	f.open("subject.dat",ios::in|ios::binary);
	int ctr=0;
	while(f.read((char*)&s1,sizeof(s1)))
	{
		if(s1.retprac()!=0)
		ctr++;
	}

	f.close();
	system("cls");
	cout<<"\n\n\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<"\t 			User Query Screen\n";
	cout<<"----------------------------------------------------------------------------";
	cout<<"\n The number of practical subjects are "<<ctr;
	cout<<"\n\n";
}

void counttype()				//Function for counting subject type
{
	f.open("subject.dat",ios::in|ios::binary);
	char stype[20];
	system("cls");
	cout<<"\n\n\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<"\t 			User Query Screen\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<" Enter subject type to be counted : ";
	cin>>stype;
	int ctr=0;
	while(f.read((char*)&s1,sizeof(s1)))
	{
		if(strcmp(s1.rettype(),stype)==0)
		ctr++;

	}

	f.close();
	cout<<"\n The number of subjects of this type are "<<ctr;
	cout<<"\n\n";
}

void countgroup()				//Function for counting number of subjects by group
{
	f.open("subject.dat",ios::in|ios::binary);
	char sgroup[20];
	system("cls");
	cout<<"\n\n\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<"\t 			User Query Screen\n";
	cout<<"----------------------------------------------------------------------------\n";
	cout<<" Enter subject group to be counted : ";
	cin>>sgroup;
	int ctr=0;
	while(f.read((char*)&s1,sizeof(s1)))
	{
		if(strcmp(s1.retgroup(),sgroup)==0)
		ctr++;

	}

	f.close();
	cout<<"\n The number of subjects in this group are "<<ctr;
	cout<<"\n\n";
}


int main()				//Main Screen for file operations
{
	int ch,choice;
	system("cls");
	char ch1;
	do
	{
		system("cls");
		cout<<"----------------------------------------------------------------------------\n";
		cout<<"\t 			FILE OPERATION MENU\n";
		cout<<"----------------------------------------------------------------------------";
		cout<<"\n 1.  Create a file";
		cout<<"\n 2.  Read all record";
		cout<<"\n 3.  Search";
		cout<<"\n 4.  Edit nth record";
		cout<<"\n 5.  Edit id";
		cout<<"\n 6.  Edit name";
		cout<<"\n 7.  Insert new record at first position";
		cout<<"\n 8.  Insert new record at last position";
		cout<<"\n 9.  Insert new record after nth record";
		cout<<"\n 10. Insert new record after an id";
		cout<<"\n 11. Insert new record after a name";
		cout<<"\n 12. Delete first record";
		cout<<"\n 13. Delete last record";
		cout<<"\n 14. Delete nth record";
		cout<<"\n 15. Delete record of a name";
		cout<<"\n 16. Delete record of an id";
		cout<<"\n 17. Count total subjects";
		cout<<"\n 18. Count total subjects of a type";
		cout<<"\n 19. Count total subjects with practicals";
		cout<<"\n 20. Count total subjects in a group";
		cout<<"\n----------------------------------------------------------------------------";
		cout<<"\n Enter your choice (1 - 20) : ";
		cin>>ch;
    cin.get();
		switch(ch)
		{
			case 1:create();
			break;

			case 2:showfile();
			break;

			case 3:search();
			break;

			case 4:editn();
			break;

			case 5:editid();
			break;

			case 6:editname();
			break;

			case 7:insfst();
			break;

			case 8:inslst();
			break;

			case 9:insnth();
			break;

			case 10:insid();
			break;

			case 11:insname();
			break;

			case 12:delfst();
			break;

			case 13:dellst();
			break;

			case 14:deln();
			break;

			case 15:delname();
			break;

			case 16:delid();
			break;

			case 17:countsub();
			break;

			case 18:counttype();
			break;

			case 19:countprac();
			break;

			case 20:countgroup();
		}
		cout<<"\n Do you want to go back to main menu (Y/N)? : ";
    cin.get();
		cin>>ch1;

	}
	while(ch1=='y'||ch1=='Y');
}
