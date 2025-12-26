CREATE DATABASE Politie
GO 
USE Politie
CREATE TABLE Sectoare(
id INT PRIMARY KEY IDENTITY,
denumire VARCHAR(100)
);
CREATE TABLE Grade(
id INT PRIMARY KEY IDENTITY,
denumire VARCHAR(100)
);

CREATE TABLE Sectii(
id INT PRIMARY KEY IDENTITY,
denumire VARCHAR(100),
adresa VARCHAR(100)
);
CREATE TABLE Politisti(
id INT PRIMARY KEY IDENTITY,
nume VARCHAR(100),
prenume VARCHAR(100),
sectie INT FOREIGN KEY REFERENCES Sectii(id),
grad INT FOREIGN KEY REFERENCES Grade(id)
);
CREATE TABLE Inregistrari(
id INT PRIMARY KEY IDENTITY,
sector int FOREIGN KEY REFERENCES Sectoare(id),
politist int FOREIGN KEY REFERENCES Politisti(id),
data_intrare DATETIME,
data_iesire DATETIME
);

INSERT INTO Sectoare (denumire) VALUES 
('Sector 1'),
('Sector 2'),
('Sector 3'),
('Sector 4'),
('Sector 5');

INSERT INTO Grade (denumire) VALUES 
('Agent'),
('Agent principal'),
('Subinspector'),
('Inspector'),
('Comisar');

INSERT INTO Sectii (denumire, adresa) VALUES 
('Sectia 1', 'Strada Principala 10'),
('Sectia 2', 'Bulevardul Libertatii 25'),
('Sectia 3', 'Calea Victoriei 45'),
('Sectia 4', 'Strada Independentei 5'),
('Sectia 5', 'Aleea Parcului 30');

INSERT INTO Politisti (nume, prenume, sectie, grad) VALUES 
('Popescu', 'Ion', 1, 1),
('Ionescu', 'Maria', 2, 2),
('Dumitrescu', 'Andrei', 3, 3),
('Vasilescu', 'Elena', 4, 4),
('Radu', 'Cristian', 5, 5);

INSERT INTO Inregistrari (sector, politist, data_intrare, data_iesire) VALUES 
 (1,1,'2025-01-11 08:00','2025-01-11 16:00'),
(1, 1, '2025-01-15 08:00:00', '2025-01-15 16:00:00'),
(2, 2, '2025-01-15 09:00:00', '2025-01-15 17:00:00'),
(3, 3, '2025-01-15 10:00:00', '2025-01-15 18:00:00'),
(4, 4, '2025-01-15 11:00:00', '2025-01-15 19:00:00'),
(5, 5, '2025-01-15 12:00:00', '2025-01-15 20:00:00');

CREATE OR ALTER PROCEDURE cerinta2
@politist INT,
@sector INT,
@data_intrare DATETIME,
@data_iesire DATETIME
AS 
BEGIN
	IF EXISTS(Select 1 from Inregistrari where politist=@politist and
	sector=@sector)
		BEGIN
			UPDATE Inregistrari 
			SET data_intrare=@data_intrare, data_iesire=@data_iesire
			where politist=@politist and sector=@sector
		END
	ELSE
		BEGIN
			INSERT INTO Inregistrari(politist,sector,data_intrare,data_iesire)
			VALUES(@politist,@sector,@data_intrare,@data_iesire)
		END
	END
exec cerinta2 1,1,'2025-01-11 08:00','2025-01-11 16:00';
exec cerinta2 5,1,'2025-02-01 08:00','2025-02-01 16:00';
select * from Inregistrari

CREATE OR ALTER VIEW cerinta3
AS 
SELECT 
	S.denumire as Denumire,
	P.nume as Nume,
	P.prenume as Prenume,
	Count(I.id)*8 as Total_ore_munca
	FROM Inregistrari I 
	INNER JOIN Politisti P on I.politist=P.id
	INNER JOIN Sectii S ON P.sectie=S.id
	WHERE YEAR(I.data_intrare)=YEAR(GETDATE())
	and MONTH(I.data_intrare)=1
	GROUP BY S.denumire,P.nume,P.prenume;
select * from cerinta3 order By Denumire,Nume;
