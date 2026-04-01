#include "parser.h"

const std::map<std::string, Filters> STRING_TO_ENUM = {
    {"-crop", Filters::CROP},         {"-gs", Filters::GRAYSCALE},       {"-neg", Filters::NEGATIVE},
    {"-sharp", Filters::SHARPENING},  {"-edge", Filters::EDGEDETECTION}, {"-blur", Filters::BLUR},
    {"-crystal", Filters::CRYSTALIZE}};

BMPTools ParseArguments(int argc, char** argv, std::vector<std::pair<Filters, std::vector<float>>>& arguments) {

    std::vector<std::pair<Filters, std::vector<float>>> ret;
    switch (argc) {
        case 1:
            throw std::runtime_error("No arguments");
            break;

        case 2:
            throw std::runtime_error("No write path");
            break;
    }
    int current_agr = 1;  // skip ./file
    std::string read_path = argv[current_agr++];
    std::string write_path = argv[current_agr++];
    BMPTools new_tool(read_path, write_path);
    for (int i = current_agr; i < argc; i++) {
        std::string flag = argv[i];
        if (STRING_TO_ENUM.find(flag) == STRING_TO_ENUM.end()) {
            throw std::runtime_error("Unknown filter");
        }
        Filters filter = STRING_TO_ENUM.at(flag);
        std::vector<float> arguments;
        int j = i + 1;
        while (j < argc && argv[j][0] != '-') {
            try {
                arguments.push_back(std::stof(argv[j]));
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error("Arguments are not digits");
            }
            j++;
        }
        ret.push_back({filter, arguments});
        i = j - 1;
    }
    arguments = ret;
    return new_tool;
}