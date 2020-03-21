#include "ShiftScheduling.h"
#include "Testing/ShiftSchedulingTests.h"
#include "vector.h"
#include "error.h"
using namespace std;

/* TODO: Refer to ShiftScheduling.h for more information about what this function should do.
 * Then, delete this comment.
 */
HashSet<Shift> highestValueScheduleFor(const HashSet<Shift>& shifts, int maxHours) {
    HashSet<Shift> best, now;
    int maxValue = 0, nowValue = 0;

    if (maxHours < 0){
        error("maxHours must be positive");
        return best;
    }

    help(shifts, best, maxValue, now, nowValue, maxHours);

    return best;
}

void help(HashSet<Shift> shifts, HashSet<Shift>& best, int& maxValue, HashSet<Shift> now, int nowValue, int hour){
    if (hour <= 0 || shifts.size() == 0){
        if (nowValue > maxValue){
            maxValue = nowValue;
            best = now;
        }
        return;
    }

    Shift shift = shifts.first();
    shifts.remove(shift);

    if (hour >= lengthOf(shift) && judge(now, shift)){
        now.add(shift);
        nowValue += valueOf(shift);
        hour -= lengthOf(shift);

        help(shifts, best, maxValue, now, nowValue, hour);

        now.remove(shift);
        nowValue -= valueOf(shift);
        hour += lengthOf(shift);
    }

    help(shifts, best, maxValue, now, nowValue, hour);



    //    if (nowValue > maxValue){
//        best = now;
//        maxValue = nowValue;
//    }

//    if (shifts.size() == 0){
//        return;
//    }

//    Shift i = shifts.first();
//    if (judge(now, i) && hour >= lengthOf(i)){
//        now.add(i);
//        nowValue += valueOf(i);
//        hour -= lengthOf(i);
//        shifts.remove(i);

//        help(shifts, best, maxValue, now, nowValue, hour);
//        now.remove(i);
//        nowValue -= valueOf(i);
//        hour += lengthOf(i);
//    }
//    else{
//        shifts.remove(i);
//        help(shifts, best, maxValue, now, nowValue, hour);
//    }

}

bool judge(HashSet<Shift> best, Shift res){
    for (Shift i : best){
        if (overlapsWith(i, res))
            return false;
    }

    return true;
}

/* * * * * * Test Cases * * * * * */

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */














/* * * * * * Test cases from the starter files below this point. * * * * * */

/* This nice utility function lets you call highestValueScheduleFor, passing in
 * a Vector of shifts rather than a Set. This makes it a bit easier to test things.
 * You shouldn't need this function outside of these test cases.
 */
HashSet<Shift> asSet(const Vector<Shift>& shifts) {
    HashSet<Shift> result;
    for (Shift s: shifts) {
        result += s;
    }
    return result;
}

ADD_TEST("Provided Test: Pick a shift you do have time for.") {
    HashSet<Shift> shifts = {
        { Day::MONDAY, 9, 17, 1000 },  // Monday, 9AM - 5PM, value is 1000
    };

    EXPECT(highestValueScheduleFor(shifts, 24).size() == 1);
    EXPECT(highestValueScheduleFor(shifts, 24) == shifts);
}

ADD_TEST("Provided Test: Don't pick a shift you don't have time for.") {
    HashSet<Shift> shifts = {
        { Day::MONDAY, 9, 17, 1000 },  // Monday, 9AM - 5PM, value is 1000
    };

    EXPECT(highestValueScheduleFor(shifts, 3).isEmpty());
}

ADD_TEST("Provided Test: Don't pick overlapping shifts.") {
    Vector<Shift> shifts = {
        { Day::MONDAY, 9, 17, 1000 },  // Monday,  9AM - 5PM, value is 1000
        { Day::MONDAY, 8, 18, 2000 },  // Monday, 10AM - 6PM, value is 2000
    };

    EXPECT(highestValueScheduleFor(asSet(shifts), 100).size() == 1);
    EXPECT(highestValueScheduleFor(asSet(shifts), 100).contains(shifts[1]));
}

ADD_TEST("My test") {
    Vector<Shift> shifts = {
        { Day::MONDAY,     8, 12, 27 },  // Mon  8AM - 12PM, value 27 *
        { Day::MONDAY,    12, 16, 28 },  // Mon 12PM -  4PM, value 28 *
    };

    /* Get back the solution. */
    HashSet<Shift> computedSolution = highestValueScheduleFor(asSet(shifts), 20);

    /* Form the correct answer. It's the starred entries. */
    HashSet<Shift> actualSolution = {
        shifts[0], shifts[1]
    };
    EXPECT(computedSolution == actualSolution);

}

ADD_TEST("Provided Test: Passes the example from the handout.") {
    Vector<Shift> shifts = {
        { Day::MONDAY,     8, 12, 27 },  // Mon  8AM - 12PM, value 27 *
        { Day::MONDAY,    12, 16, 28 },  // Mon 12PM -  4PM, value 28 *
        { Day::MONDAY,    16, 20, 25 },  // Mon  4PM -  8PM, value 25 *
        { Day::MONDAY,     8, 14, 39 },  // Mon  8AM -  2PM, value 39
        { Day::MONDAY,    14, 20, 31 },  // Mon  2PM -  8PM, value 31
        { Day::TUESDAY,    8, 12,  7 },  // Tue  8AM - 12PM, value  7
        { Day::TUESDAY,   12, 16,  7 },  // Tue 12PM -  4PM, value  7
        { Day::TUESDAY,   16, 20, 11 },  // Tue  4PM -  8PM, value 11
        { Day::TUESDAY,    8, 14, 10 },  // Tue  8AM -  2PM, value 10
        { Day::TUESDAY,   14, 20,  8 },  // Tue  2PM -  8PM, value  8
        { Day::WEDNESDAY,  8, 12, 10 },  // Wed  8AM - 12PM, value 10
        { Day::WEDNESDAY, 12, 16, 11 },  // Wed 12PM -  4PM, value 11
        { Day::WEDNESDAY, 16, 20, 13 },  // Wed  4PM -  8PM, value 13
        { Day::WEDNESDAY,  8, 14, 19 },  // Wed  8AM -  2PM, value 19
        { Day::WEDNESDAY, 14, 20, 25 },  // Wed  2PM -  8PM, value 25 *
    };

    /* Get back the solution. */
    HashSet<Shift> computedSolution = highestValueScheduleFor(asSet(shifts), 20);

    /* Form the correct answer. It's the starred entries. */
    HashSet<Shift> actualSolution = {
        shifts[0], shifts[1], shifts[2], shifts[14]
    };
    EXPECT(computedSolution == actualSolution);

}
