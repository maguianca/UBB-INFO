--comentariu pe o linie
/* comentariu 
pe mai multe
linii
*/
--crearea unei baze de date
CREATE DATABASE[Laborator 1];

GO 
--conectare la baza de mai sus (folosim GO ca sa avem eroare)
USE [Laborator 1];
--crearea unui tabel
CREATE TABLE Persoane
(cod_p INT PRIMARY KEY IDENTITY(1,1), 
nume VARCHAR(100), 
data_nasterii DATE,
localitate VARCHAR(140)
);