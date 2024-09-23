#include "IteratorMatrice.h"
#include "Matrice.h"

using namespace std;

// complexitate: O(n) - capacitatea curenta a Matricei
IteratorMatrice::IteratorMatrice(const Matrice& m,int l) : m(m) {
    curent = m.rad;
    this->l=l;
    this->rl= nullptr;
    // se adauga in stiva ramura stanga a elementului curent
    while (curent != nullptr) {
        if(curent->i==l)
        {
            if(this->rl== nullptr)
                this->rl=curent;
            st.push(curent);
            curent=curent->dr;
        }
        else{
            if(curent->i>l)
                curent=curent->st;
            else
                curent=curent->dr;
        }
    }
    /*
    // se sterge frunza din varful stivei
    if (!s.empty()) {
        s.pop();
        curent = anterior;
    }*/
}

// complexitate: theta(1)
TElem IteratorMatrice::element() {
    if (!valid()) {
        throw exception();
    }
    return st.top()->e;
}

// complexitate: theta(1)
bool IteratorMatrice::valid() const {
    return curent != nullptr;
}

// complexitate: O(n) - capacitatea curenta a Matricei
void IteratorMatrice::urmator() {
    if (!valid()) {
        throw exception();
    }
    // stergem nodul din varful stivei
    if (!st.empty()) {
        curent = st.top();
        st.pop();
    }
}

// complexitate: O(n) - capacitatea curenta a Matricei
void IteratorMatrice::prim() {
    curent= this->rl;
}