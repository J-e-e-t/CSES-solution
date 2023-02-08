/*
List Removals

    Task Submit Results Statistics 

    Time limit: 1.00 s Memory limit: 512 MB 

You are given a list consisting of n
integers. Your task is to remove elements from the list at given positions, and report the removed elements.

Input

The first input line has an integer n: the initial size of the list. During the process, the elements are numbered 1,2,…,k where k is the current size of the list.

The second line has n integers x1,x2,…,xn: the contents of the list.

The last line has n integers p1,p2,…,pn: the positions of the elements to be removed.

Output

Print the elements in the order they are removed.

Constraints

    1≤n≤2⋅105


1≤xi≤109

1≤pi≤n−i+1


Example

Input:
5
2 6 1 4 2
3 1 3 1 1

Output:
1 2 2 6 4

Explanation: The contents of the list are [2,6,1,4,2], [2,6,4,2], [6,4,2], [6,4], [4] and []. 
*/

/*

Brute force is quite simple if you simply simulate what is mentioned in the problem.
Let us try to optimize. So whenever we are asked to delete some xth element of the list we need to first locate the xth element, print it and then delete it.

How can we make the above processes faster?
Let us keep a boolean array PRESENT of size N and PRESENT[i] = 1 if the ith element of the list has not yet been deleted, 0 otherwise.

Now let us say we have the query : delete the xth element of the list, then this means we are going to delete the element at the jth index of the initial list such that :

    PRESENT[j] = 1.
    sum of PRESENT[i] for all i from 1 to j = x.

Why above conditions are necessary and sufficient to locate the correct element?
If are we deleting the element it has to be present in the list currently and so PRESENT[j] should be 1.
If this element at index j(of the initial list) is the xth element of the list(current state of the list) then there are exactly x elements present in the list in range [1,j](of the initial list) and remaining j — x elements got deleted in some previous queries.

How do I find this j?

Binary Search.

The correct j lies in the range [1,N]. Is the index mid the correct index?
Consider following facts :
If number of elements not yet deleted in [1,mid] > x then search range should be updated to [1,mid-1] else If number of elements not yet deleted in [1,mid] < x search range should be updated to [mid+1,N].

else If number of elements not yet deleted from [1,mid] = x then if PRESENT[mid] = 1, mid is the correct index else update search range to [1,mid-1].

How do I find number of elements not yet deleted in the range [1,j]?
Build a range sum query segment tree on the PRESENT array and find the sum of the range [1,j] in logN time. 

Once you have found the correct j, you need to print it and also mark PRESENT[j] = 0 and make the required point update in the segment tree.

Time complexity analysis is similar to previous problem.
*/

// https://usaco.guide/problems/cses-1749-list-removals/solution



    #include<bits/stdc++.h>
    #define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
    #define ll long long
    using namespace std;
    #define left(i) (2*i + 1)
    #define right(i) (2*i + 2)
    #define parent(i) ((i-1)/2)
    #include <vector>
     
    template<class T>
    class SegmentTree
    {
        public:
            SegmentTree(std::vector<T> data, T value, T (*combine)(T obj1, T obj2));
            SegmentTree(T ar[], int n, T value, T (*combine)(T obj1, T obj2));
            T query(int l, int r);
            void update(int idx, T val);
            //TODO lazy propagation
        private:
            T *tree;
            void buildTree(std::vector<T> data);
            int segTreeSize;
            T valueForExtraNodes;
            T (*combine)(T obj1, T obj2);
            int calculateSize(int n);
            T queryHelper(int l,int r, int st, int ed, int node);
    };
     
    template<class T> SegmentTree<T>::SegmentTree(std::vector<T> data,
                                                    T value, T (*combine)(T obj1, T obj2))
    {
       this->combine = combine;
       valueForExtraNodes = value;
       segTreeSize = calculateSize(data.size());
       buildTree(data);
    }
     
    template<class T> SegmentTree<T>::SegmentTree(T ar[], int n,
                                                T value, T (*combine)(T obj1, T obj2))
    {
       this->combine = combine;
       valueForExtraNodes = value;
       segTreeSize = calculateSize(n);
     
       std::vector<T> data;
       for(int i = 0; i < n; i++)
             data.push_back(ar[i]);
     
       buildTree(data);
    }
     
     
    template<class T> int SegmentTree<T>::calculateSize(int n)
    {
        int pow2 = 1;
        while( pow2 < n)
        {
            pow2 = pow2 << 1;
        }
        return 2*pow2 - 1;
    }
     
    template<class T> T SegmentTree<T>::query(int l, int r)
    {
        int st = 0, ed = segTreeSize/2;
        return queryHelper(l, r, st, ed, 0);
    }
     
    template<class T> T SegmentTree<T>::queryHelper(int l,int r, int st, int ed, int node)
    {
        if( (r < st) || (l > ed) || (l > r) )
            return valueForExtraNodes;
        if(st >= l && ed <= r)
            return tree[node];
        T leftVal = queryHelper(l, r, st, (st + ed)/2, left(node));
        T rightVal = queryHelper(l, r, (st+ed)/2 + 1, ed, right(node));
        return combine(leftVal, rightVal);
    }
     
    template<class T> void SegmentTree<T>::buildTree(std::vector<T> data)
    {
       int n = data.size();
       tree = new T[segTreeSize];
       int extraNodes = (segTreeSize/2 + 1) - n;
       for(int i = segTreeSize - 1; i >= 0; i--)
       {
           if(extraNodes>0)
               {
                   tree[i] = valueForExtraNodes;
                   extraNodes--;
               }
           else if(n>0)
               {
                   tree[i] = data[n-1];
                   n--;
               }
           else
               tree[i] = combine(tree[left(i)], tree[right(i)]);
       }
    }
     
    template<class T> void SegmentTree<T>::update(int idx, T val)
    {
        int segTreeIdx = (segTreeSize/2) + idx;
        tree[segTreeIdx] = val;
        while(parent(segTreeIdx) >= 0)
        {
            segTreeIdx = parent(segTreeIdx);
            if(right(segTreeIdx) < segTreeSize)
              tree[segTreeIdx] = combine(tree[left(segTreeIdx)], tree[right(segTreeIdx)]);
            if(segTreeIdx == 0)
                break;
        }
    }
     
    int sum(int x,int y) { return x+y; }
    int main()
    {
        fast_io;
        int n;
        cin>>n;
     
        vector<int> v(n);
        vector<int> present(n,1);
     
        for(int i=0;i<n;i++)
            cin >> v[i];
     
        SegmentTree<int> rangeSumQueries(present, 0, sum);
        for(int i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            int lo = 0, hi = n - 1;
            while(lo!=hi)
            {
                int mid = (lo+hi)/2;
                int till_mid = rangeSumQueries.query(0,mid);
                if(till_mid > x)
                    hi = mid - 1;
                else if(till_mid < x)
                    lo = mid + 1;
                else
                {
                    if(present[mid]){
                        lo = mid;
                        break;
                    }
                    else hi = mid - 1;
                }
            }
            present[lo] = 0;
            rangeSumQueries.update(lo, 0);
            cout << v[lo] <<' ';
        }
        return 0;
    }
     
     