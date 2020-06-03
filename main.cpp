#include <iostream>
#include <cstring>
#include <cassert>//按行读取
#include <fstream>//读写文件
#include <iomanip>
#include <stdlib.h>
using namespace std;
class person
{
protected:
    char name[60];        //姓名
    char telnb[20];       //电话
    char type[60];        //职业类型
    char email[60];       //邮箱
    int id;               //编号
    person *Mynext;       //指向下一个对象
public:
    person();             //初始化变量
    person(char pname[],char ptelnb[],char ptype[],char pemail[],int pid);
    person(char pname[],char ptelnb[],char ptype[],char pemail[],int pid,person *next);
    char *getname();
    char *gettelnb();
    char *gettype();
    char *getemail();
    int   getid();
    person *getnext();
    void  setnext(person *next);

};
person::person()
{
    strcpy(name,"");
    strcpy(telnb,"");
    strcpy(type,"");
    strcpy(email,"");
    Mynext = NULL;
    id = 0;
}
person::person(char pname[],char ptelnb[],char ptype[],char pemail[],int pid)
{
    strcpy(name,pname);
    strcpy(telnb,ptelnb);
    strcpy(type,ptype);
    strcpy(email,pemail);
    Mynext = NULL;
    id = pid;
}
person::person(char pname[],char ptelnb[],char ptype[],char pemail[],int pid,person *next)
{
    strcpy(name,pname);
    strcpy(telnb,ptelnb);
    strcpy(type,ptype);
    strcpy(email,pemail);
    Mynext = next;
    id = pid;
}
char *person::getname()
{
    return name;
}
char *person::gettelnb()
{
    return telnb;
}
char *person::gettype()
{
    return type;
}
char *person::getemail()
{
    return email;
}
person *person::getnext()
{
    return Mynext;
}
void person::setnext(person *next)
{
    Mynext = next;
}
int person::getid()
{
    return id;
}
class AddressBook
{
private:
    person *myfirst;
public:
    AddressBook();//初始化
    AddressBook(char npname[],char nptelnb[],char nptype[],char npemail[],int npid);//创建对象
    ~AddressBook();
    void Show_Link();//查看
    void Add_Link();//添加
    void Call_Link();//拨号
    void Edi_Link();//修改
    void Del_Link();//删除
    void Log_Out();//退出
    void output(char seltype[60]);//按类打印


};
AddressBook::AddressBook()
{
    myfirst = NULL;
}
AddressBook::AddressBook(char npname[],char nptelnb[],char nptype[],char npemail[],int npid)
{
    myfirst = new person(npname,nptelnb,nptype,npemail,npid);
}
AddressBook::~AddressBook()
{
    person *next = myfirst,*temp;
    while(next != NULL)
    {
        temp = next;
        next = next->getnext();
        delete temp;

    }
    myfirst = NULL;
}
void AddressBook::Add_Link()
{


    int adid,tpcode;
    int i = 0;
    ifstream in("AddressBook_data.txt");
    string line;
    while(getline(in,line))
    {
        i++;
    }
    if(i == 15)
    {
        cout<<"储存空间已满！"<<endl;
        return;
    }
    char adname[60],adtelnb[20],adtype[60],ademail[60],flag[5];


    strcpy(flag,"y\0");
    while(strcmp(flag,"y\0") == 0)
    {

        person *p = myfirst;
        cout<<"联系人姓名:"<<endl;
        cin>>adname;
        cout<<"电话:"<<endl;
        cin>>adtelnb;
        while(1)
        {

            cout<<"选择分类[1]办公类[2]个人类[3]商务类:"<<endl;
            cin>>tpcode;
            if(tpcode > 3 || tpcode < 1)
            {
                cout<<"输入错误！重新输入..."<<endl;
                continue;
            }
            switch(tpcode)
            {
            case 1:
                strcpy(adtype,"办公类");
                break;
            case 2:
                strcpy(adtype,"个人类");
                break;
            case 3:
                strcpy(adtype,"商务类");
                break;
            }
            break;

        }
        cout<<"E-mail:"<<endl;
        cin>>ademail;
        i = i+1;
        adid = i;
        if(p == NULL)
        {
            myfirst = new person(adname,adtelnb,adtype,ademail,adid);
        }
        else
        {
            while(p->getnext() != NULL)
            {
                p = p->getnext();
            }
            p ->  setnext(new person(adname,adtelnb,adtype,ademail,adid,p->getnext())) ;

        }
        cout<<"是【y】否【n】继续添加联系人？"<<endl;
        cin>>flag;

    }
    person *psave = myfirst;
    std::ofstream fout("AddressBook_data.txt",ios::app);//在文件末尾追加
    while(psave)
    {
        fout<<psave->getid()<<"\t"<<psave->getname()<<"\t"<<psave->gettelnb()<<"\t"<<psave->gettype()<<"\t"<<psave->getemail()<<"\n";
        psave = psave->getnext();
    }
    fout.close();
    cout<<"保存成功！"<<endl;


}
void AddressBook::output(char seltype[60])
{
    person *head;
    head = myfirst;
    int i = 0;
    cout<<setw(10)<<"ID"<<setw(20)<<"姓名"<<setw(20)<<"电话"<<setw(20)<<"分类"<<setw(20)<<"E-mail"<<endl;
    cout<<"______________________________________________________________________________"<<endl;
    cout<<endl;
    while(head)
    {
        if(strcmp(head->gettype(), seltype)==0)
        {
            cout<<setw(10)<<head->getid()<<setw(20)<<head->getname()<<setw(20)<<head->gettelnb()<<setw(20)<<head->gettype()<<setw(20)<<head->getemail()<<endl;
            //cout<<head->getid()<<head->getname()<<head->gettelnb()<<head->gettype()<<head->getemail()<<endl;
            i = i+1;
        }
        head = head -> getnext();
    }
    if(i == 0)
    {
        cout<<seltype<<"暂无数据！"<<endl;
    }
    else
    {
        cout<<"__________"<<endl;
        cout<<seltype<<"-"<<i<<"-"<<"人"<<endl;
    }


}
void AddressBook::Show_Link()
{
    while(1)
    {
        //分类菜单
        cout<<"     +-----------------------------------+"<<endl;
        cout<<"     |              [菜单]               |"<<endl;
        cout<<"     |                                   |"<<endl;
        cout<<"     |              * 1.办公类           |"<<endl;
        cout<<"     |              * 2.个人类           |"<<endl;
        cout<<"     |              * 3.商务类           |"<<endl;
        cout<<"     |              * 0.退出             |"<<endl;
        cout<<"     +-----------------------------------+"<<endl;
        int i;
        char stype[60];
        cout<<".";
        cin>>i;

        switch(i)
        {
        case 1:
            strcpy(stype,"办公类");
            output(stype);
            break;
        case 2:
            strcpy(stype,"个人类");
            output(stype);
            break;
        case 3:
            strcpy(stype,"商务类");
            output(stype);
            break;

        case(0):
            return;
        default:
            cout<<"输入有误！请重新输入..."<<endl;
            continue;
        }
    }


}











int main()
{
    AddressBook call;
    cout<<setiosflags(ios::left);
    while(1)
    {
        //主菜单
        cout<<"     +--------------------------------------------------+"<<endl;
        cout<<"     |              [通讯录管理系统]                    |"<<endl;
        cout<<"     |                                                  |"<<endl;
        cout<<"     |              * 1.查看联系人                      |"<<endl;
        cout<<"     |              * 2.添加联系人                      |"<<endl;
        cout<<"     |              * 3.拨号                            |"<<endl;
        cout<<"     |              * 4.修改                            |"<<endl;
        cout<<"     |              * 5.删除                            |"<<endl;
        cout<<"     |              * 0.退出                            |"<<endl;
        cout<<"     +--------------------------------------------------+"<<endl;
        int i;
        cout<<".";
        cin>>i;
        switch(i)
        {
        case(1):
            call.Show_Link();
            break;
        case(2):
            call.Add_Link();
            break;
        case(3):
            //Call_Link();
            break;
        case(4):
            //Edi_Link();
            break;
        case(5):
            //Del_Link();
            break;
        case(0):
            return 0;
        default:
            cout<<"输入有误！请重新输入..."<<endl;
            continue;
        }
    }
    return 0;

}


