#include <iostream>
#include <thread>
#include "../include/zipreader.hpp"

using namespace std;

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
    std::thread t(ZipReader::DeCompress, "/tmp/words.gz", "/tmp/words.txt", FileType::TYPE_GZIP);
    t.join();
    }
    return 0;
}
