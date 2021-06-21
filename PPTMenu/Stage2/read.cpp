#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include "class.h"
using namespace std;

int main() {
    Document doc;
    fstream file;
    
    file.open("record.dat", ios::in | ios::binary);
    doc.Load(file);
    file.close();

    doc.Display();

    cout<<"Rectangle"<<sizeof(Rectangle)<<endl;
    cout<<"Ellipse"<<sizeof(Ellipse)<<endl;
    cout<<"point"<<sizeof(Point)<<endl;
    doc.Show();
    return 0;
}
