#include <iostream>
#include <list>
#include <forward_list>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>

using namespace std;

// 圖書結構
struct Book {
    string title;  // 書名
    string author; // 作者
    string id;     // 圖書編號

    // 建構子
    Book(string t, string a, string i) : title(t), author(a), id(i) {}
};

// 借閱者結構
struct Borrower {
    string name;                 // 借閱者姓名
    vector<string> borrowedBooks; // 借閱的圖書編號列表

    // 建構子
    Borrower(string n, vector<string> b) : name(n), borrowedBooks(b) {}
};

// 驗證圖書編號格式
bool isValidBookId(const string& id) {
    regex pattern("^[A-Za-z][0-9]{4}$"); // 正則表達式：首字母為英文字母，後四位為數字
    return regex_match(id, pattern);      // 驗證
}

// 列印所有圖書
void printBooks(const list<Book>& books) {
    for (const auto& book : books) {
        cout << "書名: " << book.title << ", 作者: " << book.author << ", 圖書編號: " << book.id << endl;
    }
}

// 列印所有借閱者
void printBorrowers(const forward_list<Borrower>& borrowers) {
    for (const auto& borrower : borrowers) {
        cout << "借閱者姓名: " << borrower.name << ", 借閱的圖書編號: ";
        for (const auto& id : borrower.borrowedBooks) {
            cout << id << " ";
        }
        cout << endl;
    }
}

int main() {
    list<Book> books;                 // 管理圖書的雙向鏈結串列
    forward_list<Borrower> borrowers; // 管理借閱者的單向鏈結串列
    //Head ->[Prev:nullptr, Data : {title: "紅樓夢", author : "曹雪芹", id : "A1234"}, Next : Node2] < ->[Prev:Node1, Data : {title: "西遊記", author : "吳承恩", id : "B2345"}, Next : nullptr] < -Tail
    // 測試圖書資料
   // books[["紅樓夢", "曹雪芹", "A1234"],["西遊記", "吳承恩", "B2345"]]
    books.emplace_back("紅樓夢", "曹雪芹", "A1234");
    books.emplace_back("西遊記", "吳承恩", "B2345");
    books.emplace_back("水滸傳", "施耐庵", "B3456");
    books.emplace_back("三國演義", "羅貫中", "C4567");
    books.emplace_back("金瓶梅", "蘭陵笑笑生", "C5678");
    books.emplace_back("聊齋志異", "蒲松齡", "D6789");
    books.emplace_back("儒林外史", "吳敬梓", "D7890");
    books.emplace_back("封神演義", "許仲琳", "E8901");
    books.emplace_back("鏡花緣", "李汝珍", "E9012");
    books.emplace_back("老殘遊記", "劉鶚", "F0123");

    // 測試借閱者資料
    borrowers.emplace_front("小明", vector<string>{"A1234", "B2345"});
    borrowers.emplace_front("小華", vector<string>{"C4567"});
    borrowers.emplace_front("小美", vector<string>{"D6789", "E8901"});
    borrowers.emplace_front("小強", vector<string>{"F0123"});
    borrowers.emplace_front("小麗", vector<string>{"B3456", "C5678"});

    int choice; // 用戶選擇的操作
    do {
        // 顯示操作選單
        cout << "1. 添加新圖書\n2. 刪除指定圖書\n3. 搜索指定圖書\n4. 列出所有圖書\n";
        cout << "5. 添加新借閱者\n6. 刪除指定借閱者\n7. 搜索指定借閱者\n8. 列出所有借閱者\n";
        cout << "0. 退出\n請選擇操作: ";
        cin >> choice;

        switch (choice) {
        case 1: { // 添加新圖書
            string title, author, id;
            cout << "輸入書名: ";
            cin >> title;
            cout << "輸入作者: ";
            cin >> author;

            // 驗證圖書編號格式
            do {
                cout << "輸入圖書編號: ";
                cin >> id;
                if (!isValidBookId(id)) {
                    cout << "圖書編號格式不正確，請重新輸入！\n";
                }
            } while (!isValidBookId(id));

            books.emplace_back(title, author, id); // 將新圖書添加到串列
            break;
        }
        case 2: { // 刪除指定圖書
            string id;
            cout << "輸入要刪除的圖書編號: ";
            cin >> id;

            // 使用 remove_if 刪除指定編號的圖書
            auto it = remove_if(books.begin(), books.end(),
                [&id](const Book& book) { return book.id == id; }); //用迴圈找尋id並確認id是否在list裡
            if (it != books.end()) {
                books.erase(it, books.end()); // 實際刪除元素
                cout << "刪除成功！\n";
            }
            else {
                cout << "找不到指定的圖書編號！\n";
            }
            break;
        }
        case 3: { // 搜索指定圖書
            string id;
            cout << "輸入要搜索的圖書編號: ";
            cin >> id;

            // 使用 find_if 搜索指定編號的圖書
            auto it = find_if(books.begin(), books.end(),
                [&id](const Book& book) { return book.id == id; });
            if (it != books.end()) {
                cout << "找到圖書：\n書名: " << it->title << ", 作者: " << it->author << ", 圖書編號: " << it->id << endl;
            }
            else {
                cout << "找不到指定的圖書編號！\n";
            }
            break;
        }
        case 4: // 列出所有圖書
            cout << "所有圖書：\n";
            printBooks(books);
            break;
        case 5: { // 添加新借閱者
            string name;
            vector<string> borrowedIds;
            cout << "輸入借閱者姓名: ";
            cin >> name;

            string id;
            cout << "輸入借閱的圖書編號（輸入空白結束）: ";
            while (cin >> id && !id.empty()) {
                borrowedIds.push_back(id); // 將借閱的圖書編號添加到列表
            }

            borrowers.emplace_front(name, borrowedIds); // 添加新借閱者
            break;
        }
        case 6: { // 刪除指定借閱者
            string name;
            cout << "輸入要刪除的借閱者姓名: ";
            cin >> name;

            // 使用 remove_if 刪除指定姓名的借閱者
            auto it = remove_if(borrowers.begin(), borrowers.end(),
                [&name](const Borrower& borrower) { return borrower.name == name; });
            if (it != borrowers.end()) {
                borrowers.erase_after(it); // 實際刪除元素
                cout << "刪除成功！\n";
            }
            else {
                cout << "找不到指定的借閱者姓名！\n";
            }
            break;
        }
        case 7: { // 搜索指定借閱者
            string name;
            cout << "輸入要搜索的借閱者姓名: ";
            cin >> name;
            bool found = false;
            for (const auto& borrower : borrowers) {
                auto lastIt = borrowers.begin();
                if (borrower.name == name) {
                    // 找到借閱者                  
                    cout << "找到借閱者：\n借閱者姓名: " << borrower.name << ", 借閱的圖書編號: ";
                    for (const auto& id : borrower.borrowedBooks) {
                        cout << id << " ";
                    }
                    cout << endl;
                    found = true;
                    break;
                }                                  
            }
            if (!found)
            {
                cout << "找不到指定的借閱者姓名！\n";
            }
            break;
        }
        case 8: // 列出所有借閱者
            cout << "所有借閱者：\n";
            printBorrowers(borrowers);
            break;
        case 0: // 退出程式
            cout << "退出程式。\n";
            break;
        default: // 處理無效選擇
            cout << "無效選擇，請重新選擇！\n";
        }

        cin.clear(); // 清除輸入錯誤狀態
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除輸入緩衝區
    } while (choice != 0); // 繼續直到用戶選擇退出

    return 0;
}
