
/* ============================ Week One ==============================*/

// Question 1
void stringRevInPlace(string &str) {
    int len = str.length();
    /* We need to make sure to only loop up to halfway though the string
     * or we will end up with the original string! Try it out on
     * paper if this isn't clear.
     */
    for(int i = 0; i < len/2; i++) {
        char temp = str[i];
        str[i] =  str[len - i - 1];         // -1 to account for 0 indexing
        str[len - i - 1] = temp;
    }
}


// Question 2
/* We need to refine our previous method to use indexes. */
void stringRevInPlace(string &str, int start, int end) {
    int len = end - start;        // end is the index one after where you want to reverse
    for(int i = 0; i < len/2; i++) {
        char temp = str[start + i];
        str[start + i] =  str[end - i - 1]; // -1 to account for 0 indexing
        str[end- i - 1] = temp;
    }
}

void reverseWordsInPlace(string &str) {
    int start = 0;
    for(int i = 0; i < str.length(); i++) {         // reverse each word
        if(str[i] == ' ') {                             // if we are at the end of a word
            stringRevInPlace(str, start, i);
            start = i + 1;
        }
    }
    stringRevInPlace(str, 0, str.length());         // reverse entire string
}

// Question 3
bool binarySearchRecHelper(const Vector<int> &vec, int toFind, int start, int end) {
    if(start > end) return false;

    int mid = (start + end)/2;          // should use start + (end - start)/2 to avoid overflow

    /* If the element at mid is the one we are looking for, success! */
    if(vec[mid] == toFind) return true;

    /* If element at mid is less than the one we are looking for, recurse on left
     * range, elese recurse o the right range
     */
    return (vec[mid] < toFind) ? binarySearchRecHelper(vec, toFind, mid + 1, end)
                               : binarySearchRecHelper(vec, toFind, start, mid - 1);

}

bool binarySearchRec(const Vector<int> &vec, int toFind) {
    return binarySearchRecHelper(vec, toFind, 0, vec.size() - 1);
}

bool binarySearchIter(const Vector<int> &vec, int toFind) {
    /* Our range starts of as the entire vector */
    int start = 0;
    int end = vec.size() - 1;
    while(start <= end) {

        int mid = (start + end)/2;        // should use start + (end - start)/2 to avoid overflow

        /* If element at mid is less than the one we are looking for, recurse on left
         * range, elese recurse o the right range
         */
        if(vec[mid] < toFind) {
            start = mid + 1;
        } else if(vec[mid] > toFind) {
            end = mid - 1;
        }
        /* If the element at mid is the one we are looking for, success! */
        else {
            return true;
        }
    }
    return false;
}



// Question 4
struct RidgePoint {
    int elevation;
};

/*
 * Returns true if is a good collection point. Also accounts
 * for the edge cases where the point is on the left or right edge.
 */
bool isGoodPoint(const Vector<RidgePoint> &vec, int ind) {
    return (ind == 0 || vec[ind].elevation <= vec[ind - 1].elevation) &&
            (ind == vec.size()-1 || vec[ind].elevation <= vec[ind + 1].elevation);

}

int findCollectionHelper(const Vector<RidgePoint> &vec, int start, int end) {
    int mid = (start + end)/2;                  // should use start + (end - start)/2 to avoid overflow
    if(isGoodPoint(vec, mid)) return mid;       // if the current point is good, return it!

    /* If we are on a downward facing slope (left is greater than curr)
     * then search to the right of here
     */
    if(mid > 0 && vec[mid - 1].elevation > vec[mid].elevation) {
        return findCollectionHelper(vec, mid + 1, end);
    }

    /* Otherwise we are on upward facing slope; collection point is to the left
     * so we can limit our search to the left range.
     */
    else {
        return findCollectionHelper(vec, start, mid - 1);
    }
}

int findCollectionPoint(const Vector<RidgePoint> &points) {
    return findCollectionHelper(points, 0, points.size());
}

/* ============================ Week Two ==============================*/

// Question 1
Map<int, Set<string>> reverseMap(const Map<string, int> map) {
    /* Algorithm:
     *      for each oldkey in the map:
     *          use the value as a new key and add the old key
     *          to the set of values
     */
    Map<int, Set<string>> revMap;
    for(const string &oldKey : map) {
        int newKey = map[oldKey];
        revMap[newKey] += oldKey;
    }
    return revMap;
}

// Question 2
/* TODO Not code related */

