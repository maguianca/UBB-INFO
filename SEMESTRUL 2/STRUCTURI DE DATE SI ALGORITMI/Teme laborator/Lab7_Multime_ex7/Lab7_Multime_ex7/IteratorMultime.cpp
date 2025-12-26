#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>

//CF:Theta(1)
//CD:Theta(n)
//CT:O(n)
IteratorMultime::IteratorMultime(const Multime& m) : multime(m) {
    curent = m.radacina;
    while (curent != -1) {
        s.push(curent);
        curent = m.stang[curent];
    }
    if (!s.empty()) {
        curent = s.top();
        s.pop();
    }
    else
        curent = -1;
}
//CF:Theta(1)
//CD:Theta(n)
//CT:O(n)
void IteratorMultime::prim() {
    while (!s.empty())
        s.pop();
    curent = multime.radacina;
    while (curent != -1) {
        s.push(curent);
        curent = multime.stang[curent];
    }
    if (!s.empty()) {
        curent = s.top();
        s.pop();
    }
    else
        curent = -1;
}
//CF:Theta(1)
//CD:Theta(n)
//CT:O(n)
void IteratorMultime::urmator() {
    if (!valid()) {
        throw std::exception();
    }
    if (multime.drept[curent] != -1) {
        curent = multime.drept[curent];
        while (curent != -1) {
            s.push(curent);
            curent = multime.stang[curent];
        }
    }
    if (!s.empty()) {
        curent = s.top();
        s.pop();
    }
    else {
        curent = -1;
    }
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
TComparabil IteratorMultime::element() const {
    if (!valid())
        throw std::exception();
    return multime.elems[curent];
}
//CF:Theta(1)
//CD:Theta(1)
//CT:Theta(1)
bool IteratorMultime::valid() const {
    return curent != -1;
}
