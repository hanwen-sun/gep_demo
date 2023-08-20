#pragma once
#include <boost/geometry.hpp>
#include <boost/geometry/multi/io/wkt/wkt.hpp> 
#include <boost/geometry/extensions/gis/io/wkb/write_wkb.hpp>
#include <iostream>

namespace bg = boost::geometry;

typedef bg::cs::cartesian Cartesian;
typedef bg::cs::geographic<bg::degree> Wsg84; 
typedef std::vector<boost::uint8_t> byte_vector;

enum class GeoType {
    NUL = 0,
    POINT = 1,
    LINESTRING = 2,
    POLYGON = 3
};

enum class SRID {
    NUL = 0,
    WSG84 = 4326,
    CARTESIAN = 7203
};

class GeoBase {
    // point_base point_;
    // std::string EWKB;
    SRID srid_;
    GeoType type_;

 public:
    GeoBase(SRID srid, GeoType type) : srid_(srid), type_(type) {}

    virtual ~GeoBase() {}

    virtual std::string AsEWKB() = 0;

    virtual std::string AsEWKT() = 0;

    GeoType GetType() {
        return type_;
    }

    SRID GetSrid() {
        return srid_;
    }
};

std::string dec2hex(SRID srid_type, int width);

std::string set_extension(std::string EWKB, SRID srid_type);

SRID ExtractSRID(std::string EWKB);

GeoType ExtractType(std::string EWKB);