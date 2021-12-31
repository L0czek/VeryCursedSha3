#include "sha3.hpp"
#include <ostream>
#include <string>

std::vector<char> read_all_stdin()
{
    std::vector<char> data;
    while(std::cin) {
        std::vector<char> chunk(0x1000, '\0');
        std::cin.read(chunk.data(), chunk.size());
        data.insert(data.end(), chunk.begin(), chunk.begin() + std::cin.gcount());
    }
    return data;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " sha3_512|sha3_384|sha3_256|sha3_224" << std::endl;
        std::cerr << "Reads data from stdin and outputs hash on stdout" << std::endl;
    } else if (std::string(argv[1]) == "sha3_512") {
        std::vector<char> data = read_all_stdin();
        SHA3_512 sha3;
        sha3.hash(data.begin(), data.end());
        std::cout << sha3.hexdigest() << std::endl;
    } else if (std::string(argv[1]) == "sha3_384") {
        std::vector<char> data = read_all_stdin();
        SHA3_384 sha3;
        sha3.hash(data.begin(), data.end());
        std::cout << sha3.hexdigest() << std::endl;
    } else if (std::string(argv[1]) == "sha3_256") {
        std::vector<char> data = read_all_stdin();
        SHA3_256 sha3;
        sha3.hash(data.begin(), data.end());
        std::cout << sha3.hexdigest() << std::endl;
    } else if (std::string(argv[1]) == "sha3_224") {
        std::vector<char> data = read_all_stdin();
        SHA3_224 sha3;
        sha3.hash(data.begin(), data.end());
        std::cout << sha3.hexdigest() << std::endl;
    } else {
        std::cerr << "Invalid hash type: " << argv[1] << std::endl;
    }
}

