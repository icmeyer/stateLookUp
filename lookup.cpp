#include <emscripten/bind.h>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>

std::map<std::string, std::string> abbrev2state = {
        {"al", "alabama"},
        {"ak", "alaska"},
        {"ar", "arkansas"},
        {"az", "arizona"},
        {"ca", "california"},
        {"co", "colorado"},
        {"ct", "connecticut"},
        {"de", "delaware"},
        {"fl", "florida"},
        {"ga", "georgia"},
        {"hi", "hawaii"},
        {"ia", "iowa"},
        {"id", "idaho"},
        {"il", "illinois"},
        {"in", "indiana"},
        {"ks", "kansas"},
        {"ky", "kentucky"},
        {"la", "louisiana"},
        {"ma", "massachusetts"},
        {"md", "maryland"},
        {"me", "maine"},
        {"mi", "michigan"},
        {"mn", "minnesota"},
        {"mo", "missouri"},
        {"ms", "mississippi"},
        {"mt", "montana"},
        {"nc", "north carolina"},
        {"nd", "north dakota"},
        {"ne", "nebraska"},
        {"nh", "new hampshire"},
        {"nj", "new jersey"},
        {"nm", "new mexico"},
        {"nv", "nevada"},
        {"ny", "new york"},
        {"oh", "ohio"},
        {"ok", "oklahoma"},
        {"or", "oregon"},
        {"pa", "pennsylvania"},
        {"ri", "rhode island"},
        {"sc", "south carolina"},
        {"sd", "south dakota"},
        {"tn", "tennessee"},
        {"tx", "texas"},
        {"ut", "utah"},
        {"va", "virginia"},
        {"vt", "vermont"},
        {"wa", "washington"},
        {"wi", "wisconsin"},
        {"wv", "west virginia"},
        {"wy", "wyoming"},
        {"dc", "district of columbia"},
        {"as", "american samoa"},
        {"gu", "guam"},
        {"mp", "northern mariana islands"},
        {"pr", "puerto rico"},
        {"vi", "u.s. virgin islands"}
};

std::map<std::string, std::string> fips2state  = {
        {"01", "alabama"},
        {"02", "alaska"},
        {"04", "arizona"},
        {"05", "arkansas"},
        {"06", "california"},
        {"08", "colorado"},
        {"09", "connecticut"},
        {"10", "delaware"},
        {"11", "district of columbia"},
        {"12", "florida"},
        {"13", "georgia"},
        {"15", "hawaii"},
        {"16", "idaho"},
        {"17", "illinois"},
        {"18", "indiana"},
        {"19", "iowa"},
        {"20", "kansas"},
        {"21", "kentucky"},
        {"22", "louisiana"},
        {"23", "maine"},
        {"24", "maryland"},
        {"25", "massachusetts"},
        {"26", "michigan"},
        {"27", "minnesota"},
        {"28", "mississippi"},
        {"29", "missouri"},
        {"30", "montana"},
        {"31", "nebraska"},
        {"32", "nevada"},
        {"33", "new hampshire"},
        {"34", "new jersey"},
        {"35", "new mexico"},
        {"36", "new york"},
        {"37", "north carolina"},
        {"38", "north dakota"},
        {"39", "ohio"},
        {"40", "oklahoma"},
        {"41", "oregon"},
        {"42", "pennsylvania"},
        {"44", "rhode island"},
        {"45", "south carolina"},
        {"46", "south dakota"},
        {"47", "tennessee"},
        {"48", "texas"},
        {"49", "utah"},
        {"50", "vermont"},
        {"51", "virginia"},
        {"53", "washington"},
        {"54", "west virginia"},
        {"55", "wisconsin"},
        {"56", "wyoming"},
};

std::map<std::string, std::string> createState2Abbrev() {
    std::map<std::string, std::string> state2abbrev;
    for (const auto &kv : abbrev2state) {
        state2abbrev[kv.second] = kv.first;  
    }
    return state2abbrev;
}
std::map<std::string, std::string> state2abbrev = createState2Abbrev();

std::map<std::string, std::string> createAbbrev2Fips() {
    std::map<std::string, std::string> abbrev2fips;
    for (const auto &kv : fips2state) {
        abbrev2fips[state2abbrev[kv.second]] = kv.first;
    }
    return abbrev2fips;
}
std::map<std::string, std::string> abbrev2fips = createAbbrev2Fips();

std::string capitalizeFirstLetter(std::string input) {
    // Capitalize first letter of each word
    for (size_t i = 0; i < input.size(); i++) {
        if (i == 0 || input[i - 1] == ' ') {
            input[i] = toupper(input[i]);
        }
    }
    return input;
}

std::string lookupStateByName(std::string input) {
    std::string state;
    std::string abbrev;
    std::string fips;
    
    // Convert input to lowercase
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    
    // Check if input is a state name
    if (state2abbrev.find(input) != state2abbrev.end()) {
        abbrev = state2abbrev[input];
        fips = abbrev2fips[abbrev];

        state = capitalizeFirstLetter(state);
        std::transform(abbrev.begin(), abbrev.end(), abbrev.begin(), ::tolower);
        return state + "|" + abbrev + "|" + fips;
    }
    
    return "State|Not|Found";
}

EMSCRIPTEN_BINDINGS(module) {
    emscripten::function("lookupStateByName", &lookupStateByName);
}
