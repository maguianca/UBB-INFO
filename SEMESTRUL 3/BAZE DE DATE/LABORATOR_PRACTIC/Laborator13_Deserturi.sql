/*Enunț
Să se creeze baza de date a unei aplicații care gestionează deserturile achiziționate de diverși clienți.
Entitățile de interes pentru domeniul problemei sunt: 
producători, tipuri de deserturi, deserturi și clienți. 
Un producător are un nume și un site web. 
Un tip de deserturi are un nume. 
Fiecare desert are un nume, un mod de preparare, un preț, un număr de calorii și aparține unui singur producător și unui singur tip de deserturi. 
Prețul este un număr real. 
Un producător poate produce mai multe deserturi, dar un desert poate fi produs doar de către un singur producător. 
Un tip de deserturi conține mai multe deserturi, dar un desert aparține doar unui singur tip de deserturi. 
Un client are un nume, o adresă de email și o dată a nașterii. 
Un client poate achiziționa mai multe deserturi, și un desert poate fi achiziționat de mai mulți clienți, dar cantitatea poate varia. 
Fiecare desert poate fi asociat unui client maxim o singură dată. 
Cantitatea este un număr întreg.
Cerințe
Scrieți un script SQL care creează un model relațional pentru a reprezenta datele. (4 puncte)
Creați o procedură stocată care primește un desert, un client și o cantitate și adaugă desertul clientului respectiv. Dacă desertul a fost deja adăugat clientului respectiv, se va actualiza cantitatea. (3 puncte)
Creați o funcție definită de utilizator care afișează numele producătorului, numele desertului, numărul de calorii, cantitatea și numele clientului pentru toți clienții al căror nume începe cu litera ‘A’. (2 puncte)
*/
CREATE DATABASE Deserturi 
GO
USE Deserturi
GO
CREATE TABLE Producator(
id int IDENTITY(1,1) PRIMARY KEY ,
nume VARCHAR(300),
site_web VARCHAR(300)
);

CREATE TABLE Tip(
id int IDENTITY(1,1) PRIMARY KEY,
nume VARCHAR(300)
);

CREATE TABLE Desert(
id int IDENTITY(1,1) PRIMARY KEY,
nume VARCHAR(300),
mod_preparare VARCHAR(300),
pret FLOAT,
nr_calorii INT,
id_producator int  FOREIGN KEY references Producator(id),
id_tip int FOREIGN KEY references Tip(id),
);

CREATE TABLE Client(
id int IDENTITY(1,1) PRIMARY KEY,
nume VARCHAR(300),
mail VARCHAR(300),
data_nasterii DATE
);

CREATE TABLE Cantitate(
id_client int FOREIGN KEY references Client(id),
id_desert int FOREIGN KEY references Desert(id),
PRIMARY KEY(id_client,id_desert),
cantitate int,
);

SELECT * from Tip;
Select * from Producator;
select * from Desert;
select* from client;
select* from cantitate;

INSERT INTO Tip(nume)
VALUES('prajitura'),
('cozonac'),
('trufe');

Insert into Producator(nume,site_web)
values('Pralina','www.pralina.ro'),
('Nadinier','www.nadinier.ro'),
('IrisDelice','www.irisdelice.ro'),
('Sucre','www.sucre.ro');

insert into Desert(nume,mod_preparare,pret,nr_calorii,id_producator,id_tip)
VALUES('tiramisu','3 oua,cafea,piscoturi,mascarpone,zahar,dissarono',25.5,200,3,1),
('tiramisu capsuni','capsuni 3 oua,cafea,piscoturi,mascarpone,zahar,dissarono',22,300,1,1),
('cozonac fistic','apa,lapte,zahar,fistic,ciocolata,alune',150,3000,2,2),
('cozonac dubai','apa,lapte,zahar,fistic,ciocolata,alune,cataif',200,2800,3,2),
('pavlova','8 albusuri,fructe,zahar,mascarpone',30,400,4,1),
('ecler','galbenusuri,zahar,vanilie,topping',24.9,500,4,1),
('ciocolata belgiana','ciocolata,zahar,vanilie',100,1000,1,3),
('trufe cu vin fiert','ciocolata,aroma vin fiert',120,1200,2,3);

insert into Client(nume,mail,data_nasterii)
Values('Anca','anca@yahoo.com','2004-05-12'),
('Denisa','denisa@yahoo.com','1995-04-11'),
('Sebastrian','seba@yahoo.com','1998-03-01'),
('Andra','andra@yahoo.com','1998-11-11'),
('Mihaela','mihaela@yahoo.com','1980-03-03'),
('Antonia','antonia@yahoo.com','1999-12-12');

insert into Cantitate(id_client,id_desert,cantitate)
values(1,3,2),(2,6,1),(2,7,5),(1,8,2),(3,1,20),(3,4,1),(3,7,2),
(4,3,3),(4,2,4),(5,1,1),(5,2,2),(5,3,3),(6,4,4),(6,5,5),(6,6,2),(6,7,3),(6,8,1);

create or alter procedure Adaugare_desert(@client_id int,@desert_id int,@cantitate int)
as 
begin
	if exists(
		select 1 from Cantitate
		where id_desert=@desert_id and id_client=@client_id
	 )
	 begin
		update Cantitate
		set cantitate=cantitate+@cantitate
		where id_desert=@desert_id and id_client=@client_id;
	end
	else
	begin
		insert into Cantitate(id_client,id_desert,cantitate)
		values(@client_id,@desert_id,@cantitate);
	end
end;

select * from cantitate;
exec Adaugare_desert 3,5,1;

CREATE FUNCTION Afisare()
RETURNS TABLE
AS
RETURN 
	SELECT P.nume as Producator,
	       D.nume as Desert,
		   D.nr_calorii as Calorii,
		   C.cantitate as Cantitate,
		   Cl.nume as Client
		   FROM Cantitate C
		   JOIN Desert D ON C.id_desert=D.id
		   JOIN Client Cl ON C.id_client=Cl.id
		   JOIN Producator P ON D.id_producator=P.id
		   WHERE Cl.nume LIKE 'A%';

select * from Afisare();
