#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
class CGraph {
   private:
    string type;
    string color;
    int lineWidth;

   public:
    CGraph() {
        type = "None";
        color = "black";
        lineWidth = 1;
    }
    ~CGraph() {}
    void show() {
        cout << "type :" << type << endl
             << "color :" << color << endl
             << "lineWidth :" << lineWidth << endl;
    }
    virtual void Save(fstream &file) = 0;
    virtual void Load(fstream &file) = 0;
};
class Point : public CGraph {
   public:
    int x;
    int y;
    Point(): x(10), y(10) {}
    Point(int x ,int y) : x(x), y(y) {}
    ~Point() {}
    void Save(fstream &file) {
        file.write((char *)&x, sizeof(x));
        file.write((char *)&y, sizeof(y));
    }
    void Load(fstream &file) {
        file.read((char *)&x, sizeof(x));
        file.read((char *)&y, sizeof(y));
    }
};
class Rectangle : public CGraph {
   private:
    int width, height;
    Point p;
    string msg;

   public:
    Rectangle() : p(100, 100), width(200), height(50), msg("") {}
    Rectangle(string msg) : p(100, 100), width(200), height(50), msg(msg) {}
    Rectangle(const Point &p, int width, int height, string msg)
        : p(p), width(width), height(height), msg(msg) {}

    void ShowMsg() {
        cout << "x:" << p.x << endl
             << "y:" << p.y << endl
             << "width:" << width << endl
             << "height:" << height << endl
             << "msg:" << msg << endl;
    }
    ~Rectangle() {}
    void Save(fstream &file) {
        file.write((char *)&width, sizeof(width));
        file.write((char *)&height, sizeof(height));
        p.Save(file);
        file.write((char *)&msg, sizeof(msg));
    }
    void Load(fstream &file) {
        file.read((char *)&width, sizeof(width));
        file.read((char *)&height, sizeof(height));
        p.Load(file);
        file.read((char *)&msg, sizeof(msg));
    }
};
class Ellipse : public CGraph {
   private:
    Point A, B, C, D;
    string msg;

   public:
    Ellipse() {
        A.x = -5;
        A.y = 0;
        B.x = 5;
        B.y = 0;
        C.x = 0;
        C.y = 4;
        D.x = 0;
        D.y = -4;
        msg = "";
    }
    Ellipse(const Point &A, const Point &B, const Point &C, const Point &D,
            string &msg)  //值传递 地址传递
        : A(A), B(B), C(C), D(D), msg(msg) {}
    Ellipse(const Ellipse &Copy) {
        A = Copy.A;
        B = Copy.B;
        C = Copy.C;
        D = Copy.D;
        msg = Copy.msg;
    }
    ~Ellipse() {}
    void Save() {}
    void Load() {}
};
class TextRect : public CGraph {
   private:
    int width, height;
    Point p;
    string *msg;

   public:
    TextRect() {
        p.x = 100;
        p.y = 100;
        this->width = 200;
        this->height = 50;
        // this->msg = "";
        msg = new string();
    }

    TextRect(const Point &p, int width, int height, string msg) {
        this->p = p;
        this->width = width;
        this->height = height;
        this->msg = new string(msg);
    }
    ~TextRect() {
        // no malloc no free
        // no new no delete
        delete msg;
    }
    void display() {
        cout << "x:" << p.x << endl
             << "y:" << p.y << endl
             << "width:" << width << endl
             << "height:" << height << endl
             << "msg:" << *msg << endl;
    }
    void move(int x, int y) {
        p.x = x;
        p.y = y;
    }
    void resize(int w, int h) {
        if (w > 0 && h > 0) {
            width = w;
            height = h;
        }
    }
    void edit(string s) { *msg = s; }
    void save() {
        ofstream file;
        file.open("TextRectData/index.txt");
        file << *msg;
        file.close();
    }
    void load() {
        ifstream file;
        file.open("TextRectData/index.txt");
        // file >> s;
        char ch;
        char str[255];
        string s;
        while (file) {
            file.getline(str, 255);  // getline函数可以读取整行并保存在str数组里
            s += str;
        }
        file.close();
    }
};
class CTexyEllipseRect : public Ellipse, public TextRect {
   private:
    /* data */
   public:
    CTexyEllipseRect() {}
    ~CTexyEllipseRect() {}
    void save() {}
    void load() {}
    void show() {}
};
class CPage {
   private:
    vector<Rectangle> r;
    vector<Ellipse> e;
    string name;

   public:
    CPage() { name = ""; }
    void InsertRectangle(const Rectangle &A) { r.push_back(A); }
    void InsertRectangle(int n, const Rectangle &A) {
        r.insert(r.begin() + n, A);
    }
    void ShowMsg() {
        cout << "Number of rectangle: " << r.size() << endl
             << "Number of ellipse: " << e.size() << endl;
    }
    ~CPage() {}
};
class CDocument {
   private:
    vector<CPage> pages;

   public:
    CDocument() {}
    ~CDocument() {}
    void Show() {}
    void Copy() {}
    void Delete() {}
    void Insert() {}
    void Save() {}
    void load() {}
};

