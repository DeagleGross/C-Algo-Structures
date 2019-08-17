#pragma warning (disable:4786)
#pragma warning (disable:4503)

#include "rail_system.h"
//#include <fstream>
#include <sstream>

// ----------------------------------------------------------------------------------------------------------------
//
//        Fields:
//        /// Map implements NAME -> List of roads OUTCOMING from city
//        std::map<std::string, std::list<Service*> > outgoing_services;
//        /// Map implements NAME -> OBJECT of this city
//        std::map<std::string, City*> cities;
//
// CLASS RAILSYSTEM
// ----------------------------------------------------------------------------------------------------------------

    /// constructor with incoming filename
    RailSystem::RailSystem(const std::string &filename)
    {
        load_services(filename);
    }

    /// desctructor to delete list of pointers in outgoing_services
    /// and to delete cities pointers in cities.map
    RailSystem::~RailSystem()
    {

    }

    /// Throws std::logic_error in case of incorrect file.
    void RailSystem::load_services(const std::string &filename)
    {
        /*
         * example of input:
         * Lisbon Madrid 75 450
         * from: Lisbon
         * to: Madrid
         * fee: 75
         * distance: 450
         */

        std::ifstream file (filename);

        if (file.is_open())
        {
            std::string str;

            std::string from;
            std::string to;
            int fee;
            int distance;

            // file is opened okay
            // Считка слов из файла
            while(getline(file, str))
            {
                // making a stream from string to split
                std::istringstream streamFromString(str);

                //reading
                streamFromString >> from >> to >> fee >> distance;

                // filling map of cities
                    // inserting from and to cities
                    // std::map.insert checks if it exists
                    // so we dont need to check that they are in map
                    cities.insert(std::pair<std::string, City*>(from, new City(from)));
                    cities.insert(std::pair<std::string, City*>(to, new City(to)));

                // filling map of services
                    outgoing_servicesIterator iterator = outgoing_services.find(from);

                    // if smth was found
                    if (iterator != outgoing_services.end())
                    {
                        // taking the list from iterator and pushing new element to it
                        std::list<Service*> roadsOfCity = iterator->second;
                        roadsOfCity.push_back(new Service(to, fee, distance));
                    }
                    else
                    {
                        // new list that will contain 1 element - the first road
                        std::list<Service*> newList = std::list<Service*>();
                        newList.push_back(new Service(to, fee, distance));

                        // inserting a FROM - list that is already filled
                        outgoing_services.insert(std::pair<std::string, std::list<Service*>>(from, newList));
                    }
            }
        }
        else
        {
            // file is not opened okay
            // throwing error
            throw std::logic_error("File couldn't be opened.");
        }
    }

    /// Fills all fields as starting values for DEIKSTRA
    void RailSystem::reset()
    {
        // no need to do smth with outgoing_services map
        for(citiesIterator it = cities.begin(); it != cities.end(); ++it)
        {
            // zeroing all values of cities
            // and making distance && total_fee max = all we need for DEIKSTRA
            it->second->total_distance = INT_MAX;
            it->second->total_fee = INT_MAX;
            it->second->visited = false;
        }
    }

    /// returns route that is the smallest
    std::vector<std::string> RailSystem::recover_route(const std::string &city)
    {
        std::vector<std::string> route = std::vector<std::string>();
        City* rootCity = cities.find(city)->second;

        // going to the first_city, which "from_city" field is not defined
        while (rootCity->from_city.empty()) // || rootCity->from_city == "")
        {
            // pushing name
            route.push_back(rootCity->name);

            // going back to root one
            rootCity = cities.find(rootCity->from_city)->second;
        }

        // inversing vector - we were placing cities from end to start
        std::reverse(route.begin(), route.end());
        return route;
    }

    /// PRINTF cheapest route
    void RailSystem::output_cheapest_route(const std::string &from, const std::string &to)
    {
        // firstly - RESET
        reset();

        // then calc and get values
        std::pair<int, int> values = calc_route(from, to);

        // then get a vector of route
        std::vector<std::string> route = recover_route(to);

        for (int i = 0; i < route.size() - 1; ++i)
        {
            std::cout << route[i] << " to ";
        }

        std::cout << route[route.size()-1] << values.first << " " << values.second;
    }

    /// if there a city in the map (cities) ???
    bool RailSystem::is_valid_city(const std::string &name)
    {
        citiesIterator it = cities.find(name);

        // finding in obvious for iterators method
        return (it != cities.end());
    }

    Route RailSystem::getCheapestRoute(const std::string &from, const std::string &to)
    {
        reset();

        std::pair<int,int> values = calc_route(from, to);
        std::vector<std::string> route = recover_route(to);

        return Route(from, to, values.first, values.second, route);
    }

// ---------------------------------------------------------------------------------------------------
// all needed for deikstra - below
// ---------------------------------------------------------------------------------------------------

    /* Returns a pointer to a city with minimal "total_distance"
     * that was not marked VISITED before
     *
     * param - cities - a map of cities
     */
    City* RailSystem::getCheapestCity()
    {
        City* min;

        for (citiesIterator it = cities.begin(); it != cities.end(); ++it)
        {
            if ((min == nullptr // if min is not defined yet
                 || it->second->total_fee < min->total_fee) // if there is a city with less total_distance
                && (!it->second->visited))  // if it is not marked VISITED
            {
                min = it->second;
            }
        }

        return min;
    }

    /* Gets a list of Services of current city
     * and recounts distances if needed
     */
    void RailSystem::recountInNearby(City* city)
    {
        outgoing_servicesIterator listIt = outgoing_services.find(city->name);

        if (listIt == outgoing_services.end())
        {
            // no roads where found
            // marking this city in map of cities as visited
            // and leaving this method
            cities.find(listIt->first)->second->visited = true;
        }

        // list of outcoming roads from this city
        std::list<Service*> list = listIt->second;

        for (std::list<Service*>::iterator it = list.begin(); it != list.end(); ++it)
        {
            // object of road
            Service* road = (*it);

            // city to which road comes
            City* destination = cities.find(road->destination)->second;

            // checking if we need to change value
            if (city->total_fee + road->fee < destination->total_fee)
            {
                // int values remade
                destination->total_fee = city->total_fee + road->fee;
                destination->total_distance = city->total_distance + road->distance;

                // also we need to remake FROM_CITY field
                destination->from_city = city->name;
            }
        }

        // marking this city as visited!
        city->visited = true;
    }

    /// Throws std::invalid_argument in case of invalid cities.
    /// DEIKSTRA
    /// returns fee/distance
    std::pair<int, int> RailSystem::calc_route(std::string from, std::string to)
    {
        // checking on invalid
        if (cities.find(from) == cities.end() || outgoing_services.find(from) == outgoing_services.end()
        ||  cities.find(to) == cities.end() || outgoing_services.find(to) == outgoing_services.end())
            throw std::invalid_argument("Such cities were not found");

        // firstly making distance to FROM = 0
        cities.find(from)->second->total_distance = 0;

        // setup is ready for making Algorithm
        // ------------------------------
        while (true)
        {
            // searching for the city with lowest total_fee-value
            // and that is still not visited
            City* current = getCheapestCity();
            if (current == nullptr) // if no city was found it returns nullptr
                break;  // finishing algo if all are visited

            // going through all nearby cities and recounting their distances
            recountInNearby(current);
        }

        // here we've visited all cities
        // and returning values if last city
        // if it was not found its params will remain INT_MAX
        City* cityTo = cities.find(to)->second;
        return std::pair<int, int>(cityTo->total_fee, cityTo->total_distance);
    }