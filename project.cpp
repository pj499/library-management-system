#include<iostream>
#include<fstream>
#include<cstring>
#include<bcrypt/BCrypt.hpp>

using namespace std;

class hashtable
{
public :

int hash1(int k)
{
  int ans=k%10;
  return ans;
}

int hash(int key)
{
  int index1=hash1(key);
  return index1;
}
};

class Login
{
    char username[20];
    char name[20];
    int hashnum;
    char password[50];
    
public:
	  

  void setData()
    {
       cout<<"Enter required details"<<endl;
       
       cout<<"UserName :\t";
       cin>>username;
       
       cout<<"Name :\t";
       cin>>name;
       
       cout<<"Password :\t";
       cin>>password;
       
       int len=strlen(username);
       hashtable h;
       hashnum=h.hash(len);
       
    }

   void showData()
    {
       cout<<"--------------------------------------------------"<<endl;
       cout<<"Welcome! "<<name<<endl;
       cout<<"--------------------------------------------------"<<endl;
    }
    
    int ret_hash()
    {
      return hashnum;
    }

    int secure_password(string pwd)
	{
		BCrypt bcrypt;
		string hash = bcrypt.generateHash(password);
		if(bcrypt.validatePassword(pwd,hash)==0)
		{
		  cout<<"Wrong password"<<endl;
			return 0;
		}
		else
		return 1;
	}
	 
};


void delete_record(int n)
  {
    int flag=0;
    Login obj;
    ifstream inFile;
    inFile.open("login.dat", ios::binary);

    ofstream outFile;
    outFile.open("temp.dat", ios::out | ios::binary);
    
    while(inFile.read((char*)&obj, sizeof(obj)))
    {
        if(obj.ret_hash() != n)
        {
            outFile.write((char*)&obj, sizeof(obj));
            flag=1;
        }
    }

    inFile.close();
    outFile.close();
    
    remove("login.dat");
    rename("temp.dat", "login.dat");
    
    if(flag==0)
    cout<<"No database found"<<endl;
    else
    cout<<"Record Deleted"<<endl;
  }
  
  void write_record()
  {
    ofstream out;
    out.open("login.dat",ios::binary|ios::app);

    Login obj;
    obj.setData();
    
    out.write((char*)&obj, sizeof(obj));
    
    out.close();
  }

  void search(int n)
  {
    int flag=0;
    char pwd[50];
    ifstream inFile;
    inFile.open("login.dat", ios::binary);
    cout<<"Enter password"<<endl;
    cin>>pwd;
    Login obj;

    while(inFile.read((char*)&obj, sizeof(obj)))
    {
        if(obj.ret_hash() == n)
        {
	   if(obj.secure_password(pwd))
           obj.showData();
           flag=1;   
        }
    }
    
    if(flag==0)
    cout<<"No database found"<<endl;  
    inFile.close();
  }



int main()
{
  hashtable h;
  int len;
  char uname[20];
  int choice;
  char ans;
  
	do
	{
    cout<<"Enter\n1.Sign in\n2.Log in"<<endl;
    cin>>choice;
    switch(choice)
    {
      case 1:
      {
        write_record();
      }
      break;
      
      case 2:
      {
        cout<<"Enter your username"<<endl;
        cin>>uname;
        len=strlen(uname);
        len=h.hash(len);
        search(len);
      }
      break;        
	  
      default:
      cout<<"Invalid input"<<endl;
      
    }
    cout<<"Any further operations?"<<endl;
    cin>>ans;
  }
  while(ans=='y');		

  return 0;
}
