#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include "AVTree/AVLTree.h"
#include "Skiplist/Skiplist.h"


int FindKey(const std::string &str) {

    std::istringstream iss(str);
    std::string tmp;
    iss >> tmp;
    tmp.clear();
    iss >> tmp;
    int key = atoi(tmp.c_str());
    return key;
}

int FindValue(const std::string &str) {

    std::istringstream iss(str);
    std::string tmp;
    iss >> tmp;
    tmp.clear();
    iss >> tmp;
    tmp.clear();
    iss >> tmp;
    int value = atoi(tmp.c_str());
    return value;
}

bool FileIsEqual(const std::string &firstFileName, const std::string &secondFileName) {

    std::ifstream firstFile(firstFileName), secondFile(secondFileName);
    assert(firstFile);
    assert(secondFile);

    std::string buffer1((std::istreambuf_iterator<char>(firstFile)), std::istreambuf_iterator<char>());
    std::string buffer2((std::istreambuf_iterator<char>(secondFile)), std::istreambuf_iterator<char>());
    firstFile.close();
    secondFile.close();

    return (buffer1 == buffer2);
}

int main(int argc, char *argv[]) {

    std::string line;
    std::ifstream fileIn(argv[1]);
    assert(fileIn);
    std::ofstream fileOut(argv[2]);
    assert(fileOut);

    //AVL tree tests

    CAVLTree avlTree;

    srand(time(0));

    while (getline(fileIn, line)) {

        if (line.find("delete") == 0) {

                if (!avlTree.Remove(FindKey(line))) {

                    fileOut << "error" << std::endl;

                } else {

                    fileOut << "Ok" << std::endl;
                }

        }

        if (line == "print") {

            avlTree.Print(fileOut);
            fileOut << std::endl;

        }

        if (line.find("add") == 0) {

            std::pair<int,int>ins;
            ins.first=FindKey(line);
            ins.second=FindValue(line);
            avlTree.Add(ins);

        }

        if (line.find("has") == 0) {

            fileOut << avlTree.Has(FindKey(line)) << std::endl;

        }

        if (line == "min") {

            fileOut << avlTree.Min() << std::endl;

        }

        if (line == "max") {

            fileOut << avlTree.Max() << std::endl;

        }

        if (line == " ") {

            fileOut << "error" << std::endl;

        }

    }

    std::cout << "runtime = " << clock()/1000.0 << std::endl;




    fileIn.clear();
    fileIn.seekg(0);
    fileOut.clear();
    fileOut.seekp(0);



    skiplist skplist(1,1000);

    srand(time(0));

    while (getline(fileIn, line)) {

        if (line.find("delete") == 0) {

            if (!skplist.Remove(FindKey(line))) {

                fileOut << "error" << std::endl;

            } else {

                fileOut << "Ok" << std::endl;
            }

        }

        if (line == "print") {

            skplist.printList(fileOut);
            fileOut << std::endl;

        }

        if (line.find("add") == 0) {

            std::pair<int,int>inst;
            inst.first=FindKey(line);
            inst.second=FindValue(line);
            skplist.Add(inst);

        }

        if (line.find("has") == 0) {

            fileOut << skplist.Has(FindKey(line)) << std::endl;

        }

        if (line == "min") {

            fileOut << skplist.Min() << std::endl;

        }

        if (line == "max") {

            fileOut << skplist.Max() << std::endl;

        }

        if (line == " ") {

            fileOut << "error" << std::endl;

        }

    }

    std::cout << "runtime = " << clock()/1000.0 << std::endl;

    if (FileIsEqual(argv[2], argv[3])) {

        std::cout << "Correct" << std::endl;

    } else {

        std::cout << "Not correct" << std::endl;

    }

    fileIn.close();
    fileOut.close();

    return 0;
}
