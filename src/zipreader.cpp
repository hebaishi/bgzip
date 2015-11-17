#include <iostream>
#include <memory>
#include <vector>
#include <exception>

#include "../include/zipreader.hpp"

using namespace std;

const vector <char> GZIP_SIGNATURE = {31, -117, 8};
const vector <char> BZIP2_SIGNATURE = {'B', 'Z', 'h'};
const int HEADER_SIZE = 3;


void ZipReader::DeCompress(const std::string input_filename, const std::string output_filename, FileType compression_format) {
	ifstream input_file(input_filename);
	boost::iostreams::filtering_istream compFilter;
	if (compression_format == FileType::TYPE_GZIP) {
    	compFilter.push (boost::iostreams::gzip_decompressor());
    } else if (compression_format == FileType::TYPE_BZIP2) {
    	compFilter.push (boost::iostreams::bzip2_decompressor());
    }
    compFilter.push (input_file);
	ofstream output_stream(output_filename);
	boost::iostreams::copy(compFilter, output_stream);
}

void ZipReader::Compress(const std::string input_filename, const std::string output_filename, FileType compression_format) {
	ifstream input_file(input_filename);
	boost::iostreams::filtering_ostream compFilter;
	if (compression_format == FileType::TYPE_GZIP) {
    	compFilter.push (boost::iostreams::gzip_compressor());
    } else if (compression_format == FileType::TYPE_BZIP2) {
    	compFilter.push (boost::iostreams::bzip2_compressor());
    }
	ofstream output_file(output_filename);
	compFilter.push (output_file);
	boost::iostreams::copy(cin, compFilter);
}

/**
 * Return the format of a compressed Failed
 * @param  filename filename
 * @return          Type: Gzip / Bzip2 / Unknown(Uncompressed)
 */
FileType detectCompression(std::string filename) {
	ifstream input_file;
	try {
		input_file.open(filename);
	} catch (...) {
		cout << "Failed to open " << filename << endl;
		exit(-1);
	}
	FileType result;
	vector <char> byte_vector(HEADER_SIZE);
	input_file.read(byte_vector.data(), HEADER_SIZE);
	if (!input_file)
        return FileType::TYPE_UNKNOWN;
    if (byte_vector == GZIP_SIGNATURE) {
    	result = FileType::TYPE_GZIP;
    } else if (byte_vector == BZIP2_SIGNATURE) {
    	result = FileType::TYPE_BZIP2;
	}
    else { result = FileType::TYPE_UNKNOWN; }
    input_file.close();
    return result;
}
