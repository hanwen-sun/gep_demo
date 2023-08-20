#include "geobase.h"

template<typename T>
class polygon;

template<typename T>
class line;

template<typename T>
class point: public GeoBase {
    typedef bg::model::point<double, 2, T> point_base;
    point_base point_;
    std::string EWKB;
    /*SRID srid_;
    GeoType type_; */
    // line<T> other;
    // friend class line<T>;

 public:
    point(SRID srid, GeoType type, int construct_type, std::string content);
    
    std::string AsEWKB() override;

    std::string AsEWKT() override;

    /*GeoType GetType() override;

    SRID GetSrid() override; */

    // pointbase GetGeo();
    bg::model::point<double, 2, T> GetGeoData();

    double Distance(std::unique_ptr<point<T>>& other);
    // double Distance(line& other);
    double Distance(std::unique_ptr<line<T>>& other);

    double Distance(std::unique_ptr<polygon<T>>& other);
};

template<typename T>
class line: public GeoBase {
    typedef bg::model::point<double, 2, T> point_;
    bg::model::linestring<point_> line_;
    std::string EWKB;
    /*SRID srid_;
    GeoType type_; */
    
 public:
    line(SRID srid, GeoType type, int construct_type, std::string content);
    
    std::string AsEWKB() override;

    std::string AsEWKT() override;

    /*GeoType GetType() override;

    SRID GetSrid() override; */

    bg::model::linestring<bg::model::point<double, 2, T>> GetGeoData();

    double Distance(std::unique_ptr<point<T>>& other);
};

template<typename T>
class polygon: public GeoBase {
    typedef bg::model::point<double, 2, T> point;
    bg::model::polygon<point> polygon_;
    std::string EWKB;
    /*SRID srid_;
    GeoType type_; */
    
 public:
    polygon(SRID srid, GeoType type, int construct_type, std::string content);
    
    std::string AsEWKB() override;

    std::string AsEWKT() override;

    /*GeoType GetType() override;

    SRID GetSrid() override; */
};