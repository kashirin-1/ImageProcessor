#pragma once

#include "bmptools.h"
#include <vector>
#include "filters_list.h"

BMPTools ParseArguments(int argc, char** argv, std::vector<std::pair<Filters, std::vector<float>>>& arguments);