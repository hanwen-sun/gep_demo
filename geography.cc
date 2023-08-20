#include "geography.h"

template<typename T>
geography<T>::geography(SRID srid, GeoType type, int construct_type, std::string content) {
    type_ = type;
    switch(type) {
        case GeoType::POINT: {
            point_.reset(new point<T>(srid, type, construct_type, content));
            break;            
        }

        case GeoType::LINESTRING: {
            line_.reset(new line<T>(srid, type, construct_type, content));
            break;    
        }

        case GeoType::POLYGON: {
            polygon_.reset(new polygon<T>(srid, type, construct_type, content));
            break;    
        }
    }
}

template<typename T>
geography<T>::geography(std::string EWKB) {
    type_ = ExtractType(EWKB);
    SRID srid = ExtractSRID(EWKB);
    std::string WKB = EWKB.substr(0, 10) + EWKB.substr(18);
    WKB[8] = '0';

    switch(type_) {
        case GeoType::POINT:
            point_.reset(new point<T>(srid, type_, 0, WKB));
            break;
        case GeoType::LINESTRING:
            line_.reset(new line<T>(srid, type_, 0, WKB));
            break;
        case GeoType::POLYGON:
            polygon_.reset(new polygon<T>(srid, type_, 0, WKB));
    }
}


template<typename T>
std::string geography<T>::AsEWKB() {
    switch(type_) {
        case GeoType::POINT:
            return point_->AsEWKB();
        case GeoType::LINESTRING:
            return line_->AsEWKB();
        case GeoType::POLYGON:
            return polygon_->AsEWKB();
        default:
            break;
    }
}

template<typename T>
std::string geography<T>::AsEWKT() {
    switch(type_) {
        case GeoType::POINT:
            return point_->AsEWKT();
        case GeoType::LINESTRING:
            return line_->AsEWKT();
        case GeoType::POLYGON:
            return polygon_->AsEWKT();
        default:
            break;
    }
}

/*std::unique_ptr<GeoBase>& geography::SelectGeo() {
    switch(type_) {
        case GeoType::POINT:
            return point_;
        case GeoType::LINESTRING:
            return line_;
        case GeoType::POLYGON:
            return polygon_;
    }
}*/

template<typename T>
std::unique_ptr<point<T>>& geography<T>::GetPoint() {
    return point_;
}

template<typename T>
std::unique_ptr<line<T>>& geography<T>::GetLine() {
    return line_;
}

template<typename T>
std::unique_ptr<polygon<T>>& geography<T>::GetPolygon() {
    return polygon_;
}

template<typename T>
GeoType geography<T>::GetType() {
    return type_;
}

template<typename T>
double geography<T>::Distance(geography<T>& other) {
    // SelectGeo()->Distance();
    /*if(getsid() != other.GetType()) {
        std::cout << "srid dismatch!" << std::endl;
        exit(0);
    }*/

    switch(type_) {
        case GeoType::POINT:
            switch(other.type_) {
                case GeoType::POINT:
                    return point_->Distance(other.GetPoint());
                case GeoType::LINESTRING:
                    return point_->Distance(other.GetLine());
                case GeoType::POLYGON:
                    return point_->Distance(other.GetPolygon());
            }
        break;
    }
} 

void test_encode() {
    geography<Wsg84> g(SRID::WSG84, GeoType::POINT, 0, "0101000000000000000000f03f0000000000000040");
    std::cout << g.AsEWKB() << std::endl;
    std::cout << g.AsEWKT() << std::endl;
    
    geography<Cartesian> g_(SRID::CARTESIAN, GeoType::POINT, 1, "POINT(1.0 1.0)");
    std::cout << g_.AsEWKB() << std::endl;
    std::cout << g_.AsEWKT() << std::endl; 

    geography<Wsg84> line(SRID::WSG84, GeoType::LINESTRING, 0, "010200000003000000000000000000000000000"
    "00000000000000000000000004000000000000000400000000000000840000000000000F03F");
    std::cout << line.AsEWKB() << std::endl;
    std::cout << line.AsEWKT() << std::endl;

    geography<Cartesian> line_(SRID::CARTESIAN, GeoType::LINESTRING, 1, "LINESTRING(0 0,2 2,3 1)");
    std::cout << line_.AsEWKB() << std::endl;
    std::cout << line_.AsEWKT() << std::endl;

    geography<Wsg84> polygon(SRID::WSG84, GeoType::POLYGON, 0, "0103000000010000000500000000000000000000000000000000000000000"
    "00000000000000000000000001C400000000000001040000000000000004000000000000000400000000000000000000000000000000"
    "00000000000000000");
    std::cout << polygon.AsEWKB() << std::endl;
    std::cout << polygon.AsEWKT() << std::endl;

    geography<Cartesian> polygon_(SRID::CARTESIAN, GeoType::POLYGON, 1, "POLYGON((0 0,0 7,4 2,2 0,0 0))");
    std::cout << polygon_.AsEWKB() << std::endl;
    std::cout << polygon_.AsEWKT() << std::endl; 
}

