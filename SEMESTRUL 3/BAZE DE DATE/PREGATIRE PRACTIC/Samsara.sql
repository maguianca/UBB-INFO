CREATE DATABASE Samsara
GO 
USE Samsara

CREATE TABLE Client(
id int primary key identity,
nume VARCHAR(100),
nr_telefon VARCHAR(100)
);
CREATE TABLE Preparat(
id int primary key identity,
denumire varchar(100),
cantitate int,
pret int
);
CREATE TABLE Ingredient(
id int primary key identity,
denumire varchar(100),
calorii int
);
CREATE TABLE IngredientePreparat(
id_ingredient int foreign key references Ingredient(id),
id_preparat int foreign key references Preparat(id)
constraint pk_ip primary key(id_ingredient,id_preparat)
);
drop table ComandaPreparate;
drop table Comanda;
CREATE TABLE Comanda(
id int primary key identity,
adresa_livrare VARCHAR(100),
data DATETIME,
client int foreign key references Client(id)
);
CREATe table ComandaPreparate(
id_comanda int foreign key references Comanda(id) ON DELETE CASCADE,
id_preparat int foreign key references Preparat(id),
constraint pk_cp primary key(id_comanda,id_preparat)
);
-- Inserare clienți
INSERT INTO Client (nume, nr_telefon)
VALUES 
('Popescu Ion', '0712345678'),
('Ionescu Maria', '0723456789'),
('Vasilescu Andrei', '0734567890'),
('Dumitru Elena', '0745678901'),
('Bogdan Ioan','0734343536')

-- Inserare preparate
INSERT INTO Preparat (denumire, cantitate, pret)
VALUES 
('Pizza Margherita', 1, 30),
('Burger', 1, 25),
('Shaorma Mare', 1, 20),
('Paste Carbonara', 1, 35),
('Salată Caesar', 1, 15);

-- Inserare ingrediente
INSERT INTO Ingredient (denumire, calorii)
VALUES 
('Brânză', 200),
('Roșii', 30),
('Pui', 250),
('Salată Verde', 10),
('Sos Caesar', 100),
('Pâine', 150),
('Carne Vită', 300),
('Paste', 350);

-- Inserare ingrediente-preparate
INSERT INTO IngredientePreparat (id_ingredient, id_preparat)
VALUES 
(1, 1), -- Brânză la Pizza Margherita
(2, 1), -- Roșii la Pizza Margherita
(7, 2), -- Carne de vită la Burger
(6, 2), -- Pâine la Burger
(3, 3), -- Pui la Shaorma
(6, 3), -- Pâine la Shaorma
(4, 5), -- Salată Verde la Salată Caesar
(5, 5); -- Sos Caesar la Salată Caesar

delete from IngredientePreparat where id_ingredient=5 and id_preparat=3;
-- Inserare comenzi
INSERT INTO Comanda (adresa_livrare, data, client)
VALUES 
('Str. Unirii, nr. 12', '2024-01-10 18:30:00', 1),
('Str. Libertății, nr. 45', '2024-01-15 13:00:00', 2),
('Str. Independenței, nr. 78', '2024-01-20 20:00:00', 3),
('Str. Revoluției, nr. 90', '2024-01-25 12:00:00', 4),
('Str Republicii nr.22','2025-01-01',5),
('Str Amiezii nr.22','2024-12-12',5),
('Str. Cucurigu nr.11','2024-11-19',5);

-- Inserare comenzi-preparate
INSERT INTO ComandaPreparate (id_comanda, id_preparat)
VALUES 
(1, 1), -- Pizza Margherita în comanda 1
(1, 2), -- Burger în comanda 1
(2, 3), -- Shaorma Mare în comanda 2
(3, 4), -- Paste Carbonara în comanda 3
(3, 5), -- Salată Caesar în comanda 3
(4, 1), -- Pizza Margherita în comanda 4
(4, 5),-- Salată Caesar în comanda 4
(5,2),
(5,4),
(6,1),
(6,2),
(7,3);

create or alter procedure cerinta2
@nume_ingredient VARCHAR(100)
AS
BEGIN
	DECLARE @nr int
	/*SELECT @nr=count(*) from Comanda Com*/
	DELETE Com FROM Comanda Com
	INNER JOIN Client Cl ON Com.client=Cl.id
	INNER JOIN ComandaPreparate CP ON CP.id_comanda=Com.id
	INNER JOIN IngredientePreparat IP ON IP.id_preparat=CP.id_preparat
	INNER JOIN Ingredient I on I.id=IP.id_ingredient
	WHERE I.denumire=@nume_ingredient;
	SET @nr=@@ROWCOUNT;
	PRINT 'Numar comenzi sterse '+CAST(@nr AS VARCHAR(10));
END;

exec cerinta2 'Sos Caesar';
select * from Comanda;

create or alter view cerinta3
AS
SELECT 
	Com.id,Com.data as DataComenzii,Sum(P.pret) as SumaAchitata from Comanda Com
	inner join ComandaPreparate CP ON CP.id_comanda=Com.id
	INNER JOIN Client C on Com.client=C.id
	INNER JOIN Preparat P on CP.id_preparat=P.id
	where C.nume='Bogdan Ioan'
	group by Com.data,Com.id
select * from cerinta3;

