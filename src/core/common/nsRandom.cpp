#include "nsRandom.h"

namespace ns {

std::random_device Random::rd{};
std::mt19937 Random::mt19937{rd()};

}