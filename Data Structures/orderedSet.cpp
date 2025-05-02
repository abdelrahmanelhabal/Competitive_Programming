/*
 * erase and insert in log(n)
 * by *find_by_order given index --> val
 * by order_of_key given  value --> index
 */
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using ordered_set = tree<T, null_type , less_equal<T> , rb_tree_tag , tree_order_statistics_node_update> ;
struct orderedSet{
    ordered_set<ll> se ;

    void insert( ll val ){ se.insert( val ); }

    bool exist(ll val) {
        if (se.upper_bound(val) == se.end()) { return false; }
        return (*se.upper_bound(val)) == val;
    }
    void erase(ll val) {
        if (exist(val)) { se.erase(se.upper_bound(val)); }
    }

    ll less_elements(ll val) {
        return se.order_of_key(val);
    }
    ll greater_elements(ll val) {
        return se.size()-se.order_of_key(val);
    }
    ll index(ll val) {
        if (!exist(val)) { return -1; }
        return se.order_of_key(val);
    }
    ll LastIdx(ll val) {
        if (!exist(val)) { return -1; }
        if (*se.find_by_order(se.size() - 1) == val) {
            return se.size() - 1;
        }
        return index(*se.lower_bound(val)) - 1;
    }
    ll lower_bound(ll val) {  return *se.upper_bound(val); }

    ll upper_bound(ll val) { return *se.lower_bound(val); }

    ll operator[](ll idx) { return *se.find_by_order(idx) ;}

    ll size(){ return se.size(); }

    void clear(){ se.clear() ; }
};
