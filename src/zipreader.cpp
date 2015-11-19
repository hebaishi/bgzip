#include <iostream>
#include <memory>
#include <vector>
#include <exception>

#include "zipreader.hpp"

using namespace std;

const vector <char> GZIP_SIGNATURE = {31, -117, 8};
const vector <char> BZIP2_SIGNATURE = {'B', 'Z', 'h'};
const int HEADER_SIZE = 3;

namespace ZipReader {

void DeCompress(std::string input_filename) {
	ifstream input_file(input_filename);
	boost::iostreams::filtering_istream compFilter;
	FileType compression_format = addDecompressor(input_filename, compFilter);
    compFilter.push (input_file);
	string output_filename = getDecompressedFilename(input_filename, compression_format);
	ofstream output_stream(output_filename);
	boost::iostreams::copy(compFilter, output_stream);
}

void Compress(std::string input_filename, FileType compression_format) {
	ifstream input_file(input_filename);
	boost::iostreams::filtering_ostream compFilter;
	addCompressor(compFilter, compression_format);
	string output_filename = getCompressedFilename(input_filename, compression_format);
	ofstream output_file(output_filename);
	compFilter.push (output_file);
	boost::iostreams::copy(input_file, compFilter);
}

/**
 * Return the format of a compressed Failed
 * @param  filename filename
 * @return          Type: Gzip / Bzip2 / Unknown(Uncompressed)
 */
FileType addDecompressor(std::string filename, boost::iostreams::filtering_istream & compression_filter) {
	ifstream input_file;
	try {
		input_file.open(filename);
	} catch (...) {
		cout << "Failed to open " << filename << endl;
		exit(-1);
	}
	vector <char> byte_vector(HEADER_SIZE);
	input_file.read(byte_vector.data(), HEADER_SIZE);
	FileType type = FileType::TYPE_UNKNOWN;
	if (byte_vector == GZIP_SIGNATURE) {
    	compression_filter.push(boost::iostreams::gzip_decompressor());
		type = FileType::TYPE_GZIP;
    } else if (byte_vector == BZIP2_SIGNATURE) {
    	compression_filter.push(boost::iostreams::bzip2_decompressor());
		type = FileType::TYPE_BZIP2;
	}
    input_file.close();
	return type;
}

void addCompressor(boost::iostreams::filtering_ostream & compression_filter, FileType type) {
	if (type == FileType::TYPE_GZIP) {
		compression_filter.push(boost::iostreams::gzip_compressor());
	} else if (type == FileType::TYPE_BZIP2) {
		compression_filter.push(boost::iostreams::bzip2_compressor());
	}
}

string getDecompressedFilename(string &input_file, FileType type) {
	string output_file;
	string extension;
	if (type == FileType::TYPE_GZIP) {
		extension = ".gz";
	} else if (type == FileType::TYPE_BZIP2) {
		extension = ".bz2";
	}

	size_t extension_pos = input_file.rfind(extension);
	if (extension_pos != string::npos) {
		output_file = input_file.substr(0, extension_pos);
	}

	return output_file;
}

string getCompressedFilename(string &input_file, FileType type) {
	string output_file = input_file;
	if (type == FileType::TYPE_GZIP) {
		output_file += ".gz";
	} else if (type == FileType::TYPE_BZIP2) {
		output_file += ".bz2";
	}
	return output_file;
}

}
