#include <iostream>
#include <thread>
#include "../include/zipreader.hpp"

using namespace std;

using namespace boost::iostreams;

int main(int argc, char const *argv[]) {
    string input_file;
    if (argc == 2) {
        input_file.assign(argv[1]);
        ZipReader Zr;
        std::thread t(&ZipReader::DeCompress, &Zr, input_file, input_file);
        t.join();
    }
    return 0;
}