// Question 3
bool isCompoundWord(const string &word, const Lexicon &dict) {
    /* Try splitting the word into two possible words for
     * every position you can make the split.
     */
    for(int i = 1; i < word.length(); i++) {
        /* If this results in two dictionary words, return true */
        if(dict.contains(word.substr(0, i)) &&
                dict.contains(word.substr(i))) {
            return true;
        }
    }
    return false;
}

void printCompoundWords(const Lexicon &dict) {
    for(const string &word : dict) {
        if(isCompoundWord(word, dict)) cout << word << endl;
    }
}

/* ============================ Week Three ==============================*/

// Question 1
void drawCarpetHelper(GWindow &window, int order,  int x, int y, double size) {
    if(order != 0) {
        int subSize = size/3;               // size of subgirds
        for(int i = 0; i < 3; i++) {        // double for loop to go through 9x9 grid
            for(int j = 0; j < 3; j++) {
                if(i != 1 || j != 1) {      // dont recurse on middle grid
                    drawCarpetHelper(window, order - 1, x + i*subSize, y  + j*subSize, subSize);
                }
            }
        }
        /* Draw square in middle sub grid */
        window.fillRect(x + subSize, y + subSize, subSize, subSize);
    }
}

void drawCarpet(GWindow &window, int order, double size) {
    drawCarpetHelper(window, order, 0, 0, size);
}


// Question 2
int numWaysToTile(int width) {
    /* There are no ways to tile a board with negative width */
    if(width < 0) return 0;
    /* If the width is 0, there is 1 way to tile it, namely leaving it*/
    if(width == 0) return 1;
    /*
     * Suppose a domino looks like this:
     *  ____
     * | ^ |
     * |_^_|
     *
     * There are 2 choices we can make:
     *
     *      Case 1 (One vertical domino):
     *           ______________________
     *          | ^ |  |  |  |  |  |  |
     *          |_^_|__|__|__|__|__|__|
     *
     *          Here the width has shrunk by 1
     * -----------
     *      Case 2 (Two stacked horizontal dominoes):
     *           ____________________
     *          | < < |  |  |  |  |  |
     *          |_< <_|__|__|__|__|__|
     *
     *          Here the width has shrunk by 2
     */

    /* We recurse on the two decisions we can make. What other recursive
     * function does this look like? It's the Fibonacci numbers!
     */
    return numWaysToTile(width - 1) + numWaysToTile(width - 2);
}


/* ============================ Week Four ==============================*/

// Question 1
void waysToSumHelper(int n, const Vector<int> &soFar) {
    if(n < 0) return;

    /* If n is 0, we have a good partition so we can print it!
     */
    if(n == 0) {
        cout << soFar << endl;      // You can print this nicely if you want
    } else {
        /* Our next number can be any non-zero number
         * less than or equal to n.
         */
        for(int i = 1; i <= n; i++) {
            Vector<int> soFarCopy = soFar;
            soFarCopy.add(i);
            waysToSumHelper(n - i, soFarCopy);
        }
    }
}

void waysToSum(int n) {
    waysToSumHelper(n, {});
}

// Question 2
void waysToSumHelperOrderless(int n, const Vector<int> &soFar) {
    if(n < 0) return;

    /* If n is 0, we have a good partition so we can print it! */
    if(n == 0) {
        cout << soFar << endl;      // You can print this nicely if you want
    } else {
        /* Our next number can be any non-zero number less than or equal to n. */
        for(int i = 1; i <= n; i++) {
            /* To avoid repetitions, we can ensure that we only build ascending sequences! */
            if(soFar.isEmpty() || i >= soFar[soFar.size()-1]) {
                Vector<int> soFarCopy = soFar;
                soFarCopy.add(i);
                waysToSumHelperOrderless(n - i, soFarCopy);
            }
        }
    }
}

void waysToSumOrderless(int n) {
    waysToSumHelperOrderless(n, {});

}

// Question 3
void listOrderingHelper(int k, const Vector<string> &soFar, const Vector<string> &choices) {
    if(k == 0) {
        cout << soFar << endl;
    } else {
        /* For each choice we can make */
        for(int i = 0; i < choices.size(); i++) {
            Vector<string> soFarCopy = soFar;
            Vector<string> choicesCopy = choices;
            /* Remove this choice from set of future choices */
            choicesCopy.remove(i);
            /* Add this to our choices made soFar */
            soFarCopy.add(choices[i]);
            /* Recurse on k-1 since we have used up one choice*/
            listOrderingHelper(k - 1, soFarCopy, choicesCopy);
        }
    }
}

void listKOrderings(int k, const Vector<string> &choices) {
    listOrderingHelper(k, {}, choices);
}


/* ============================ Week Five ==============================*/

// Question 1

