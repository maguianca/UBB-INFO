USE MagazinDeBijuterii
GO
select* from BorderouMarcare;


------BorderouMarcare
CREATE OR ALTER FUNCTION dbo.ValideazaIdBorderou(
    @id_borderou VARCHAR(300)
)
RETURNS INT
AS
BEGIN
    IF @id_borderou IS NULL OR LTRIM(RTRIM(@id_borderou)) = ''
        RETURN 1;
    RETURN 0;
END;

CREATE OR ALTER FUNCTION dbo.ValideazaPret(
    @pret FLOAT
)
RETURNS INT
AS
BEGIN
    IF @pret IS NULL OR @pret <= 0
        RETURN 1;
    RETURN 0;
END;


CREATE OR ALTER PROCEDURE ValideazaBorderouMarcare(
    @id_borderou VARCHAR(300),
    @pret_marcare FLOAT
)
AS 
BEGIN
    DECLARE @error_msg NVARCHAR(MAX) = '';
    IF dbo.ValideazaIdBorderou(@id_borderou) = 1
    BEGIN
        SET @error_msg += 'ID-ul borderoului nu poate fi gol. ';
    END;
    IF dbo.ValideazaPret(@pret_marcare) = 1
    BEGIN
        SET @error_msg += 'Pretul de marcare trebuie sã fie un numar pozitiv. ';
    END;
    IF EXISTS (SELECT 1 FROM BorderouMarcare WHERE id_borderou = @id_borderou)
    BEGIN
        SET @error_msg += 'Borderoul specificat exista deja în baza de date. ';
    END;
    IF LEN(@error_msg) > 0
    BEGIN
        RAISERROR (@error_msg, 16, 1);
        RETURN;
    END;

    PRINT 'Borderoul a fost validat cu succes.';
END;


/*CREATE OR ALTER PROCEDURE CRUD_BorderouMarcare(
    @id_borderou VARCHAR(300),
    @pret_marcare FLOAT,
    @pret_nou FLOAT
)
AS
BEGIN
    SET NOCOUNT ON;
    
    BEGIN TRY
        EXEC ValideazaBorderouMarcare @id_borderou, @pret_marcare;
        
        -- insert 
        INSERT INTO BorderouMarcare (id_borderou, pret_marcare)
        VALUES (@id_borderou, @pret_marcare);
        
        -- select
        SELECT * FROM BorderouMarcare
        WHERE id_borderou = @id_borderou;

        -- Update
        UPDATE BorderouMarcare
        SET pret_marcare = @pret_nou
        WHERE id_borderou = @id_borderou;

        -- select
        SELECT * FROM BorderouMarcare
        WHERE id_borderou = @id_borderou;

        -- Delete
        DELETE FROM BorderouMarcare
        WHERE id_borderou = @id_borderou;

        -- select
        SELECT * FROM BorderouMarcare
        ORDER BY id_borderou;

        PRINT 'Operatiile CRUD s-au efectuat cu succes';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare: ' + ERROR_MESSAGE();
    END CATCH;
END;*/

EXEC CRUD_BorderouMarcare 'B1',4,5; --merge
EXEC CRUD_BorderouMarcare 'B1111',4,-5; --arunca exceptie


CREATE OR ALTER PROCEDURE AdaugaBorderouMarcare(
    @id_borderou VARCHAR(300),
    @pret_marcare FLOAT
)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        EXEC ValideazaBorderouMarcare @id_borderou, @pret_marcare;

        INSERT INTO BorderouMarcare (id_borderou, pret_marcare)
        VALUES (@id_borderou, @pret_marcare);

        PRINT 'Borderoul a fost adaugat cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la adaugare: ' + ERROR_MESSAGE();
    END CATCH;
END;

CREATE OR ALTER PROCEDURE ActualizeazaBorderouMarcare(
    @id_borderou VARCHAR(300),
    @pret_nou FLOAT
)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        EXEC ValideazaBorderouMarcare @id_borderou, @pret_nou;

        UPDATE BorderouMarcare
        SET pret_marcare = @pret_nou
        WHERE id_borderou = @id_borderou;

        PRINT 'Borderoul a fost actualizat cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la actualizare: ' + ERROR_MESSAGE();
    END CATCH;
END;

CREATE OR ALTER PROCEDURE StergeBorderouMarcare(
    @id_borderou VARCHAR(300)
)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        DELETE FROM BorderouMarcare
        WHERE id_borderou = @id_borderou;

        PRINT 'Borderoul a fost sters cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la stergere: ' + ERROR_MESSAGE();
    END CATCH;
