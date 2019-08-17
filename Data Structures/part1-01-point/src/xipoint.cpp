////////////////////////////////////////////////////////////////////////////////
// Module Name:  xipoint.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.1
// Date:         08.09.2017
//
// This is a part of the course "Algorithms and Data Structures"
// provided by  the School of Software Engineering of the Faculty
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "xipoint.h"

#include <algorithm>        // min
#include <cmath>

namespace xi {
    typedef unsigned int Uint;

    /// Constructor initialize a point object with two coordinates
    Point::Point(int x, int y) {
        _x = x;
        _y = y;
    }

    ///< Gets x-coordinate
    int Point::getX() const {
        return _x;
    }

    ///< Gets y-coordinate
    int Point::getY() const {
        return _y;
    }

    ///< Sets x-coordinate
    void Point::setX(int x) {
		_x = x;
    }

    ///< Sets y-coordinate
    void Point::setY(int y) {
        _y = y;
    }

    /// Shifts coordinates by adding given value shf to both coordinates
    void Point::shift(int shf) {
        _x += shf;
        _y += shf;
    }

    /// Shifts coordinates by adding given values of corresponding coordinates
    void Point::shift(int xSh, int ySh) {
        _x += xSh;
        _y += ySh;
    }

    /// Shifts coordinates by adding given values of corresponding coordinates
    /// of the give point pt
    void Point::shift(const xi::Point &pt) {
        _x += pt.getX();
        _y += pt.getY();
    }

    /// Distance to another point.  Pythagorean thm.
    double Point::dist(const xi::Point &other) {
        int x_delta = _x - other.getX();
        int y_delta = _y - other.getY();

        return sqrt(x_delta*x_delta + y_delta*y_delta);
    }

    // HERE COMES THE POINT ARRAY
    // --------------------------



    /** \brief Default constructor (a constructor with no arguments)
     *
     *  It should create an array with size 0.
     */
    PointArray::PointArray() {
        _arr = nullptr;
        _size = 0;
    }

    /** \brief Initialiaze an object with c-style array
     *
     *  The costructor initialized an object with a given c-style
     *  array points and its size (n).
     *  One need to allocate dynamically the internal array to the size of a given array.
     *  Note that const Point points[] clause is equal to const Point* points
     */
    PointArray::PointArray(const xi::Point *points, xi::PointArray::Uint n) {
        _size = n;
        _arr = new Point[_size];
        for (int i = 0; i < _size; ++i)
            _arr[i] = points[i];
    }

    /// Constructor creates a copy of a given PointArray
    PointArray::PointArray(const xi::PointArray &pv) {
        _size = pv.getSize();
        _arr = new Point[_size];
        for (int i = 0; i < _size; ++i)
            _arr[i] = pv.getRawPtr()[i];
    }

    /// Destructor that deletes the internal array of the PointArray (frees the allocated memory)
    PointArray::~PointArray() {
        clear();
    }

    /// Adds a Point to the end of the array
    void PointArray::append(const xi::Point &pt) {
        resize(_size + 1);
        _arr[_size-1] =  pt;
    }

    /** \brief Inserts a Point at a given position of the array, shifting the
     *  elements past pos to the right.
     *
     *  If pos == 0, inserts a point into the beginning of the array.
     *  If pos is bigger then the number of elements, put the point to the end.
     */
    void PointArray::insert(const xi::Point &pt, xi::PointArray::Uint pos) {

        // last probable situation
        if (pos >= _size) {
            append(pt);
            return;
        }

        _size++;
        Point* _arrNew = new Point[_size]; // new temporary array

        for (int i = 0; i < pos; ++i)   // copying before position
            _arrNew[i] = _arr[i];

        _arrNew[pos] = pt; // copying the position point

        for (int i = pos; i < _size; ++i)   // copying before position
            _arrNew[i+1] = _arr[i];

        delete[] _arr;  // clearing memory for the previous one
        _arr = _arrNew; // redirecting to new array
    }

    /** \brief Removes a Point at a given position of the array, shifting the
     *  remaining elements to the left .
     *
     *  If pos is bigger then the number of elements, does nothing.
     *  If the removed element is the last one, no more underlying array is presented
     *  after removing.
     */
    void PointArray::remove(xi::PointArray::Uint pos) {
        // first situation
        if (pos >= _size)
            return;

        // second situation
        if (_size == 1){
            clear();
            return;
        }

        // normal behaviour
        _size--;
        Point* _arrNew = new Point[_size]; // new temporary array

        for (int i = 0; i < pos; ++i)   // copying before position
            _arrNew[i] = _arr[i];

        // skipping the position copy

        for (int i = pos; i < _size; ++i)   // copying after position
            _arrNew[i+1] = _arr[i];

        delete[] _arr;  // clearing memory for the previous one
        _arr = _arrNew; // redirecting to new array
    }

    // Removes all elements from the array and sets its size to 0
    void PointArray::clear() {
        delete[] _arr;
        _arr = nullptr;
        _size = 0;
    }

    // \return The sum of distances between neighbouring points in the array.
    double PointArray::computePath() {
        double sum = 0;
        for (int i = 0; i < _size-1; ++i)
            sum += _arr[i].dist(_arr[i+1]);

        return sum;
    }

    /// Gets the size of the array
    const Uint PointArray::getSize() const {
        return _size;
    }

    /** \brief Gets a pointer to the element at a given position of the array
     *
     *  If the array contains no given element, returns nullptr
     */
    Point* PointArray::get(xi::PointArray::Uint pos) {
        if (pos >= _size)
            return nullptr;
        Point* pointer = _arr + pos;
        return pointer;
    }

    /// Const overloaded version of get() method
    const Point* PointArray::get(xi::PointArray::Uint pos) const {
        if (pos >= _size)
            return nullptr;
        const Point* pointer = _arr + pos; // because it is const, so i return const value
        return pointer;
    }

    /// Allocates a new array of size n, copies the first min (previous array
    /// size, n) existing elements into it, and deallocates the old array.
    void PointArray::resize(xi::PointArray::Uint n) {
        Point* _arrNew = new Point[n];
        for (int i = 0; i < std::min(n, _size); ++i)
            _arrNew[i] = _arr[i];

        delete[] _arr;
        _size = n;
        _arr = _arrNew;
    }

} // namespace xi {