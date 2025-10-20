/* This file includes:
Definition of the self-contained vec3 class
Definition of vector utility functions
*/

#ifndef VEC3_H
#define VEC3_H

/* 
The vector is represented as an array of 3 doubles:
e[0], e[1], and e[2] are the x, y, and z components, respectively
*/
class vec3 {
    public:
        double e[3];

        vec3() : e{0,0,0} {} //default constructor that creates a zero vector
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {} //parameterized constructur that creates a vector

        //Provide named access to components (x, y, z)
        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        //operator overloads
        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); } //unary minus
        double operator[](int i) const{ return e[i]; } //index access
        double& operator[] (int i) { return e[i]; }

        //compound addition
        vec3& operator+=(const vec3& v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        //scalar multiplication
        vec3& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        //scalar division
        vec3& operator/=(double t) {
            return *this *= 1/t;
        }

        //calculate the magnitude
        double length() const {
            return std::sqrt(length_squared());
        } 

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }
}; //end class vec3

//point3 is just an alias for vec3, but it is useful for geometric clarity in the code
using point3 = vec3;

//Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' <<v.e[2];
}

/*arithmetic component-wise operations between two vectors*/
inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}
inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}
inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

/*scalar multiplication and division*/
inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}
inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}
inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

//dot product
inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

//cross product
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

//returns a normalized vector with length=1
inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

#endif