CREATE DATABASE Caleidoscop 
GO
USE Caleidoscop

-- Caleidoscop este un serial Netflix. Are 9 episoade. Fiecare episod are durata,
-- nume si ordine cronologica. Fiecare utilizator (nume, email) vizioneaza epsisoadele
-- intr-o ordine aleatorie, mai putin episodul 9 care va fi vizionat ultimul.
-- Intr-un episod joaca mai multi actori. Fiecare actor are un nume si mai multe replici
-- intr-un episod. O replica contine un text si e spus la un moment dat in episod.
-- Un actor poate sa apara in mai multe episoade.
--  

create table Episod(
id int primary key identity,
durata TIME,
nume varchar(100),
ordine_cronologica INT
);

create table Utilizator(
id int primary key identity,
nume varchar(100),
email varchar(100)
);
create table OrdineEpisodUtilizator(
id_utilizator int foreign key references Utilizator(id),
id_episod int foreign key references Episod(id),
ordine int,
constraint pk_oeu primary key(id_utilizator,id_episod,ordine),
constraint pk_check check(id_episod!=9 or ordine=9)
);
create table Actor(
id int primary key identity,
nume varchar(100)
);
create table Replici(
id int primary key identity,
text varchar(500),
episod int foreign key references Episod(id)
);
create table ActorReplici(
id_actor int foreign key references Actor(id),
id_replici int foreign key references Replici(id),
constraint pk_ar primary key(id_actor,id_replici));

create table ActorEpisod(
id_actor int foreign key references Actor(id),
id_episod int foreign key references Episod(id),
constraint pk_ae primary key(id_actor,id_episod)
);

-- 1. Scrieti un script SQL care creeaza un model relational pentru a reprezenta si stoca datele specifice serialului Caleidoscop (4p)
--  
INSERT INTO Episod (durata, nume, ordine_cronologica)
VALUES
('00:45:00', 'Episod 1', 1),
('00:47:00', 'Episod 2', 2),
('00:46:00', 'Episod 3', 3),
('00:50:00', 'Episod 4', 4),
('00:43:00', 'Episod 5', 5),
('00:44:00', 'Episod 6', 6),
('00:42:00', 'Episod 7', 7),
('00:49:00', 'Episod 8', 8),
('00:51:00', 'Episod 9', 9);
INSERT INTO Utilizator (nume, email)
VALUES
('Maria Ioana','mariaioana@gmail.com'),
('Ion Popescu', 'ion.popescu@email.com'),
('Maria Ionescu', 'maria.ionescu@email.com'),
('George Georgescu', 'george.georgescu@email.com');
-- Ion Popescu
INSERT INTO OrdineEpisodUtilizator (id_utilizator, id_episod, ordine)
VALUES
(1, 1, 1),
(1, 2, 2),
(1, 3, 3),
(1, 4, 4),
(1, 5, 5),
(1, 6, 6),
(1, 7, 7),
(1, 8, 8),
(1, 9, 9);

-- Maria Ionescu
INSERT INTO OrdineEpisodUtilizator (id_utilizator, id_episod, ordine)
VALUES
(4,4,2),
(4,5,1),
(2, 5, 1),
(2, 6, 2),
(2, 7, 3),
(2, 8, 4),
(2, 1, 5),
(2, 2, 6),
(2, 3, 7),
(2, 4, 8),
(2, 9, 9);

