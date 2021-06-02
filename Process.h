//
// Created by Jokarc on 2021/5/25.
//

#ifndef USERANDPRODUCT_TEST_PROCESS_H
#define USERANDPRODUCT_TEST_PROCESS_H
#include <string>
#include "io.h"
#include "BasicOp.h"
#include "Product.h"
using std::string;

class Process {
private:
    BasicOp Operation;
public:
    Process(){}
    ~Process(){}
    void TraverseProductFile();
    void PrintOpList_1(User *CurrentUser);
    void PrintOpList_2(User *CurrentUser);
    void PrintOpList_3(User *CurrentUser);
    void Register(User *CurrentUser);
    void OutProduct(string,string,string,string,string,string);
    void work(User *CurrentUser, int& Logged, Customer &CurrentCustomer, Merchant &CurrentMerchant);
    void ShowProductForGuest(User *CurrentUser, int &Logged, Customer &CurrentCustomer, Merchant &CurrentMerchant);
    int Login(User *CurrentUser, int& Logged, Customer &CurrentCustomer, Merchant &CurrentMerchant);
    int UserLogin(User *CurrentUser, string usrname, string password);
};

/**********************************************************
函数：PrintOpList_1
形参：User *CurrentUser
类型：void
作用：未登录的初始界面
返回：
**********************************************************/
void Process::PrintOpList_1(User *CurrentUser) {
    cout << "*----------------------*" << endl;
    cout << "1：我要登录" << endl;
    cout << "2：我要注册" << endl;
    cout << "3：看看商品" << endl;
    cout << "*----------------------*" << endl;
}
/**********************************************************
函数：PrintOpList_2
形参：User*CurrentUser
类型：void
作用：顾客登录后界面
返回：
**********************************************************/
void Process::PrintOpList_2(User *CurrentUser) {
    cout << "*----------------------*" << endl;
    cout << "1：退出登录" << endl;
    cout << "2：查询余额" << endl;
    cout << "3：看看商品" << endl;
    cout << "4：我叫什么" << endl;
    cout << "5：账户类型" << endl;
    cout << "6：我要充钱" << endl;
    cout << "7：修改密码" << endl;
    cout << "8：我要提现" << endl;
    cout << "9：购物车和订单" << endl;
    cout << "0：关闭程序" << endl;
    cout << "*----------------------*" << endl;
}
/**********************************************************
函数：PrintOpList_3
形参：User*CurrentUser
类型：void
作用：商家登录后界面
返回：
**********************************************************/
void Process::PrintOpList_3(User *CurrentUser) {
    cout << "*----------------------*" << endl;
    cout << "1：退出登录" << endl;
    cout << "2：查询余额" << endl;
    cout << "3：看看商品" << endl;
    cout << "4：我叫什么" << endl;
    cout << "5：账户类型" << endl;
    cout << "6：我要充钱" << endl;
    cout << "7：修改密码" << endl;
    cout << "8：我要提现" << endl;
    cout << "9：管理商品" << endl;
    cout << "0：关闭程序" << endl;
    cout << "*----------------------*" << endl;
}
/**********************************************************
函数：Register
形参：User* CurrentUser
类型：void
作用：选择注册类型，输入op，用户名，密码，调用UserRegister进行注册
返回：
**********************************************************/
void Process::Register(User *CurrentUser) {
    string cus = "Customer";
    string mer = "Merchant";
    cout << "*----------------------*" << endl;
    cout << "1：注册为顾客" << endl;
    cout << "2：注册为商家" << endl;
    cout << "用户名格式要求：以字母开头，仅能由字母，数字以及下划线构成，至少4位" << endl;
    cout << "密码格式要求：同时有字母以及数字，至少6位，不能有空格" << endl;
    cout << "*----------------------*" << endl;
    //int op; cin >> op;
    int op = Operation.checkOp();
    if (op == -1) {
        cout << "输入不合法，请输入数字" << endl;
    }
    if (op != 1 && op != 2) return ;
    cout << "请分行输入用户名及密码" << endl;
    string name, word;
    //getchar();
    while (1) {

        getline(cin, name);
        getline(cin, word);
        if (CurrentUser->UserRegister(name, word, op == 1 ? (cus) : (mer)))
            break;
        else {
            cout << "ERROR" << endl;
        }
    }
}
/**********************************************************
函数：UserLogin
形参：User *CurrentUser，string usrname，string password
类型：int
作用：用户登录，在UserInfo.txt中寻找用户名以及相应密码，判断是否能登录
返回：0，用户名或密码不正确
     1，登录为客户
     2，登录为商家
    -1，找不到文件
**********************************************************/
int Process::UserLogin(User *CurrentUser, string usrname, string password) {
    ifstream FileIn("../Data/UserData/UserInfo.txt", ios::in);
    string temp, temp2, temp3;
    string cus = "Customer";
    string mer = "Merchant";
    bool UserNameExist = false;
    bool pswdCorrect = false;
    if (!FileIn) {
        cout << "can't find UserInfo.txt when UserLogin." << endl;
        return -1;
    }
    while (getline(FileIn, temp)) {
        getline(FileIn, temp2);
        getline(FileIn, temp3);
        if (usrname == temp){
            UserNameExist = 1;
            if (password == temp2){
                pswdCorrect = 1;
                break;
            }
        }
    }
    if (!UserNameExist || (UserNameExist && !pswdCorrect))
        cout << "UserName Or Password Error." << endl;
    if (UserNameExist && pswdCorrect) {
        cout << "Login Success." << endl;
        cout << "Your user type is " << temp3 << endl;
    }
    FileIn.close();
    if (UserNameExist && pswdCorrect && temp3 == cus) return 1;
    if (UserNameExist && pswdCorrect && temp3 == mer) return 2;
    return 0;
}
/**********************************************************
函数：Login
形参：User *CurrentUser，int &Logged，Customer &CurrentCustomer，Merchant &CurrentMerchant
类型：int
作用：输入用户名以及密码，调用UserLogin函数判断是否能登录，根据类型不同给不同对象初始化
返回：1，登录为顾客
     2，登录为商家
**********************************************************/
int Process::Login(User *CurrentUser, int& Logged, Customer &CurrentCustomer, Merchant &CurrentMerchant) {
    cout << "请分行输入用户名及密码" << endl;
    string name, word;
    User* temp = NULL;
    while (1) {
        cin >> name;
        cin >> word;
        getchar();
        int flag = UserLogin(CurrentUser, name, word);
        Logged = flag;
        if (flag == 1) {
            CurrentCustomer.setInfo(name,word);
            CurrentCustomer.setBalance(CurrentCustomer.findBalance());
            return 1;
        }
        if (flag == 2) {
            CurrentMerchant.setInfo(name, word);
            CurrentMerchant.setBalance(CurrentMerchant.findBalance());
            return 2;
        }
        if (Logged) break;
    }
    return 0;
}
/**********************************************************
函数：ShowProductForGuest
形参：User *CurrentUser，int &Logged，Customer &CurrentCustomer，Merchant &CurrentMerchant
类型：void
作用：为游客用户提供商品的查看
返回：
**********************************************************/
void Process::ShowProductForGuest(User *CurrentUser, int &Logged, Customer &CurrentCustomer, Merchant &CurrentMerchant) {

}
/**********************************************************
函数：work
形参：User *CurrentUser，int &Logged，Customer &CurrentCustomer，Merchant &CurrentMerchant
类型：void
作用：维持初始界面，根据Logged值不同，打印不同界面
返回：
**********************************************************/
void Process::work(User *CurrentUser, int& Logged, Customer &CurrentCustomer, Merchant &CurrentMerchant) {
    //int op = 0;
    while (1) {
        if (!Logged) {
            PrintOpList_1(CurrentUser);

            //scanf ("%d", &op);
            int op = Operation.checkOp();
            if (op == -1) {
                cout << "输入不合法，请输入数字" << endl;
            }
            if (op == 1) {
                int Type = Login(CurrentUser, Logged, CurrentCustomer, CurrentMerchant);
                if (Type == 1) CurrentUser = &CurrentCustomer;
                if (Type == 2) CurrentUser = &CurrentMerchant;
            }
            if (op == 2) Register(CurrentUser);
            if (op == 3) TraverseProductFile();
        } else {
            if (Logged == 1) PrintOpList_2(CurrentUser);
            if (Logged == 2) PrintOpList_3(CurrentUser);
            int op = Operation.checkOp();
            if (op == -1) {
                cout << "输入不合法，请输入数字" << endl;
            }
            if (op == 0) break;
            if (op == 1) CurrentUser->UserLogOut(Logged);
            if (op == 2) cout << "当前余额：" << CurrentUser -> getAccountBalance() << endl;
            if (op == 3) TraverseProductFile();
            if (op == 4) cout << "您的用户名为：" << CurrentUser -> getUserName() << endl;
            if (op == 5) {
                if (Logged == 1) CurrentCustomer.getUserType();
                if (Logged == 2) CurrentMerchant.getUserType();
            }
            if (op == 6) CurrentUser -> UserRecharge(1);
            if (op == 7) CurrentUser -> UserChangePswd();
            if (op == 8) CurrentUser -> UserRecharge(-1);
            if (op == 9 && Logged == 2) {
                CurrentMerchant.ManageProduct();
            }
            if (op == 9 && Logged == 1) {
                CurrentCustomer.Shop();
            }
        }
    }
}
/**********************************************************
函数：OutProduct
形参：
类型：void
作用：输出商品信息
返回：
**********************************************************/
void Process::OutProduct(string name, string price, string num, string dis, string descrip, string Mer) {
    cout << "商品名称：" << name << endl;
    cout << "商品定价：" << price << endl;
    cout << "商品库存：" << num << endl;
    double k = Operation.Converse(dis);
    double newPrice = k * Operation.Converse(price);
    double koff = 1-k;
    cout << "折扣力度：减" << koff * 100 << "%，实时价格：" << newPrice << endl;
    cout << "商品描述：" << descrip << endl;
    cout << "在售商家：" << Mer << endl;
    cout << "*------------------------*" << endl;
}
/**********************************************************
函数：TraverseProductFile
形参：
类型：void
作用：遍历产品文件，可以按需输出
返回：
**********************************************************/
void Process::TraverseProductFile() {
    cout << "*----------------------*" << endl;
    cout << "1：查看书本类商品" << endl;
    cout << "2：查看衣服类商品" << endl;
    cout << "3：查看食物类商品" << endl;
    cout << "4：以名称查看商品" << endl;
    cout << "*----------------------*" << endl;
    string namefind;
    int op = Operation.checkOp();
    if (op == -1) {
        cout << "输入不合法" << endl;
        return ;
    }
    cout << "*----------------------*" << endl;
    if (op == 4) {
        cout << "请输入要查找的商品名称" << endl;
        getline(cin, namefind);
    }
    int namefindok = 0;
    string book = "Book";
    string clothes = "Clothes";
    string food = "Food";
    string inPath = "../Data/ProductData/*.txt";
    //***********
    long handle;
    struct _finddata_t fileinfo;
    handle = _findfirst(inPath.c_str(), &fileinfo);
    if (handle == -1) return ;
    do {
        char filename[100] = "../Data/ProductData/";
        strcat(filename, fileinfo.name);
        ifstream FileIn(filename, ios::in);
        if (!FileIn) {
            cout << "can't find " << filename << " when TraverseProductFile." << endl;
            continue;
        }
        int line = -4;
        string name, kind, price, num, dis, descrip,Mer = "", Mer1="";
        for (int i = 0; fileinfo.name[i] != '.'; i++) Mer1 += fileinfo.name[i];
        int l = Mer1.length();
        Mer = Mer1.substr(0, l-9);
        getline(FileIn, name);
        while (getline(FileIn, name)) {
            getline(FileIn, kind);
            getline(FileIn, price);
            getline(FileIn, num);
            getline(FileIn, dis);
            getline(FileIn, descrip);
            line += 6;
            if (op == 1 && kind == book)
                OutProduct(name,price,num,dis,descrip,Mer);
            if (op == 2 && kind == clothes)
                OutProduct(name,price,num,dis,descrip,Mer);
            if (op == 3 && kind == food)
                OutProduct(name,price,num,dis,descrip,Mer);
            if (name == namefind && op == 4){
                namefindok = 1;
                OutProduct(name,price,num,dis,descrip,Mer);
                break;
            }
        }
        FileIn.close();
    } while (!_findnext(handle, &fileinfo));
    //*************
    if (op == 4 && !namefindok) cout << "您要找的商品不存在" << endl;
    _findclose(handle);
}
#endif //USERANDPRODUCT_TEST_PROCESS_H
