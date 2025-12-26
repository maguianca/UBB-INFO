CREATE DATABASE Oser 
GO 
USE Oser

-- Organizatorii Oser doresc sa construiasca un catalog online pentru a le fi mai usor 
-- clientilor sa gaseasca obiectele de care au nevoie. Fiecare hala (litera, suprafata) are mai multe tarabe 
-- (suprafata, numar). Pe fiecare taraba se pot gasi mai multe categorii de produse. Fiecare categorie de produs
-- are un nume si poate fi gasita pe mai multe tarabe. Fiecare categorie de produse are mai multe produse.
-- Un produs are denumire, pret si poate aparatine unei singure categorii de produse.
 
-- 1. Scrieti un script SQL care creeaza un model relational pentru a reprezenta si stoca datele (4p)
 
-- 2. Un vanzator vrea sa faca bani. Creati o procedura stocata care actualizeaza pretul produselor de pe o taraba data:
-- Daca pretul e < 100, va creste cu 10 lei.
-- Daca pretul e > 200, va creste 50 lei.
-- Daca pretul e intre 100 si 200, va creste 10%. (3p)
 
-- 3. Spre finalul programalui, vanzatorii reduc din pret, dar nu toti. Creati un view care afiseaza toate produsele (denumire si pret) avand
-- pretul redus cu 60% din categoriile haine si vesela din halele "A", "F" si "X" (2p)
CREATE TABLE Hala(
id int primary key identity,
litera varchar(10),
suprafata int
);
CREATE TABLE Taraba(
id int primary key identity,
suprafata int,
numar int
);
CREATE TABLE TarabaHala(
id_taraba int foreign key references Taraba(id),
id_hala int foreign key references Hala(id),
constraint pk_th primary key(id_taraba,id_hala)
);
CREATE TABLE Categorie(
id int primary key identity,
nume varchar(100)
);
CREATE TABLE CategorieTaraba(
id_taraba int foreign key references Taraba(id),
id_categorie int foreign key references Categorie(id),
constraint pk_ct primary key(id_taraba,id_categorie)
);
CREATE TABLE Produse(
id int primary key identity,
denumire varchar(100),
pret int,
categorie int foreign key references Categorie(id)
);

INSERT INTO Hala (litera, suprafata)
VALUES
('F',125),
('X',120),
('A', 200),
('B', 150),
('C', 300);


INSERT INTO Taraba (suprafata, numar)
VALUES
(20, 1),
(15, 2),
(25, 3),
(30, 4),
(25,5),
(15,5),
(10,6);

INSERT INTO TarabaHala (id_taraba, id_hala)
VALUES
(5,4),
(6,5),
(7,5),
(1, 1),  -- Taraba 1 este în Hala A
(2, 1),  -- Taraba 2 este în Hala A
(3, 2),  -- Taraba 3 este în Hala B
(4, 3);  -- Taraba 4 este în Hala C

INSERT INTO Categorie (nume)
VALUES
('Haine'),
('Vesela'),
('Legume'),
('Fructe'),
('Produse lactate'),
('Produse de panificație');
select * from categorie
INSERT INTO CategorieTaraba (id_taraba, id_categorie)
VALUES
(7,2),
(5,5),
(6,6),
(7,5),
(1, 1),  -- Taraba 1 vinde Legume
(2, 2),  -- Taraba 2 vinde Fructe
(3, 3),  -- Taraba 3 vinde Produse lactate
(4, 4);  -- Taraba 4 vinde Produse de panificație

INSERT INTO Produse (denumire, pret, categorie)
VALUES
('Roșii', 10, 1),         -- Categoria Legume
('Mere', 8, 2),           -- Categoria Fructe
('Brânză', 25, 3),        -- Categoria Produse lactate
('Pâine', 5, 4),          -- Categoria Produse de panificație
('Castraveți', 9, 1),     -- Categoria Legume
('Portocale', 12, 2),     -- Categoria Fructe
('Lapte', 7, 3),          -- Categoria Produse lactate
('Cornuri', 6, 4);        -- Categoria Produse de panificație
('geaca',120,5),
('sosete',10,5),
('pantofi',200,5),
('furculite',20,6),
('oale',25,6),
('tigaie',50,6);
-- 2. Un vanzator vrea sa faca bani. Creati o procedura stocata care actualizeaza pretul produselor de pe o taraba data:
-- Daca pretul e < 100, va creste cu 10 lei.
-- Daca pretul e > 200, va creste 50 lei.
-- Daca pretul e intre 100 si 200, va creste 10%. (3p)
create or alter procedure cerinta2
@id_taraba int
AS 
BEGIN
	UPDATE PRODUSE
	SET pret=
			CASE 
				WHEN pret<100 THEN pret+10
				WHEN pret>200 THEN pret+50
				WHEN pret>=100 AND pret<=200 THEN pret*1.1
				ELSE pret
			END
	WHERE categorie IN (select id_categorie from CategorieTaraba where id_taraba=@id_taraba)
END;
exec cerinta2 4;
select * from produse;

-- 3. Spre finalul programalui, vanzatorii reduc din pret, dar nu toti. Creati un view care afiseaza toate produsele (denumire si pret) avand
-- pretul redus cu 60% din categoriile haine si vesela din halele "A", "F" si "X" (2p)
CREATE OR ALTER VIEW cerinta3
AS 
SELECT
	P.denumire as DENUMIRE,P.pret*0.4 AS PRET from Produse P 
	INNER JOIN CategorieTaraba CT ON P.categorie=CT.id_categorie
	INNER JOIN TarabaHala TH ON TH.id_taraba=CT.id_taraba
	INNER JOIN Categorie C ON CT.id_categorie=C.id
	INNER JOIN Hala H ON TH.id_hala=H.id
	WHERE H.litera IN ('A','F','X') and C.nume IN ('vesela','haine')

select * from cerinta3;
