#include "geoimpl.h"
#include <boost/geometry/multi/io/wkt/wkt.hpp> 
#include <boost/geometry/extensions/gis/io/wkb/write_wkb.hpp>
#include <boost/geometry/extensions/gis/io/wkb/read_wkb.hpp>
#include <boost/geometry/extensions/gis/io/wkb/utility.hpp>

// 前向申明?

template<typename T>
point<T>::point(SRID srid, GeoType type, int construct_type, std::string content) : GeoBase(srid, type) {
    // srid_ = srid;
    // type_ = type;

    if(construct_type == 0) {
        byte_vector wkb_;
        bg::hex2wkb(content, std::back_inserter(wkb_));
        if(!bg::read_wkb(wkb_.begin(), wkb_.end(), point_)) {
            std::cout << "error!" << std::endl;
            exit(0);
        }
        //EWKB = content;
        EWKB = set_extension(content, GetSrid());
    }

    if(construct_type == 1) {
        std::string wkb_out;
        bg::read_wkt(content, point_);
        if(!bg::write_wkb(point_, std::back_inserter(wkb_out))) {
            std::cout << "error!" << std::endl;
            exit(0);
        }
        bg::wkb2hex(wkb_out.begin(), wkb_out.end(), EWKB);
        EWKB = set_extension(EWKB, GetSrid()); 
    }
}

template<typename T>
std::string point<T>::AsEWKB() {
    return EWKB;
}

template<typename T>
std::string point<T>::AsEWKT() {
    std::string EWKT;
    std::stringstream ioss;

    ioss << "SRID=" << static_cast<int>(GetSrid()) << ";" << bg::wkt(point_) << std::endl;

    std::string tmp;
    while(ioss >> tmp) {
        EWKT += tmp;
        EWKT += ' ';
    }
    
    return EWKT;
}

/*
template<typename T>
GeoType point<T>::GetType() {
    return GeoType::POINT;
}

template<typename T>
SRID point<T>::GetSrid() {
    return srid_;
} */

template<typename T>
bg::model::point<double, 2, T> point<T>::GetGeoData() {
    return point_;
}

template<typename T>
double point<T>::Distance(std::unique_ptr<point<T>>& other) {
    if(other->GetSrid() != GetSrid()) {
        std::cout << "srid mismatch!" << std::endl;
        exit(0);
    }

    // return 0;
    return bg::distance(point_, other->GetGeoData());
}

template<typename T>
double point<T>::Distance(std::unique_ptr<line<T>>& other) {
    if(other->GetSrid() != GetSrid()) {
        std::cout << "srid mismatch!" << std::endl;
        exit(0);
    }

    return bg::distance(point_, other->GetGeoData());
}

template<typename T>
double point<T>::Distance(std::unique_ptr<polygon<T>>& other) {
    if(other->GetSrid() != GetSrid()) {
        std::cout << "srid mismatch!" << std::endl;
        exit(0);
    }
}


template<typename T>
line<T>::line(SRID srid, GeoType type, int construct_type, std::string content) : GeoBase(srid, type) {
    //srid_ = srid;
    //type_ = type;

    if(construct_type == 0) {
        byte_vector wkb_;
        bg::hex2wkb(content, std::back_inserter(wkb_));
        if(!bg::read_wkb(wkb_.begin(), wkb_.end(), line_)) {
            std::cout << "error!" << std::endl;
            exit(0);
        }
        //EWKB = content;
        EWKB = set_extension(content, GetSrid());
    }

    if(construct_type == 1) {
        std::string wkb_out;
        bg::read_wkt(content, line_);
        if(!bg::write_wkb(line_, std::back_inserter(wkb_out))) {
            std::cout << "error!" << std::endl;
            exit(0);
        }
        bg::wkb2hex(wkb_out.begin(), wkb_out.end(), EWKB);
        EWKB = set_extension(EWKB, GetSrid()); 
    }
}

template<typename T>
std::string line<T>::AsEWKB() {
    return EWKB;
}

template<typename T>
std::string line<T>::AsEWKT() {
    std::string EWKT;
    std::stringstream ioss;

    ioss << "SRID=" << static_cast<int>(GetSrid()) << ";" << bg::wkt(line_) << std::endl;

    std::string tmp;
    while(ioss >> tmp) {
        EWKT += tmp;
        EWKT += ' ';
    }
    
    return EWKT;
}

/* 
template<typename T>
GeoType line<T>::GetType() {
    return GeoType::LINESTRING;
}

template<typename T>
SRID line<T>::GetSrid() {
    return srid_;
}
*/

template<typename T>
bg::model::linestring<bg::model::point<double, 2, T>> line<T>::GetGeoData() {
    return line_;
}


template<typename T>
polygon<T>::polygon(SRID srid, GeoType type, int construct_type, std::string content) : GeoBase(srid, type) {
    //srid_ = srid;
    //type_ = type;

    if(construct_type == 0) {
        byte_vector wkb_;
        bg::hex2wkb(content, std::back_inserter(wkb_));
        if(!bg::read_wkb(wkb_.begin(), wkb_.end(), polygon_)) {
            std::cout << "error!" << std::endl;
            exit(0);
        }
        //EWKB = content;
        EWKB = set_extension(content, GetSrid());
    }

    if(construct_type == 1) {
        std::string wkb_out;
        bg::read_wkt(content, polygon_);
        if(!bg::write_wkb(polygon_, std::back_inserter(wkb_out))) {
            std::cout << "error!" << std::endl;
            exit(0);
        }
        bg::wkb2hex(wkb_out.begin(), wkb_out.end(), EWKB);
        EWKB = set_extension(EWKB, GetSrid()); 
    }
}

template<typename T>
std::string polygon<T>::AsEWKB() {
    return EWKB;
}

template<typename T>
std::string polygon<T>::AsEWKT() {
    std::string EWKT;
    std::stringstream ioss;

    ioss << "SRID=" << static_cast<int>(GetSrid()) << ";" << bg::wkt(polygon_) << std::endl;

    std::string tmp;
    while(ioss >> tmp) {
        EWKT += tmp;
        EWKT += ' ';
    }
    
    return EWKT;
}

/* template<typename T>
GeoType polygon<T>::GetType() {
    return GeoType::POLYGON;
}

template<typename T>
SRID polygon<T>::GetSrid() {
    return srid_;
} */

template class point<Wsg84>;
template class point<Cartesian>;
template class line<Wsg84>;
template class line<Cartesian>;
template class polygon<Wsg84>;
template class polygon<Cartesian>;
// template class geography<Wsg84>;
// template class geography<Cartesian>;