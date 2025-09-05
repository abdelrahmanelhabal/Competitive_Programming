/*
 * erase and insert in log(n)
 * by *find_by_order given index --> val
 * by order_of_key given  value --> index
 */
struct orderedSet{
    ordered_set<int> se ;

    void insert( int val ){ se.insert( val ); }

    bool exist(int val) {
        if (se.upper_bound(val) == se.end()) { return false; }
        return (*se.upper_bound(val)) == val;
    }
    void erase(int val) {
        if (exist(val)) { se.erase(se.upper_bound(val)); }
    }

    int less_elements(int val) {
        return se.order_of_key(val);
    }
    int greater_elements(int val) {
        return se.size()-se.order_of_key(val);
    }
    int index(int val) {
        if (!exist(val)) { return -1; }
        return se.order_of_key(val);
    }
    int LastIdx(int val) {
        if (!exist(val)) { return -1; }
        if (*se.find_by_order(se.size() - 1) == val) {
            return se.size() - 1;
        }
        return index(*se.lower_bound(val)) - 1;
    }
    int lower_bound(int val) {  return *se.upper_bound(val); }

    int upper_bound(int val) { return *se.lower_bound(val); }

    int operator[](int idx) { return *se.find_by_order(idx) ;}

    int size(){ return se.size(); }

    void clear(){ se.clear() ; }
};
