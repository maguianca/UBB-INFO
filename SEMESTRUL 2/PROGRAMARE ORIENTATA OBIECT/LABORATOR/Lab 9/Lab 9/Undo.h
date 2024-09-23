#pragma once
#include "domeniu.h"
#include "repo.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() {};
};

class UndoAdauga :public ActiuneUndo {
	Turism oferta;
	Repo& repo;
public:
	UndoAdauga(Repo& repo, const Turism& o) :repo{ repo }, oferta{ o } {}
	void doUndo()override {
		repo.stergere(oferta);
	}
};
class UndoModifica :public ActiuneUndo {
	Turism ofertaVeche, ofertaNoua;
	Repo& repo;
public:
	UndoModifica(Repo& repo, Turism& ofertaVeche, Turism& ofertaNoua) :repo{ repo }, ofertaVeche{ ofertaVeche }, ofertaNoua{ ofertaNoua } {}
	void doUndo()override {
		repo.stergere(ofertaNoua);
		repo.store(ofertaVeche);
	}
};
class UndoSterge : public ActiuneUndo {
	Turism ofertaStearsa;
	Repo& repo;
public:
	UndoSterge(Repo& repo, Turism& ofertaStearsa) : repo{ repo }, ofertaStearsa{ ofertaStearsa } {}

	void doUndo() override {
		repo.store(ofertaStearsa);
	}
};