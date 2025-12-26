CREATE DATABASE Vanzari 
GO 
USE Vanzari

create table Produse(
id int primary key identity,
denumire varchar(100),
unitate_masura varchar(100)
);
create table Agenti(
id int primary key identity,
nume varchar(100),
prenume varchar(100)
);

CREATE TABLE Clienti(
id int primary key identity,
denumire VARCHAR(100),
cod_fiscal VARCHAR(100)
);

create table Factura(
id int primary key identity,
numar int,
data_emitere DATE,
clientul int foreign key references Clienti(id),
agent int foreign key references Agenti(id)
);

create table Lista(
nr_ordine int,
id_produs int foreign key references Produse(id),
id_factura int foreign key references Factura(id),
pret int,
cantitate int,
constraint pk_lista primary key(id_produs,id_factura,pret)
);

-- Inserare Produse (adãugat "Shaorma")
INSERT INTO Produse (denumire, unitate_masura)
VALUES 
('Lapte', 'Litru'),
('Paine', 'Bucata'),
('Zahar', 'Kilogram'),
('Ulei', 'Litru'),
('Cafea', 'Gram'),
('Shaorma', 'Bucata');

-- Inserare Agenti
INSERT INTO Agenti (nume, prenume)
VALUES 
('Popescu', 'Ion'),
('Ionescu', 'Maria'),
('Vasilescu', 'Andrei'),
('Dumitru', 'Elena');

-- Inserare Clienti
INSERT INTO Clienti (denumire, cod_fiscal)
VALUES 
('SC ABC SRL', 'RO123456'),
('SC XYZ SRL', 'RO654321'),
('SC Food SRL', 'RO111222'),
('SC Drinks SRL', 'RO333444');

-- Inserare Facturi (minim 15 facturi în luni diferite)
INSERT INTO Factura (numar, data_emitere, clientul, agent)
VALUES 
(1001, '2024-01-10', 1, 2),
(1002, '2024-02-15', 2, 1),
(1003, '2024-03-20', 3, 3),
(1004, '2024-04-25', 4, 4),
(1005, '2024-05-05', 1, 2),
(1006, '2024-06-10', 2, 3),
(1007, '2024-07-15', 3, 1),
(1008, '2024-08-20', 4, 4),
(1009, '2024-09-05', 1, 2),
(1010, '2024-10-10', 2, 3),
(1011, '2024-11-15', 3, 1),
(1012, '2024-12-20', 4, 4),
(1013, '2025-01-05', 1, 2),
(1014, '2025-02-10', 2, 3),
(1015, '2025-03-15', 3, 1);

-- Inserare Lista (Produse pentru fiecare Facturã, inclus "Shaorma")
-- Inserare Lista (corectat pentru includerea id_produs)
INSERT INTO Lista (nr_ordine, id_produs, id_factura, pret, cantitate)
VALUES 
(1, 1, 1, 10, 5),  -- Lapte
(2, 6, 1, 25, 2),  -- Shaorma
(1, 2, 2, 15, 3),  -- Paine
(2, 3, 2, 8, 5),   -- Zahar
(1, 4, 3, 10, 7),  -- Ulei
(2, 6, 3, 20, 15), -- Shaorma
(1, 5, 4, 20, 10), -- Cafea
(1, 3, 5, 6, 12),  -- Zahar
(2, 6, 5, 30, 4),  -- Shaorma
(1, 1, 6, 5, 20),  -- Lapte
(2, 6, 6, 25, 5),  -- Shaorma
(1, 2, 7, 3, 10),  -- Paine
(2, 6, 7, 15, 6),  -- Shaorma
(1, 3, 8, 4, 8),   -- Zahar
(2, 6, 8, 12, 4),  -- Shaorma
(1, 4, 9, 7, 15),  -- Ulei
(2, 6, 9, 18, 3),  -- Shaorma
(1, 5, 10, 10, 6), -- Cafea
(2, 6, 10, 20, 2), -- Shaorma
(1, 3, 11, 8, 10), -- Zahar
(2, 6, 11, 26, 5), -- Shaorma
(1, 1, 12, 6, 12), -- Lapte
(2, 6, 12, 25, 4), -- Shaorma
(1, 2, 13, 9, 10), -- Paine
(2, 6, 13, 30, 8), -- Shaorma
(1, 4, 14, 5, 7),  -- Ulei
(2, 6, 14, 20, 2), -- Shaorma
(1, 5, 15, 15, 8), -- Cafea
(2, 6, 15, 24, 3); -- Shaorma

select * from Lista
create or alter procedure cerinta2
@id_factura int,
@id_produs int,
@nr_ordine int,
@pret int,
@cantitate int
AS
BEGIN
	IF EXISTS(select 1 from Lista where id_factura=@id_factura and 
		id_produs=@id_produs and pret=@pret)
		BEGIN 
		INSERT INTO Lista(id_factura,id_produs,nr_ordine,pret,cantitate)
		VaLUES(@id_factura,@id_produs,@nr_ordine,-@pret,@cantitate)
		END
	ELSe
		BEGIN 
		INSERT INTO Lista(id_factura,id_produs,nr_ordine,pret,cantitate)
		VaLUES(@id_factura,@id_produs,@nr_ordine,@pret,@cantitate)
		END
END;

exec cerinta2 15,4,3,26,10
select * from Lista

CREATe OR ALTER VIEW cerinta3
AS
SELECT 
	C.denumire,F.numar,F.data_emitere,Sum(L.Cantitate*L.Pret) as Valoare
	from Factura F 
	INNER JOIN Lista L on L.id_factura=F.id
	INNER JOIN Clienti C on F.clientul=C.id
	INNER JOIN Produse P on L.id_produs=P.id
	WHERE F.id IN (
		SELECT DISTINCT L2.id_factura
		FROM Lista L2
	    INNER JOIN Produse P ON L2.id_produs = P.id
		WHERE P.denumire LIKE '%shaorma%')
	group by L.id_factura,C.denumire,F.numar,F.data_emitere
	having Sum(L.Cantitate*L.Pret)>300;

select * from cerinta3;

create or alter function cerinta4(@year int)
RETURNS TABLE AS
RETURN 
	SELECT TOP 100 PERCENT 
	MONTH(F.data_emitere) as Luna,
	A.nume as NumeAgent,
	A.prenume as PrenumeAgent,
	Sum(L.Cantitate*L.Pret) as ValoareTotala
	from Factura F 
	INNER JOIN Lista L on L.id_factura=F.id
	INNER JOIN Agenti A on F.agent=A.id
	where YEAR(F.data_emitere)=@year
	group by MONTH(F.data_emitere),A.nume,A.prenume,L.id_factura
	order by MONTH(F.data_emitere),A.nume,A.prenume;

SELECT * 
FROM dbo.cerinta4(2024)
ORDER BY Luna, NumeAgent;
