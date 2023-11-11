#include<iostream>
#include<algorithm>
#include<assert.h>
using namespace std;
const int Max_Books=10,Max_Users=10;
struct Book
{
    int ID,Quant,borrowed;
    string Name;
    Book()
    {
        ID=-1;
        borrowed=Quant=0;
        Name="";
    }
    void read()
    {
        puts("enter Name & ID & Quat");
        cin>>Name>>ID>>Quant;
    }
    bool Borrowed()
    {
        if(Quant-borrowed==0)
            return false;
        borrowed+=1;
            return true;
    }
    Return()
    {
        
    }
};
bool comp_id(Book &a , Book &b)
{
    return a.ID<b.ID;
}
bool comp_name(Book &a , Book &b)
{
    return a.Name<b.Name;
}
struct User
{
    int ID;
    string Name;
    int Borrowed_Books_ID[Max_Books];
    int len;
    User()
    {
        ID=-1;
        Name="";
        len=0;
    }
    void read()
    {
        puts("Enter User's Name & ID");
        cin>>Name>>ID;
    }
    void Borrow(int id)
    {
        Borrowed_Books_ID[len++]=id;
    }
    void Remove(int id)
    {
        for(int i=id+1;i<len;i++)
            Borrowed_Books_ID[i-1]=Borrowed_Books_ID[i];
        len--;
    }
};
struct libarary
{
    int Total_Books,Total_Users;
    Book book[Max_Books];
    User user[Max_Users];
    libarary()
    {
        Total_Books=Total_Users=0;
    }
    void Run()
    {
        int choice;
        while(true)
        {
            choice=menu();
            if(choice==1)
                Add_Book();
            else if(choice==2)
                Search();
            else if(choice==3)
                User_Borrowed_Books();
            else if(choice==4)
                print_Lib_id();
            else if(choice==5)
                print_Lib_name();
            else if(choice==6)
                Add_User();
            else if(choice==7)
                Users_Borrow_Book();
            else if(choice==8)
                Users_Return_Book();
            else if(choice==9)
                Print_users();
            else if(choice==10)
                break;
        }
        puts("Have a GoodDay!,Bye");
    }
    int menu()
    {
        int choice=-1;
        while(choice==-1)
        {
            puts("Enter Your Menu Choice[1-10]");
            puts("1)Add_Book");
            puts("2)Search Book By Prefix");
            puts("3)User_Borrowed_Books");
            puts("4)Print_libarary_by_id");
            puts("5)Print_libarary_by_name");
            puts("6)Add_users");
            puts("7)Users Borrow_Book");
            puts("8)Users Return Books");
            puts("9)Print All Users");
            puts("10)Exit");
            cin>>choice;
            if(choice>10||choice<1)
            {
                choice=-1;
                puts("Choice Invalid");
            }
        }
        return  choice;
    }
    void Add_Book()
    {
        book[Total_Books++].read();
    }
    void Add_User()
    {
        user[Total_Users++].read();
    }
    void Print_users()
    {
        cout<<"There Are "<<Total_Users<<" Users\n";
        for(int i=0;i<Total_Users;i++)
        {
            cout<<"User ID:"<<user[i].ID<<" Users Name: "<<user[i].Name;
        }
    }
    void print_Lib_id()
    {
        sort(book, book+Total_Books, comp_id);
        cout<<"There are "<<Total_Books<<"\n";
        for(int i=0;i<Total_Books;i++)
            cout<<"Book ID "<<book[i].ID<<" Book Name "<<book[i].Name<<"\n";
    }
    void print_Lib_name()
    {
        sort(book,book+Total_Books,comp_name);
        cout<<"There are "<<Total_Books<<"\n";
        for(int i=0;i<Total_Books;i++)
            cout<<"Book ID "<<book[i].ID<<" Book Name "<<book[i].Name<<"\n";
    }
    int find_user_idx_by_name(string name)
    {
        for(int i=0;i<Total_Users;i++)
            if(user[i].Name==name)
                return i;
        return -1;
    }
    int find_book_idx_by_name(string name)
    {
        for(int i=0;i<Total_Books;i++)
            if(book[i].Name==name)
                return i;
        return -1;
    }
    bool user_name_book(int bidx,int uidx)
    {
        int try_cnt=3;
        string book_Name,User_Name;
        while(try_cnt--)
        {
            puts("Enter Book_Name & User_Name");
            cin>>book_Name>>User_Name;
            int book_idx=find_book_idx_by_name(book_Name);
            int user_idx=find_user_idx_by_name(User_Name);
            if(user_idx==-1)
            {
                puts("Invalid User");
                continue;
            }
            if(book_idx==-1)
            {
                puts("Invalid Book");
                continue;
            }
            return true;
        }
        puts("Several tries , Try Again Later");
        return false;
    }
    void Users_Borrow_Book()
    {
        int book_id,user_id;
        if(!user_name_book(book_id,user_id))
            return;
        int user_id_x=user[user_id].ID;
        int book_id_x=book[book_id].ID;
        if(!(book[book_id_x].Borrowed()))
            puts("Sorry No More Copies");
        else
            user[user_id_x].Borrow(book_id_x);
    }
    void Search()
    {
        puts("Enter_Book_Name");
        string name;
        cin>>name;
        sort(book,book+Total_Books,comp_name);
        for(int i=0;i<Total_Books;i++)
            if(name==book[i].Name)
            {
                cout<<"Book Index is "<<i<<" Book ID is "<<book[i].ID<<"\n";
                return;
            }
        puts("Book Not Found !!");
    }
    void User_Borrowed_Books()
    {
        puts("Enter User's Name");
        string name;
        cin>>name;
        if(find_user_idx_by_name(name)==-1)
        {
            puts("Sorry User does'nt exist");
            return;
        }
        int idx=find_user_idx_by_name(name);
        int borrowed_books_length=user[idx].len;
        if(borrowed_books_length==0)
            puts("User's Didn't Borrow Any Book!");
        else
        {
            cout<<"User Borrowed "<<borrowed_books_length<<"Books \n";
            for(int i=0;i<borrowed_books_length;i++)
                cout<<"Book ID "<<user[idx].Borrowed_Books_ID[i]<<"\n";
        }        
    }
    int find_Borrowed(int B_id,int U_id)
    {
        int len=user[U_id].len;
        for(int i=0;i<len;i++)
            if(B_id==user[U_id].Borrowed_Books_ID[i])
                return i;
        return -1;
    }
    void Users_Return_Book()
    {
        puts("Enter User's Name & Borrowed Book");
        string B_name,U_name;
        cin>>U_name>>B_name;
        int U_idx=find_user_idx_by_name(U_name),B_idx=find_book_idx_by_name(B_name);
        if(U_idx==-1)
        {
            puts("User Doesn't Exist");
            return;
        }
        if(B_idx==-1)
        {
            puts("Book Does'nt Exist");
            return;
        }
        int Borrowed_book_idx=find_Borrowed(B_idx,U_idx);
        if(Borrowed_book_idx==-1)
        {
            puts("User Did'nt Borrow This Book");
            return;
        }
        user[U_idx].Return(B_idx);
    }
};

int main()
{
    libarary lib;
    lib.Run();
}