bool isMultCompoundWord(const string &word, const Lexicon &dict) {

    /* This technically counts an empty string as a multi compound word
     * but we could just wrap this in a function to avoid that case.
     */
    if(word == "") return true;

    /* Try every prefix of the word string that is a dictionary word.
     * For each such prefix, we can check if the remaning is a dictionary word
     * and if so return true. If the remaining isn't a dictionary word,
     * we can recurse on it because there may be ways to break down the remaining
     * into smaller pieces that are English words.
     */
    for(int i = 1; i < word.length(); i++) {
        /* If the prefix is an English word */
        if(dict.contains(word.substr(0, i))) {

            /* If the remaining is an English word or can be split up into
             * English words, return true;
             */
            if(dict.contains(word.substr(i)) || isMultCompoundWord(word.substr(i), dict)) {
                return true;
            }
        }
    }
    return false;
}

void printMultCompoundWords(const Lexicon &dict) {
    for(const string &word : dict) {
        if(isMultCompoundWord(word, dict)) cout << word << endl;
    }
}


// Question 2
bool canMoveToBottomHelper(int r, int c, const Grid<int> &grid, Grid<bool> &visited) {
    /* If we are out of bounds or been here before, we can't continue */
    if(!grid.inBounds(r, c) || visited[r][c]) return false;

    /* If we are at the final spot, we've made it! */
    if(r == grid.numRows() - 1 && c == grid.numCols() - 1) return true;

    /* Mark this spot as visited so we don't end up in ifninite loop. */
    visited[r][c] = true;   

    int currNum = grid[r][c];           // how much we can move

    /* Try moving in each direction by the allowed amount */
    return canMoveToBottomHelper(r + currNum, c, grid, visited)
            || canMoveToBottomHelper(r - currNum, c, grid, visited)
                || canMoveToBottomHelper(r, c  + currNum, grid, visited)
                    || canMoveToBottomHelper(r, c  - currNum, grid, visited);
}


bool canMoveToBottom(const Grid<int> &grid) {

    /* Need to keep track of places we've visited to avoid 
     * infinite loop. */
    Grid<bool> visited(grid.numRows(), grid.numCols(), false);

    /* 0,0 is upper left corner */
    return canMoveToBottomHelper(0, 0, grid, visited);
}

// Question 3
/* This is pretty much the midterm problem */

/* ============================ Week Six ==============================*/

// Question 1
// TODO

// Question 2
// TODO


/* ============================ Week Seven ==============================*/

struct Node {
    string value;
    Node *next;
};


int listLength(Node *list) {
    int count = 0;
    for(Node *curr = list; curr != nullptr; curr = curr->next) {
        count++;
    }
    return count;
}

/*
 * One simple approach is to figure out the length of
 * the list and then move len - k steps into the list.
 */
Node *kthToLastSimple(Node *list, int k) {
    /* Find length of the list */
    int len = listLength(list);

    /* If the list is too small, just return nullptr*/
    if(len < k) return nullptr;

    /* Move len - k + 1 steps into the list */
    Node *curr = list;
    for(int i = 0; i < len - k; i++) {
        curr = curr->next;
    }
    return curr;
}

/*
 * Another interesting approach is to use the runner technique.
 * We have two pointers, the runner and the follower. We first
 * move the runner k steps into the list, then move both the
 * runner and the follower until the runner hits the end of the
 * list.
 */
Node *kthToLastRunner(Node *list, int k) {
    /* Move the runner k steps into the list */
    Node *runner = list;
    for(int i = 0; i < k; i++) {
        /* If the runner reaches the end of the list before
         * exhausting k, the list is too small.
         */
        if(runner == nullptr) return nullptr;
        runner = runner->next;
    }
    /* Advance both follower and runner together until runner
     * hits end of the list.
     */
    Node *follower = list;
    while(runner != nullptr) {
        runner = runner->next;
        follower = follower->next;
    }
    return follower;
}


/*
 * The recursive method uses the recursion to find
 * out many nodes are in front of list.
 */
int kthToLastRecHelper(Node *list, Node *&ret, int k) {
    /* If list is empty, there are 0 nodes in front */
    if(list == nullptr) return 0;

    /* If the number of nodes in front of list is equal to
     * k-1 then this is the k-th last node. We can set the
     * out parameter to this node.
     */
    int numInFront = kthToLastRecHelper(list, ret, k);
    if(numInFront == k - 1) {
        ret = list;
    }
    /* Tell previous recursive call's node how many nodes are in front of it*/
    return numInFront + 1;
}


Node *kthToLastRec(Node *list, int k) {
    Node *ret;
    (void) kthToLastRecHelper(list, ret, k);    // discard int return
    return ret;
}