void test_distance() {
    geography<Cartesian> g_c_1(SRID::CARTESIAN, GeoType::POINT, 1, "POINT(1.0 1.0)");
    geography<Cartesian> g_c_2(SRID::CARTESIAN, GeoType::POINT, 1, "POINT(2.0 3.0)");
    std::cout << g_c_1.Distance(g_c_2) << std::endl;

    geography<Wsg84> g_w_1(SRID::WSG84, GeoType::POINT, 1, "POINT(12.0 13.0)");
    geography<Wsg84> g_w_2(SRID::WSG84, GeoType::POINT, 1, "POINT(2.0 3.0)");

    std::cout << g_w_1.Distance(g_w_2) << std::endl;

    // geography<Cartesian> g_c_1(SRID::CARTESIAN, GeoType::LINESTRING, 1, "POINT(1.0 1.0)");
    geography<Cartesian> l_c_1(SRID::CARTESIAN, GeoType::LINESTRING, 1, "LINESTRING(0 0,2 2,3 1)");
    std::cout << g_c_2.Distance(l_c_1) << std::endl;

    geography<Wsg84> p_w_1(SRID::WSG84, GeoType::POLYGON, 1, "POLYGON((0 0,0 7,4 2,2 0,0 0))");
    std::cout << g_w_1.Distance(p_w_1) << std::endl;
}

void test_fault() {
    //geography<Wsg84> g(SRID::WSG84, GeoType::POINT, 0, "111111");
    //geography<Cartesian> c(SRID::CARTESIAN, GeoType::POINT, 0, "111111");

    // 这里默认第二个参数是0!!!
    geography<Wsg84> w(SRID::WSG84, GeoType::POINT, 1, "POINT(1.0)");
    std::cout << w.AsEWKB() << std::endl;
    std::cout << w.AsEWKT() << std::endl;

    geography<Cartesian> c(SRID::CARTESIAN, GeoType::POINT, 1, "POINT(1.0 2.0 3.0)");
    std::cout << c.AsEWKB() << std::endl;
    std::cout << c.AsEWKT() << std::endl;

}

void test_construct_fromewkb() {
    /*
    SRID s = ExtractSRID("0101000020E6100000000000000000F03F000000000000F03F");
    GeoType t = ExtractType("0101000020E6100000000000000000F03F000000000000F03F");
    if(s == SRID::WSG84)
        std::cout << "true!" << std::endl;
    if(t == GeoType::POINT)
        std::cout << "true!" << std::endl;
    
    SRID s_ = ExtractSRID("0102000020231C00000300000000000000000000000000000000000000" 
    "000000000000004000000000000000400000000000000840000000000000F03F");
    GeoType t_ = ExtractType("0102000020231C00000300000000000000000000000000000000000000" 
    "000000000000004000000000000000400000000000000840000000000000F03F");
    if(s_ == SRID::CARTESIAN)
        std::cout << "true!" << std::endl;
    if(t_ == GeoType::LINESTRING)
        std::cout << "true!" << std::endl;
    */

    std::string EWKB1 = "0101000020E6100000000000000000F03F000000000000F03F";
    SRID s = ExtractSRID(EWKB1);
    if(s == SRID::WSG84) {
        geography<Wsg84> a(EWKB1);
        std::cout << a.AsEWKT() << std::endl;
        std::cout << a.AsEWKB() << std::endl;
    }

    if(s == SRID::CARTESIAN) {
        geography<Cartesian> b(EWKB1);
        std::cout << b.AsEWKT() << std::endl;
        std::cout << b.AsEWKB() << std::endl;
    }

    std::string EWKB2 = "0102000020231C00000300000000000000000000000000000000000000" 
    "000000000000004000000000000000400000000000000840000000000000F03F";
    SRID s_ = ExtractSRID(EWKB2);
    if(s_ == SRID::WSG84) {
        geography<Wsg84> a(EWKB2);
        std::cout << a.AsEWKT() << std::endl;
        std::cout << a.AsEWKB() << std::endl;
    }

    if(s_ == SRID::CARTESIAN) {
        geography<Cartesian> b(EWKB2);
        std::cout << b.AsEWKT() << std::endl;
        std::cout << b.AsEWKB() << std::endl;
    }
}

int main() {
    // test_encode();
    // test_distance();
    // test_fault();
    test_construct_fromewkb();

    return 0;
}