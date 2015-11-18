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
    string gzip_filename = "file.gz";
    string bzip2_filename = "file.bz2";
    string uncompressed_filename = "file.txt";

    std::cerr << "gzip_filename = " << gzip_filename << std::endl;
    std::cerr << "bzip2_filename = " << bzip2_filename << std::endl;
    std::cerr << "uncompressed_filename = " << uncompressed_filename << std::endl;

    std::cerr << "getCompressedFilename(uncompressed_filename, FileType::TYPE_GZIP) = " << getCompressedFilename(uncompressed_filename, FileType::TYPE_GZIP) << std::endl;
    std::cerr << "getCompressedFilename(uncompressed_filename, FileType::TYPE_BZIP2) = " << getCompressedFilename(uncompressed_filename, FileType::TYPE_BZIP2) << std::endl;

    std::cerr << "getDecompressedFilename(gzip_filename, FileType::TYPE_GZIP) = " << getDecompressedFilename(gzip_filename, FileType::TYPE_GZIP) << std::endl;
    std::cerr << "getDecompressedFilename(bzip2_filename, FileType::TYPE_BZIP2) = " << getDecompressedFilename(bzip2_filename, FileType::TYPE_BZIP2) << std::endl;

    string filename = "/tmp/words.gz";
    

    return 0;
}
