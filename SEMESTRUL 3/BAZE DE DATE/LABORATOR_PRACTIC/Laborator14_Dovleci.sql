/*Enunț
Să se creeze o bază de date care gestionează o competiție de decorare a dovlecilor de Halloween.
Un participant la competiție are un nume, un număr de telefon și o adresă.
Organizatorii competiției pun la dispoziție mai mulți dovleci care pot fi decorați de către mai mulți participanți.
Fiecare dovleac poate fi decorat de către mai mulți participanți, iar fiecare participant poate participa la decorarea mai multor dovleci.
Un dovleac are o descriere, data la care a fost decorat, timpul total necesar acțiunii de decorare și o mențiune care marchează dacă decorarea dovleacului a fost sau nu finalizată.
Contribuția fiecărui participant la decorarea fiecărui dovleac va fi menționată printr-o descriere a activității de decorare.
Se poate stoca maxim o singură descriere a activității de decorare efectuată de către fiecare participant asupra fiecărui dovleac.
La finalul competiției, mai mulți evaluatori vor acorda câte o notă cuprinsă între 1 și 10 fiecărui dovleac. Fiecare evaluator poate acorda maxim o singură notă fiecărui dovleac.
Nota este un număr întreg.
Un evaluator are un nume, o adresă de email și o dată a nașterii.
Cerințe
Scrieți un script SQL care creează un model relațional pentru a reprezenta datele. (4 puncte)
Creați o procedură stocată care primește un participant și un dovleac și adaugă descrierea activității de decorare a participantului asupra dovleacului. Dacă dovleacul a fost deja asociat participantului respectiv, descrierea activității de decorare va fi actualizată. (3 puncte)
Creați un view care afișează numele participantului care a decorat cei mai mulți dovleci marcați ca finalizați în cadrul competiției. (2 puncte)
*/

CREATE DATABASE Dovleac

GO 
USE Dovleac

CREATE TABLE Participant(
id int primary key identity,
nume VARCHAR(100),
telefon VARCHAR(100),
adresa VARCHAR(100)
);
CREATE TABLE Dovleci(
id int primary key identity,
descriere VARCHAR(100),
data DATETIME,
timp TIME,
decorat BIT
);
CREATE TABLE Activitate(
id_participant int FOREIGN KEY REFERENCES Participant(id),
id_dovleac int foreign key references Dovleci(id),
PRIMARY KEY (id_participant,id_dovleac),
descriere VARCHAR(100)
);
CREATE TABLE Evaluator(
id int primary key identity,
nume varchar(100),
adresa_email varchar(100),
data_nasterii DATETIME
);

CREATE TABLE Note(
id_dovleac int foreign key references Dovleci(id),
id_evaluator int foreign key references Evaluator(id),
primary key(id_dovleac,id_evaluator),
nota int check(nota between 1 and 10)
);

INSERT INTO Participant(nume,telefon,adresa) VALUES
('Maria','038374678','Dorobanti Cluj'),
('Ioana','98376467','Marasti Cluj 87'),
('Miruna','0102929','Iulius Mall'),
('Georgel','029293093','Dealul Ciuperca'),
('Mihai','072726363','Crinului');

INSERT INTO Dovleci(descriere,data,timp,decorat)VALUES
('dovleac 1','2024-11-12','00:07:11',1),
('dovleac 2','2025-01-01','01:00:10',1),
('dovleac 3','2025-01-20','00:01:00',0),
('dovleac 4','2025-01-22','00:03:00',0),
('dovleac 5','2025-01-20','00:55:30',1);

INSERT INTO Activitate(id_participant,id_dovleac,descriere) VALUES
(1,1,'A taiat codita dovleacului'),
(3,1,'A vopsit dovleacul roz'),
(5,1,'A scos semintele'),
(2,2,'A scos semintele'),
(3,2,'A venit cu design-ul'),
(4,2,'A executat tot'),
(5,3,'A facut tot de unul singur si s-a lasat'),
(4,4,'A incercat sa taie dovleacul dar nu a putut'),
(2,5,'A taiat gura si nasul'),
(3,5,'A scos semintele');

INSERT INTO Evaluator(nume,adresa_email,data_nasterii)VALUES
('Martina','martina@yahoo.com','1999-11-11'),
('Domnul Mihai','domnul@gmail.com','1988-12-03'),
('Tanti Irina','irina12@yahoo.com','1945-09-09'),
('Mircea Tatu','mircea@gmail.com','1987-04-06');
INSERT INTO Note(id_dovleac,id_evaluator,nota)VALUES
(1,1,9),
(1,2,10),
(1,3,7),
(1,4,6),
(2,1,8),
(2,2,10),
(2,3,8),
(2,4,5),
(3,1,8),
(3,2,10),
(3,3,9),
(3,4,9),
(4,1,8),
(4,2,8),
(4,3,10),
(4,4,5),
(5,1,9),
(5,2,4),
(5,3,7),
(5,4,6);

CREATE OR ALTER PROCEDURE cerinta2 
@id_participant INT,
@id_dovleac INT,
@descriere VARCHAR(100)
AS
BEGIN
	IF  EXISTS(select * from Activitate 
	where id_participant=@id_participant and id_dovleac=@id_dovleac)
	BEGIN
		UPDATE Activitate 
		SET descriere=@descriere
		WHERE id_participant=@id_participant and id_dovleac=@id_dovleac
	END
	ELSE
	BEGIN
		INSERT INTO Activitate(id_participant,id_dovleac,descriere)
		VALUES(@id_participant,@id_dovleac,@descriere)
	END
END

exec cerinta2 2,2,'A scos semintele si a taiat codita';
select * from Activitate;
exec cerinta2 5,4,'A lustruit dovleacul';

CREATE OR ALTER VIEW cerinta3
AS
SELECT TOP 1 
	P.nume AS Nume,
	P.adresa AS Adresa,
	P.telefon As Telefon
FROM Participant P
INNER JOIN Activitate A ON A.id_participant=P.id
INNER JOIN Dovleci D On D.decorat=1 AND D.id=A.id_dovleac
GROUP BY P.nume,P.adresa,P.telefon
Order BY COUNT(*) DESC;

select * from cerinta3;



