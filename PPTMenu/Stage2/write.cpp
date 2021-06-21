#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include "class.h"
using namespace std;

int main() {
    Page page;
    Point p(100, 200);
    TextEllipseRect *a = new TextEllipseRect(p,111,222,"hello world",100);
    Rectangle *b = new Rectangle(p, 300, 4, "how are you?");
    Ellipse *c= new Ellipse(p, p, p, p, "n123123123");
    Ellipse *d= new Ellipse();

    page.PushGraph(a);
    page.PushGraph(b);
    page.PushGraph(c);
    page.PushGraph(d);

    Document doc;
    doc.AddPage(page);
    page.PopGraph();
    doc.AddPage(page);

    fstream file;
    file.open("record.dat", ios::in | ios::out | ios::binary | ios::trunc);
    doc.Save(file);
    file.close();
    cout << "Page Saved" << endl;
    doc.Display();

    
    return 0;
}
