#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int a = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (i != j && preferences[i][j] > preferences[j][i])
            {
                pairs[a].winner = i;
                pairs[a].loser = j;
                a++;
                pair_count++;
            }
            
            else if (i != j && preferences[i][j] < preferences[j][i])
            {
                pairs[a].winner = j;
                pairs[a].loser = i;
                a++;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory //selection sort
void sort_pairs(void)
{
    int max, tempwin, templos;
    
    for (int i = 0; i < pair_count - 1; i++)
    {
        int a = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        max = i;
        
        for (int j = i + 1; j < pair_count; j++)
        {
            int b = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            
            if (a < b)
            {
                max = j;
            }
        }
        tempwin = pairs[i].winner;
        pairs[i].winner = pairs[max].winner;
        pairs[max].winner = tempwin;
        templos = pairs[i].loser;
        pairs[i].loser = pairs[max].loser;
        pairs[max].loser = templos;
    }   
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int a = 0;
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        locked[pairs[i].loser][pairs[i].winner] = false;
        locked[i][i] = false;
    }
    for (int j = 0; j < pair_count; j++)
    {
        for (int k = j + 1; k < pair_count; k++)
        {
            a++;
            if (pairs[j].winner == pairs[k].winner)
            {
                return;
            }
            else if (a == pair_count + 1)
            {
                locked[pairs[pair_count - 1].winner][pairs[pair_count - 1].loser] = false;
            }
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int a = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[0][i] == false)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                if (locked[j][i] == false)
                {
                    a++;
                    if (a == candidate_count)
                    {
                        printf("%s\n", candidates[i]);
                        return;
                    }
                }
                else
                {
                    a = 0;
                }
            }
        }
    }
    return;
}
