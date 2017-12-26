#include "AVLTree.h"
#include "Skiplist.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>



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


        skiplist skpl(1, 10000);
        CAVLTree avlt;


        std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
        start = std::chrono::high_resolution_clock::now();

        while (getline(fileIn, line)) {

            if (line.find("delete") == 0) {

                if (!avlt.Remove(FindKey(line))) {

                    fileOut << "error1" << std::endl;

                }

            }

            if (line.find("print") == 0) {

                fileOut << "structure: ";
                avlt.Print(fileOut);
                fileOut << std::endl;

            }

            if (line.find("add") == 0) {

                std::pair<int,int> pair;
                pair.first=FindKey(line);
                pair.second=FindValue(line);
                avlt.Add(pair);

            }

            if (line.find("has") == 0) {

                if (!avlt.Has(FindKey(line))) {

                    fileOut << FindValue(line) << " hasn't found" << std::endl;

                } else {

                    fileOut << FindKey(line) << " has found" << std::endl;

                }
            }

            if (line.find("min") == 0) {

                fileOut << avlt.Min() << std::endl;

            }

            if (line.find("min") == 0) {

                fileOut << avlt.Max() << std::endl;

            }

        }



            stop = std::chrono::high_resolution_clock::now();

            std::cout << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;


        fileIn.clear();
        fileIn.seekg(0);
        fileOut.clear();
        fileOut.seekp(0);


                start = std::chrono::high_resolution_clock::now();

                while (getline(fileIn, line)) {

                    if (line.find("delete") == 0) {

                        if (!skpl.Remove(FindValue(line))) {

                            fileOut << "error1" << std::endl;

                        }

                    }

                    if (line.find("print") == 0) {

                        fileOut << "structure: ";
                        skpl.printList(fileOut);
                        fileOut << std::endl;

                    }

                    if (line.find("add") == 0) {

                        std::pair<int,int> pair;
                        pair.first=FindKey(line);
                        pair.second=FindValue(line);
                        skpl.Add(pair);

                    }

                    if (line.find("has") == 0) {

                        if (!skpl.Has(FindKey(line))) {

                            fileOut << FindKey(line) << " hasn't found" << std::endl;

                        } else {

                            fileOut << FindKey(line) << " has found" << std::endl;
                        }

                    }

                    if (line.find("min") == 0) {

                        fileOut << skpl.Min() << std::endl;

                    }

                    if (line.find("min") == 0) {

                        fileOut << skpl.Max() << std::endl;

                    }

                }


                stop = std::chrono::high_resolution_clock::now();
                std::cout  << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;


                fileIn.close();


                if ( FileIsEqual(argv[2], argv[3]) ) {

                     std::cout << "Correct" << std::endl;

                    }

                     else {

                        std::cout << "Not correct" << std::endl;
                    }

             fileOut.close();

        }