-- George Georgescu
INSERT INTO OrdineEpisodUtilizator (id_utilizator, id_episod, ordine)
VALUES
(3, 3, 1),
(3, 1, 2),
(3, 4, 3),
(3, 5, 4),
(3, 2, 5),
(3, 6, 6),
(3, 7, 7),
(3, 8, 8),
(3, 9, 9);
select * from OrdineEpisodUtilizator
INSERT INTO Actor (nume)
VALUES
('John Doe'),
('Jane Smith'),
('Michael Johnson'),
('Emily Davis');
INSERT INTO Replici (text, episod)
VALUES
('Replica 1 din Episod 1', 1),
('Replica 2 din Episod 1', 1),
('Replica 1 din Episod 2', 2),
('Replica 2 din Episod 2', 2),
('Replica 1 din Episod 3', 3),
('Replica 2 din Episod 3', 3),
('Replica 1 din Episod 4', 4),
('Replica 2 din Episod 4', 4),
('Replica 1 din Episod 5', 5),
('Replica 2 din Episod 5', 5),
('Replica 1 din Episod 6', 6),
('Replica 2 din Episod 6', 6),
('Replica 1 din Episod 7', 7),
('Replica 2 din Episod 7', 7),
('Replica 1 din Episod 8', 8),
('Replica 2 din Episod 8', 8),
('Replica 1 din Episod 9', 9),
('Replica 2 din Episod 9', 9);
-- John Doe în Episodul 1
INSERT INTO ActorReplici (id_actor, id_replici)
VALUES
(1, 1),
(1, 2);

-- Jane Smith în Episodul 2
INSERT INTO ActorReplici (id_actor, id_replici)
VALUES
(2, 3),
(2, 4);

-- Michael Johnson în Episodul 3
INSERT INTO ActorReplici (id_actor, id_replici)
VALUES
(3, 5),
(3, 6);

-- Emily Davis în Episodul 4
INSERT INTO ActorReplici (id_actor, id_replici)
VALUES
(4, 7),
(4, 8);

-- Continuă cu alți actori și replici
-- John Doe apare în Episodul 1
INSERT INTO ActorEpisod (id_actor, id_episod)
VALUES
(1, 1);

-- Jane Smith apare în Episodul 2
INSERT INTO ActorEpisod (id_actor, id_episod)
VALUES
(2, 2);

-- Michael Johnson apare în Episodul 3
INSERT INTO ActorEpisod (id_actor, id_episod)
VALUES
(3, 3);

-- Emily Davis apare în Episodul 4
INSERT INTO ActorEpisod (id_actor, id_episod)
VALUES
(4, 4);


-- 2. Creati o procedura care "da play" la urmatorul episod pentru un utilizator dat. (3p)
-- Puteti folosi functiile RAND() (intoarce un nr in (0,1)) si FLOOR(x) (intoarce cel mai mic intreg fata de x)
--  
-- 3. Creati un view care genereaza scriptul serialului (toate replicile) in format "NUME_ACTOR: TEXT_REPLICA" (2p)
create or alter procedure cerinta2
@id_utilizator int
as
begin
    DECLARE @episod INT
	SELECT @episod=COUNT(*) from OrdineEpisodUtilizator 
	WHERE id_utilizator=@id_utilizator

	IF @episod=8
		BEGIN 
			INSERT INTO OrdineEpisodUtilizator(id_utilizator,id_episod,ordine)
			VALUES (@id_utilizator,9,9)
			RETURN 0
		END
	ELSE
		BEGIN
		DECLARE @episod_p INT 
		SET @episod_p=FLOOR(RAND()*8)+1;
		WHILE EXISTS(select 1 from OrdineEpisodUtilizator 
			where id_utilizator=@id_utilizator and id_episod=@episod_p)
				BEGIN 
					SET @episod_p=FLOOR(RAND()*8)+1;
				END
		INSERT INTO OrdineEpisodUtilizator(id_utilizator,id_episod,ordine)
			VALUES (@id_utilizator,@episod_p,@episod+1)
		END
end;
exec cerinta2 4;
select * from OrdineEpisodUtilizator;

-- 3. Creati un view care genereaza scriptul serialului (toate replicile) in format "NUME_ACTOR: TEXT_REPLICA" (2p)

create or alter view cerinta4
AS
select TOP 100 PERCENT
	A.Nume as NUME_ACTOR,R.text as TEXT_REPLICA 
	from Actor A
	inner join ActorReplici AR ON AR.id_actor=A.id
	inner join Replici R ON AR.id_replici=R.id
	inner JOIN Episod E on R.episod=E.id
	ORDER BY E.ordine_cronologica 
select * from cerinta4 
