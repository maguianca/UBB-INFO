CREATE DATABASE Restaurant 
GO 
USE Restaurant

CREATE TABLE Tip(
id INT PRIMARY KEY IDENTITY,
nume VARCHAR(100),
descriere VARCHAR(100)
);
CREATE TABLE Oras(
id INT PRIMARY KEY IDENTITY,
nume VARCHAR(100)
);
CREATE TABLE Restaurant(
id INT PRIMARY KEY IDENTITY,
nume VARCHAR(100),
adresa VARCHAR(100),
telefon VARCHAR(100),
id_tip INT FOREIGN KEY REFERENCES Tip(id),
id_oras INT FOREIGN KEY REFERENCES Oras(id)
);
CREATE TABLE Utilizator(
id INT PRIMARY KEY IDENTITY,
nume_utilizator VARCHAR(100),
email VARCHAR(100),
parola VARCHAR(100)
);
CREATE TABLE Note(
id_utilizator INT FOREIGN KEY REFERENCES Utilizator(id),
id_restaurant INT FOREIGN KEY REFERENCES Restaurant(id),
PRIMARY KEY(id_utilizator,id_restaurant),
nota FLOAT
);
INSERT INTO Tip (nume, descriere) VALUES
('Pizzerie', 'Specializat în pizza'),
('Fast-Food', 'Mâncare rapidă'),
('Fine Dining', 'Restaurant de lux'),
('Bistro', 'Restaurant casual');
INSERT INTO Oras (nume) VALUES
('București'),
('Cluj-Napoca'),
('Timișoara'),
('Iași'),
('Brașov');
INSERT INTO Restaurant (nume, adresa, telefon, id_tip, id_oras) VALUES
('Pizza Hut', 'Strada Principală 12', '0723456789', 1, 1),   -- Pizzerie, București
('McDonald s', 'Bd. Unirii 45', '0745123456', 2, 2),         -- Fast-Food, Cluj-Napoca
('Casa Lux', 'Calea Victoriei 15', '0734567890', 3, 1),       -- Fine Dining, București
('La Bistro', 'Piața Mare 10', '0756123456', 4, 3),           -- Bistro, Timișoara
('Burger King', 'Str. Libertății 9', '0745781234', 2, 4);     -- Fast-Food, Iași
INSERT INTO Utilizator (nume_utilizator, email, parola) VALUES
('Ion Popescu', 'ion.popescu@example.com', 'parola123'),
('Maria Ionescu', 'maria.ionescu@example.com', 'parola456'),
('Andrei Vasilescu', 'andrei.vasilescu@example.com', 'parola789');
INSERT INTO Note (id_utilizator, id_restaurant, nota) VALUES
(1, 1, 8.5),  -- Ion Popescu notează Pizza Hut cu 8.5
(2, 2, 7.0),  -- Maria Ionescu notează McDonald's cu 7.0
(3, 3, 9.0),  -- Andrei Vasilescu notează Casa Lux cu 9.0
(1, 4, 6.5),  -- Ion Popescu notează La Bistro cu 6.5
(2, 5, 8.0);  -- Maria Ionescu notează Burger King cu 8.0

CREATE PROCEDURE cerinta2(@id_restaurant INT, @id_utilizator INT,@nota FLOAT)
AS 
BEGIN 
	IF EXISTS(SELECT 1 FROM Note where id_restaurant=@id_restaurant and id_utilizator=@id_utilizator)
		BEGIN 
			UPDATE Note
			SET nota=@nota
			WHERE id_restaurant=@id_restaurant and id_utilizator=@id_utilizator
		END 
	ELSE 
		BEGIN 
			INSERT INTO Note(id_restaurant,id_utilizator,nota)
			VALUES(@id_restaurant,@id_utilizator,@nota);
		END 
END;

EXEC cerinta2 2, 2, 9.5;  -- Maria Ionescu (id_utilizator = 2) actualizează nota pentru Pizza Hut (id_restaurant = 1)
EXEC cerinta2 5, 3, 8.7;  -- Andrei Vasilescu (id_utilizator = 3) adaugă o nouă notă pentru Burger King (id_restaurant = 5)

SELECT * FROM Note;

CREATE OR ALTER FUNCTION cerinta3(@adresa VARCHAR(100))
RETURNS TABLE 
AS 
RETURN
( 
	SELECT 
		T.nume AS TipRestaurant,
		R.nume as NumeRestaurant,
		R.telefon as Telefon,
		O.nume as Oras,
		N.nota as Nota,
		U.nume_utilizator as NumeUtilizator,
		U.email as EmailUtilizator
	FROM Note N 
	INNER JOIN Utilizator U on N.id_utilizator=U.id
	INNER JOIN Restaurant R on N.id_restaurant=R.id
	INNER JOIN Tip T on R.id_tip=T.id
	INNER JOIN Oras O on R.id_oras=O.id
	WHERE U.email=@adresa
);

select * from cerinta3('ion.popescu@example.com');