CREATE DATABASE Trenuri
GO
USE Trenuri
CREATE TABLE Tip(
id INT PRIMARY KEY IDENTITY,
descriere VARCHAR(100)
);

CREATE TABLE Tren(
id INT PRIMARY KEY IDENTITY,
nume VARCHAR(100),
tip int FOREIGN KEY REFERENCES Tip(id)
);

CREATE TABLE Statie(
id INT PRIMARY KEY IDENTITY,
nume VARCHAR(100)
);
CREATE TABLE Ruta(
id INT PRIMARY KEY IDENTITY,
nume VARCHAR(100),
tren INT FOREIGN KEY REFERENCES Tren(id)
);
CREATE TABLE RutaStatie(
id_ruta INT FOREIGN KEY REFERENCES Ruta(id),
id_statie INT FOREIGN KEY REFERENCES Statie(id),
PRIMARY KEY(id_ruta,id_statie),
ora_plecare TIME,
ora_sosire TIME,
);
INSERT INTO Tip (descriere) VALUES 
('InterRegio'), 
('Regio'), 
('Marfar');
INSERT INTO Tren (nume, tip) VALUES 
('IR 1745', 1), 
('R 3489', 2), 
('Marfar 5001', 3);
INSERT INTO Statie (nume) VALUES 
('București Nord'), 
('Ploiești Sud'), 
('Brașov'), 
('Sinaia'), 
('Predeal');
INSERT INTO Ruta (nume, tren) VALUES 
('București - Brașov', 1), 
('București - Ploiești', 2), 
('Ploiești - Predeal', 3);
INSERT INTO Ruta (nume, tren) VALUES 
('București - Predeal',3);
INSERT INTO RutaStatie (id_ruta, id_statie, ora_plecare, ora_sosire) VALUES 
(1, 1, '06:00', '06:05'), -- București Nord
(1, 2, '07:00', '07:10'), -- Ploiești Sud
(1, 3, '08:30', '08:40'), -- Brașov

(2, 1, '09:00', '09:05'), -- București Nord
(2, 2, '10:00', '10:10'), -- Ploiești Sud

(3, 2, '11:00', '11:05'), -- Ploiești Sud
(3, 4, '12:00', '12:10'), -- Sinaia
(3, 5, '12:45', '12:50'); -- Predeal

INSERT INTO RutaStatie (id_ruta, id_statie, ora_plecare, ora_sosire) VALUES 
(4, 1, '21:00', '21:05'), -- București Nord
(4, 2, '22:00', '22:10'), -- Ploiești Sud
(4, 3, '22:30', '23:00'), -- Brașov
(4, 4, '23:30', '23:50'), -- Sinaia
(4, 5, '00:10', '00:50'); -- Predeal

SELECT * FROM Tip;
SELECT * FROM Statie;
SELECT * FROM Ruta;
SELECT * FROM RutaStatie;
SELECT * FROM Tren;

CREATE OR ALTER PROCEDURE cerinta2(@ruta_id INT,@statie_id INT, @ora_sosire TIME,
@ora_plecare TIME)
AS 
BEGIN
	IF EXISTS(SELECT 1 FROM RutaStatie WHERE id_statie=@statie_id and id_ruta=@ruta_id)
	BEGIN 
		UPDATE RutaStatie 
		SET ora_plecare=@ora_plecare, ora_sosire=@ora_sosire
		WHERE id_statie=@statie_id and id_ruta=@ruta_id
	END 
	ELSE
	BEGIN 
		INSERT INTO RutaStatie(id_ruta,id_statie,ora_plecare,ora_sosire) VALUES
		(@ruta_id,@statie_id,@ora_plecare,@ora_sosire);
	END
END;

EXEC cerinta2 1,4,'09:00','08:45';
EXEC cerinta2 1,2,'07:15', '07:05';

CREATE OR ALTER VIEW cerinta3 
AS
SELECT nume as NumeRuta 
FROM Ruta R
INNER JOIN RutaStatie RS ON R.id=RS.id_ruta 
GROUP BY R.nume
HAVING COUNT(DISTINCT RS.id_statie)=(SELECT COUNT(*) FROM Statie);

select * from cerinta3