#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>
#include <ctime>

#include "AvlTree.h"




int FindValue(const std::string &str) {
    std::istringstream iss(str);
    std::string tmp;
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
    if (argc < 4) {
        return 0;
    }
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
                if (!avlTree.Remove(FindValue(line))) {
                    fileOut << "error" << std::endl;
                }

        }
        if (line == "print") {
            avlTree.Print(fileOut);
            fileOut << std::endl;
        }
        if (line.find("add") == 0) {
//          
                avlTree.Add(FindValue(line));
//            
        }
        if (line.find("search") == 0) {
//            if (LineIsOk(line, "search") != 0) {
                if (!avlTree.Has(FindValue(line))) {
                    fileOut << "error" << std::endl;
                }

//            
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

    fileIn.close();
    fileOut.close();

    if (FileIsEqual(argv[2], argv[3])) {
        std::cout << "Correct" << std::endl;
    } else {
        std::cout << "Not correct" << std::endl;
    }

    //SkipList tests
    
SkipList skplst;

    srand(time(0));

    while (getline(fileIn, line)) {
        if (line.find("delete") == 0) {
                if (!skplst.Remove(FindValue(line))) {
                    fileOut << "error" << std::endl;
                }

        }
        if (line == "print") {
            skplst.Print(fileOut);
            fileOut << std::endl;
        }
        if (line.find("add") == 0) {
//          
                skplst.Add(FindValue(line));
//            
        }
        if (line.find("search") == 0) {
//            if (LineIsOk(line, "search") != 0) {
                if (!skplst.Has(FindValue(line))) {
                    fileOut << "error" << std::endl;
                }

//            
        }
        if (line == "min") {
            fileOut << skplst.Min() << std::endl;
        }
        if (line == "max") {
            fileOut << skplst.Max() << std::endl;
        }
        if (line == " ") {
            fileOut << "error" << std::endl;
        }
    }

    std::cout << "runtime = " << clock()/1000.0 << std::endl;

    fileIn.close();
    fileOut.close();

    if (FileIsEqual(argv[2], argv[3])) {
        std::cout << "Correct" << std::endl;
    } else {
        std::cout << "Not correct" << std::endl;
    }


    return 0;

}
