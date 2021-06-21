#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
// class StringTool is created for saving and loading class string
class StringTool {
   public:
    void Save(fstream &file, string s) {
        size_t len = s.size();
        file.write((char *)&len, sizeof(size_t));
        file.write(s.c_str(), len);
    }
    string Load(fstream &file) {
        size_t len;
        file.read((char *)&len, sizeof(size_t));
        char *temp = new char[len + 1];
        file.read(temp, len);
        temp[len] = '\0';
        string s = temp;
        delete[] temp;
        return s;
    }
};
// Base class Graph
class Graph {
   protected:
    // The type and color can be string,but here I use int
    int type;
    int color;
    int lineWidth;
    StringTool t;

   public:
    Graph() {
        type = 0;
        color = 0;
        lineWidth = 1;
    }
    Graph(int type, int color, int lineWidth)
        : type(type), color(color), lineWidth(lineWidth) {}
    ~Graph() {}

    virtual void Display() = 0;
    virtual void Save(fstream &file) = 0;
    virtual void Load(fstream &file) = 0;

    void GraphSave(fstream &file) {
        file.write((char *)&type, sizeof(type));
        file.write((char *)&color, sizeof(color));
        file.write((char *)&lineWidth, sizeof(lineWidth));
    }
};
class Point : public Graph {
   public:
    int x;
    int y;
    Point() : x(10), y(10) {
        type = 1;
        color = 0;
        lineWidth = 1;
    }
    Point(int x, int y) : x(x), y(y) {
        type = 1;
        color = 0;
        lineWidth = 1;
    }
    ~Point() {}
    void Display() {}
    void Save(fstream &file) {
        file.write((char *)&x, sizeof(x));
        file.write((char *)&y, sizeof(y));
    }
    void Load(fstream &file) {
        file.read((char *)&x, sizeof(x));
        file.read((char *)&y, sizeof(y));
    }
};
class Rectangle : public Graph {
   protected:
    int width, height;
    Point p;
    string msg;

   public:
    Rectangle() : p(100, 100), width(200), height(50), msg("") {
        type = 2;
        color = 0;
        lineWidth = 1;
    }
    Rectangle(const Point &p, int width, int height, string msg)
        : p(p), width(width), height(height), msg(msg) {
        type = 2;
        color = 0;
        lineWidth = 1;
    }
    ~Rectangle() {}
    void Display() {
        cout << "***** Rectangle Imformations *****" << endl
             << "Point P: (" << p.x << "," << p.y << ")" << endl
             << "width:" << width << endl
             << "height:" << height << endl
             << "msg:" << msg << endl
             << "**********************************" << endl;
    }
    void Save(fstream &file) {
        Graph::GraphSave(file);
        file.write((char *)&width, sizeof(width));
        file.write((char *)&height, sizeof(height));
        p.Save(file);
        t.Save(file, msg);
    }
    void Load(fstream &file) {
        file.read((char *)&width, sizeof(width));
        file.read((char *)&height, sizeof(height));
        p.Load(file);
        msg = t.Load(file);
    }
};
class Ellipse : virtual public Graph {
   protected:
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
        msg = "I'm an ellipse";
        type = 3;
        color = 0;
        lineWidth = 1;
    }
    Ellipse(const Point &A, const Point &B, const Point &C, const Point &D,
            string msg)  //值传递 地址传递
        : A(A), B(B), C(C), D(D), msg(msg) {
        type = 3;
        color = 0;
        lineWidth = 1;
    }
    Ellipse(const Ellipse &Copy) {
        A = Copy.A;
        B = Copy.B;
        C = Copy.C;
        D = Copy.D;
        msg = Copy.msg;
        type = 3;
        color = 0;
        lineWidth = 1;
    }
    ~Ellipse() {}
    void Display() {
        cout << "***** Ellipse Imformations *****" << endl
             << "Point A: (" << A.x << "," << A.y << ")" << endl
             << "Point B: (" << B.x << "," << B.y << ")" << endl
             << "Point C: (" << C.x << "," << C.y << ")" << endl
             << "Point D: (" << D.x << "," << D.y << ")" << endl
             << "msg:" << msg << endl
             << "type:" << type << endl
             << "********************************" << endl;
    }
    void Save(fstream &file) {
        Graph::GraphSave(file);
        t.Save(file, msg);
        A.Save(file);
        B.Save(file);
        C.Save(file);
        D.Save(file);
    }
    void Load(fstream &file) {
        msg = t.Load(file);
        A.Load(file);
        B.Load(file);
        C.Load(file);
        D.Load(file);
    }
};
class TextRect : virtual public Graph {
   protected:
    int width, height;
    Point p;
    string msg;

   public:
    TextRect() {
        p.x = 100;
        p.y = 100;
        width = 200;
        height = 50;
        // this->msg = "";
        msg = "I'm TextRect";
        type = 4;
        color = 0;
        lineWidth = 1;
    }
    TextRect(const Point &p, int width, int height, string msg) {
        this->p = p;
        this->width = width;
        this->height = height;
        this->msg = msg;
        type = 4;
        color = 0;
        lineWidth = 1;
    }
    ~TextRect() {}

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
    void Edit(string s) { msg = s; }
    void Display() {
        cout << "***** TextRect Imformations *****" << endl
             << "Point P: (" << p.x << "," << p.y << ")" << endl
             << "width:" << width << endl
             << "height:" << height << endl
             << "msg:" << msg << endl
             << "*********************************" << endl;
    }
    void Save(fstream &file) {
        Graph::GraphSave(file);
        file.write((char *)&width, sizeof(width));
        file.write((char *)&height, sizeof(height));
        p.Save(file);
        t.Save(file, msg);
    }
    void Load(fstream &file) {
        file.read((char *)&width, sizeof(width));
        file.read((char *)&height, sizeof(height));
        p.Load(file);
        msg = t.Load(file);
    }
};
class TextEllipseRect : public Ellipse, public TextRect {
   protected:
    int round;

