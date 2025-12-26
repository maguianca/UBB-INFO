USE MagazinDeBijuterii
GO

---------------------BORDEROUMarcare
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
    IF @pret IS NULL OR @pret<0
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
        SET @error_msg += 'Pretul de marcare trebuie să fie un numar pozitiv. ';
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
        IF dbo.ValideazaIdBorderou(@id_borderou) = 1
        BEGIN
            PRINT 'ID-ul borderoului nu poate fi gol sau NULL.';
            RETURN;
        END;
        IF dbo.ValideazaPret(@pret_nou) = 1
        BEGIN
            PRINT 'Pretul trebuie să fie un numar pozitiv.';
            RETURN;
        END;
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


EXEC AdaugaBorderouMarcare 'B12',12
EXEC ListeazaBorderouriMarcare 
EXEC ActualizeazaBorderouMarcare 'B12',13
EXEC ListeazaBorderouriMarcare
EXEC StergeBorderouMarcare 'B12'
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


CREATE OR ALTER PROCEDURE AdaugaBijuterie(
    @cod_bij VARCHAR(300),
    @pret_bij INT,
    @descriere_bij VARCHAR(300),
    @gramaj_bij FLOAT,
    @id_borderou VARCHAR(300)
)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        IF dbo.ValideazaCodBijuterie(@cod_bij) = 1
        BEGIN
            PRINT 'Codul bijuteriei nu poate fi gol sau NULL.';
            RETURN;
        END;

        IF dbo.ValideazaPret(@pret_bij) = 1
        BEGIN
            PRINT 'Pretul bijuteriei trebuie sa fie un numar pozitiv.';
            RETURN;
        END;

        IF dbo.ValideazaGramaj(@gramaj_bij) = 1
        BEGIN
            PRINT 'Gramajul bijuteriei trebuie să fie un numar pozitiv.';
            RETURN;
        END;

        IF dbo.ValideazaDescriere(@descriere_bij) = 1
        BEGIN
            PRINT 'Descrierea bijuteriei nu poate fi goala sau NULL.';
            RETURN;
        END;

        IF dbo.ValideazaIdBorderou(@id_borderou) = 1
        BEGIN
            PRINT 'ID-ul borderoului nu exista in baza de date.';
            RETURN;
        END;
        INSERT INTO Bijuterie (id_bij, pret_bij, descriere_bij, gramaj_bij, id_borderou)
        VALUES (@cod_bij, @pret_bij, @descriere_bij, @gramaj_bij, @id_borderou);

        PRINT 'Bijuteria a fost adaugata cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la adaugare: ' + ERROR_MESSAGE();
    END CATCH;
END;

CREATE OR ALTER PROCEDURE ActualizeazaBijuterie(
    @cod_bij VARCHAR(300),
    @pret_nou INT
)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        IF dbo.ValideazaPret(@pret_nou) = 1
        BEGIN
            PRINT 'Pretul trebuie sa fie un numar pozitiv.';
            RETURN;
        END;
        UPDATE Bijuterie
        SET pret_bij = @pret_nou
        WHERE id_bij = @cod_bij;

        PRINT 'Pretul bijuteriei a fost actualizat cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la actualizare: ' + ERROR_MESSAGE();
    END CATCH;
END;

CREATE OR ALTER PROCEDURE StergeBijuterie(
    @cod_bij VARCHAR(300)
)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        DELETE FROM Bijuterie
        WHERE id_bij = @cod_bij;

        PRINT 'Bijuteria a fost stearsă cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la stergere: ' + ERROR_MESSAGE();
    END CATCH;
END;

CREATE OR ALTER PROCEDURE ListeazaBijuterii
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        SELECT * FROM Bijuterie
        ORDER BY id_bij;

        PRINT 'Bijuteriile au fost listate cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la listare: ' + ERROR_MESSAGE();
    END CATCH;
END;

EXEC AdaugaBijuterie 'Br90',12,'jhdjd',12,'B1';
EXEC ListeazaBijuterii
EXEC ActualizeazaBijuterie 'Br90',122;
EXEC ListeazaBijuterii
EXEC StergeBijuterie 'Br90'
EXEC ListeazaBijuterii


--------Angajat---
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


CREATE OR ALTER PROCEDURE AdaugaAngajat(
    @nume VARCHAR(300),
    @post VARCHAR(300),
    @cod_magazin INT
)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        IF dbo.ValideazaNumeAngajat(@nume) = 1
        BEGIN
            PRINT 'Numele angajatului nu poate fi gol sau NULL.';
            RETURN;
        END;

        IF dbo.ValideazaPostAngajat(@post) = 1
        BEGIN
            PRINT 'Postul angajatului nu poate fi gol sau NULL.';
            RETURN;
        END;

        IF dbo.ValideazaCodMagazin(@cod_magazin) = 1
        BEGIN
            PRINT 'Codul magazinului nu exista în baza de date.';
            RETURN;
        END;
        INSERT INTO Angajati (nume, post, id_magazin)
        VALUES (@nume, @post, @cod_magazin);

        PRINT 'Angajatul a fost adaugat cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la adăugare: ' + ERROR_MESSAGE();
    END CATCH;
