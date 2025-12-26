CREATE DATABASE JewelryShop;
GO
USE JewelryShop;

CREATE TABLE Bijuterie(
id_bij INT IDENTITY PRIMARY KEY,
pret_bij INT,
descriere_bij VARCHAR(300),
gramaj_bij FLOAT
);
CREATE TABLE Material(
id_material INT IDENTITY PRIMARY KEY,
denumire VARCHAR(300),
pret_bursa FLOAT
);
CREATE TABLE Procent(
id_bij INT,
id_material INT,
procent DECIMAL(5,2),
PRIMARY KEY (id_bij,id_material),
FOREIGN KEY (id_bij)REFERENCES Bijuterie(id_bij),
FOREIGN KEY (id_material)REFERENCES Material(id_material)
);
CREATE TABLE Magazin(
id_magazin INT IDENTITY PRIMARY KEY,
nume VARCHAR(300),
locatie VARCHAR(300),
nr_tel VARCHAR(300)
);
CREATE TABLE StocBijuterieMagazin(
id_bij INT,
id_magazin INT,
bucati INT,
PRIMARY KEY(id_bij,id_magazin),
FOREIGN KEY(id_bij) REFERENCES Bijuterie(id_bij),
FOREIGN KEY(id_magazin) REFERENCES Magazin(id_magazin)
);
CREATE TABLE Angajati(
id_angajat INT IDENTITY PRIMARY KEY,
nume VARCHAR(300),
post VARCHAR(300),
id_magazin INT,
FOREIGN KEY(id_magazin) REFERENCES Magazin(id_magazin)
);
CREATE TABLE Client(
id_client INT IDENTITY PRIMARY KEY,
nume VARCHAR(300),
adresa VARCHAR(300),
telefon VARCHAR(300),
email VARCHAR(300)
);
CREATE TABLE Comanda(
id_comanda INT IDENTITY PRIMARY KEY,
data DATE,
status VARCHAR(300),
id_client INT,
FOREIGN KEY(id_client) REFERENCES Client(id_client)
);

CREATE TABLE BijuterieComanda(
id_bij INT,
id_comanda INT,
pret_bucata FLOAT,
cantitate INT,
PRIMARY KEY(id_bij,id_comanda),
FOREIGN KEY(id_bij) REFERENCES Bijuterie(id_bij),
FOREIGN KEY(id_comanda) REFERENCES Comanda(id_comanda)
);
CREATE TABLE Categorie(
id_categorie INT IDENTITY PRIMARY KEY,
descriere VARCHAR(300)
);
CREATE TABLE BijuterieCategorie(
id_bij INT,
id_categorie INT,
PRIMARY KEY(id_bij,id_categorie),
FOREIGN KEY(id_bij) REFERENCES Bijuterie(id_bij),
FOREIGN KEY(id_categorie) REFERENCES Categorie(id_categorie)
);


