//
// Created by Jokarc on 2021/6/2.
//

#ifndef TRANSACTION_TEST_SHOPCART_H
#define TRANSACTION_TEST_SHOPCART_H
#include "Product.h"
#include "io.h"
#include <vector>
#include <set>
struct OrderInfoToChange {
    char filename[50] = "";
    int linenum;
    int thisproductNum;
    double pri;
    string thisName;
    string linedata;
    string MerName;
};
class ShopCart {
protected:
    BasicOp Operation;
    int AddedNum;
    int needToPay;
    double priceToPay;
    set <Product> ProductList;
    OrderInfoToChange myorder[100];
public:
    ShopCart() {
        AddedNum = 0;
        needToPay = 0;
        priceToPay = 0;
    }
    ~ShopCart() {
        if (needToPay) CancelOrder();
    }
    int GenerateOrder();
    int SettleOrder();
    int CancelOrder();
    int OrderExist() {return needToPay;}
    double HowMuch() {return priceToPay;}
    void Show();
    void Clear();
    void AddProduct();
    void ManageShopCartProduct();
    void ShowOrder();
    void OutProduct(string name, string price, string num, string dis, string descrip, string Mer);
};
/**********************************************************
函数：ShopCat::Show
形参：
类型：void
作用：查看购物车内容
返回：
**********************************************************/
void ShopCart::Show() {
    if (ProductList.empty()) {
        cout << "购物车为空" << endl;
    }
    double totprice = 0;
    set<Product>::iterator iter;
    for (iter = ProductList.begin(); iter != ProductList.end(); iter++) {
        Product pres = *iter;
        cout << "*------------------------*" << endl;
        cout << "商品名称：" << pres.ShowName() << endl;
        cout << "实时单价：" << pres.getPrice() << endl;
        cout << "加购数量：" << pres.ShowNum() << endl;
        cout << "商品描述：" << pres.ShowProductDescription() << endl;
        cout << "所属商家：" << pres.ShowOwner() << endl;
        totprice += pres.getPrice() * pres.ShowNum();
    }
    cout << "*------------------------*" << endl;
    cout << "总价" << totprice << endl;
    cout << "*------------------------*" << endl;
}
/**********************************************************
函数：Clear
形参：
类型：void
作用：清空购物车
返回：
**********************************************************/
void ShopCart::Clear() {
    cout << "*------------------------*" << endl;
    cout << "确认要清空吗？" << endl;
    cout << "1：是：" << endl;
    cout << "2：否："  << endl;
    cout << "*------------------------*" << endl;
    int op = Operation.checkOp();
    if (op == 1) ProductList.clear();
    if (op == 2) return ;
}
void ShopCart::OutProduct(string name, string price, string num, string dis, string descrip, string Mer) {
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
函数：AddProduct
形参：
类型：void
作用：添加新商品进购物车
返回：
**********************************************************/
void ShopCart::AddProduct() {
    cout << "请输入要查找的商品名称" << endl;
    string namefind;
    getline(cin, namefind);
    int namefindok = 0;
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
            cout << "can't find " << filename << " when ShopCart AddProduct." << endl;
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
            if (name == namefind){
                namefindok = 1;
                OutProduct(name,price,num,dis,descrip,Mer);
                break;
            }
        }
        FileIn.close();
    } while (!_findnext(handle, &fileinfo));
    _findclose(handle);
    //*************
    if (!namefindok) cout << "您要找的商品不存在" << endl;
    else {
        cout << "以上商品均为您要找的商品，请输入您要加购的商品所属商家" << endl;
        string MerchantName;
        getline(cin, MerchantName);
        char FileName[50] = "../Data/ProductData/";
        Operation.StrCat(FileName, MerchantName);
        strcat(FileName, "_Products.txt");
        ifstream FileIn(FileName, ios::in);
        if (!FileIn) {
            cout << "can't find " << FileName << " when AddProduct with MerchantName." << endl;
            return ;
        }
        string name, kind, price, num, dis, descrip;
        getline(FileIn, name);
        while (getline(FileIn, name)) {
            getline(FileIn, kind);
            getline(FileIn, price);
            getline(FileIn, num);
            getline(FileIn, dis);
            getline(FileIn, descrip);
            if (name == namefind){
                set<Product>::iterator iter;
                for (iter = ProductList.begin(); iter != ProductList.end(); iter++) {
                    Product p = *iter;
                    if (p.ShowName() == name && p.ShowOwner() == MerchantName) {
                        cout << "商品已存在购物车，可以返回修改数量" << endl;
                        return ;
                    }
                }
                cout << "已找到商品，请输入加购数量，正整数" << endl;
                string s;
                getline(cin, s);
                int x = Operation.checkInt(s);
                if (!x) {
                    cout << "输入不合法" << endl;
                    return ;
                }
                x = (int) Operation.Converse(s);
                if (x < 0) {
                    cout << "请输入正数" << endl;
                    return ;
                }
                double pri = Operation.Converse(price);
                pri *= Operation.Converse(dis);
                Product pro = Product(name,kind, pri,x,
                                      Operation.Converse(dis),descrip, MerchantName);
                ProductList.insert(pro);
                cout << "已加购" << endl;
                break;
            }
        }
    }
}
/**********************************************************
函数：ManageShopCartProduct
形参：
类型：void
作用：管理购物车商品
返回：
**********************************************************/
void ShopCart::ManageShopCartProduct() {
    string namefind, Merfind;
    int findok = 0;
    cout << "请输入要管理的商品名称" << endl;
    getline(cin, namefind);
    cout << "请输入要管理的商品所属商家" << endl;
    getline(cin, Merfind);
    set<Product>::iterator iter;
    for (iter = ProductList.begin(); iter != ProductList.end(); iter++) {
        Product temp = *iter;
        if (temp.ShowName() == namefind && temp.ShowOwner() == Merfind) {
            findok = 1;
            while (1) {
                cout << "*----------------------*" << endl;
                cout << "1：调整数量" << endl;
                cout << "2：从购物车移除" << endl;
                cout << "-1：返回" << endl;
                cout << "*----------------------*" << endl;
                int op = Operation.checkOp();
                if (op == -1) break;
                if (op == 1) {
                    cout << "请输入新数量，正整数" << endl;
                    string s;
                    getline(cin, s);
                    int x = Operation.checkInt(s);
                    if (!x) {
                        cout << "输入不合法" << endl;
                        continue;
                    }
                    x = (int) Operation.Converse(s);
                    if (x <= 0) {
                        cout << "请输入正数" << endl;
                        continue;
                    }
                    Product np = temp;
                    np.setNum(x);
                    ProductList.erase(iter);
                    ProductList.insert(np);
                    return ;
                }
                if (op == 2) {
                    ProductList.erase(iter);

                }
            }
        }
    }
    if (!findok) {
        cout << "未加购来自" << Merfind << "的商品" << namefind << endl;
    }
}
/**********************************************************
函数：ShowOrder
形参：
类型：void
作用：显示订单
返回：
**********************************************************/
void ShopCart::ShowOrder() {
    if (!needToPay) {
        cout << "未生成订单" << endl;
        return ;
    }
    double totpri = 0;
    for (int i = 1; i <= AddedNum; i++) {
        totpri += myorder[i].pri * myorder[i].thisproductNum;
        cout << "*------------------------*" << endl;
        cout << "商品名称：" << myorder[i].thisName << endl;
        cout << "商品单价：" << myorder[i].pri << endl;
        cout << "购买数量：" << myorder[i].thisproductNum << endl;
        cout << "所属商家：" << myorder[i].MerName << endl;
    }
    cout << "*------------------------*" << endl;
    cout << "需支付" << totpri << endl;
}
/**********************************************************
函数：GenerateOrder
形参：
类型：int
作用：将当前购物车商品生成订单
返回：-1，生成订单失败(库存不足，无商品)。 1，成功
**********************************************************/
int ShopCart::GenerateOrder() {
    AddedNum = 0; priceToPay = 0;
    if (ProductList.empty()) {
        cout << "购物车为空" << endl;
        return -1;
    }
    if (needToPay) {
        cout << "您还有一笔订单未支付" << endl;
        return -1;
    }
    cout << "订单生成中" << endl;
    set<Product>::iterator iter;
    for (iter = ProductList.begin(); iter != ProductList.end(); iter++) {
        Product pres = *iter;
        char FileName[50] = "../Data/ProductData/";
        Operation.StrCat(FileName, pres.ShowOwner());
        strcat(FileName, "_Products.txt");
        ifstream FileIn(FileName, ios::in);
        if (!FileIn) {
            cout << "can't find " << FileName << " when GenerateOrder." << endl;
            return -1;
        }
        int existFlag(0);
        string temp, temp2, temp3, temp4, temp5, temp6;
        getline(FileIn, temp);
        int line = -1;
        while (getline(FileIn, temp)) {     //Name
            getline(FileIn, temp2);         //Kind
            getline(FileIn, temp3);         //Price
            getline(FileIn, temp4);         //Num
            getline(FileIn, temp5);         //Discount
            getline(FileIn, temp6);         //Description
            line += 6;
            if (temp == pres.ShowName()) {
                int StoreNum = (int)Operation.Converse(temp4);
                if (pres.ShowNum() > StoreNum) {
                    cout << "ERROR，商家" << pres.ShowOwner() << "的商品" << pres.ShowName() << "库存不足生成该订单" << endl;
                    return -1;
                }
                existFlag = 1;
                AddedNum++;
                strcpy(myorder[AddedNum].filename, FileName);
                myorder[AddedNum].thisName = temp;
                myorder[AddedNum].pri = Operation.Converse(temp3) * Operation.Converse(temp5);
                myorder[AddedNum].MerName = pres.ShowOwner();
                myorder[AddedNum].linenum = line;
                myorder[AddedNum].linedata = to_string(StoreNum-pres.ShowNum());
                myorder[AddedNum].thisproductNum = pres.ShowNum();
                cout << "商品" << pres.ShowName() << "成功添加" << endl;
                Operation.ModifyLineData(FileName, line, to_string(StoreNum-pres.ShowNum()));
                priceToPay += Operation.Converse(temp3) * Operation.Converse(temp5);
            }
        }
        FileIn.close();
        if (!existFlag) {
            cout << "商品" << pres.ShowName() << "在" << pres.ShowOwner() << "店铺中不存在" << endl;
            return -1;
        }
    }
    if (AddedNum == ProductList.size()) {
        needToPay = 1;
        ProductList.clear();
        return 1;
    }
    return -1;
}
/**********************************************************
函数：SettleOrder
形参：
类型：int
作用：结算订单
返回：-1，失败(无需结算)，1，成功
**********************************************************/
int ShopCart::SettleOrder() {
    if (!needToPay) return -1;
    for (int i = 1; i <= AddedNum; i++) {
        string MerName = myorder[i].MerName;
        char filename[50] = "../Data/UserData/UserBalance.txt";
        ifstream FileIn(filename, ios::in);
        string temp;
        string temp2;
        int line = 0;
        while (getline(FileIn, temp)) {
            getline(FileIn, temp2);
            line += 2;
            if (temp == MerName) {
                double p = Operation.Converse(temp2);
                p += myorder[i].pri * myorder[i].thisproductNum;
                Operation.ModifyLineData(filename, line, to_string(p));
            }
        }
    }
    needToPay = 0; AddedNum = 0;
    return 1;
}
/**********************************************************
函数：CancelOrder
形参：
类型：int
作用：取消订单，将冻结库存恢复至商家仓库
返回：-1，失败，1，成功
**********************************************************/
int ShopCart::CancelOrder() {
    if (!needToPay) {
        cout << "未生成订单" << endl;
        return -1;
    }
    for (int i = 1; i <= AddedNum; i++) {
        ifstream FileIn(myorder[i].filename, ios::in);
        if (!FileIn) {
            cout << "can't find " << myorder[i].filename << " when CancelOrder." << endl;
            return -1;
        }
        string temp, temp2, temp3, temp4, temp5, temp6;
        getline(FileIn, temp);
        int line = -1;
        while (getline(FileIn, temp)) {     //Name
            getline(FileIn, temp2);         //Kind
            getline(FileIn, temp3);         //Price
            getline(FileIn, temp4);         //Num
            getline(FileIn, temp5);         //Discount
            getline(FileIn, temp6);         //Description
            line += 6;
            int StoreNum = (int) Operation.Converse(temp4);
            Operation.ModifyLineData(myorder[i].filename, line, to_string(myorder[i].thisproductNum + StoreNum));
        }
        FileIn.close();
    }
    return 1;
}
#endif //TRANSACTION_TEST_SHOPCART_H
