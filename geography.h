#pragma once
#include "geoimpl.h"
#include <vector>

template<typename T>
class geography {
    std::unique_ptr<point<T>> point_;
    std::unique_ptr<line<T>> line_;
    std::unique_ptr<polygon<T>> polygon_;
    
    GeoType type_;

 public:
    geography(SRID srid, GeoType type, int construct_type, std::string content);
    geography(std::string EWKB);
    ~geography() {}

    std::vector<std::string> ListTypes();
    std::vector<int> ListSrids();
    std::string AsEWKB();
    std::string AsEWKT(); 
    std::unique_ptr<point<T>>& GetPoint();
    std::unique_ptr<line<T>>& GetLine();
    std::unique_ptr<polygon<T>>& GetPolygon();

    GeoType GetType();
    
    // std::unique_ptr<GeoBase>& SelectGeo();
    double Distance(geography<T>& other);
}; 