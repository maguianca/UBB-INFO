CREATE DATABASE MagazinDeBijuterii;
GO
USE MagazinDeBijuterii;
CREATE TABLE BorderouMarcare(
id_borderou VARCHAR(300) PRIMARY KEY,
pret_marcare FLOAT
);
CREATE TABLE Bijuterie(
id_bij VARCHAR(300) PRIMARY KEY,
pret_bij INT,
descriere_bij VARCHAR(300),
gramaj_bij FLOAT,
id_borderou VARCHAR(300) FOREIGN KEY REFERENCES BorderouMarcare(id_borderou)
);
CREATE TABLE Material(
id_material INT PRIMARY KEY IDENTITY(1,1),
denumire VARCHAR(300),
pret_bursa FLOAT
);
CREATE TABLE Procent(
id_bij VARCHAR(300) FOREIGN KEY REFERENCES Bijuterie(id_bij),
id_material INT FOREIGN KEY REFERENCES Material(id_material),
procent DECIMAL(5,2),
CONSTRAINT pkProcent PRIMARY KEY(id_bij,id_material)
);
CREATE TABLE Magazin(
id_magazin INT PRIMARY KEY IDENTITY(1,1),
nume VARCHAR(300),
locatie VARCHAR(300),
oras VARCHAR(300),
nr_tel VARCHAR(300)
);
CREATE TABLE StocBijuterieMagazin(
id_bij VARCHAR(300) FOREIGN KEY REFERENCES Bijuterie(id_bij),
id_magazin INT FOREIGN KEY REFERENCES Magazin(id_magazin),
cantitate INT,
CONSTRAINT pkStoc PRIMARY KEY(id_bij,id_magazin)
);
CREATE TABLE Angajati(
id_angajat INT PRIMARY KEY IDENTITY(1,1),
nume VARCHAR(300),
post VARCHAR(300),
id_magazin INT FOREIGN KEY REFERENCES Magazin(id_magazin)
);
CREATE TABLE Client(
id_client INT PRIMARY KEY IDENTITY(1,1),
nume VARCHAR(300),
adresa VARCHAR(300),
telefon VARCHAR(300),
email VARCHAR(300)
);
CREATE TABLE Comanda(
id_comanda INT PRIMARY KEY IDENTITY(1000,1),
data DATE,
status VARCHAR(300),
id_client INT FOREIGN KEY REFERENCES Client(id_client)
);
CREATE TABLE BijuterieComanda(
id_bij VARCHAR(300) FOREIGN KEY REFERENCES Bijuterie(id_bij),
id_comanda INT FOREIGN KEY REFERENCES Comanda(id_comanda),
cantitate INT,
CONSTRAINT pkBijuterieComanda PRIMARY KEY (id_bij,id_comanda)
);
ALTER TABLE BijuterieComanda
ADD pret_bucata INT;
CREATE TABLE Categorie(
id_categorie INT PRIMARY KEY IDENTITY(1,1),
descriere VARCHAR(300)
);
CREATE TABLE BijuterieCategorie(
id_bij VARCHAR(300) FOREIGN KEY REFERENCES Bijuterie(id_bij),
id_categorie INT FOREIGN KEY REFERENCES Categorie(id_categorie),
CONSTRAINT pkBijuterieCategorie PRIMARY KEY (id_bij,id_categorie)
);