END;

CREATE OR ALTER PROCEDURE ListeazaBorderouriMarcare
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        SELECT * FROM BorderouMarcare
        ORDER BY id_borderou DESC;

        PRINT 'Borderourile au fost listate cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la listare: ' + ERROR_MESSAGE();
    END CATCH;
END;


EXEC AdaugaBorderouMarcare 'B121',12
EXEC ListeazaBorderouriMarcare 
EXEC ActualizeazaBorderouMarcare 'B121',13
EXEC ListeazaBorderouriMarcare
EXEC StergeBorderouMarcare 'B121'
EXEC ListeazaBorderouriMarcare


---------Bijuterie---------------------

CREATE OR ALTER FUNCTION dbo.ValideazaCodBijuterie(
    @cod_bij VARCHAR(300)
)
RETURNS INT
AS
BEGIN
    IF @cod_bij IS NULL OR LTRIM(RTRIM(@cod_bij)) = ''
        RETURN 1;
    RETURN 0;
END;


CREATE OR ALTER FUNCTION dbo.ValideazaPret(
    @pret INT
)
RETURNS INT
AS
BEGIN
    IF @pret IS NULL OR @pret <= 0
        RETURN 1;
    RETURN 0;
END;

CREATE OR ALTER FUNCTION dbo.ValideazaGramaj(
    @gramaj_bij FLOAT
)
RETURNS INT
AS
BEGIN
    IF @gramaj_bij IS NULL OR @gramaj_bij <= 0
        RETURN 1;
    RETURN 0;
END;


CREATE OR ALTER FUNCTION dbo.ValideazaDescriere(
    @descriere VARCHAR(300)
)
RETURNS INT
AS
BEGIN
    IF @descriere IS NULL OR LTRIM(RTRIM(@descriere)) = ''
        RETURN 1;
    RETURN 0;
END;


CREATE OR ALTER FUNCTION dbo.ValideazaIdBorderou(
    @id_borderou VARCHAR(300)
)
RETURNS INT
AS
BEGIN
    IF NOT EXISTS (SELECT 1 FROM BorderouMarcare WHERE id_borderou = @id_borderou)
        RETURN 1;
    RETURN 0;
END;

CREATE OR ALTER PROCEDURE ValideazaBijuterie(
    @cod_bij VARCHAR(300),
    @pret_bij INT,
    @pret_nou INT,
    @descriere VARCHAR(300),
    @gramaj_bij FLOAT,
    @id_borderou VARCHAR(300)
)
AS
BEGIN
    DECLARE @error_msg NVARCHAR(MAX) = '';
    IF dbo.ValideazaCodBijuterie(@cod_bij) = 1
    BEGIN
        SET @error_msg += 'Codul bijuteriei nu poate fi gol. ';
    END;
    IF dbo.ValideazaPret(@pret_bij) = 1
    BEGIN
        SET @error_msg += 'Pretul bijuteriei trebuie sa fie un numar pozitiv. ';
    END;
    IF dbo.ValideazaPret(@pret_nou) = 1
    BEGIN
        SET @error_msg += 'Pretul nou al bijuteriei trebuie sa fie un numar pozitiv. ';
    END;
    IF dbo.ValideazaGramaj(@gramaj_bij) = 1
    BEGIN
        SET @error_msg += 'Gramajul bijuteriei trebuie sa fie un numar pozitiv. ';
    END;
    IF dbo.ValideazaDescriere(@descriere) = 1
    BEGIN
        SET @error_msg += 'Descrierea bijuteriei nu poate fi goala. ';
    END;
    IF dbo.ValideazaIdBorderou(@id_borderou) = 1
    BEGIN
        SET @error_msg += 'id_borderou nu exista in tabela Borderou. ';
    END;
    IF LEN(@error_msg) > 0
    BEGIN
        RAISERROR (@error_msg, 16, 1);
        RETURN;
    END;

    PRINT 'Bijuteria a fost validata cu succes.';
END;


EXEC ValideazaBijuterie 'Br900',1233,6,'a',12.2,'B1' --ok
EXEC ValideazaBijuterie '',-182,2.2,'',91,'B78e373'  --not ok

