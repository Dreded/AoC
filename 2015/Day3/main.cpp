#include "helpers/getInput.hpp"
#include <algorithm>
#include <set>

#define EXAMPLE_FILE 0
#define PUZZLE_FILE 1

void part1(std::vector<std::string> lines);
void part2(std::vector<std::string> lines);
void printTotal(int total);
void divideDirections(std::string &directions, std::string &santa, std::string &robo);
void getCoords(std::string &directions, std::set<std::pair<int,int>> &visited_coords);

int main()
{
    std::vector<std::string> lines = readFile(PUZZLE_FILE);
    part1(lines);
    part2(lines);
    return 0;
}

void part1(std::vector<std::string> lines)
{
    int total = 0;

    //get our directions from the first line of the text file
    std::string directions = lines.front();

    //get a set representing the coords - sets only contain unique items
    std::set<std::pair<int,int>> visited_coords;
    getCoords(directions, visited_coords);

    //the total is the size of the coordinate set
    total = visited_coords.size();
    printTotal(total);
}



void part2(std::vector<std::string> lines)
{
    int total = 0;

    //get our directions from the first line of the text file
    std::string directions = lines.front();

    //create our storage strings since we know the size initialize them
    int sub_directions_length = directions.length()/2+1;
    std::string santa_directions (sub_directions_length, ' ');
    std::string robo_santa_directions (sub_directions_length, ' ');

    divideDirections(directions, santa_directions, robo_santa_directions);

    //get a set representing the coords - sets only contain unique items
    std::set<std::pair<int,int>> santa_visited_coords;
    std::set<std::pair<int,int>> robo_santa_visited_coords;

    getCoords(santa_directions, santa_visited_coords);
    getCoords(robo_santa_directions, robo_santa_visited_coords);

    //merge our two sets into one unique set of coords.
    std::set<std::pair<int,int>> visited_coords;
    std::merge(santa_visited_coords.begin(), santa_visited_coords.end(),
               robo_santa_visited_coords.begin(), robo_santa_visited_coords.end(),
               std::inserter(visited_coords, visited_coords.begin()));

    //the total is the size of the coordinate set
    total = visited_coords.size();

    printTotal(total);
}

// This will take a input where every other character in the drections goes to robo_santa
// and split it into directions for santa and directions for robo_santa
void divideDirections(std::string &directions, std::string &santa, std::string &robo)
{
    for (int i = 0; i < directions.length(); i++)
    {
        if (i % 2 == 0) santa += directions[i];
        else robo += directions[i];
    }
}

void getCoords(std::string &directions, std::set<std::pair<int,int>> &visited_coords)
{
    std::pair<int,int> coord = {0,0};

    //add out starting position
    visited_coords.insert(coord);

    //loop through every character of line 1 in lines ( there is only 1 line)
    for (char &d : directions)
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
    printf("Part%i Total: %i\n", calls,total);
    calls++;
}