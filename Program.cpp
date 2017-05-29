#include "Battleground.h"
using namespace std;

// class Test
// Testing Battleground game  (Autobots vs Decepticons)
class Test
{
public:
    Test() : testCount(0){}

    // Create battleground and run all tests
    void run()
    {
        try
        {
            Battleground bg;

            // Test1 - tie
            bg.add("A1", 'A', (int[8]){0,0,0,0,1,0,0,0});
            bg.add("D1", 'D', (int[8]){0,0,0,0,1,0,0,0});
            test(bg, 1, "", "");
            bg.clear();

            // Test2 - elimination by name Optimus Prime
            bg.add("Optimus Prime", 'A', (int[8]){0,0,0,0,10,0,0,0});
            bg.add("D1", 'D', (int[8]){0,0,0,0,1,0,0,0});
            test(bg, 1, "Autobots", "None");
            bg.clear();

            // Test3 - elimination by name Predaking
            bg.add("A2", 'A', (int[8]){0,0,0,0,2,0,0,0});
            bg.add("Predaking", 'D', (int[8]){0,0,0,0,10,0,0,0});
            bg.add("A1", 'A', (int[8]){0,0,0,0,1,0,0,0});
            test(bg, 1, "Decepticons", "A1");
            bg.clear();

            // Test4 -  Optimus Prime vs Predaking = fatal OptimusVsPredakingException
            bg.add("A4", 'A', (int[8]){0,0,0,0,4,0,0,0});
            bg.add("Optimus Prime", 'A', (int[8]){0,0,0,0,10,0,0,0});
            bg.add("A1", 'A', (int[8]){0,0,0,0,1,0,0,0});
            bg.add("Predaking", 'D', (int[8]){0,0,0,0,10,0,0,0});
            bg.add("D1", 'D', (int[8]){1,0,0,0,1,0,0,0});
            test(bg, -1, "", "");
            bg.clear();

            // Test5 - elimination if 
            // (courageDifference >= 4  &&  strengthDifference >= 3) 
            bg.add("A2", 'A', (int[8]){0,9,8,7,2,0,6,0});
            bg.add("D3", 'D', (int[8]){4,0,0,0,3,5,0,0});
            bg.add("A3", 'A', (int[8]){0,9,8,7,3,0,6,0});
            bg.add("A4", 'A', (int[8]){0,9,8,7,4,0,6,0});
            bg.add("D2", 'D', (int[8]){5,0,0,0,2,4,0,0});
            bg.add("A1", 'A', (int[8]){0,9,8,7,1,0,6,0});
            test(bg, 2, "Decepticons", "A2, A1");
            bg.clear();

            // Test6 - elimination if (skillDifference >= 3) 
            bg.add("A2", 'A', (int[8]){0,0,0,0,2,0,0,0});
            bg.add("A4", 'A', (int[8]){0,0,0,0,4,0,0,5});
            bg.add("D2", 'D', (int[8]){0,0,0,0,2,0,0,0});
            bg.add("A3", 'A', (int[8]){0,0,0,0,3,0,0,0});
            bg.add("D3", 'D', (int[8]){0,0,0,0,3,0,0,2});
            test(bg, 2, "Autobots", "None");
            bg.clear();

            // Test7 - winner by overallRating  
            bg.add("D3", 'D', (int[8]){2,7,7,4,3,2,6,3});
            bg.add("A1", 'A', (int[8]){0,9,8,7,1,0,6,0});
            bg.add("A4", 'A', (int[8]){0,9,8,7,4,0,6,2});
            bg.add("D2", 'D', (int[8]){1,4,5,5,2,3,8,1});
            bg.add("A2", 'A', (int[8]){0,9,8,7,2,0,6,0});
            bg.add("A3", 'A', (int[8]){0,9,8,7,3,0,6,2});
            test(bg, 2, "Autobots", "None");
            bg.clear();

            // Test 8 - all ties
            bg.add("D3", 'D', (int[8]){0,0,0,0,3,0,0,0});
            bg.add("A3", 'A', (int[8]){0,0,0,0,3,0,0,0});
            bg.add("A4", 'A', (int[8]){0,0,0,0,4,0,0,0});
            bg.add("A1", 'A', (int[8]){0,0,0,0,1,0,0,0});
            bg.add("D2", 'D', (int[8]){0,0,0,0,2,0,0,0});
            bg.add("A2", 'A', (int[8]){0,0,0,0,2,0,0,0});
            bg.add("D1", 'D', (int[8]){0,0,0,0,1,0,0,0});
            test(bg, 3, "", "");
            bg.clear();

            // Test 9 - 1 win(D3) and 2 ties(D2,D1)
            bg.add("D1", 'D', (int[8]){9,3,4,0,1,1,2,4});
            bg.add("A4", 'A', (int[8]){9,3,4,0,4,1,2,3});
            bg.add("D3", 'D', (int[8]){9,3,4,0,3,1,2,6});
            bg.add("A3", 'A', (int[8]){9,3,4,0,3,1,2,3});
            bg.add("A1", 'A', (int[8]){9,3,4,0,1,1,2,3});
            bg.add("D2", 'D', (int[8]){9,3,4,0,2,1,2,3});
            bg.add("A2", 'A', (int[8]){9,3,4,0,2,1,2,3});
            test(bg, 3, "Decepticons", "A1");
            bg.clear();

            // Test 10 - 2 wins(A3,A1) and 2 ties("Optimus Prime",A2)
            bg.add("D3", 'D', (int[8]){9,3,4,0,3,1,2,3});
            bg.add("D6", 'D', (int[8]){9,3,4,0,6,1,2,3});
            bg.add("A3", 'A', (int[8]){9,3,4,0,3,1,2,8});
            bg.add("D1", 'D', (int[8]){9,3,4,0,1,1,2,3});
            bg.add("A1", 'A', (int[8]){9,3,5,0,1,1,2,3});
            bg.add("D2", 'D', (int[8]){9,3,4,0,2,1,2,3});
            bg.add("D4", 'D', (int[8]){9,3,4,0,4,1,2,3});
            bg.add("A4", 'A', (int[8]){9,3,4,0,4,1,2,3});
            bg.add("D5", 'D', (int[8]){9,3,4,0,5,1,2,3});
            bg.add("A2", 'A', (int[8]){9,3,4,0,2,1,2,3});
            test(bg, 4, "Autobots", "D2, D1");
            bg.clear();

            // Test 11 - 2 wins(Predaking,D3), 1 loss(D5) and 1 tie(D4)
            bg.add("D2", 'D',               (int[8]){9,3,4,0,2,1,2,3});
            bg.add("A2", 'A',               (int[8]){9,3,4,0,2,1,2,3});
            bg.add("D3", 'D',               (int[8]){6,9,9,9,3,1,9,9});
            bg.add("Optimus Prime", 'A',    (int[8]){9,3,4,0,3,1,2,3});
            bg.add("A4", 'A',               (int[8]){9,3,4,0,4,1,2,3});
            bg.add("D5", 'D',               (int[8]){9,3,4,0,5,1,2,3});
            bg.add("Predaking", 'D',        (int[8]){9,3,4,0,6,1,2,3});
            bg.add("D1", 'D',               (int[8]){9,3,4,0,1,1,2,3});
            bg.add("D4", 'D',               (int[8]){9,3,4,0,4,1,2,3});
            bg.add("A1", 'A',               (int[8]){1,3,4,0,1,5,2,3});
            test(bg, 4, "Decepticons", "None");
            bg.clear();

            cout << "* Successfully passed all " << testCount << " tests" << endl;
        }
        catch (...)
        {
            cout << "Fatal error: Unhandled exception. End of game." << endl;
            exit(1);
        }
    }
    
private:
    int testCount;

