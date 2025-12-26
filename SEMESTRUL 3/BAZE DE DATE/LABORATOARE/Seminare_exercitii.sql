CREATE DATABASE Seminar4
GO 
USE Seminar4

CREATE TABLE Sectiuni (
    cod_s INT PRIMARY KEY, 
    nume VARCHAR(100), 
    descriere VARCHAR(100)
);

CREATE TABLE Atractii (
    cod_a INT PRIMARY KEY, 
    nume VARCHAR(100), 
    descriere VARCHAR(100),
    varsta_min INT,
    cod_s INT,
    FOREIGN KEY(cod_s) REFERENCES Sectiuni(cod_s)
);

CREATE TABLE Categorii (
    cod_c INT PRIMARY KEY,
    nume VARCHAR(100)
);

CREATE TABLE Vizitatori (
    cod_v INT PRIMARY KEY,
    nume VARCHAR(100),
    email VARCHAR(200),
    cod_c INT,
    FOREIGN KEY(cod_c) REFERENCES Categorii(cod_c)
);

CREATE TABLE Note (
    cod_a INT,
    cod_v INT,
    PRIMARY KEY (cod_a, cod_v),
    FOREIGN KEY(cod_a) REFERENCES Atractii(cod_a),
    FOREIGN KEY(cod_v) REFERENCES Vizitatori(cod_v),
    nota INT
);

INSERT INTO Sectiuni (cod_s, nume, descriere)
VALUES
(1, 'Aventura', 'Sectiunea pentru activitati de aventura'),
(2, 'Relaxare', 'Sectiunea pentru activitati de relaxare'),
(3, 'Copii', 'Sectiunea pentru activitati destinate copiilor');


INSERT INTO Atractii (cod_a, nume, descriere, varsta_min, cod_s)
VALUES
(1, 'Rollercoaster', 'Un rollercoaster palpitant', 12, 1),
(2, 'Piscina', 'O piscina pentru relaxare', 6, 2),
(3, 'Labirintul copiilor', 'Un labirint pentru cei mici', 3, 3);


INSERT INTO Categorii (cod_c, nume)
VALUES
(1, 'Adult'),
(2, 'Copil'),
(3, 'Senior'),
(4,'Pensionar');


INSERT INTO Vizitatori (cod_v, nume, email, cod_c)
VALUES
(1, 'Ion Popescu', 'ion.popescu@example.com', 1),
(2, 'Maria Ionescu', 'maria.ionescu@example.com', 2),
(3, 'Vasile Dumitru', 'vasile.dumitru@example.com', 3);

INSERT INTO Note (cod_a, cod_v, nota)
VALUES
(1, 1, 10),
(2, 2, 9),
(3, 3, 8);

CREATE FUNCTION CodCategorie(@nume VARCHAR(70))
RETURNS INT AS 
BEGIN 
	DECLARE @cod_c INT;
	SELECT @cod_c=cod_c
	FROM Categorii
	WHERE nume=@nume

	if @cod_c IS NULL
		RETURN 0
	RETURN @cod_c
END
GO
PRINT dbo.CodCategorie('Copil');

CREATE TRIGGER Trg_PreventDeleteCategorii
ON Categorii
INSTEAD OF DELETE
AS
BEGIN
    PRINT 'Stergerea din tabelul Categorii este interzisã.'
END;
GO

DELETE FROM Categorii WHERE cod_c=1;

SELECT * FROM Categorii;
SELECT* FROM Atractii;
SELECT * FROM Note;
SELECT * FROM Sectiuni;
GO
CREATE VIEW View_pensionar_copil
AS 
SELECT C.cod_c,C.nume
FROM Categorii C
WHERE C.nume='Pensionar' OR C.nume='Copil';
GO

SELECT * FROM View_pensionar_copil;

CREATE VIEW Sectiune_C AS
SELECT *
FROM Sectiuni
WHERE nume LIKE 'C%';

SELECT * FROM Sectiune_C;

CREATE FUNCTION Sectiune_nume(@caracter NVARCHAR(1))
RETURNS 
TABLE AS
RETURN(
	SELECT * 
	FROM Sectiuni
	WHERE LEN(nume)>=2 AND nume LIKE '%'+ @caracter
);
GO
SELECT * FROM dbo.Sectiune_nume('a');

CREATE VIEW View_VisitorNoteAttraction
AS
SELECT 
    Vizitatori.nume AS Nume,
    Note.nota AS Nota,
    Atractii.nume AS NumeAtractie
FROM Note
INNER JOIN Vizitatori ON Note.cod_v = Vizitatori.cod_v
INNER JOIN Atractii ON Note.cod_a = Atractii.cod_a;