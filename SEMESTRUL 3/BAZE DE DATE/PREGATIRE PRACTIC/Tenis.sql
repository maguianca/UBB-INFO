use Tenis
go

CREATE TABLE Turnee(
id INT PRIMARY KEY IDENTITY,
locatie VARCHAR(100),
data_inceput DATE,
data_final DATE
);

CREATE TABLE Jucator(
id INT PRIMARY KEY IDENTITY,
nume VARCHAR(100),
puncte INT,
valoare INT
);
CREATE TABLE Arene(
id INT PRIMARY KEY IDENTITY,
nume VARCHAR(100)
);

CREATE TABLE Partide(
id INT PRIMARY KEY IDENTITY,
id_jucator1 INT FOREIGN KEY REFERENCES Jucator(id),
id_jucator2 INT FOREIGN KEY REFERENCES Jucator(id),
arena INT FOREIGN KEY REFERENCES Arene(id),
turneu INT FOREIGN KEY REFERENCES Turnee(id),
data_ora DATETIME,
castigator INT FOREIGN KEY REFERENCES Jucator(id)
);
ALTER TABLE Partide 
ADD turneu INT FOREIGN KEY REFERENCES Turnee(id);
CREATE TABLE Premii(
id_partida INT FOREIGN KEY REFERENCES Partide(id),
id_jucator INT FOREIGN KEY REFERENCES Jucator(id),
PRIMARY KEY(id_partida,id_jucator),
puncte INT,
valoare INT
);

INSERT INTO Turnee (locatie, data_inceput, data_final)  
VALUES  
('Paris', '2025-03-01', '2025-03-10'),  
('New York', '2025-04-15', '2025-04-25'),  
('Tokyo', '2025-06-01', '2025-06-10');

INSERT INTO Jucator (nume, puncte, valoare)  
VALUES  
('Novak Djokovic', 1500, 1000000),  
('Rafael Nadal', 1400, 900000),  
('Roger Federer', 1300, 850000),  
('Carlos Alcaraz', 1200, 800000);

INSERT INTO Arene (nume)  
VALUES  
('Roland Garros'),  
('Arthur Ashe Stadium'),  
('Tokyo Dome');

INSERT INTO Partide (id_jucator1, id_jucator2, arena, data_ora, castigator)  
VALUES  
(1, 2, 1, '2025-03-05 15:00:00', 1),  
(3, 4, 2, '2025-04-20 18:00:00', 4),  
(1, 4, 3, '2025-06-07 20:00:00', 1);

INSERT INTO Premii (id_partida, id_jucator, puncte, valoare)  
VALUES  
(1, 1, 500, 100000),  
(1, 2, 300, 80000),  
(2, 3, 400, 90000),  
(2, 4, 600, 110000),  
(3, 1, 700, 120000),  
(3, 4, 400, 95000);

SELECT * FROM Jucator;
SELECT * FROM Turnee;
SELECT * from Arene;
SELECT * from Premii;
SELECT * from Partide;
UPDATE Partide 
SET turneu=2 Where id=2;

CREATE OR ALTER PROCEDURE cerinta2
@id_turneu INT,
@id_jucator1 INT,
@id_jucator2 INT,
@puncte1 INT,
@puncte2 INT,
@valoare1 INT,
@valoare2 INT,
@castigator INT,
@arena INT,
@data DATETIME
AS 
BEGIN
	IF NOT(EXISTS(SELECT 1 from Partide 
	where turneu=@id_turneu and id_jucator1=@id_jucator1 and id_jucator2=@id_jucator2
	and data_ora=@data))
		BEGIN
			DECLARE @id INT
			INSERT INTO Partide(id_jucator1,id_jucator2,arena,turneu,data_ora,castigator)
			VALUES(@id_jucator1,@id_jucator2,@arena,@id_turneu,@data,@castigator);
			
			SELECT top 1 @id=id from Partide order by id desc
			
			INSERT INTO Premii(id_partida,id_jucator,puncte,valoare)
			VALUES(@id,@id_jucator1,@puncte1,@valoare1)
			INSERT INTO Premii(id_partida,id_jucator,puncte,valoare)
			VALUES(@id,@id_jucator2,@puncte2,@valoare2)
		END
END;

CREATE OR ALTER VIEW cerinta3 
AS 
SELECT 
	J.nume,
	Count(P.id) as PartideCastigate 
FROM Jucator J
	INNER JOIN Partide P ON (P.id_jucator1=J.id or P.id_jucator2=J.id) and 
	P.castigator=J.id
GROUP BY J.nume;

SELECT * from cerinta3 order by PartideCastigate DESC;

CREATE OR ALTER FUNCTION cerinta4(@id_jucator INT)
RETURNS VARCHAR(300)
BEGIN 
	declare @puncte INT
	declare @valoare INT
	set @puncte=0
	set @valoare=0
	select @puncte=puncte, @valoare=valoare from Jucator where Jucator.id=@id_jucator
	select @puncte=@puncte+puncte, @valoare=@valoare+valoare 
	from Partide P
	Inner Join Premii Pr On P.id=Pr.id_partida 
	where (P.id_jucator1=@id_jucator or P.id_jucator2=@id_jucator)
	and Pr.id_jucator=@id_jucator
	return ('Puncte:' + str(@puncte)+ 'Valoare:'+str(@valoare))
END;

print dbo.cerinta4(1);