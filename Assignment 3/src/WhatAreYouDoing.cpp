#include "WhatAreYouDoing.h"
#include "Testing/WhatAreYouDoingTests.h"
#include "strlib.h"
#include "cctype"
using namespace std;

/* TODO: Read the comments in WhatAreYouDoing.h to see what this function needs to do, then
 * delete this comment.
 *
 * Don't forget about the tokenize function defined in WhatAreYouDoing.h; you'll almost
 * certainly want to use it.
 */
HashSet<string> allEmphasesOf(const string& sentence) {
    Vector<string> token = tokenize(sentence);
    HashSet<string> ans;

    for(int i = 0; i < token.size(); i++){
        token[i] = toLowerCase(token[i]);
    }
    ans = helper(token, ans);

    return ans;
}

HashSet<string> helper(const Vector<string>& token, HashSet<string> ans){
    if (token.size() == 0) {
        ans.add("");
        return ans;
    }

    ans.clear();
    if (isalpha(token[0][0])){
        HashSet<string> res = helper(token.subList(1, token.size()-1), ans);
        for (string i: res){
            ans.add(token[0] + i);
        }
        for (string i: res){
            ans.add(toUpperCase(token[0]) + i);
        }
    }
    else{
        HashSet<string> res = helper(token.subList(1, token.size()-1), ans);
        for (string i: res){
            ans.add(token[0] + i);
        }
    }
    return ans;
}



/* * * * * * Test Cases * * * * * */

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */














/* * * * * * Test cases from the starter files below this point. * * * * * */

ADD_TEST("Provided Test: Enumerates all options in a simple case.") {
    HashSet<string> expected = {
        "hello",
        "HELLO",
    };

    EXPECT_EQUAL(allEmphasesOf("Hello"), expected);
}

ADD_TEST("Provided Test: Each option has the right length.") {
    string sentence = "Hello, world!";
    for (string option: allEmphasesOf(sentence)) {
        EXPECT_EQUAL(option.length(), sentence.length());
    }
}

ADD_TEST("Provided Test: Enumerates all options in a more typical case.") {
    HashSet<string> expected = {
        "you are?",
        "you ARE?",
        "YOU are?",
        "YOU ARE?"
    };

    EXPECT_EQUAL(allEmphasesOf("You Are?"), expected);
}

ADD_TEST("Provided Test: Warning! This next test will hang if you produce duplicate capitalizations.") {
    // Nothing to see here, folks. Move along!
}

ADD_TEST("Provided Test: Recursion doesn't branch on non-word symbols.") {
    string punctuation(50, '*'); // 50 copies of *

    /* The only emphasis is itself. */
    HashSet<string> expected = {
        punctuation
    };

    EXPECT_EQUAL(allEmphasesOf(punctuation), expected);
}
