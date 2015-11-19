#include <iostream>
#include <thread>
#include "zipreader.hpp"

using namespace std;
using namespace ZipReader;
using namespace boost::iostreams;

void printUsage() {
    cout << "Usage: bgzip [-cgz/-cbz2/-d] file1 file2 file3 ...\n";
    cout << "-cgz: Gzip compress files \n";
    cout << "-cbz2: Bzip2 compress files\n";
    cout << "-d: Decompress files (autodetect format)\n";
}

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        printUsage();
    }

    // string filename = "/tmp/words";
    // Compress(filename, FileType::TYPE_GZIP);

    return 0;
}
