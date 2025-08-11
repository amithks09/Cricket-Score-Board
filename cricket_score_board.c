#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct batsman
{
    char name[50];
    int runs;
    int balls;
    int fours;
    int sixes;
    int out;
    struct batsman *next;
};
typedef struct batsman *bat;

struct bowler
{
    char name[50];
    int runsgiven;
    int wickets;
    int oversbowled;
    struct bowler *next;
};
typedef struct bowler *ball;

int main()
{
    char team_1[50], team_2[50];
    char toss[10];
    int toss_result, user_choice;
    int batsman_count, bowler_count;
    int userBattingFirst;
    FILE *fp = fopen("cricket_score_board.txt", "w");
    if (!fp)
    {
        printf("Error opening file!\n");
        return 1;
    }
    srand(time(NULL)); // Seed random number generator

    printf("Enter name of Team 1: ");
    scanf(" %[^\n]", team_1);
    printf("Enter name of Team 2: ");
    scanf(" %[^\n]", team_2);

    printf("\n--- Toss ---\n");
    printf("Choose Heads or Tails: ");
    scanf("%s", toss);

    fprintf(fp, "Teams: %s vs %s\n", team_1, team_2);

    printf("\nTOSS TIME!\nChoose heads or tails (enter 'heads' or 'tails'): ");
    toss_result = rand() % 2; // 0 for Heads, 1 for Tails
    if ((toss_result == 0 && strcmp(toss, "Heads") == 0) || (toss_result == 1 && strcmp(toss, "Tails") == 0))
    {
        printf("You won the toss!\nChoose:\n1. Bat\n2. Bowl\nEnter your choice: ");
        scanf("%d", &user_choice);
        userBattingFirst = (user_choice == 1);
        fprintf(fp, "User won the toss and chose to %s first.\n", userBattingFirst ? "bat" : "bowl");
    }
    else
    {
        printf("Computer won the toss!\n");
        userBattingFirst = rand() % 2;
        printf("Computer chose to %s first.\n", userBattingFirst ? "bat" : "bowl");
        fprintf(fp, "Computer won the toss and chose to %s first.\n", userBattingFirst ? "bat" : "bowl");
    }

    fprintf(fp, "\n--- First Innings: %s Batting ---\n", team_1);
    printf("\n--- First Innings: %s Batting ---\n", team_1);
    printf("Enter number of batsmen for %s: ", team_1);
    scanf("%d", &batsman_count);

    bat firstInningsBatsmen = NULL;
    bat tempBatsman = NULL;
    for (int i = 0; i < batsman_count; i++)
    {
        printf("\n--- Batsman %d ---\n", i + 1);
        struct batsman *newBatsman = (struct batsman *)malloc(sizeof(struct batsman));
        printf("Enter name: ");
        scanf(" %[^\n]", newBatsman->name);
        printf("Enter runs: ");
        scanf("%d", &newBatsman->runs);
        printf("Enter balls: ");
        scanf("%d", &newBatsman->balls);
        printf("Enter fours: ");
        scanf("%d", &newBatsman->fours);
        printf("Enter sixes: ");
        scanf("%d", &newBatsman->sixes);
        printf("Enter out (1 for out, 0 for not out): ");
        scanf("%d", &newBatsman->out);
        newBatsman->next = NULL;
        if (i == 0)
        {
            firstInningsBatsmen = newBatsman;
            tempBatsman = newBatsman;
        }
        else
        {
            tempBatsman->next = newBatsman;
            tempBatsman = newBatsman;
        }
    }

    printf("\nEnter number of bowlers for %s: ", team_2);
    scanf("%d", &bowler_count);
    ball firstInningsBowlers = NULL;
    ball tempBowler = NULL;
    for (int i = 0; i < bowler_count; i++)
    {
        printf("\n--- Bowler %d ---\n", i + 1);
        struct bowler *newBowler = (struct bowler *)malloc(sizeof(struct bowler));
        printf("Enter name: ");
        scanf(" %[^\n]", newBowler->name);
        printf("Enter runs given: ");
        scanf("%d", &newBowler->runsgiven);
        printf("Enter wickets: ");
        scanf("%d", &newBowler->wickets);
        printf("Enter balls bowled: ");
        scanf("%d", &newBowler->oversbowled);
        newBowler->next = NULL;
        if (i == 0)
        {
            firstInningsBowlers = newBowler;
            tempBowler = newBowler;
        }
        else
        {
            tempBowler->next = newBowler;
            tempBowler = newBowler;
        }
    }

    fprintf(fp, "\n--- Batting Stats of %s ---\n", team_1);
    int firstInningsScore = 0;
    fprintf(fp, "\n%-20s %-5s %-5s %-5s %-5s %-10s %-10s\n", "Name", "Runs", "Balls", "4s", "6s", "StrikeRate", "Status");
    bat b = firstInningsBatsmen;
    while (b != NULL)
    {
        float strikeRate;
        if (b->balls > 0)
        {
            strikeRate = ((float)b->runs / b->balls) * 100;
        }
        else
        {
            strikeRate = 0;
        }
        fprintf(fp, "%-20s %-5d %-5d %-5d %-5d %-10.2f %-10s\n",
               b->name, b->runs, b->balls, b->fours, b->sixes,
               strikeRate, b->out ? "Out" : "Not Out");
        firstInningsScore += b->runs;
        b = b->next;
    }

    fprintf(fp, "\n--- Bowling Stats of %s ---\n", team_2);
    fprintf(fp, "\n%-20s %-10s %-10s %-10s %-10s\n", "Name", "Overs", "Runs", "Wickets", "Economy");
    ball bow = firstInningsBowlers;
    while (bow != NULL)
    {
        float overs = bow->oversbowled / 6.0;
        float economy;
        if (overs > 0)
        {
            economy = (float)bow->runsgiven / overs;
        }
        else
        {
            economy = 0;
        }
        fprintf(fp, "%-20s %-10.1f %-10d %-10d %-10.2f\n", bow->name, overs, bow->runsgiven, bow->wickets, economy);
        bow = bow->next;
    }
    fprintf(fp, "\nTotal Score of %s: %d\n", team_1, firstInningsScore);

    // Second Innings
    fprintf(fp, "\n--- Second Innings: %s Batting ---\n", team_2);
    printf("\n--- Second Innings: %s Batting ---\n", team_2);
    printf("Enter number of batsmen for %s: ", team_2);
    scanf("%d", &batsman_count);
    bat secondInningsBatsmen = NULL;
    tempBatsman = NULL;
    for (int i = 0; i < batsman_count; i++)
    {
        printf("\n--- Batsman %d ---\n", i + 1);
        struct batsman *newBatsman = (struct batsman *)malloc(sizeof(struct batsman));
        printf("Enter name: ");
        scanf(" %[^\n]", newBatsman->name);
        printf("Enter runs: ");
        scanf("%d", &newBatsman->runs);
        printf("Enter balls: ");
        scanf("%d", &newBatsman->balls);
        printf("Enter fours: ");
        scanf("%d", &newBatsman->fours);
        printf("Enter sixes: ");
        scanf("%d", &newBatsman->sixes);
        printf("Enter out (1 for out, 0 for not out): ");
        scanf("%d", &newBatsman->out);
        newBatsman->next = NULL;
        if (i == 0)
        {
            secondInningsBatsmen = newBatsman;
            tempBatsman = newBatsman;
        }
        else
        {
            tempBatsman->next = newBatsman;
            tempBatsman = newBatsman;
        }
    }

    printf("\nEnter number of bowlers for %s: ", team_1);
    scanf("%d", &bowler_count);
    ball secondInningsBowlers = NULL;
    tempBowler = NULL;
    for (int i = 0; i < bowler_count; i++)
    {
        printf("\n--- Bowler %d ---\n", i + 1);
        struct bowler *newBowler = (struct bowler *)malloc(sizeof(struct bowler));
        printf("Enter name: ");
        scanf(" %[^\n]", newBowler->name);
        printf("Enter runs given: ");
        scanf("%d", &newBowler->runsgiven);
        printf("Enter wickets: ");
        scanf("%d", &newBowler->wickets);
        printf("Enter balls bowled: ");
        scanf("%d", &newBowler->oversbowled);
        newBowler->next = NULL;
        if (i == 0)
        {
            secondInningsBowlers = newBowler;
            tempBowler = newBowler;
        }
        else
        {
            tempBowler->next = newBowler;
            tempBowler = newBowler;
        }
    }

    fprintf(fp, "\n--- Batting Stats of %s ---\n", team_2);
    int secondInningsScore = 0;
    fprintf(fp, "\n%-20s %-5s %-5s %-5s %-5s %-10s %-10s\n", "Name", "Runs", "Balls", "4s", "6s", "StrikeRate", "Status");
    b = secondInningsBatsmen;
    while (b != NULL)
    {
        float strikeRate;
        if (b->balls > 0)
        {
            strikeRate = ((float)b->runs / b->balls) * 100;
        }
        else
        {
            strikeRate = 0;
        }
        fprintf(fp, "%-20s %-5d %-5d %-5d %-5d %-10.2f %-10s\n",
               b->name, b->runs, b->balls, b->fours, b->sixes,
               strikeRate, b->out ? "Out" : "Not Out");
        secondInningsScore += b->runs;
        b = b->next;
    }
    fprintf(fp, "\n--- Bowling Stats of %s ---\n", team_1);
    fprintf(fp, "\n%-20s %-10s %-10s %-10s %-10s\n", "Name", "Overs", "Runs", "Wickets", "Economy");
    bow = secondInningsBowlers;
    while (bow != NULL)
    {
        float overs = bow->oversbowled / 6.0;
        float economy;
        if (overs > 0)
        {
            economy = (float)bow->runsgiven / overs;
        }
        else
        {
            economy = 0;
        }
        fprintf(fp, "%-20s %-10.1f %-10d %-10d %-10.2f\n", bow->name, overs, bow->runsgiven, bow->wickets, economy);
        bow = bow->next;
    }

    fprintf(fp, "\nTotal Score of %s: %d\n", team_2, secondInningsScore);

    // Determine the winner based on scores and print the result
    fprintf(fp, "\n--- Match Result ---\n");
    if (firstInningsScore > secondInningsScore)
    {
        fprintf(fp, "\n%s wins by %d runs!\n", team_1, firstInningsScore - secondInningsScore);
    }
    else if (secondInningsScore > firstInningsScore)
    {
        fprintf(fp, "\n%s wins by %d runs!\n", team_2, secondInningsScore - firstInningsScore);
    }
    else
    {
        fprintf(fp, "\nIt's a tie!\n");
    }

    fprintf(fp, "\n--- End of Game ---\n");
    fprintf(fp, "Thank you for playing!\n");
    fclose(fp);
    printf("\nMatch details have been saved to cricket_score_board.txt\n");
    return 0;
}
