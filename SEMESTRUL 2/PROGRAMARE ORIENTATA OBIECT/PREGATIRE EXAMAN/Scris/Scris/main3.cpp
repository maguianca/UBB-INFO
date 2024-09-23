#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Transformer {
public:
    Transformer() = default;
    virtual ~Transformer() = default;
    virtual void transform(vector<int>& nrs) = 0; 
};

class Adder : public Transformer {
private:
    int cat;
public:
    Adder(int cat) : cat{ cat } {}
    virtual void transform(vector<int>& nrs) override {
        for (auto& l : nrs)
            l = l + cat;
    }
};

class Nuller : public Adder {
public:
    Nuller(int cat) : Adder(cat) {}
    void transform(vector<int>& nrs) override {
        Adder::transform(nrs); 
        for (auto& l : nrs)
            if (l > 10)
                l = 0;
    }
};

class Swapper : public Transformer {
public:
    Swapper() = default;
    void transform(vector<int>& nrs) override {
        for (int i = 0; i + 1 < nrs.size(); i += 2) 
            swap(nrs[i], nrs[i + 1]);
    }
};

class Composite : public Transformer {
private:
    Transformer* t1;
    Transformer* t2;
public:
    Composite(Transformer* t1, Transformer* t2) : t1{ t1 }, t2{ t2 } {}
    void transform(vector<int>& nrs) override {
        t1->transform(nrs);
        t2->transform(nrs);
    }
    ~Composite() { delete t1; delete t2; }
};

class Numbers {
private:
    Transformer* t1;
    vector<int> toti;
public:
    Numbers(Transformer* t1) : t1{ t1 } {}
    void add(int x) {
        toti.push_back(x);
    }
    vector<int> transform() {
        sort(toti.begin(), toti.end(), [](int t1, int t2) {
            return t1 > t2; 
            });
        t1->transform(toti);
        return toti;
    }
    ~Numbers() {
        if (t1 != nullptr)
            delete t1;
    }
};

Numbers functie2() {
    Numbers ob(new Composite(new Nuller{ 9 }, new Composite(new Swapper, new Adder{ 3 })));
    return ob;
}
//EXERCITIUL 4
class Examen {
private:
    string nume;
public:
    Examen(const string denumire, const string ora){
        this->nume = denumire + " " + ora; }
      string getDescriere()const {
          return nume;
      }
};
template<typename T>
class ToDo {
private:
    vector<T>examene;
public:
    ToDo() = default;
    ToDo &operator << (const T& ex) {
        examene.push_back(ex);
        return *this;
    }
    void printToDoList(ostream& out)
    {
        out <<endl<< "De facut: ";
        for (int i = 0; i < examene.size(); i++) {
            out << examene[i].getDescriere()<<" ";
            if (i != examene.size() - 1)
                out << ";";
        }
    }
};
void todolist() {
    ToDo<Examen> todo;
    Examen oop{ "oop scris","8:00" };
    todo << oop << Examen{ "oop practic", "11:00" }; //Adauga 2 examene la todo
    std::cout << oop.getDescriere(); //tipareste la consola: oop scris ora 8:00
    //itereaza elementele adaugate si tipareste la consola lista de activitati
    //in acest caz tipareste: De facut:oop scris ora 8:00;oop practic ora 11:00
    todo.printToDoList(std::cout);
}
/*
int main() {
    Numbers o1 = functie2();
    Numbers o2 = functie2();
    o1.add(0);
    o1.add(2);
    o1.add(4);
    o1.add(6);
    o1.add(8);

    o1.add(1);
    o1.add(3);
    o1.add(5);
    o1.add(7);
    o1.add(9);

    vector<int> a1 = o1.transform();
    vector<int> a2 = o2.transform();

    for (auto l : a1)
        cout << l << " ";
    cout << endl;
    for (auto l : a2)
        cout << l << " ";
    cout << endl;
    
    todolist();
    return 0;
}
*/