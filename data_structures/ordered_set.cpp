// s.find_by_order(k) -> Returns iterator to the k-th smallest element (0-based index)
// s.order_of_key(x)  -> Returns number of elements strictly less than x
// For ordered_multiset erase one occurrence:
// s.erase(s.find_by_order(s.order_of_key(x)));

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

