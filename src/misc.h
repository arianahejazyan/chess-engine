#pragma once

#include <string>

namespace athena::misc {

inline std::string version() { return ATHENA_VERSION; }    
inline std::string author()  { return "Ariana Hejazyan"; }   
inline std::string github()  { return "https://github.com/arianahejazyan/Athena"; }

} // namespace athena