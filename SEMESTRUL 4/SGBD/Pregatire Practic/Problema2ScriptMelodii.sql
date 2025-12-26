CREATE DATABASE Practic_Melodii 
GO 
USE Practic_Melodii

CREATE TABLE Tari(
cod_tara INT PRIMARY KEY IDENTITY,
nume_tara TEXT,
descriere TEXT);

CREATE TABLE Artisti(
cod_artist INT PRIMARY KEY IDENTITY,
nume_artist TEXT,
data_nasterii DATE,
website TEXT,
cod_tara INT FOREIGN KEY REFERENCES Tari(cod_tara) ON DELETE CASCADE ON UPDATE CASCADE);

CREATE TABLE Melodii(
cod_melodie INT PRIMARY KEY IDENTITY,
titlu TEXT,
an_lansare INT,
durata INT,
cod_artist INT FOREIGN KEY REFERENCES Artisti(cod_artist) ON DELETE CASCADE ON UPDATE CASCADE);

CREATE TABLE Clasamente(
cod_clasament INT PRIMARY KEY IDENTITY,
nume_clasament TEXT);

CREATE TABLE PozitieClasament(
cod_melodie INT FOREIGN KEY REFERENCES Melodii(cod_melodie) ON DELETE CASCADE ON UPDATE CASCADE,
cod_clasament INT FOREIGN KEY REFERENCES Clasamente(cod_clasament) ON DELETE CASCADE ON UPDATE CASCADE,
pozitie_maxima INT,
CONSTRAINT pk_key PRIMARY KEY(cod_melodie,cod_clasament));


INSERT INTO Tari(nume_tara,descriere)VALUES
('Romania','tara europeana');
select * from Melodii;
INSERT INTO Artisti(nume_artist,data_nasterii,website, cod_tara)
VALUES('Inna','2000-10-10','inna.com',1),
('Antonia','1998-12-03','antonia.com',1),
('Vunk','1991-10-11','vunk.ro',1);
select * from Artisti;
INSERT INTO Melodii(titlu, an_lansare,durata,cod_artist)VALUES
('Tu si eu',2009,2,1),
('Vama',2010,3,3),
('Marabu', 2015,2,2);

CREATE NONCLUSTERED INDEX idx_melodii
ON Melodii(an_lansare);

CREATE NONCLUSTERED INDEX idx_many
ON Melodii(an_lansare,durata);

select * from Melodii;

select cod_melodie from Melodii 
where an_lansare>2009 and durata>=3;