// Question 2
void sortedInsert(Node *toIns, Node *&list) {
    /* If new node should be inserted at the start */
    if(list == nullptr || toIns->value < list->value) {
        toIns->next = list;
        list = toIns;
    } else {
        Node *curr = list;
        Node *prev = nullptr;
        /* Loop through the list until you find the place to
         * to insert the new node.
         */
        while(curr != nullptr && curr->value < toIns->value) {
            prev = curr;
            curr = curr->next;
        }
        toIns->next = curr;
        prev->next = toIns;
    }

}

void listInsertionSort(Node *&list) {
    Node *sortedList = nullptr;
    Node *curr = list;
    while(curr != nullptr) {
        /* Need to store next because inserting will mess with
         * curr's next pointer. */
        Node *next = curr->next;
        sortedInsert(curr, sortedList);
        curr = next;
    }
    list = sortedList;

}

// Question 3
Node *getIntersection(int diff, Node *bigger, Node *smaller) {
    /* Advance the bigger list for the difference in lengths
     * of the two lists. By the end of this, if the two lists
     * intersect, then bigger and smaller are both the same
     * distance away from the end point.
     */
    for(int i = 0; i < diff; i++) {
        bigger = bigger->next;
    }
    /* Now we can advance both together. If they have a common
     * point, they will hit it at the same time (try it out on paper)!.
     */
    Node *curr1 = bigger;
    Node *curr2 = smaller;
    while(curr1 != nullptr && curr2 != nullptr) {
        if(curr1 == curr2)  {
            return curr1;
        }
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    return nullptr;
}

/*
 * One idea is to gain the fundamental insight that
 * if two linked list meet at some point, if we start
 * the same distance away from the common end point of the
 * two lists and then advance forward simultaneously in both,
 * we will eventually hit the same node.
 */
Node *findIntersection(Node *list1, Node *list2) {
    /* Find the difference in lenght between the two lists */
    int len1 = listLength(list1);
    int len2 = listLength(list2);
    int diff = abs(len1 - len2);

    /* Pass the bigger list as the second parameter */
    if(len1 > len2) {
        return getIntersection(diff, list1, list2);
    } else {
        return getIntersection(diff, list2, list1);
    }
}


/* ============================ Week Eight ==============================*/

// Question 1
struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;
};

bool mirrorEquals(TreeNode *root1, TreeNode *root2) {
    /* Two empty trees are trivially equal */
    if(root1 == nullptr && root2 == nullptr) return true;
    /* If one of the trees is empty and the other is not or the
     * values of root1 and root2 are different, the trees can't
     * be mirror images of each other.
     */
    if(root1 == nullptr || root2 == nullptr ||
            root1->value != root2->value) return false;
    /* Recursively check if the left subtree of the first tree is a
     * mirror image of the right subtree of the second tree and similarly,
     * if the right substree of the first tree is a mirror image of the
     * left subtree of the second tree.
     */
    return mirrorEquals(root1->left, root2->right) &&
            mirrorEquals(root1->right, root2->left);
}

bool isPalindromicTree(TreeNode *root) {
    return mirrorEquals(root, root);
}


// Question 2

/*
 * Gets last node in a linked list.
 */
TreeNode *lastNode(TreeNode *list) {
    if(list == nullptr) return nullptr;
    while(list->right != nullptr) {
        list = list->right;
    }
    return list;
}

TreeNode *flattenTree(TreeNode *root) {
    /* If root is null we already have a DLL :) */
    if(root == nullptr) return nullptr;

    TreeNode *head = root;      // this will be the head of the DLL we return

    /* Recursively convert left and right subtree to a DLL, where
     * the value returned by the recursion is the **HEAD** of
     * the converted DLL.
     */
    TreeNode *left = flattenTree(root->left);
    TreeNode *right = flattenTree(root->right);

    /* We want to combine the left DLL, current node, and right DLL.
     * To do this we need the last node in the left DLL so we can
     * connect it to the current node.
     */
    TreeNode *leftLast = lastNode(left);
    root->left = leftLast;
    
    /* If the left list isn't empty, then we should set the head of
     * the DLL we are going to return to be the head of the left DLL.
     */
    if(leftLast != nullptr) {
        head = left;
        leftLast->right = root;
    }

    /* Connect current node to the right DLL */
    root->right = right;

    /* Return head of new DLL */
    return head;
}


// Question 3
// Not code related

/* ============================ Week Nine ==============================*/

// Question 1
// Not code related

// Question 2
/* You could use BFS or a DFS with a limit on the recursion depth. */
