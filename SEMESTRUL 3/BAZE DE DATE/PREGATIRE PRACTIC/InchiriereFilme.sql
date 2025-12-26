CREATE DATABASE InchirieriFilme
GO 
USE InchirieriFilme

CREATE TABLE Tip(
id INT PRIMARY KEY IDENTITY,
descriere VARCHAR(100)
);
CREATE TABLE Regizor(
id INT PRIMARY KEY IDENTITY,
nume VARCHAR(100),
data_nasterii DATETIME
);
CREATE TABLE Filme(
id INT PRIMARY KEY IDENTITY,
titlu VARCHAR(100),
durata INT,
anul INT,
pret INT,
regizor INT FOREIGN KEY REFERENCES Regizor(id),
tip INT FOREIGN KEY REFERENCES Tip(id)
);
CREATE TABLE Tari(
id INT PRIMARY KEY IDENTITY,
nume VARCHAR(100)
);
CREATE TABLE Actori(
id INT PRIMARY KEY IDENTITY,
nume VARCHAR(100) UNIQUE,
tara INT FOREIGN KEY REFERENCES Tari(id)
);
CREATE TABLE ActoriFilme(
id_actor INT FOREIGN KEY REFERENCES Actori(id),
id_filme INT FOREIGN KEY REFERENCES Filme(id),
PRIMARY KEY(id_actor,id_filme)
);
CREATE TABLE Clienti(
id INT PRIMARY KEY IDENTITY,
nume VARCHAR(100)
);
CREATE TABLE Inchiriere(
id_client INT FOREIGN KEY REFERENCES Clienti(id),
id_film INT FOREIGN KEY REFERENCES Filme(id),
PRIMARY KEY(id_client,id_film),
data_inchiriere DATETIME,
data_returnare DATETIME
);

INSERT INTO Tip (descriere) VALUES 
('Comedie'),
('Drama'),
('Actiune'),
('Horror'),
('Documentar');

INSERT INTO Regizor (nume, data_nasterii) VALUES 
('Steven Spielberg', '1946-12-18'),
('Christopher Nolan', '1970-07-30'),
('Quentin Tarantino', '1963-03-27'),
('Martin Scorsese', '1942-11-17'),
('James Cameron', '1954-08-16');

INSERT INTO Filme (titlu, durata, anul, pret, regizor, tip) VALUES 
('Povestea lui Han-Tatar',150,1980,15,1,2),
('O poveste de Craciun',200,1999,18,2,3),
('Jurassic Park', 127, 1993, 15, 1, 3),
('Inception', 148, 2010, 20, 2, 2),
('Pulp Fiction', 154, 1994, 18, 3, 2),
('The Wolf of Wall Street', 180, 2013, 25, 4, 1),
('Avatar', 162, 2009, 22, 5, 4);

INSERT INTO Tari (nume) VALUES 
('SUA'),
('Canada'),
('Marea Britanie'),
('Franta'),
('Australia');

INSERT INTO Actori (nume, tara) VALUES 
('Leonardo DiCaprio', 1),
('Brad Pitt', 1),
('Tom Hardy', 3),
('Margot Robbie', 5),
('Samuel L. Jackson', 1);

INSERT INTO ActoriFilme (id_actor, id_filme) VALUES 
(2, 5),
(3, 6),
(1, 4), -- Leonardo DiCaprio in The Wolf of Wall Street
(2, 3), -- Brad Pitt in Pulp Fiction
(3, 2), -- Tom Hardy in Inception
(4, 4), -- Margot Robbie in The Wolf of Wall Street
(5, 3); -- Samuel L. Jackson in Pulp Fiction


INSERT INTO Clienti (nume) VALUES 
('Andrei Popescu'),
('Maria Ionescu'),
('Alex Dumitrescu'),
('Elena Georgescu'),
('Cristian Radu');

INSERT INTO Inchiriere (id_client, id_film, data_inchiriere, data_returnare) VALUES 
(4, 2, '2021-01-10 14:00:00', '2021-01-12 18:00:00'),
(4, 3, '2021-01-10 14:00:00', '2021-01-12 18:00:00'),
(5, 1, '2021-01-10 14:00:00', '2021-01-12 18:00:00'),
(1, 2, '2025-01-10 14:00:00', '2025-01-12 18:00:00'),
(2, 4, '2025-01-11 10:00:00', '2025-01-15 16:00:00'),
(3, 1, '2025-01-09 12:00:00', '2025-01-11 20:00:00'),
(4, 5, '2025-01-14 09:00:00', '2025-01-18 19:00:00'),
(5, 3, '2025-01-13 15:00:00', '2025-01-16 17:00:00');

select * from filme F
where F.titlu LIKE '%poveste%';

CREATE OR ALTER VIEW cerinta3
AS
SELECT 
	A.nume as Nume,A.tara as TaraProvenienta,Count(*) as Numar
	FROM Actori A 
	INNER JOIN ActoriFilme AF ON A.id=AF.id_actor
	group by A.nume,A.tara
	having Count(*) >=3
select * from cerinta3

CREATE OR ALTER PROCEDURE cerinta4
AS 
BEGIN 
	Select 
		F.titlu,
		F.durata,
		F.anul,
		F.pret,
		F.regizor,
		F.tip 
		from Filme F 
		WHERE F.id NOT IN(SELECT id_film from Inchiriere)
END;
CREATE OR ALTER PROCEDURE cerinta4_2
AS 
BEGIN 
	Select 
		F.titlu,
		F.durata,
		F.anul,
		F.pret,
		F.regizor,
		F.tip 
		from Filme F 
		LEFT JOIN Inchiriere I on I.id_film=F.id
		WHERE I.id_film is NULL
END;
exec cerinta4;
exec cerinta4_2;

CREATE OR ALTER FUNCTION cerinta5()
RETURNS INT AS
BEGIN 
	DECLARE @numar INT
	SET @numar=0
	SELECT @numar=COUNT(*) from
	(SELECT DISTINCT I.id_client from Inchiriere I 
	INNER JOIN Filme F On I.id_film=F.id 
	where YEAR(I.data_inchiriere)=2021 and F.pret>30
	GROUP BY I.id_client) as Clienti
	RETURN @numar
END;

print dbo.cerinta5();

	
