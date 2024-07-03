#include <emscripten/bind.h>
#include <string>
#include <map>
#include <algorithm>

std::map<std::string, std::string> abbrev2state = {
        {"al", "alabama"},
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

// Make a reverse map
std::map<std::string, std::string> state2abbrev = {
        {"alabama", "al"},
        {"arkansas", "ar"},
        {"arizona", "az"},
        {"california", "ca"},
        {"colorado", "co"},
        {"connecticut", "ct"},
        {"delaware", "de"},
        {"florida", "fl"},
        {"georgia", "ga"},
        {"hawaii", "hi"},
        {"iowa", "ia"},
        {"idaho", "id"},
        {"illinois", "il"},
        {"indiana", "in"},
        {"kansas", "ks"},
        {"kentucky", "ky"},
        {"louisiana", "la"},
        {"massachusetts", "ma"},
        {"maryland", "md"},
        {"maine", "me"},
        {"michigan", "mi"},
        {"minnesota", "mn"},
        {"missouri", "mo"},
        {"mississippi", "ms"},
        {"montana", "mt"},
        {"north carolina", "nc"},
        {"north dakota", "nd"},
        {"nebraska", "ne"},
        {"new hampshire", "nh"},
        {"new jersey", "nj"},
        {"new mexico", "nm"},
        {"nevada", "nv"},
        {"new york", "ny"},
        {"ohio", "oh"},
        {"oklahoma", "ok"},
        {"oregon", "or"},
        {"pennsylvania", "pa"},
        {"rhode island", "ri"},
        {"south carolina", "sc"},
        {"south dakota", "sd"},
        {"tennessee", "tn"},
        {"texas", "tx"},
        {"utah", "ut"},
        {"virginia", "va"},
        {"vermont", "vt"},
        {"washington", "wa"},
        {"wisconsin", "wi"},
        {"west virginia", "wv"},
        {"wyoming", "wy"},
        {"district of columbia", "dc"},
        {"american samoa", "as"},
        {"guam", "gu"},
        {"northern mariana islands", "mp"},
        {"puerto rico", "pr"},
        {"u.s. virgin islands", "vi"}
};

std::string capitalizeFirstLetter(std::string input) {
    // Capitalize first letter of each word
    for (size_t i = 0; i < input.size(); i++) {
        if (i == 0 || input[i - 1] == ' ') {
            input[i] = toupper(input[i]);
        }
    }
    return input;
}

std::string lookupState(std::string input) {
    std::string state;
    
    // Convert input to lowercase
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    
    // Check if input is an abbreviation
    if (abbrev2state.find(input) != abbrev2state.end()) {
        state = abbrev2state[input];
        return capitalizeFirstLetter(state);
    }
    
    // Check if input is a state name
    if (state2abbrev.find(input) != state2abbrev.end()) {
        state = state2abbrev[input];
        std::transform(state.begin(), state.end(), state.begin(), ::toupper);
        return state;
    }
    
    return "Not found";
}

EMSCRIPTEN_BINDINGS(module) {
    emscripten::function("lookupState", &lookupState);
}
