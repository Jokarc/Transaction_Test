//
// Created by Jokarc on 2021/6/2.
//

#ifndef TRANSACTION_TEST_SHOPCART_H
#define TRANSACTION_TEST_SHOPCART_H
#include "Product.h"
#include <vector>
#include <set>
struct OrderInfoToChange {
    char filename[50] = "";
    int linenum;
    int thisproductNum;
    string linedata;
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
    int GenerateOrder();
    int SettleOrder();
    int CancelOrder();
    int OrderExist() {return needToPay;}
    double HowMuch() {return priceToPay;}
    void Show();
    void Clear();
    void AddProduct();
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
/**********************************************************
函数：AddProduct
形参：
类型：void
作用：添加新商品进购物车
返回：
**********************************************************/
void ShopCart::AddProduct() {

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
    cout << "订单生成中" << endl;
    set<Product>::iterator iter;
    for (iter = ProductList.begin(); iter != ProductList.end(); iter++) {
        Product Store;
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
                myorder[AddedNum].linenum = line;
                myorder[AddedNum].linedata = to_string(StoreNum-pres.ShowNum());
                myorder[AddedNum].thisproductNum = pres.ShowNum();
                cout << "商品" << pres.ShowName() << "成功添加" << endl;
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
}
#endif //TRANSACTION_TEST_SHOPCART_H
