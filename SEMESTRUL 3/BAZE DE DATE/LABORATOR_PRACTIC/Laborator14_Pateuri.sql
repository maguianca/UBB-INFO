/*
Enunț
Să se creeze baza de date a unei aplicații care gestionează recenziile lăsate de către participanți pateurilor pe care le-au gustat în cadrul unor evenimente de degustare.
Entitățile de interes pentru domeniul problemei sunt: participanți, producători, pateuri și evenimente de degustare.
Fiecare producător are un nume, un website, și un număr de telefon. Un producător poate produce mai multe pateuri, dar fiecare pate poate fi produs de către un singur producător. Fiecare pate are o denumire, o descriere, un număr de calorii, un gramaj, o dată a lansării pe piață și un producător asociat. Un pate poate fi inclus în cadrul mai multor evenimente de degustare, iar în cadrul unui eveniment de degustare pot fi incluse mai multe pateuri. Fiecare eveniment de degustare are un nume, o dată și oră, o adresă și un sponsor principal. Un participant poate participa la mai multe evenimente de degustare, iar un eveniment de degustare poate avea mai mulți participanți.
Fiecare participant poate acorda fiecărui pate gustat în cadrul fiecărui eveniment o singură recenzie.
Nu se pot stoca în baza de date recenzii care au valoarea NULL.
Fiecare participant are un nume, o adresă de email și o dată a nașterii.
Cerințe
Scrieți un script SQL care creează un model relațional pentru a reprezenta datele. (4 puncte)
Creați o procedură stocată care primește un pate, un eveniment de degustare și un participant și adaugă o recenzie pateului gustat de către participant în cadrul evenimentului de degustare. Dacă recenzia există deja, ea va fi actualizată. (3 puncte)
Creați o funcție definită de utilizator care afișează numele producătorului, denumirea pateului, descrierea pateului, numărul de calorii  și conținutul recenziei pentru toate pateurile a căror denumire conține cuvântul ‘crocodil’ și a căror recenzie se încheie cu cuvântul ‘grăsime’. (2 puncte)
*/
CREATE DATABASE Pateuri 
GO
USE Pateuri

CREATE TABLE Producator(
id int primary key identity,
nume VARCHAR(100),
website VARCHAR(100),
numar_telefon VARCHAR(100)
);
Create TABLE Pateu(
id int primary key identity,
denumire VARCHAR(100),
descriere VARCHAR(100),
numar_calorii int,
gramaj int,
data_lansarii DATETIME,
producator int foreign key references Producator(id)
);
Create Table Eveniment(
id int primary key identity,
nume VARCHAR(100),
data DATETIME,
adresa VARCHAR(100),
sponsor VARCHAR(100)
);
Create table Participant(
id int primary key identity,
nume VARCHAR(100),
adresa_email VARCHAR(100),
data_nasterii DATETIME
);
create table Note(
id_participant int foreign key references Participant(id),
id_eveniment int foreign key references Eveniment(id),
id_pateu int foreign key references Pateu(id),
recenzie varchar(100) NOT NULL,
constraint pk_key_note primary key(id_participant,id_eveniment,id_pateu)
);

CREATE OR ALTER PROCEDURE cerinta2
@id_pateu int,
@id_eveniment int,
@id_participant int,
@recenzie VARCHAR(100)
AS 
BEGIN 
	IF EXISTS(SELECT 1 FROM Note where id_participant=@id_participant
	and id_eveniment=@id_eveniment and id_pateu=@id_pateu)
		BEGIN 
			UPDATE Note
			SET recenzie=@recenzie
			where id_participant=@id_participant
	and id_eveniment=@id_eveniment and id_pateu=@id_pateu
		END
	ELSE
		BEGIN
			INSERT INTO Note(id_eveniment,id_participant,id_pateu,recenzie)
			VALUES(@id_eveniment,@id_participant,@id_pateu,@recenzie)
		END
END

INSERT INTO Producator (nume, website, numar_telefon) VALUES
('Producator Delicios', 'www.delicios.ro', '0712345678'),
('Gust Autentic', 'www.gustautentic.com', '0723456789'),
('Bunătăți Naturale', 'www.bunatati.ro', '0734567890');
INSERT INTO Pateu (denumire, descriere, numar_calorii, gramaj, data_lansarii, producator) VALUES
('Pateu Clasic', 'Pateu cu gust tradițional', 250, 100, '2023-06-15', 1),
('Pateu Vegetal', 'Pateu fără carne, pentru vegetarieni', 200, 120, '2024-01-10', 2),
('Pateu Gourmet', 'Pateu cu ingrediente premium', 300, 150, '2023-09-25', 3),
('Bucuria crocodilului', 'Pateu cu gust de crocodil',500,200,'2024-12-12',2),
('Pateu de crocodil','Pateu cu gust rafinat',450,220,'2024-11-12',2);

INSERT INTO Eveniment (nume, data, adresa, sponsor) VALUES
('Festivalul Pateului', '2025-03-10', 'Piața Centrală, București', 'Producator Delicios'),
('Târgul Gusturilor', '2025-06-20', 'Parcul Mare, Cluj-Napoca', 'Gust Autentic'),
('Ziua Pateului', '2025-12-01', 'Sala Polivalentă, Iași', 'Bunătăți Naturale');
INSERT INTO Participant (nume, adresa_email, data_nasterii) VALUES
('Maria Popescu', 'maria.popescu@gmail.com', '1990-05-12'),
('Ion Ionescu', 'ion.ionescu@yahoo.com', '1985-08-20'),
('Ana Georgescu', 'ana.georgescu@outlook.com', '1995-02-15');
INSERT INTO Note (id_participant, id_eveniment, id_pateu, recenzie) VALUES
(1, 1, 1, 'Delicios! Mi-a plăcut foarte mult.'),
(2, 2, 2, 'Foarte bun și sănătos.'),
(3, 3, 3, 'Un gust rafinat, merită încercat.'),
(1, 2, 3, 'Puțin prea scump, dar gustos.'),
(2, 1, 2, 'Perfect pentru vegetarieni!'),
(1,3,4,'Are foarte putina grasime,recomand!'),
(2,3,5,'Are un gust rafinat, nu se simte grasimea de crocodil');

exec cerinta2 1,1,2, 'Nu pot spune ca m-a dat pe spate!';
select * from note;
exec cerinta2 1,1,1,'Delicios! Mi-a plăcut foarte mult.Ador!';
exec cerinta2 4,3,1,'Recomand!Are foarte putina grasime';

CREATE OR ALTER FUNCTION cerinta4()
RETURNS TABLE 
AS
RETURN 
SELECT 
	Pr.nume as NumeProducator,
	P.denumire as NumePateu,
	P.descriere as DescrierePateu,
	P.numar_calorii as NumarCalorii,
	N.recenzie as Recenzie
	FROM Note N
	INNER JOIN Pateu P on N.id_pateu=P.id
	INNER JOIN Producator Pr ON P.producator=Pr.id
	where N.recenzie LIKE '%grasime' and P.denumire LIKE '%crocodil%';

select * from cerinta4();