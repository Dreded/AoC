#include "helpers/getInput.hpp"
#include <algorithm>
#include <set>

#define EXAMPLE_FILE 0
#define PUZZLE_FILE 1

void part1(const std::vector<std::string> &lines);
void part2(const std::vector<std::string> &lines);
void printTotal(int total);
void divideDirections(const std::string &directions, std::string &santa, std::string &robo);
void getCoords(const std::string &directions, std::set<std::pair<int, int>> &visited_coords);

int main()
{
    std::vector<std::string> lines = readFile(PUZZLE_FILE);
    part1(lines);
    part2(lines);
    return 0;
}

void part1(const std::vector<std::string> &lines)
{
    int total = 0;

    // get our directions from the first line of the text file
    std::string directions = lines.front();

    // get a set representing the coords - sets only contain unique items
    std::set<std::pair<int, int>> visited_coords;
    getCoords(directions, visited_coords);

    // the total is the size of the coordinate set
    total = visited_coords.size();
    printTotal(total);
}

void part2(const std::vector<std::string> &lines)
{
    int total = 0;

    // get our directions from the first line of the text file
    std::string directions = lines.front();

    // create our storage strings 
    std::string santa_directions;
    std::string robo_santa_directions;

    //divide them for the two santas
    divideDirections(directions, santa_directions, robo_santa_directions);

    // get a set representing the coords - sets only contain unique items
    std::set<std::pair<int, int>> santa_visited_coords;
    std::set<std::pair<int, int>> robo_santa_visited_coords;

    //get the coordinates each santa visits
    getCoords(santa_directions, santa_visited_coords);
    getCoords(robo_santa_directions, robo_santa_visited_coords);

    // merge our two sets into one unique set of coords.
    std::set<std::pair<int, int>> visited_coords;
    visited_coords.insert(santa_visited_coords.begin(),santa_visited_coords.end());
    visited_coords.insert(robo_santa_visited_coords.begin(),robo_santa_visited_coords.end());

    // merge is not neccesary, set can do it itself as above
    // std::merge(santa_visited_coords.begin(), santa_visited_coords.end(),
    //            robo_santa_visited_coords.begin(), robo_santa_visited_coords.end(),
    //            std::inserter(visited_coords, visited_coords.begin()));

    // the total is the size of the coordinate set
    total = visited_coords.size();

    printTotal(total);
}

// Split directions, alternate between santa and robo santa
void divideDirections(const std::string &directions, std::string &santa, std::string &robo)
{
    for (int i = 0; i < directions.length(); i++)
    {
        if (i % 2 == 0)
            santa += directions[i];
        else
            robo += directions[i];
    }
}

//find all the coordinates santa visits
void getCoords(const std::string &directions, std::set<std::pair<int, int>> &visited_coords)
{
    std::pair<int, int> coord = {0, 0};

    // add out starting position
    visited_coords.insert(coord);

    for (char d : directions)
    {
        if (d == '^')
        {
            coord.second++;
        }
        else if (d == '>')
        {
            coord.first++;
        }
        else if (d == 'v')
        {
            coord.second--;
        }
        else if (d == '<')
        {
            coord.first--;
        }
        visited_coords.insert(coord);
    }
}

void printTotal(int total)
{
    static int calls = 1;
    printf("Part%i Total: %i\n", calls, total);
    calls++;
}