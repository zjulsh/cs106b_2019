#include "YouGotHufflepuff.h"
#include "Testing/YouGotHufflepuffTests.h"
#include "hashset.h"
#include "vector.h"
#include "strlib.h"
#include <string>
#include <cmath>
using namespace std;

void administerQuiz(const HashSet<Question>& questions,
                    int numQuestions,
                    const HashSet<Person>& people) {
    HashMap<char, int> ans;
    ans['O'] = ans['C'] = ans['E'] = ans['A'] = ans['N'] = 0;

    for (int i = 0; i< numQuestions; i++){
        Question question = randomElement(questions);
        questions.remove(question);
        int score = askPersonalityQuestion(question);
        Vector<char> keys = question.factors.keys();

        for(int j = 0; j < keys.size(); j++){
            ans[keys[j]] += question.factors[keys[j]] * (score - 3);
        }
        displayScores(ans);
    }

    if ((int) judge(ans) == 0){
        displayMessage("Zero!");
    }
    else{
        string max_name;
        double max_sim = 0;

        for(auto p : people){
            string Name = p.name;
            HashMap<char, int> Score = p.scores;
            double Simi = similarity(ans, Score);
            if (Simi > max_sim){
                max_name = Name;
                max_sim = Simi;
            }
        }

        displayMessage("You Got " + max_name + "! (Similarity: " + doubleToString(max_sim));
    }

}

double judge(const HashMap<char, int>& score){
    Vector<char> keys = score.keys();
    double tot;

    for(auto key : keys){
        tot += score[key] * score[key];
    }
    tot = sqrt(tot);

    return tot;
}

Vector<double> norm(const HashMap<char, int>& score){
    Vector<char> keys = score.keys();
    Vector<double> ans;
    double tot;

    for(auto key : keys){
        tot += score[key] * score[key];
    }
    tot = sqrt(tot);

    for(auto key : keys){
        ans.add(score[key] / tot);
    }

    return ans;
}

double similarity(HashMap<char, int> a, HashMap<char, int> b){
    double ans = 0;
    Vector<double> aa = norm(a);
    Vector<double> bb = norm(b);

    for (int i = 0; i < a.size(); i++){
        ans += aa[i] * bb[i];
    }

    return ans;
}


/* * * * *   Test Cases Below This Point   * * * * */

/* Because administerQuiz is a function that requires interaction with the user,
 * you won't be able to directly test that administerQuiz returns the correct
 * values. Similarly, you can't call the askPersonalityQuestion, displayScores,
 * or displayMessage functions, as those are wired into the demo and don't
 * work in testing.
 *
 * However, you are welcome to add test cases to test any helper functions you
 * write! To do so, use the ADD_TEST macro to define tests, just as you did in
 * Assignment 1 and for Rising Tides.
 *
 * You aren't required to include test cases in this part of the assignment,
 * though we definitely would encourage you to do so! This is a multistep
 * assignment that's going to require each individual function to work
 * correctly, and adding tests for the functions you write is a great way to
 * find and fix bugs early on.
 */