CREATE OR ALTER PROCEDURE CRUD_Bijuterie(
    @cod_bij VARCHAR(300),
    @pret_bij INT,
    @descriere_bij VARCHAR(300),
    @gramaj_bij FLOAT,
    @id_borderou VARCHAR(300),
    @pret_nou INT
)
AS
BEGIN
    SET NOCOUNT ON;
    BEGIN TRY
        EXEC ValideazaBijuterie @cod_bij, @pret_bij,@pret_nou,@descriere_bij, @gramaj_bij, @id_borderou;
        -- Inserare
        INSERT INTO Bijuterie (id_bij, pret_bij, descriere_bij, gramaj_bij, id_borderou)
        VALUES (@cod_bij, @pret_bij, @descriere_bij, @gramaj_bij, @id_borderou);
        -- Select
        SELECT * FROM Bijuterie WHERE id_bij = @cod_bij;
        -- Update
        UPDATE Bijuterie
        SET pret_bij = @pret_nou
        WHERE id_bij = @cod_bij;
        -- Select
        SELECT * FROM Bijuterie WHERE id_bij = @cod_bij;
        -- Delete
        DELETE FROM Bijuterie WHERE id_bij = @cod_bij;
        -- Select
        SELECT * FROM Bijuterie;

        PRINT 'Operatiile CRUD s-au efectuat cu succes';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare: ' + ERROR_MESSAGE();
    END CATCH;
END;
EXEC CRUD_Bijuterie 'Br122',123,'',43.3,'B111',1230
EXEC CRUD_Bijuterie 'Br122',123,'aaa',43.3,'B1',1230

-----------Angajat--------------

CREATE OR ALTER FUNCTION dbo.ValideazaNumeAngajat(
    @nume VARCHAR(300)
)
RETURNS INT
AS
BEGIN
    IF @nume IS NULL OR LTRIM(RTRIM(@nume)) = ''
        RETURN 1;  
    RETURN 0; 
END;

CREATE OR ALTER FUNCTION dbo.ValideazaPostAngajat(
    @post VARCHAR(300)
)
RETURNS INT
AS
BEGIN
    IF @post IS NULL OR LTRIM(RTRIM(@post)) = ''
        RETURN 1;  
    RETURN 0;  
END;
CREATE OR ALTER FUNCTION dbo.ValideazaCodMagazin(
    @cod_magazin INT
)
RETURNS INT
AS
BEGIN
    IF NOT EXISTS (SELECT 1 FROM Magazin WHERE id_magazin = @cod_magazin)
        RETURN 1; 
    RETURN 0;  
END;


CREATE OR ALTER PROCEDURE ValideazaAngajat(
    @nume VARCHAR(300),
    @post VARCHAR(300),
    @cod_magazin INT,
    @post_nou VARCHAR(300)
)
AS
BEGIN
    DECLARE @error_msg NVARCHAR(MAX) = '';
    IF dbo.ValideazaNumeAngajat(@nume) = 1
    BEGIN
        SET @error_msg += 'Numele angajatului nu poate fi gol. ';
    END;
    IF dbo.ValideazaPostAngajat(@post) = 1
    BEGIN
        SET @error_msg += 'Postul angajatului nu poate fi gol. ';
    END;
    IF dbo.ValideazaPostAngajat(@post_nou) = 1
    BEGIN
        SET @error_msg += 'Postul nou al angajatului nu poate fi gol. ';
    END;
    IF dbo.ValideazaCodMagazin(@cod_magazin) = 1
    BEGIN
        SET @error_msg += 'Codul magazinului nu exista in tabela Magazin. ';
    END;
    IF LEN(@error_msg) > 0
    BEGIN
        RAISERROR (@error_msg, 16, 1);
        RETURN;
    END;

    PRINT 'Angajatul a fost validat cu succes.';
END;

EXEC ValideazaAngajat 'Anca','angajata',5,'director' --ok
EXEC ValideazaAngajat '','angajat1',15,'' --not ok
select*  from Magazin;

CREATE OR ALTER PROCEDURE CRUD_Angajat(
    @nume VARCHAR(300),
    @post VARCHAR(300),
    @cod_magazin INT,
    @post_nou VARCHAR(300)
)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        EXEC ValideazaAngajat  @nume, @post, @cod_magazin,@post_nou;
        -- Inserare
        INSERT INTO Angajati ( nume, post,id_magazin)
        VALUES (@nume, @post, @cod_magazin);
        -- Select
        SELECT * FROM Angajati
		ORDER BY id_angajat DESC;
        -- update
        UPDATE Angajati
        SET post = @post_nou
        WHERE nume= @nume;
        -- Select
        SELECT * FROM Angajati WHERE nume = @nume
		ORDER BY id_angajat DESC;
        -- delete
        DELETE FROM Angajati WHERE nume = @nume;
        -- Select 
        SELECT * FROM Angajati ORDER BY id_angajat DESC;
        PRINT 'Operatiile CRUD s-au efectuat cu succes';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare: ' + ERROR_MESSAGE();
    END CATCH;
