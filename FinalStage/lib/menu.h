#include <fstream>
#include <iostream>
#include <vector>

#include "class.h"
using namespace std;
class Menu {
   private:
    vector<string> mainMenuOptions;
    vector<string> docMenuOptions;
    vector<string> editFileMenuOptions;
    vector<string> fileNames;
    int fileCount;
    string filePath;

   public:
    Menu() { filePath = "./files/"; }
    ~Menu() { fileNameSave(); }
    void start() {
        mainMenu();
    }
    void mainMenu() {
        //vector<string> mainMenuOptions;
        mainMenuOptions.resize(4);
        mainMenuOptions[1] = "New file";
        mainMenuOptions[2] = "Open file";
        mainMenuOptions[3] = "About";
        mainMenuOptions[0] = "Quit";

        string cmd;
        while (1) {
            system("cls");
            cout << "Welcome to my PPT program" << endl;
            cout << "Index\tCommand" << endl;
            for (int i = 1; i < mainMenuOptions.size(); i++) {
                cout << i << "\t" << mainMenuOptions[i] << endl;
            }
            cout << 0 << "\t" << mainMenuOptions[0] << endl;
            cout << "Please enter your command index:";

            cin >> cmd;
            if (cmd == "0" || cmd == mainMenuOptions[0]) {
                break;
            }
            if (cmd == "1" || cmd == mainMenuOptions[1]) {
                newFile();
            }
            if (cmd == "2" || cmd == mainMenuOptions[2]) {
                fileMenu();
            }
            if (cmd == "3" || cmd == mainMenuOptions[3]) {
                about();
            }
        }
    }
    void fileMenu() {
        system("cls");
        // system("tree /f");
        fileNameLoad();
        cout << "Open file" << endl;
        cout << "Index\tFile name" << endl;
        if (fileNames.size()) {
            for (int i = 0; i < fileNames.size(); i++) {
                cout << i + 1 << "\t" << fileNames[i] << endl;
            }
        } else {
            cout << "No file" << endl;
        }
        while (1) {
            cout
                << "Please enter the file name to open or enter 0 to return\n:";
            string fileName;
            cin >> fileName;
            if (fileName == "0") break;
            if (verifyOpenFile(fileName)) {
                docMenu(fileName);
                break;
            }
            cout << "File does't exist!" << endl;
        }
    }
    void docMenu(string fileName) {
        fstream file;
        file.open(filePath + fileName + ".dat", ios::in | ios::binary);
        Document doc;
        doc.Load(file);
        file.close();

        docMenuOptions.resize(5);
        docMenuOptions[0] = "Return";
        docMenuOptions[1] = "New page";
        docMenuOptions[2] = "Edit page";
        docMenuOptions[3] = "Delete page";
        docMenuOptions[4] = "Display file imformation";

        string cmd;
        while (1) {
            system("cls");
            cout << "File name:" << fileName << endl;
            cout << "Pages:\t" << doc.Size() << endl;
            cout << "Index\tCommand" << endl;
            for (int i = 1; i < docMenuOptions.size(); i++) {
                cout << i << "\t" << docMenuOptions[i] << endl;
            }
            cout << 0 << "\t" << docMenuOptions[0] << endl;
            cout << "Please enter your command index:";

            cin >> cmd;
            if (cmd == "0" || cmd == docMenuOptions[0]) {
                break;
            } else if (cmd == "1" || cmd == docMenuOptions[1]) {
                Page p;
                doc.AddPage(p);
                string t;
                cout << "Page added, please enter any key to confirm:" << endl;
                cin >> t;
            } else if (cmd == "2" || cmd == docMenuOptions[2]) {
                int pos;
                cout << "Please enter page number to edit:";
                cin >> pos;
                if (pos < 1 || pos > doc.Size()) {
                    cout << "Wrong page number!" << endl;
                    cout << "Please enter any key to confirm:" << endl;
                    string t;
                    cin >> t;
                } else {
                    editFileMenu(pos, doc);
                }

            } else if (cmd == "3" || cmd == docMenuOptions[3]) {
                int pos;
                cout << "Please enter the page number to delete\n:";
                cin >> pos;
                if (doc.Delete(pos)) {
                    string t;
                    cout << "Page deleted, please enter any key to confirm:"
                         << endl;
                    cin >> t;
                } else {
                    string t;
                    cout << "Page delete failed, please enter any key to "
                            "confirm:"
                         << endl;
                    cin >> t;
                }
            } else if (cmd == "4" || cmd == docMenuOptions[4]) {
                system("cls");
                for (int i = 0; i < doc.pages.size(); i++) {
                    cout << "page:" << i + 1
                         << "\tGraphs: " << doc.pages[i].Size() << endl;
                }
                string t;
                cout << "Please enter any key to confirm:" << endl;
                cin >> t;
            }
        }
        file.open(filePath + fileName + ".dat",
                  ios::in | ios::out | ios::binary | ios::trunc);
        doc.Save(file);
        file.close();
    }
    void editFileMenu(int pos, Document &doc) {
        editFileMenuOptions.resize(6);
        editFileMenuOptions[0] = "Return";
        editFileMenuOptions[1] = "Display graphics information";
        editFileMenuOptions[2] = "Add Rectangle";
        editFileMenuOptions[3] = "Add Ellipse";
        editFileMenuOptions[4] = "Add TextRect";
        editFileMenuOptions[5] = "Add TextEllipseRect";

        string cmd;
        while (1) {
            system("cls");
            cout << "Page:\t" << pos << endl;
            cout << "Graphs:\t" << doc.pages[pos - 1].Size() << endl;
            cout << "Index\tCommand" << endl;
            for (int i = 1; i < editFileMenuOptions.size(); i++) {
                cout << i << "\t" << editFileMenuOptions[i] << endl;
            }
            cout << 0 << "\t" << editFileMenuOptions[0] << endl;
            cout << "Please enter your command index:";

            cin >> cmd;
            if (cmd == "0" || cmd == editFileMenuOptions[0]) {
                break;
            } else if (cmd == "1" || cmd == editFileMenuOptions[1]) {
                system("cls");
                doc.pages[pos - 1].Display();
                string t;
                cout << "Please enter any key to confirm:" << endl;
                cin >> t;

            } else if (cmd == "2" || cmd == editFileMenuOptions[2]) {
                Rectangle *g = new Rectangle();
                doc.pages[pos - 1].PushGraph(g);
                string t;
                cout << "Rectangle added, please enter any key to confirm:"
                     << endl;
                cin >> t;
            } else if (cmd == "3" || cmd == editFileMenuOptions[3]) {
                Ellipse *g = new Ellipse();
                doc.pages[pos - 1].PushGraph(g);
                string t;
                cout << "Ellipse added, please enter any key to confirm:"
                     << endl;
                cin >> t;

            } else if (cmd == "4" || cmd == editFileMenuOptions[4]) {
                TextRect *g = new TextRect();
                doc.pages[pos - 1].PushGraph(g);
                string t;
                cout << "TextRect added, please enter any key to confirm:"
                     << endl;
                cin >> t;
            } else if (cmd == "5" || cmd == editFileMenuOptions[5]) {
                TextEllipseRect *g = new TextEllipseRect();
                doc.pages[pos - 1].PushGraph(g);
                string t;
                cout
                    << "TextEllipseRect added, please enter any key to confirm:"
                    << endl;
                cin >> t;
            }
        }
    }
    void fileNameSave() {
        fstream file;
        file.open("./lib/fileNames.dat",
                  ios::in | ios::out | ios::binary | ios::trunc);
        fileCount = fileNames.size();
        file.write((char *)&fileCount, sizeof(int));
        StringTool t;
        for (auto name : fileNames) {
            t.Save(file, name);
        }
        file.close();
    }
    void fileNameLoad() {
        fileNames.clear();
        fstream file;
        file.open("./lib/fileNames.dat", ios::in | ios::binary);
        file.read((char *)&fileCount, sizeof(int));
        string name;
        StringTool t;
        for (int i = 0; i < fileCount; i++) {
            name = t.Load(file);
            bool flag = true;
            for (auto n : fileNames) {
                if (n == name) flag = false;
            }
            if (flag) fileNames.push_back(name);
        }
        file.close();
    }
    bool verifyOpenFile(string s) {
        for (auto i : fileNames) {
            if (i == s) return true;
        }
        return false;
    }
    bool verifyFilename(string name) {
        char banned[] = {'/', '\\', ':', '*', '?', '\"', '<', '>', '|'};
        if (name.length() > 255) return false;
        for (int i = 0; i < name.length(); i++) {
            for (int j = 0; j < 9; j++) {
                if (name[i] == banned[j]) return false;
            }
        }
        return true;
    }
    void newFile() {
        system("cls");
        cout << "Open file" << endl;
        string fileName;

        do {
            cout << "Please enter filename:";
            cin >> fileName;
            if (verifyFilename(fileName)) {
                break;
            } else {
                cout << "The file name cannot contain the following "
                        "symbols:/,\\,:,*,?,\",<,>,| \n";
            }
        } while (1);

        fstream file;
        Document doc;
        file.open(filePath + fileName + ".dat",
                  ios::in | ios::out | ios::binary | ios::trunc);
        doc.Save(file);
        file.close();
        fileNames.push_back(fileName);
        fileNameSave();
        cout << "File created, please enter any key to confirm:" << endl;
        cin >> fileName;
    }
    void about() {
        system("cls");
        cout << "Author:\tJZK2019213853" << endl;
        cout << "Date:\tJune 16,2021" << endl;
        cout << "Version:1.0" << endl;
        cout << "Enter any key to return:" << endl;
        string t;
        cin >> t;
    }
};
