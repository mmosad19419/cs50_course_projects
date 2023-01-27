#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
const int MAX_VOTERS = 100;
const int MAX_CANDIDATES = 9;

// preferences[i][j] is jth preference for voter i
int preferences[100][9];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // checking the voter preference with the candidates names
    int i = voter;
    int j = rank;
    for (int l = 0; l < candidate_count; l++)
    {
        // update preference array
        if (strcmp(name, candidates[l].name) == 0)
        {
            preferences[i][j] = l;
            return true;
        }
    }
    //returning false if the candidate not found
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // checking the ranks of each voter
    for (int i = 0; i < voter_count; i++)
    {
        int j = 0;
        //going to the voter next rank if the candidate at the checked rank is eliminated
        while (candidates[preferences[i][j]].eliminated == true)
        {
            j++;
        }

        // add votes while candidate-eliminated-status is false
        if (candidates[preferences[i][j]].eliminated == false)
        {
            candidates[preferences[i][j]].votes++;
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // checking for the candidates with votes more than half
    for (int c = 0; c < candidate_count; c++)
    {
        if (candidates[c].votes > voter_count / 2)
        {
            printf("%s\n", candidates[c].name);
            return true;
        }
    }
    // if no candidate has more than half of the votes return false
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // checking every candidate votes to get the minimum votes
    int min = 0;
    for (int a = 0; a < candidate_count; a++)
    {
        if (candidates[a].eliminated == false)
        {
            int m = 0;
            for (int c = 0; c < candidate_count; c++)
            {
                if (candidates[c].eliminated == false)
                {
                    if (candidates[a].votes <= candidates[c].votes)
                    {
                        m++;
                    }

                    if (m == candidate_count - 1)
                    {
                        min = candidates[a].votes;
                    }
                }
            }
        }

    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // comparing min with each candidate.votes
    int n = 0;
    int t = 0;
    for (int a = 0; a < candidate_count; a++)
    {
        if (candidates[a].eliminated == false)
        {
            n ++;
            if (candidates[a].votes == min)
            {
                t++;
            }
        }
    }

    if (t == n)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // comparing each candidate votes with min, if it is equal to min eliminate him
    for (int a = 0; a < candidate_count; a++)
    {
        if (candidates[a].votes == min)
        {
            candidates[a].eliminated = true;
        }
    }
    return;
}