END;

EXEC CRUD_Angajat 'Anca','vanzator',5,'director';

-----MAGAZIN
CREATE OR ALTER FUNCTION dbo.ValideazaNumeMagazin(
    @nume VARCHAR(300)
)
RETURNS INT
AS
BEGIN
    IF @nume IS NULL OR LTRIM(RTRIM(@nume)) = ''
        RETURN 1; 
    RETURN 0; 
END;


CREATE OR ALTER PROCEDURE ValideazaMagazin(
    @nume VARCHAR(300),
    @locatie VARCHAR(300),
    @oras VARCHAR(300),
    @nr_tel VARCHAR(300),
    @nr_tel_nou VARCHAR(300)
)
AS
BEGIN
    DECLARE @error_msg NVARCHAR(MAX) = '';
    IF dbo.ValideazaNumeMagazin(@nume) = 1
    BEGIN
        SET @error_msg += 'Numele magazinului nu poate fi gol. ';
    END;
    IF dbo.ValideazaNumeMagazin(@locatie) = 1
    BEGIN
        SET @error_msg += 'Locatia magazinului nu poate fi goala. ';
    END;
    IF dbo.ValideazaNumeMagazin(@oras) = 1
    BEGIN
        SET @error_msg += 'Orasul magazinului nu poate fi gol. ';
    END;
    IF dbo.ValideazaNumeMagazin(@nr_tel) = 1
    BEGIN
        SET @error_msg += 'Numarul de telefon al magazinului nu poate fi gol. ';
    END;
    IF dbo.ValideazaNumeMagazin(@nr_tel_nou) = 1
    BEGIN
        SET @error_msg += 'Numarul de telefon nou al magazinului nu poate fi gol. ';
    END;
    IF LEN(@error_msg) > 0
    BEGIN
        RAISERROR (@error_msg, 16, 1);
        RETURN;
    END;

    PRINT 'Magazinul a fost validat cu succes.';
END;
 EXEC ValideazaMagazin 'Artemis','Sora','CLuj','029293293','09999999'
  EXEC ValideazaMagazin 'Artemis','','','029293293',''

CREATE OR ALTER PROCEDURE CRUD_Magazin(
    @nume VARCHAR(300),
    @locatie VARCHAR(300),
	@oras VARCHAR(300),
    @nr_tel VARCHAR(300),
    @nr_tel_nou VARCHAR(300)
)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        EXEC ValideazaMagazin  @nume, @locatie,@oras, @nr_tel,@nr_tel_nou;
        -- Inserare 
        INSERT INTO Magazin ( nume, locatie,oras, nr_tel)
        VALUES ( @nume, @locatie,@oras,@nr_tel);
        -- Select
        SELECT * FROM Magazin ORDER BY id_magazin DESC;
        --Update
        UPDATE Magazin
        SET nr_tel = @nr_tel_nou
        WHERE locatie = @locatie and oras=@oras;
		--select
        SELECT * FROM Magazin  ORDER BY id_magazin DESC;
        --delete
        DELETE FROM Magazin WHERE locatie = @locatie;
        -- Select
        SELECT * FROM Magazin ORDER BY id_magazin DESC;

        PRINT 'Operatiile CRUD s-au efectuat cu succes';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare: ' + ERROR_MESSAGE();
    END CATCH;
END;
EXEC CRUD_Magazin 'Artemis2','Carbochim','cluj','0721208889','07777777777';

----------StocBijuterieMagazin

CREATE OR ALTER FUNCTION dbo.ValideazaCombinatieStocBijuterieMagazin(
    @id_bij VARCHAR(300),
    @id_magazin INT
)
RETURNS INT
AS
BEGIN
    IF EXISTS (SELECT 1 FROM StocBijuterieMagazin WHERE id_bij = @id_bij AND id_magazin = @id_magazin)
        RETURN 1;  
    
    RETURN 0; 
END;

