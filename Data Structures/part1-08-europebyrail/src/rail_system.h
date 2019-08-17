#ifndef _RAILSYSTEM_H_
#define _RAILSYSTEM_H_

#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <queue>
#include <vector>
#include <assert.h>
#include <climits>      // INT_MAX
#include <algorithm>    // std::find

#include "service.h"
#include "city.h"

class Cheapest
{
public:
    Cheapest() {}

    bool operator()(const City* city1, const City* city2)
    {
        return city1->total_fee > city2->total_fee;
    }

    bool operator()(const City& city1, const City& city2)
    {
        return city1.total_fee > city2.total_fee;
    }

};

// For test only 
struct Route
{
    std::string from;
    std::string to;
    int fee;
    int distance;
    // recovered route. If no route was found, holds an empty vector.
    std::vector<std::string> cities;
    
    Route(const std::string& f, const std::string& t, int fe, int d, const std::vector<std::string>& cities)
            : from(f), to(t), fee(fe), distance(d), cities(cities) {};

    bool operator==(Route const& rhs) const
    {
        return rhs.from == this->from
               && rhs.to == this->to
               && rhs.fee == this->fee
               && rhs.distance == this->distance;
    };
};


class RailSystem
{
    // made by myself - TYPEDEFS
protected:
    /// Iterator of outgoing_services map
    typedef std::map<std::string, std::list<Service*>>::iterator outgoing_servicesIterator;

    /// Iterator of cities map
    typedef std::map<std::string, City*>::iterator citiesIterator;

protected:
    /// Map implements NAME -> List of roads OUTCOMING from city
    std::map<std::string, std::list<Service*> > outgoing_services;

    /// Map implements NAME -> OBJECT of this city
    std::map<std::string, City*> cities;

    /// Throws std::logic_error in case of incorrect file.
    void load_services(const std::string& filename);

    /// Fills all fields as starting values for DEIKSTRA
    void reset();

    /// returns route that is the smallest
    std::vector<std::string> recover_route(const std::string& city);

    /// Throws std::invalid_argument in case of invalid cities.
    /// DEIKSTRA
    /// returns fee/distance
    std::pair<int, int> calc_route(std::string from, std::string to);

public:

    RailSystem(const std::string& filename);

    ~RailSystem();

    /// PRINTF cheapest route
    void output_cheapest_route(const std::string& from, const std::string& to);

    /// if there a city in the map (cities) ???
    bool is_valid_city(const std::string& name);

    /// returns a city with cheapest total_fee value
    City* getCheapestCity();

    /// recounts values in nearby cities
    /// also marks this city as visited
    /// city from which roads are going is passed as an argument
    void recountInNearby(City* city);

    /// For test only.  
    Route getCheapestRoute(const std::string& from, const std::string& to);
};

#endif // _RAILSYSTEM_H_
