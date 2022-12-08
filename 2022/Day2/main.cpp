#include "helpers/getInput.hpp"

#define EXAMPLE_FILE 0
#define PUZZLE_FILE 1

void part1(std::vector<std::string> lines);
void part2(std::vector<std::string> lines);


int getScore(int opponent, int mine)
{
    // turn letter into 0-3
    opponent = opponent - 64;
    mine = mine - 64 - 23;

    int score = mine;
    int winnerLookup[4] = {0,2,3,1};

    if (mine == winnerLookup[opponent])
    {
        // I Win
        score +=6;
    }
    else if (opponent == mine)
    {
        // Tie
        score += 3;
    }
    else
    {
        // I Lose
    }
    return score;
}

char getMyMove(int opponent, int mine)
{
    char condition = mine;
    // turn letter into 0-3
    opponent = opponent - 64;

    int winnerLookup[4] = {0,2,3,1};
    int loserLookup[4] = {0,3,1,2};

    switch (mine)
    {
    case 'X':
        // Need Lose
        mine = loserLookup[opponent];
        break;
    case 'Y':
        // Need Draw
        mine = opponent;
        break;
    case 'Z':
        // Need Win
        mine = winnerLookup[opponent];
        break;
    }
    mine = mine + 64 + 23;
    return mine;
}

int main(int argc, char **argv)
{
    std::vector<std::string> lines = readFile(PUZZLE_FILE);
    part1(lines);
    part2(lines);
    return 0;
}

void part1(std::vector<std::string> lines)
{
    /* Notes
    * A and X = Rock        = +1
    * B and Y = Paper       = +2
    * C and Z = Scissors    = +3

    Win = +6
    Lose = +0
    Tie = 3 Each
    */  
    int totalScore = 0;
    for (std::string line : lines)
    {
        const char* newLine = line.c_str();
        totalScore += getScore(newLine[0],newLine[2]);
    }
    std::cout << "Part1: Score = " << totalScore << std::endl;
}
void part2(std::vector<std::string> lines)
{
    /* Notes
    * A = Rock        = +1
    * B = Paper       = +2
    * C = Scissors    = +3
    
    * X = Need to Lose
    * Y = Need to Draw
    * Z = Need to Win

    Win = +6
    Lose = +0
    Tie = 3 Each
    */ 
   int totalScore = 0;
    for (std::string line : lines)
    {
        const char* newLine = line.c_str();
        //get what my move should be
        char myMove = getMyMove(newLine[0],newLine[2]);
        //play that move and get result
        totalScore += getScore(newLine[0],myMove);
    }
    std::cout << "Part2: Score = " << totalScore << std::endl;
}