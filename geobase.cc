#include "geobase.h"
#include <string>

std::string dec2hex(SRID srid_type, int width) {
    int srid = static_cast<int>(srid_type);
    std::stringstream ioss; 
    std::string s_hex; 
    ioss << std::hex << srid;  
    ioss >> s_hex; 
    if (width > s_hex.size()) {
        std::string s_0(width - s_hex.size(), '0');
        s_hex = s_0 + s_hex;
    }

    s_hex = s_hex.substr(s_hex.length() - width, s_hex.length());

    std::string s_hex_;
    int i = width - 2;
    while(i >= 0) {
        s_hex_ += s_hex.substr(i, 2);
        i -= 2;
    }
    transform(s_hex_.begin(), s_hex_.end(), s_hex_.begin(), ::toupper);

    return s_hex_;
}

std::string set_extension(std::string EWKB, SRID srid_type) {
    EWKB[8] = '2';
    std::string s_hex = dec2hex(srid_type, 8);

    EWKB.insert(10, s_hex);
    return EWKB;
}

// return true if big endian;
bool Endian(std::string EWKB) {
    std::string endian = EWKB.substr(0, 2);
    if(endian == "01") return true;  
    return false;
}

// transform the little endian to big endian;
void little2big(const std::string& little, std::string& big) {
    size_t size = little.size();
    int i = size -2;
    while(i >= 0) {
        big += little.substr(i, 2);
        i -= 2;
    } 
}

SRID ExtractSRID(std::string EWKB) {
    std::string srid = EWKB.substr(10, 8);
    if(Endian(EWKB)) {
        std::string rsrid;
        little2big(srid, rsrid);
        srid = rsrid;
    }

    std::stringstream ioss(srid); 
    int Srid;
    ioss >> std::hex >> Srid;
    switch(Srid) {
        case 0:
            return SRID::NUL;
        case 4326:
            return SRID::WSG84;
        case 7203:
            return SRID::CARTESIAN;
        default:
            throw std::runtime_error("wrong srid!");
    }
}

GeoType ExtractType(std::string EWKB) {
    std::string type = EWKB.substr(2, 4);
    if(Endian(EWKB)) {
        std::string rtype;
        little2big(type, rtype);
        type = rtype;
    }

    int Type = 0;
    std::stringstream ioss(type);
    ioss >> Type;

    std::cout << Type << std::endl;
    switch(Type) {
        case 0:
            return GeoType::NUL;
        case 1:
            return GeoType::POINT;
        case 2:
            return GeoType::LINESTRING;
        case 3:
            return GeoType::POLYGON;
        default:
            throw std::runtime_error("wrong geotype!");
    }
}