#include <fstream>
#include <iostream>
using namespace std;
class Dog {
   private:
    int age, gender, height;

   public:
    Dog() { age = gender = height = 0; }
    Dog(int age, int gender, int height)
        : age(age), gender(gender), height(height) {}
    void show() {
        cout << "age:" << age << endl
             << "gender:" << (gender == 1 ? "male" : "female") << endl
             << "height:" << height << endl;
    }
    void save(fstream &file) {
        file.write((char *)&age, sizeof(age));
        file.write((char *)&gender, sizeof(gender));
        file.write((char *)&height, sizeof(height));
    }
    void load(fstream &file) {
        file.read((char *)&age, sizeof(age));
        file.read((char *)&gender, sizeof(gender));
        file.read((char *)&height, sizeof(height));
    }
};

int main() {
    Dog tom(10, 1, 200);
    tom.show();

    fstream file;
    file.open("tom.dat", ios::in | ios::out |
                         ios::binary | ios::trunc);
    tom.save(file);
    file.close();

    fstream file1;
    file1.open("tom.dat", ios::in | ios::binary);

    Dog jack;
    jack.show();
    jack.load(file1);
    jack.show();
    return 0;
}