   public:
    TextEllipseRect() {
        round = 2;
        TextRect::msg = "I'm TextEllipseRect object";
        p.x = 100;
        p.y = 200;
        width = 200;
        height = 50;
        type = 5;
        color = 0;
        lineWidth = 1;
    }
    TextEllipseRect(const Point &p, int width, int height, string msg,
                    int round) {
        TextRect::p = p;
        TextRect::width = width;
        TextRect::height = height;
        TextRect::msg = msg;
        this->round = round;
        type = 5;
        color = 0;
        lineWidth = 1;
    }
    ~TextEllipseRect() {}
    void Display() {
        cout << "***** TextEllipseRect Imformations *****" << endl
             << "Point P: (" << p.x << "," << p.y << ")" << endl
             << "width:" << width << endl
             << "height:" << height << endl
             << "round:" << round << endl
             << "msg:" << TextRect::msg << endl
             << "****************************************" << endl;
    }
    void Save(fstream &file) {
        Graph::GraphSave(file);

        file.write((char *)&round, sizeof(round));
        file.write((char *)&width, sizeof(width));
        file.write((char *)&height, sizeof(height));
        p.Save(file);
        t.Save(file, TextRect::msg);
    }
    void Load(fstream &file) {
        file.read((char *)&round, sizeof(round));
        file.read((char *)&width, sizeof(width));
        file.read((char *)&height, sizeof(height));
        p.Load(file);
        TextRect::msg = t.Load(file);
    }
};
class Page {
   private:
    vector<Graph *> graphs;
    int graphsNum;
    string name;

   public:
    Page() { name = ""; }
    ~Page() {}
    void PushGraph(Graph *graph) { graphs.push_back(graph); }
    void PopGraph() { graphs.pop_back(); }
    void Display() {
        cout << "page size :" << graphs.size() << endl;
        for (auto graph : graphs) graph->Display();
    }
    void Save(fstream &file) {
        graphsNum = graphs.size();
        file.write((char *)&graphsNum, sizeof(graphsNum));
        for (auto i : graphs) i->Save(file);
    }
    void Load(fstream &file) {
        file.read((char *)&graphsNum, sizeof(graphsNum));
        int type, color, lineWidth;
        Graph *g;
        for (int i = 0; i < graphsNum; i++) {
            file.read((char *)&type, sizeof(type));
            file.read((char *)&color, sizeof(color));
            file.read((char *)&lineWidth, sizeof(lineWidth));
            /*
            1 Point
            2 Rectangle
            3 Ellipse
            4 TextRect
            5 CTextEllipseRect
             */
            switch (type) {
                case 0:
                    g = new Ellipse();
                    break;
                case 1:
                    g = new Point();
                    break;
                case 2:
                    g = new Rectangle();
                    break;
                case 3:
                    g = new Ellipse();
                    break;
                case 4:
                    g = new TextRect();
                    break;
                case 5:
                    g = new TextEllipseRect();
                    break;
                default:
                    break;
            }
            g->Load(file);
            PushGraph(g);
        }
    }
};
class Document {
   private:
    vector<Page> pages;
    string name;
    int pagesNum;

   public:
    Document() : name("file") {}
    Document(string name) : name(name) {}
    ~Document() {}
    void Show() {
        cout << "Document \"" << name << "\""
             << " has " << pages.size()
             << ((pages.size() <= 1) ? " page" : " pages") << endl;
    }
    void Display() {
        int i = 1;
        for (auto page : pages) {
            cout << "page " << i++ << endl;
            page.Display();
        }
    }
    void Copy(int a, int b) {
        // pages[a]=pages[b];
    }
    bool Delete(int pos) {
        if (pos <= 0 || pos > pages.size()) {
            return false;
        }
        pages.erase(pages.begin() + pos - 1);
        return true;
    }
    void Rename(string name) { this->name = name; }
    void AddPage(const Page &p) { pages.push_back(p); }
    void DeletePage() { pages.pop_back(); }

    bool InsertPage(int pos, const Page &p) {
        if (pos <= 0 || pos > pages.size()) {
            return false;
        }
        pages.insert(pages.begin() + pos - 1, p);
        return true;
    }
    void Save(fstream &file) {
        pagesNum = pages.size();
        file.write((char *)&pagesNum, sizeof(pagesNum));
        for (int i = 0; i < pages.size(); i++) {
            pages[i].Save(file);
        }
    }
    void Load(fstream &file) {
        file.read((char *)&pagesNum, sizeof(pagesNum));
        //  char *temp = new char[sizeof(CPage)];
        for (int i = 0; i < pagesNum; i++) {
            Page p;
            p.Load(file);
            pages.push_back(p);
        }
        // file.read((char *)&pages, sizeof(pages));
    }
};