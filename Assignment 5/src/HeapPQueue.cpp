#include "HeapPQueue.h"
#include "Testing/HeapTests.h"
#include "vector.h"
using namespace std;

HeapPQueue::HeapPQueue() {
    /* TODO: Implement this. */
    capcity = 10000;
    logical_size = 0;
    elem = new Vector<DataPoint>;
    DataPoint dummy;
    elem->add(dummy);
}

HeapPQueue::~HeapPQueue() {
    /* TODO: Implement this. */
    delete elem;
}

void HeapPQueue::enqueue(const DataPoint& data) {
    /* TODO: Delete the next line and implement this. */
    logical_size++;
    elem->add(data);
    (*elem)[logical_size] = data;
    int i = logical_size;

    while (i != 1){
        DataPoint father = (*elem)[i/2];
        if (father.weight > data.weight){
            (*elem)[i/2] = data;
            (*elem)[i] = father;
            i /= 2;
        }
        else{
            break;
        }
    }
}

int HeapPQueue::size() const {
    /* TODO: Delete the next line and implement this. */
    return logical_size;
}

DataPoint HeapPQueue::peek() const {
    /* TODO: Delete the next line and implement this. */
    if (size() == 0) error("No element in heap.");
    return (*elem)[logical_size];
}

DataPoint HeapPQueue::dequeue() {
    /* TODO: Delete the next line and implement this. */
    if (size() == 0){
        error("No element in heap!");
        return (*elem)[0];
    }

    DataPoint ans = (*elem)[1];

    (*elem)[1] = (*elem)[logical_size];
    logical_size--;
    int i = 1;
    int next;

    while (i*2 <= logical_size){
        DataPoint now = (*elem)[i];
        DataPoint left = (*elem)[2*i];
        DataPoint right = (*elem)[2*i+1];
        if (left.weight < right.weight){
            next = 2*i;
        }else{
            next = 2*i+1;
        }

        if (now.weight > (*elem)[next].weight){
            (*elem)[i] = (*elem)[next];
            (*elem)[next] = now;
            i = next;
        }else{
            break;
        }
    }

    return ans;

}

bool HeapPQueue::isEmpty() const {
    /* TODO: Delete the next line and implement this. */
    return logical_size == 0;
}

/* This function is purely for you to use during testing. You can have it do whatever
 * you'd like, including nothing. We won't call this function during grading, so feel
 * free to fill it with whatever is most useful to you!
 *
 * TODO: Delete this comment and replace it with one describing what this function
 * actually does.
 */
void HeapPQueue::printDebugInfo() {
    /* TODO: Delete this comment and (optionally) put debugging code here. */
}




/* * * * * * Test Cases Below This Point * * * * * */

/* TODO: Add your own custom tests here! */














/* * * * * Provided Tests Below This Point * * * * */

ADD_TEST("Provided Test: Newly-created heap is empty.") {
    HeapPQueue pq;

    EXPECT(pq.isEmpty());
    EXPECT(pq.size() == 0);
}

ADD_TEST("Provided Test: Enqueue / dequeue single element") {
    HeapPQueue pq;
    DataPoint point = { "enqueue me!", 4 };
    pq.enqueue(point);
    EXPECT_EQUAL(pq.size(), 1);
    EXPECT_EQUAL(pq.isEmpty(), false);

    EXPECT_EQUAL(pq.dequeue(), point);
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);

    pq.enqueue(point);
    EXPECT_EQUAL(pq.size(), 1);
    EXPECT_EQUAL(pq.isEmpty(), false);

    EXPECT_EQUAL(pq.dequeue(), point);
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

ADD_TEST("Provided Test: Dequeue / peek on empty heap throws error") {
    HeapPQueue pq;

    EXPECT(pq.isEmpty());
    EXPECT_ERROR(pq.dequeue());
    EXPECT_ERROR(pq.peek());
}

