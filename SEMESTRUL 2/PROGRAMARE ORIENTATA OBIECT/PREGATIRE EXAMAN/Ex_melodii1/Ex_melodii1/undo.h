#pragma once
#include"repo.h"
class UndoA {
public:
	virtual void doUndo() = 0;
	virtual~UndoA() = default;
};
class UndoSterge:public UndoA{
private:
	Melodie m;
	Repo& repo;
public:UndoSterge(Repo& repo, Melodie& m) :repo{ repo },m { m} {}
	  void doUndo()override {
		  repo.adauga(m);
	  }
};
class UndoModifica :public UndoA {
private:
	Melodie mveche;
	Melodie mnoua;
	Repo& repo;
public:UndoModifica(Repo& repo, Melodie&mv, Melodie& mn) :repo{ repo }, mveche{mv}, mnoua{mn} {}
	  void doUndo()override {
		  repo.sterge(mnoua.get_id());
		  repo.adauga(mveche);
	  }
};