CREATE OR ALTER FUNCTION dbo.ValideazaCantitate(
    @cantitate INT
)
RETURNS INT
AS
BEGIN
    IF @cantitate <= 0
        RETURN 1; 
    RETURN 0;
END;

CREATE OR ALTER FUNCTION dbo.ValideazaCodMagazin(
    @id_magazin INT
)
RETURNS INT
AS
BEGIN
    IF @id_magazin IS NULL OR @id_magazin <= 0 OR NOT EXISTS (SELECT 1 FROM Magazin WHERE id_magazin = @id_magazin)
        RETURN 1; 
    RETURN 0; 
END;

CREATE OR ALTER FUNCTION dbo.ValideazaCodBijuterie1(
    @id_bij VARCHAR(300)
)
RETURNS INT
AS
BEGIN
    IF @id_bij IS NULL OR LTRIM(RTRIM(@id_bij)) = '' OR NOT EXISTS (SELECT 1 FROM Bijuterie WHERE id_bij = @id_bij)
        RETURN 1; 
    RETURN 0; 
END;

CREATE OR ALTER PROCEDURE ValideazaStocBijuterieMagazin(
    @id_bij VARCHAR(300),
    @id_magazin INT,
    @cantitate INT,
    @cantitate_nou INT
)
AS
BEGIN
    DECLARE @error_msg NVARCHAR(MAX) = '';
    IF dbo.ValideazaCodBijuterie1(@id_bij) = 1
    BEGIN
        SET @error_msg += 'Codul bijuteriei nu poate fi gol sau nu exista in tabela Bijuterie . ';
    END;
    IF dbo.ValideazaCodMagazin(@id_magazin) = 1
    BEGIN
        SET @error_msg += 'Codul magazinului nu poate fi gol sau invalid sau codul nu exita in tabela Magazin. ';
    END;
    IF dbo.ValideazaCombinatieStocBijuterieMagazin(@id_bij, @id_magazin) = 1
    BEGIN
        SET @error_msg += 'Combinatia cod_bij si cod_magazin exista deja în tabela StocBijuterieMagazin. ';
    END;
    IF dbo.ValideazaCantitate(@cantitate) = 1
    BEGIN
        SET @error_msg += 'Numarul de bucati trebuie sa fie mai mare decat 0. ';
    END;
    IF dbo.ValideazaCantitate(@cantitate_nou) = 1
    BEGIN
        SET @error_msg += 'Numarul de bucati nou trebuie sa fie mai mare decat 0. ';
    END;
    IF LEN(@error_msg) > 0
    BEGIN
        RAISERROR (@error_msg, 16, 1);
        RETURN;
    END;

    PRINT 'Stocul bijuteriei a fost validat cu succes.';
END;
EXEC ValideazaStocBijuterieMagazin 'Br999',1,233,23
EXEC ValideazaStocBijuterieMagazin 'Br30_006',1,2,2;


CREATE OR ALTER PROCEDURE CRUD_StocBijuterieMagazin(
    @id_bij VARCHAR(300),
    @id_magazin INT,
    @cantitate INT,
    @cantitate_nou INT
)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        -- Validarea stocului bijuteriei în magazin
        EXEC ValideazaStocBijuterieMagazin @id_bij, @id_magazin, @cantitate,@cantitate_nou;
        -- Inserare
        INSERT INTO StocBijuterieMagazin (id_bij, id_magazin, cantitate)
        VALUES (@id_bij, @id_magazin, @cantitate);
        -- Select
        SELECT * FROM StocBijuterieMagazin WHERE id_bij = @id_bij AND id_magazin = @id_magazin;
        -- update
        UPDATE StocBijuterieMagazin
        SET cantitate = @cantitate_nou
        WHERE id_bij = @id_bij AND id_magazin = @id_magazin;
        -- Select
        SELECT * FROM StocBijuterieMagazin WHERE id_bij = @id_bij AND id_magazin = @id_magazin;
        -- delete
        DELETE FROM StocBijuterieMagazin
        WHERE id_bij = @id_bij AND id_magazin = @id_magazin;
        -- Select
        SELECT * FROM StocBijuterieMagazin;

        PRINT 'Operatiile CRUD s-au efectuat cu succes';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare: ' + ERROR_MESSAGE();
    END CATCH;
END;
EXEC CRUD_StocBijuterieMagazin 'Br20',2,12,2;

