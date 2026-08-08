int prefXor(int n){
    if(n % 4 == 0) return n;
    if(n % 4 == 1) return 1;
    if(n % 4 == 2) return n + 1;
    return 0; 
}
int qry(int l, int r){
    return prefXor(r) ^ prefXor(l - 1);
}

