
#include <fstream>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/copy.hpp>

using std::ifstream;
using std::string;

enum FileType { TYPE_GZIP, TYPE_BZIP2, TYPE_UNKNOWN };

namespace ZipReader {

void DeCompress(const std::string, const std::string, FileType);
void Compress(const std::string, const std::string, FileType);

void addDecompressor(std::string, boost::iostreams::filtering_istream &);
void addCompressor(boost::iostreams::filtering_ostream &, FileType);

string getDecompressedFilename(string &, FileType);
string getCompressedFilename(string &, FileType);

}
