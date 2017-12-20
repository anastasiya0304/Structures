#include "AVLTree.h"
#include "Skiplist.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>



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

    std::string line;
    std::ifstream fileIn(argv[1]);
    assert(fileIn);
    std::ofstream fileOut(argv[2]);
    assert(fileOut);


    SkipList skp(10, 10);

    std::chrono::time_point<std::chrono::high_resolution_clock> start1, stop1;
    start1 = std::chrono::high_resolution_clock::now();


    while (getline(fileIn, line)) {

        if (line.find("delete") == 0) {

            if (!skp.deleteElement(FindValue(line))) {

                fileOut << "error" << std::endl;
            }

        }


        if (line == "print") {

            skp.displayList(fileOut);
            fileOut << std::endl;
        }


        if (line.find("add") == 0) {

            skp.insertElement(FindValue(line));

        }


        if (line.find("search") == 0) {

            if (!skp.searchElement(FindValue(line))) {
                fileOut << "error" << std::endl;


            }
        }


        stop1 = std::chrono::high_resolution_clock::now();
        std::cout << "runtime = " << std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1).count() << std::endl;


        CAVLTree avlTree;


        fileIn.clear();
        fileIn.seekg(0);


        std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
        start = std::chrono::high_resolution_clock::now();

        while (getline(fileIn, line)) {

            if (line.find("delete") == 0) {

                if (!avlTree.Remove(FindValue(line))) {

                    fileOut << "error1" << std::endl;

                }

            }

            if (line.find("print") == 0) {

                avlTree.Print(fileOut);
                fileOut << std::endl;
            }

            if (line.find("add") == 0) {

                avlTree.Add(FindValue(line));

            }

            if (line.find("search") == 0) {

                if (!avlTree.Has(FindValue(line))) {

                    fileOut << "false" << std::endl;
                }

            }

            if (line == "min") {

                fileOut << avlTree.Min() << std::endl;

            }

            if (line == "max") {

                fileOut << avlTree.Max() << std::endl;

            }

        }

        stop = std::chrono::high_resolution_clock::now();
        std::cout << "runtime = " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()
                  << std::endl;

        fileIn.close();

        if (FileIsEqual(argv[2], argv[3])) {

            std::cout << "Correct" << std::endl;

        } else {

            std::cout << "Not correct" << std::endl;
        }

        fileOut.close();

    }
}


