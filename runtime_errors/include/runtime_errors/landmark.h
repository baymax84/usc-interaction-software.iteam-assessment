#ifndef RUNTIMEERRORS_LANDMARK_H_
#define RUNTIMEERRORS_LANDMARK_H_

#include <string>
#include <sstream>

class Landmark
{
public:
    double x_;
    double y_;
    double theta_;
    std::string type_;
    unsigned int id_;

    Landmark( Landmark const & other );

    Landmark( double const & x = 0, double const & y = 0, double const & theta = 0, std::string const & type = "", unsigned int const & id = 0 );

    std::string toString() const;
};

#endif // RUNTIMEERRORS_LANDMARK_H_
