CREATE DATABASE Inchirieri
GO
USE Inchirieri

CREATE TABLE Clienti(
id INT PRIMARY KEY IDENTITY,
nume VARCHAR(100),
prenume VARCHAR(100)
);

CREATE TABLE Angajati(
id INT PRIMARY KEY IDENTITY,
nume VARCHAR(100),
prenume VARCHAR(100)
);

CREATE TABLE Marci(
id INT PRIMARY KEY IDENTITY,
denumire VARCHAR(100)
);

CREATE TABLE Autovehicule(
id INT PRIMARY KEY IDENTITY,
nr_inmatriculare VARCHAR(100),
tip VARCHAR(100),
marca INT FOREIGN KEY REFERENCES Marci(id)
);
CREATE TABLE Inchirieri(
id INT PRIMARY KEY IDENTITY,
angajat INT FOREIGN KEY REFERENCES Angajati(id),
client INT FOREIGN KEY REFERENCES Clienti(id),
masina INT FOREIGN KEY REFERENCES Autovehicule(id),
data_inchiriere DATETIME,
data_returnare DATETIME
);

INSERT INTO Clienti (nume, prenume) VALUES 
('Popescu', 'Andrei'),
('Ionescu', 'Maria'),
('Dumitru', 'Alexandru'),
('Radu', 'Elena');

INSERT INTO Angajati (nume, prenume) VALUES 
('Georgescu', 'Mihai'),
('Stan', 'Cristina'),
('Munteanu', 'Daniel'),
('Iliescu', 'Ana');

INSERT INTO Marci (denumire) VALUES 
('BMW'),
('Audi'),
('Mercedes'),
('Volkswagen');

INSERT INTO Autovehicule (nr_inmatriculare, tip, marca) VALUES 
('B123ABC', 'SUV', 1), -- BMW
('B456DEF', 'Sedan', 2), -- Audi
('B789GHI', 'Coupe', 3), -- Mercedes
('B101JKL', 'Hatchback', 4); -- Volkswagen

INSERT INTO Inchirieri (angajat, client, masina, data_inchiriere, data_returnare) VALUES 
(1, 1, 1, '2025-01-10 10:00:00', '2025-01-15 18:00:00'),
(2, 2, 2, '2025-01-12 09:00:00', '2025-01-14 16:00:00'),
(3, 3, 3, '2025-01-11 14:00:00', '2025-01-20 12:00:00'),
(4, 4, 4, '2025-01-13 08:30:00', '2025-01-17 20:00:00');

CREATE OR ALTER PROCEDURE cerinta2
@angajat INT,
@masina INT,
@client INT,
@data_i DATETIME,
@data_ret DATETIME,
@ok BIT
AS
BEGIN 
	IF (@ok='True')
	BEGIN 
		INSERT INTO Inchirieri(angajat,client,masina,data_inchiriere,data_returnare)
		VALUES (@angajat,@client,@masina,@data_i,@data_ret);
	END
	ELSE
	BEGIN 
		DECLARE @id INT
		UPDATE Inchirieri 
		SET data_inchiriere=@data_i, data_returnare=@data_ret
		WHERE angajat=@angajat and client=@client and @masina=masina
	END
END;

exec cerinta2 3, 3, 3, '2025-01-11 17:44:00', '2025-01-20 21:00:00',0;
select * from Inchirieri;
exec cerinta2 3, 4, 2, '2025-01-11 08:00:00', '2025-01-20 21:00:00',1;

CREATE OR ALTER VIEW cerinta3 
AS 
SELECT	
	A.nume As Nume ,
	A.prenume as Prenume 
	From Angajati A
	INNER JOIN Inchirieri I ON A.id=I.angajat
	INNER JOIN Autovehicule Auto ON I.masina=Auto.id
	INNER JOIN Marci M on Auto.marca= M.id
	Where m.denumire='Volkswagen' and MONTH(I.data_inchiriere)=MONTH(GETDATE())
	and YEAR(I.data_inchiriere)=YEAR(GETDATE());

select * from cerinta3
select * from angajati
select * from inchirieri

CREATE OR ALTER FUNCTION cerinta4(@data DATETIME)
RETURNS TABLE AS 
RETURN 
SELECT 
	Auto.nr_inmatriculare AS Numar_autovehicul,
	M.denumire AS Marca,
	Auto.tip AS Tip_Motorizare
	from Autovehicule Auto
	INNER JOIN Marci M ON Auto.marca=M.id
	WHERE Auto.id NOT IN(
	SELECT I.masina FROM Inchirieri I
	WHERE @data BETWEEN I.data_inchiriere AND I.data_returnare);

select * from cerinta4('2025-01-11 10:00')