    // Run battle and compare results from game with expected results
    void test(Battleground& bg, int expectedBattleCount, 
        const char* expectedWinner, const char* expectedSurvivers)
    {
        ++testCount;
        string report;
  
        try
        {
            report = bg.battle();
        }
        catch (OptimusVsPredakingException ex)
        {
            if(expectedBattleCount == -1)
            {
                cout << "Optimus Prime vs Predaking exception successfully handled.\n" << endl;
                return;
            }
            else
            {
                cout << "* Failed test #" << testCount << ". " << ex.what() << " End of game." << endl;
                exit(1);
            }
        }
        catch (...)
        {
            // In real game we will handle more specific exceptions.
            // Now we will just report error and end the game.
            cout << "Unknown fatal error. End of game." << endl;
            exit(3);
        }

  
        // Display game report
        cout << report << endl;
        
        // Get battle results and compare with expected results
        int battleCount = bg.getBattleCount();
        string winner = bg.getWinner();
        string survivers = bg.getSurvivers();

        if(battleCount != expectedBattleCount)
        {
            cout << "* Failed test #" << testCount << ": battleCount=" << 
                battleCount << ", expectedBattleCount=" << expectedBattleCount << endl; 
                
            exit(1);
        }
        
        if(winner != expectedWinner)
        {
            cout << "* Failed test #" << testCount << ": winner=" << 
                winner << ", expectedWinner=" << expectedWinner << endl; 
                
            exit(1);
        }
        
        if(survivers != expectedSurvivers)
        {
            cout << "* Failed test #" << testCount << ": survivers=" << 
                survivers << ", expectedSurvivers=" << expectedSurvivers << endl; 
                
            exit(1);
        }
    }
}; 

// Program main function
int main()
{
    cout << endl;
    
    Test test;
    test.run();
    
    return 0;
}