ADD_TEST("Provided Test: Enqueue elements in sorted order.") {
    HeapPQueue pq;
    for (int i = 0; i < 10; i++) {
        pq.enqueue({ "elem" + to_string(i), i });
    }

    EXPECT_EQUAL(pq.size(), 10);
    for (int i = 0; i < 10; i++) {
        auto removed = pq.dequeue();
        DataPoint expected = {
            "elem" + to_string(i), i
        };
        EXPECT_EQUAL(removed, expected);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

ADD_TEST("Provided Test: Enqueue elements in reverse-sorted order.") {
    HeapPQueue pq;
    for (int i = 10; i >= 0; i--) {
        pq.enqueue({ "elem" + to_string(i), i });
    }

    EXPECT_EQUAL(pq.size(), 11);
    for (int i = 0; i <= 10; i++) {
        auto removed = pq.dequeue();
        DataPoint expected = {
            "elem" + to_string(i), i
        };
        EXPECT_EQUAL(removed, expected);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

ADD_TEST("Provided Test: Insert ascending and descending sequences.") {
    HeapPQueue pq;
    for (int i = 0; i < 20; i++) {
        pq.enqueue({ "a" + to_string(i), 2 * i });
    }
    for (int i = 19; i >= 0; i--) {
        pq.enqueue({ "b" + to_string(i), 2 * i + 1 });
    }

    EXPECT_EQUAL(pq.size(), 40);
    for (int i = 0; i < 40; i++) {
        auto removed = pq.dequeue();
        EXPECT_EQUAL(removed.weight, i);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

ADD_TEST("Provided Test: Insert random permutation.") {
    Vector<DataPoint> sequence = {
        { "A", 0 },
        { "D", 3 },
        { "F", 5 },
        { "G", 6 },
        { "C", 2 },
        { "H", 7 },
        { "I", 8 },
        { "B", 1 },
        { "E", 4 },
        { "J", 9 },
    };

    HeapPQueue pq;
    for (DataPoint elem: sequence) {
        pq.enqueue(elem);
    }

    EXPECT_EQUAL(pq.size(), sequence.size());

    for (int i = 0; i < 10; i++) {
        auto removed = pq.dequeue();
        DataPoint expected = {
            string(1, 'A' + i), i
        };
        EXPECT_EQUAL(removed, expected);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

ADD_TEST("Provided Test: Insert duplicate elements.") {
    HeapPQueue pq;
    for (int i = 0; i < 20; i++) {
        pq.enqueue({ "a" + to_string(i), i });
    }
    for (int i = 19; i >= 0; i--) {
        pq.enqueue({ "b" + to_string(i), i });
    }

    EXPECT_EQUAL(pq.size(), 40);
    for (int i = 0; i < 20; i++) {
        auto one = pq.dequeue();
        auto two = pq.dequeue();

        EXPECT_EQUAL(one.weight, i);
        EXPECT_EQUAL(two.weight, i);
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);
}

ADD_TEST("Provided Test: Handles data points with empty string name.") {
    HeapPQueue pq;
    for (int i = 0; i < 10; i++) {
        pq.enqueue({ "" , i });
    }
    EXPECT_EQUAL(pq.size(), 10);
}

ADD_TEST("Provided Test: Handles data points with negative weights.") {
    HeapPQueue pq;
    for (int i = -10; i < 10; i++) {
        pq.enqueue({ "" , i });
    }
    EXPECT_EQUAL(pq.size(), 20);
    for (int i = -10; i < 10; i++) {
        EXPECT_EQUAL(pq.dequeue().weight, i);
    }
}

ADD_TEST("Provided Test: Interleave enqueues and dequeues.") {
    HeapPQueue pq;
    int n = 100;
    for (int i = n / 2; i < n; i++) {
        pq.enqueue({"", i});
    }
    EXPECT_EQUAL(pq.size(), 50);
    for (int i = n / 2; i < n; i++) {
        EXPECT_EQUAL(pq.dequeue().weight, i);
    }
    EXPECT_EQUAL(pq.size(), 0);

    for (int i = 0; i < n / 2; i++) {
        pq.enqueue({"", i});
    }
    EXPECT_EQUAL(pq.size(), 50);
    for (int i = 0; i < n / 2; i++) {
        EXPECT_EQUAL(pq.dequeue().weight, i);
    }
    EXPECT_EQUAL(pq.size(), 0);
}

ADD_TEST("Provided Test: Stress test: cycle 250,000 elems (should take at most a few seconds)") {
    HeapPQueue pq;
    int n = 250000;
    for (int i = 0; i < n; i++) {
        pq.enqueue({ "", randomInteger(0, 100000) });
    }
    EXPECT_EQUAL(pq.size(), n);

    for (int i = 0; i < n; i++) {
        pq.dequeue();
    }
    EXPECT_EQUAL(pq.size(), 0);
    EXPECT_EQUAL(pq.isEmpty(), true);

    for (int i = 0; i < n; i++) {
        pq.enqueue({ "", randomInteger(0, 100000) });
    }
    EXPECT_EQUAL(pq.size(), n);
}


ADD_TEST("Provided Test: Simple memory leak check.") {
    /* See how many unmatched allocations of DataPoint objects there are
     * before we perform any operations.
     */
    int allocationsBefore = netDataPointAllocations();

    HeapPQueue* pq = new HeapPQueue();
    delete pq;

    /* Net allocations now - net allocations at start = allocations leaked by
     * the HeapPQueue implementation. If this number is not zero, it might
     * indicate a memory leak.
     */
    int netAllocations = netDataPointAllocations() - allocationsBefore;
    EXPECT_EQUAL(netAllocations, 0);
}

ADD_TEST("Provided Test: More aggressive memory leak check.") {
    /* See how many unmatched allocations of DataPoint objects there are
     * before we perform any operations.
     */
    int allocationsBefore = netDataPointAllocations();

    HeapPQueue* pq = new HeapPQueue();

    /* Simulate a workflow on the priority queue. */
    for (int i = 0; i < 10000; i++) {
        pq->enqueue({ "", -i });
    }
    for (int i = 0; i < 5000; i++) {
        auto removed = pq->dequeue();
        removed.weight = -removed.weight;
        pq->enqueue(removed);
    }
    for (int i = 0; i < 9000; i++) {
        (void) pq->dequeue();
    }

    delete pq;

    /* Net allocations now - net allocations at start = allocations leaked by
     * the HeapPQueue implementation. If this number is not zero, it might
     * indicate a memory leak.
     */
    int netAllocations = netDataPointAllocations() - allocationsBefore;
    EXPECT_EQUAL(netAllocations, 0);
}