END;

CREATE OR ALTER PROCEDURE ActualizeazaPostAngajat(
    @nume VARCHAR(300),
    @post_nou VARCHAR(300)
)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        IF dbo.ValideazaPostAngajat(@post_nou) = 1
        BEGIN
            PRINT 'Postul angajatului nu poate fi gol sau NULL.';
            RETURN;
        END;
        UPDATE Angajati
        SET post = @post_nou
        WHERE nume = @nume;

        PRINT 'Postul angajatului a fost actualizat cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la actualizare: ' + ERROR_MESSAGE();
    END CATCH;
END;

CREATE OR ALTER PROCEDURE StergeAngajat(
    @nume VARCHAR(300)
)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        DELETE FROM Angajati
        WHERE nume = @nume;

        PRINT 'Angajatul a fost stearsă cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la stergere: ' + ERROR_MESSAGE();
    END CATCH;
END;

CREATE OR ALTER PROCEDURE ListeazaAngajati
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        SELECT * FROM Angajati
        ORDER BY id_angajat DESC;

        PRINT 'Angajatii au fost listati cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la listare: ' + ERROR_MESSAGE();
    END CATCH;
END;

EXEC AdaugaAngajat 'Anca','vanzator',1
EXEC ListeazaAngajati
EXEC ActualizeazaPostAngajat 'Anca','director';
EXEC ListeazaAngajati
EXEC StergeAngajat 'Anca'
EXEC ListeazaAngajati


--------------MAGAZIN-----
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

CREATE OR ALTER PROCEDURE AdaugaMagazin(
    @nume VARCHAR(300),
    @locatie VARCHAR(300),
    @oras VARCHAR(300),
    @nr_tel VARCHAR(300)
)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        IF dbo.ValideazaNumeMagazin(@nume) = 1
        BEGIN
            PRINT 'Numele magazinului nu poate fi gol sau NULL.';
            RETURN;
        END;

        IF dbo.ValideazaNumeMagazin(@locatie) = 1
        BEGIN
            PRINT 'Locatia magazinului nu poate fi goala sau NULL.';
            RETURN;
        END;

        IF dbo.ValideazaNumeMagazin(@oras) = 1
        BEGIN
            PRINT 'Orasul magazinului nu poate fi gol sau NULL.';
            RETURN;
        END;

        IF dbo.ValideazaNumeMagazin(@nr_tel) = 1
        BEGIN
            PRINT 'Numarul de telefon al magazinului nu poate fi gol sau invalid.';
            RETURN;
        END;
        INSERT INTO Magazin (nume, locatie, oras, nr_tel)
        VALUES (@nume, @locatie, @oras, @nr_tel);

        PRINT 'Magazinul a fost adaugat cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la adaugare: ' + ERROR_MESSAGE();
    END CATCH;
END;

CREATE OR ALTER PROCEDURE ActualizeazaNrTelMagazin(
    @locatie VARCHAR(300),
    @oras VARCHAR(300),
    @nr_tel_nou VARCHAR(300)
)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        IF dbo.ValideazaNumeMagazin(@nr_tel_nou) = 1
        BEGIN
            PRINT 'Numarul de telefon al magazinului nu poate fi gol sau invalid.';
            RETURN;
        END;
        UPDATE Magazin
        SET nr_tel = @nr_tel_nou
        WHERE locatie = @locatie AND oras = @oras;

        PRINT 'Numarul de telefon al magazinului a fost actualizat cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la actualizare: ' + ERROR_MESSAGE();
    END CATCH;
END;

CREATE OR ALTER PROCEDURE StergeMagazin(
    @locatie VARCHAR(300)
)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        DELETE FROM Magazin
        WHERE locatie = @locatie;

        PRINT 'Magazinul a fost sters cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la stergere: ' + ERROR_MESSAGE();
    END CATCH;
END;

CREATE OR ALTER PROCEDURE ListeazaMagazin
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        SELECT * FROM Magazin
        ORDER BY id_magazin DESC;

        PRINT 'Magazinele au fost listate cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la listare: ' + ERROR_MESSAGE();
    END CATCH;
END;

