#include "HumanPyramids.h"
#include "Testing/HumanPyramidTests.h"
#include "vector.h"
using namespace std;

/* TODO: Refer to HumanPyramids.h for more information about what this function should do.
 * Then, delete this comment.
 */
double weightOnBackOf(int row, int col, int pyramidHeight) {
    /* TODO: Delete the next few lines and implement this function. */
    //double weight = 160;
    Vector<Vector<int> > dp(row+5, Vector<int>(row+5, 0));;

    if (!check(row, col, pyramidHeight)){
        return 0;
    }

    weightHelp(row, col, dp);
    if (col == 0 && row == 0) return 0;

    if (col == 0) return dp[row-1][col];
    else if (col == row) return dp[row-1][col-1];
    else return dp[row-1][col-1] + dp[row-1][col];
}

double weightHelp(int row, int col, Vector<Vector<int> >& dp){
    if (row == 0 && col == 0){
        dp[0][0] = 80;
        return 80;
    }

    if (dp[row][col]) return dp[row][col];

    if (col == 0) {
        double ans = weightHelp(row-1, col, dp)/2 + 80;
        dp[row][col] = ans;
        return ans;
    }
    else if (col == row) {
        double ans = weightHelp(row-1, col-1, dp)/2 + 80;
        dp[row][col] = ans;
        return ans;
    }
    else{
        double ans = weightHelp(row-1, col-1, dp)/2 + weightHelp(row-1, col, dp)/2 + 160;
        dp[row][col] = ans;
        return ans;
    }
}

bool check(int row, int col, int pyramidHeight){
    if (row < 0 || row >= pyramidHeight){
        error("Please check your input!");
        return false;
    }
    if (col < 0 || col > row){
        error("Please check your input!");
        return false;
    }
    return true;
}





/* * * * * * Test Cases * * * * * */

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */














/* * * * * * Test cases from the starter files below this point. * * * * * */

ADD_TEST("Provided Test: Check Person E from the handout.") {
    /* Person E is located at row 2, column 1. */
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);
}

ADD_TEST("Provided Test: Function reports errors in invalid cases.") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 10));
    EXPECT_ERROR(weightOnBackOf(10, 10, 5));
    EXPECT_ERROR(weightOnBackOf(-1, 10, 20));
}

ADD_TEST("Provided Test: Warning! The next test will hang if you haven't implemented memoization.") {
    // Nothing to see here, folks. Move along...
}

ADD_TEST("Provided Test: Function returns a value, even for someone deep in the pyramid.") {
    /* This will take a LONG time to complete if memoization isn't implemented.
     * We're talking "heat death of the universe" amounts of time. :-)
     */
    EXPECT(weightOnBackOf(100, 50, 200) >= 10000);
}

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */
ADD_TEST("Provided Test: Function returns zero.") {
    /* This will take a LONG time to complete if memoization isn't implemented.
     * We're talking "heat death of the universe" amounts of time. :-)
     */
    EXPECT_EQUAL(weightOnBackOf(0, 0, 200), 0);
}