select*from Bijuterie;
select* from StocBijuterieMagazin;
INSERT INTO Bijuterie (id_bij,pret_bij,descriere_bij,gramaj_bij,id_borderou)
VALUES ('Br20',156,'bratara pietre semi',3.9,'B2');
EXEC CRUD_StocBijuterieMagazin 'Br30_006',2,3,4;

--------------------VIEW--------------------------
CREATE or alter VIEW V_BijuteriiBorderou
AS
SELECT 
    B.descriere_bij AS Descriere,
    B.pret_bij AS Pret,
    B.gramaj_bij AS Gramaj
FROM Bijuterie B

select * from V_BijuteriiBorderou;


create nonclustered index IX_Bijuterie ON Bijuterie(descriere_bij asc,pret_bij asc,gramaj_bij asc);

------------------------------------------------------------------
/*CREATE VIEW V_StocBijuteriiMagazin
AS
SELECT 
    S.id_bij AS CodBijuterie,
    B.descriere_bij AS Descriere,
    B.pret_bij AS Pret,
    M.nume AS NumeMagazin,
    M.locatie AS Locatie,
    S.cantitate AS Cantitate
FROM StocBijuterieMagazin S
INNER JOIN Bijuterie B ON S.id_bij = B.id_bij
INNER JOIN Magazin M ON S.id_magazin = M.id_magazin;*/
Drop View V_StocBijuteriiMagazin

/*CREATE or ALTER VIEW V_BijuteriiStocValoare AS
SELECT 
    M.nume AS Magazin,                     
    M.locatie AS Locatie,                
    B.id_bij AS CodBijuterie,          
    B.descriere_bij AS Descriere,      
    S.cantitate AS Cantitate,           
    (S.cantitate * B.pret_bij) AS TotalPret 
FROM StocBijuterieMagazin S 
INNER JOIN 
    Bijuterie B ON S.id_bij = B.id_bij  
INNER JOIN 
    Magazin M ON S.id_magazin = M.id_magazin
 WHERE S.cantitate>=2 */
 DROP VIEW V_BijuteriiBorderou

------------------------------------------------------
CREATE OR ALTER VIEW V_MagazinStocBijuterie AS
SELECT 
	M.nume as Magazin,
	M.locatie as Locatie,
	B.descriere_bij as Descriere,
	B.gramaj_bij*S.cantitate AS TotalGramaj,
	B.pret_bij*S.cantitate as TotalPret
FROM StocBijuterieMagazin S
Inner Join Bijuterie B ON B.id_bij=S.id_bij
Inner join Magazin M on s.id_magazin=m.id_magazin;

select* from V_MagazinStocBijuterie

CREATE NONCLUSTERED INDEX IX_Magazin_nume_locatie ON Magazin(id_magazin,nume,locatie asc);

---------------------------------------------------------------

select* from Bijuterie order by Bijuterie.id_borderou;
select * from BorderouMarcare order by BorderouMarcare.pret_marcare;

/*

IF EXISTS (SELECT NAME FROM sys.indexes WHERE name='IX_Bijuterie_id_bij')
DROP INDEX IX_Bijuterie_id_bij ON Bijuterie
CREATE NONCLUSTERED INDEX IX_Bijuterie_id_bij ON Bijuterie (id_bij asc);


IF EXISTS (SELECT NAME FROM sys.indexes WHERE name='IX_Bijuterie_id_borderou')
DROP INDEX IX_Bijuterie_id_borderou ON Bijuterie
CREATE NONCLUSTERED INDEX IX_Bijuterie_id_borderou ON Bijuterie (id_borderou asc);
*/
/*
DROP INDEX IX_StocBijuterieMagazin_id_bij ON StocBijuterieMagazin;
CREATE NONCLUSTERED INDEX IX_StocBijuterieMagazin_id_bij ON StocBijuterieMagazin (id_bij);
*/
/*
CREATE NONCLUSTERED INDEX IX_StocBijuterieMagazin_id_magazin ON StocBijuterieMagazin (id_magazin);


IF EXISTS (SELECT NAME FROM sys.indexes WHERE name='IX_StocBijuterieMagazin_cantitate')
DROP INDEX IX_StocBijuterieMagazin_cantitate ON StocBijuterieMagazin
CREATE NONCLUSTERED INDEX IX_StocBijuterieMagazin_cantitate ON StocBijuterieMagazin (cantitate asc);

CREATE NONCLUSTERED INDEX IX_Magazin_id_magazin ON Magazin (id_magazin);
*/