EXEC AdaugaMagazin 'Artemis','Sora','CLuj','029293293';
EXEC ListeazaMagazin
EXEC ActualizeazaNrTelMagazin 'Sora','CLuj','0999999999'
EXEC ListeazaMagazin
EXEC StergeMagazin 'Sora'
EXEC ListeazaMagazin


------------------StocBijuterieMagazin
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


CREATE OR ALTER PROCEDURE AdaugaStocBijuterieMagazin(
    @id_bij VARCHAR(300),
    @id_magazin INT,
    @cantitate INT
)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        IF dbo.ValideazaCodBijuterie1(@id_bij) = 1
        BEGIN
            PRINT 'Codul bijuteriei este invalid sau nu exista.';
            RETURN;
        END;

        IF dbo.ValideazaCodMagazin(@id_magazin) = 1
        BEGIN
            PRINT 'Codul magazinului este invalid sau nu exista.';
            RETURN;
        END;

        IF dbo.ValideazaCombinatieStocBijuterieMagazin(@id_bij, @id_magazin) = 1
        BEGIN
            PRINT 'Combinatia cod_bij si cod_magazin exista deja.';
            RETURN;
        END;

        IF dbo.ValideazaCantitate(@cantitate) = 1
        BEGIN
            PRINT 'Cantitatea trebuie sa fie mai mare decat 0.';
            RETURN;
        END;
        INSERT INTO StocBijuterieMagazin (id_bij, id_magazin, cantitate)
        VALUES (@id_bij, @id_magazin, @cantitate);

        PRINT 'Stocul bijuteriei a fost adaugat cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la adaugare: ' + ERROR_MESSAGE();
    END CATCH;
END;

CREATE OR ALTER PROCEDURE ActualizeazaStocBijuterieMagazin(
    @id_bij VARCHAR(300),
    @id_magazin INT,
    @cantitate_nou INT
)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        IF dbo.ValideazaCodBijuterie1(@id_bij) = 1
        BEGIN
            PRINT 'Codul bijuteriei este invalid sau nu exista.';
            RETURN;
        END;

        IF dbo.ValideazaCodMagazin(@id_magazin) = 1
        BEGIN
            PRINT 'Codul magazinului este invalid sau nu exista.';
            RETURN;
        END;

        IF dbo.ValideazaCantitate(@cantitate_nou) = 1
        BEGIN
            PRINT 'Cantitatea noua trebuie sa fie mai mare decat 0.';
            RETURN;
        END;
        UPDATE StocBijuterieMagazin
        SET cantitate = @cantitate_nou
        WHERE id_bij = @id_bij AND id_magazin = @id_magazin;

        PRINT 'Stocul bijuteriei a fost actualizat cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la actualizare: ' + ERROR_MESSAGE();
    END CATCH;
END;

CREATE OR ALTER PROCEDURE StergeStocBijuterieMagazin(
    @id_bij VARCHAR(300),
    @id_magazin INT
)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        IF dbo.ValideazaCodBijuterie1(@id_bij) = 1
        BEGIN
            PRINT 'Codul bijuteriei este invalid sau nu exista.';
            RETURN;
        END;

        IF dbo.ValideazaCodMagazin(@id_magazin) = 1
        BEGIN
            PRINT 'Codul magazinului este invalid sau nu exista.';
            RETURN;
        END;
        DELETE FROM StocBijuterieMagazin
        WHERE id_bij = @id_bij AND id_magazin = @id_magazin;

        PRINT 'Stocul bijuteriei a fost sters cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la stergere: ' + ERROR_MESSAGE();
    END CATCH;
END;

CREATE OR ALTER PROCEDURE ListeazaStocBijuterieMagazin
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        SELECT * FROM StocBijuterieMagazin
        ORDER BY id_bij DESC, id_magazin DESC;

        PRINT 'Stocurile bijuteriilor au fost listate cu succes.';
    END TRY
    BEGIN CATCH
        PRINT 'A aparut o eroare la listare: ' + ERROR_MESSAGE();
    END CATCH;
END;


EXEC AdaugaStocBijuterieMagazin 'Br20',2,12;
EXEC ListeazaStocBijuterieMagazin;
EXEC ActualizeazaStocBijuterieMagazin 'Br20',2,20;
EXEC ListeazaStocBijuterieMagazin;
EXEC StergeStocBijuterieMagazin 'Br20',2;
EXEC ListeazaStocBijuterieMagazin;


CREATE or alter VIEW V_BijuteriiBorderou
AS
SELECT 
    B.descriere_bij AS Descriere,
    B.pret_bij AS Pret,
    B.gramaj_bij AS Gramaj
FROM Bijuterie B

select * from V_BijuteriiBorderou;


create nonclustered index IX_Bijuterie ON Bijuterie(descriere_bij asc,pret_bij asc,gramaj_bij asc);


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