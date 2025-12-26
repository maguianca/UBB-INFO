CREATE DATABASE MagazinBijuterii;
GO
USE MagazinBijuterii;
CREATE TABLE Bijuterie(
cod_bij VARCHAR(300) PRIMARY KEY,
pret_bij INT,
descriere_bij VARCHAR(300),
gramaj_bij FLOAT
);
CREATE TABLE Material(
cod_material INT PRIMARY KEY,
denumire VARCHAR(300),
pret_bursa FLOAT
);
CREATE TABLE Procent(
cod_bij VARCHAR(300),
cod_material INT,
procent DECIMAL(5,2),
PRIMARY KEY (cod_bij,cod_material),
FOREIGN KEY (cod_bij)REFERENCES Bijuterie(cod_bij),
FOREIGN KEY (cod_material)REFERENCES Material(cod_material)
);
CREATE TABLE Magazin(
cod_magazin INT PRIMARY KEY,
nume VARCHAR(300),
locatie VARCHAR(300),
nr_tel VARCHAR(300)
);
CREATE TABLE StocBijuterieMagazin(
cod_bij VARCHAR(300),
cod_magazin INT,
bucati INT,
PRIMARY KEY(cod_bij,cod_magazin),
FOREIGN KEY(cod_bij) REFERENCES Bijuterie(cod_bij),
FOREIGN KEY(cod_magazin) REFERENCES Magazin(cod_magazin)
);
CREATE TABLE Angajati(
cod_angajat INT PRIMARY KEY,
nume VARCHAR(300),
post VARCHAR(300),
cod_magazin INT,
FOREIGN KEY(cod_magazin) REFERENCES Magazin(cod_magazin)
);
CREATE TABLE Client(
cod_client INT PRIMARY KEY,
nume VARCHAR(300),
adresa VARCHAR(300),
telefon VARCHAR(300),
email VARCHAR(300)
);
CREATE TABLE Comanda(
cod_comanda INT PRIMARY KEY,
data DATE,
status VARCHAR(300),
cod_client INT,
FOREIGN KEY(cod_client) REFERENCES Client(cod_client)
);

CREATE TABLE BijuterieComanda(
cod_bij VARCHAR(300),
cod_comanda INT,
pret_bucata FLOAT,
cantitate INT,
PRIMARY KEY(cod_bij,cod_comanda),
FOREIGN KEY(cod_bij) REFERENCES Bijuterie(cod_bij),
FOREIGN KEY(cod_comanda) REFERENCES Comanda(cod_comanda)
);
CREATE TABLE Categorie(
cod_categorie INT PRIMARY KEY,
descriere VARCHAR(300)
);
CREATE TABLE BijuterieCategorie(
cod_bij VARCHAR(300),
cod_categorie INT,
PRIMARY KEY(cod_bij,cod_categorie),
FOREIGN KEY(cod_bij) REFERENCES Bijuterie(cod_bij),
FOREIGN KEY(cod_categorie) REFERENCES Categorie(cod_categorie)
);
ALTER DATABASE MagazinBijuterii
MODIFY Name=BijuteriiShop

