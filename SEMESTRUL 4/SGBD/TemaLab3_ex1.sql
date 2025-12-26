USE JewelryShop
GO

CREATE TABLE LogActiuni(
id INT IDENTITY PRIMARY KEY,
tip_operatie VARCHAR(100),
nume_tabel VARCHAR(100),
data DATETIME)
GO

----ADAUGARE TABELE Bijuterie, Categorie si BijuterieCategorie----------------

--validare pret----
GO
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
GO
---validare gramaj-----
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
GO
---validare descriere--------
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
GO
-----validare BIJUTERIE----------
CREATE OR ALTER PROCEDURE ValideazaBijuterie(
    @pret_bij INT,
    @descriere VARCHAR(300),
    @gramaj_bij FLOAT
)
AS
BEGIN
    DECLARE @error_msg NVARCHAR(MAX) = '';
    IF dbo.ValideazaPret(@pret_bij) = 1
    BEGIN
        SET @error_msg += 'Pretul bijuteriei trebuie sa fie un numar pozitiv. ';
    END;
    IF dbo.ValideazaGramaj(@gramaj_bij) = 1
    BEGIN
        SET @error_msg += 'Gramajul bijuteriei trebuie sa fie un numar pozitiv. ';
    END;
    IF dbo.ValideazaDescriere(@descriere) = 1
    BEGIN
        SET @error_msg += 'Descrierea bijuteriei nu poate fi goala. ';
    END;
    IF LEN(@error_msg) > 0
    BEGIN
        RAISERROR (@error_msg, 16, 1);
        RETURN;
    END;

    PRINT 'Bijuteria a fost validata cu succes.';
END;
GO
----creare procedura -----------

CREATE PROCEDURE dbo.AdaugaBijuterieCategorie
	@pret_bij FLOAT,
	@descriere_bij VARCHAR(300),
	@gramaj_bij FLOAT,
	@descriere_cat VARCHAR(300)
AS
BEGIN
	BEGIN TRAN
	BEGIN TRY
		---validare bijuterie---
		EXEC ValideazaBijuterie @pret_bij,@descriere_bij,@gramaj_bij
		---validare descriere categorie
		IF dbo.ValideazaDescriere(@descriere_cat) = 1
			RAISERROR('Descrierea categoriei nu poate fi goala',14,1)

		DECLARE @id_bij_nou INT;
		DECLARE @id_categorie_nou INT;

		INSERT INTO Bijuterie(pret_bij,descriere_bij,gramaj_bij)
		VALUES (@pret_bij,@descriere_bij,@gramaj_bij)
		SET @id_bij_nou=SCOPE_IDENTITY();

		INSERT INTO Categorie(descriere)
		VALUES(@descriere_cat)
		SET @id_categorie_nou=SCOPE_IDENTITY();

		INSERT INTO BijuterieCategorie(id_bij,id_categorie)
		VALUES(@id_bij_nou,@id_categorie_nou)

		COMMIT TRAN;

		INSERT INTO LogActiuni(tip_operatie,nume_tabel,data)
		VALUES('INSERT','Bijuterie-Categorie-BijuterieCategorie',GETDATE())

		SELECT 'Transaction commited' AS Result;
	END TRY
	BEGIN CATCH 
		ROLLBACK TRAN;

		INSERT INTO LogActiuni(tip_operatie,nume_tabel,data)
		VALUES('ROLLBACK','Bijuterie-Categorie-BijuterieCategorie',GETDATE())

		SELECT 'Transaction rollbacked' AS Result;

		SELECT ERROR_MESSAGE() AS ErrorMessage;
	END CATCH
END 
GO

------TESTE------

---insert ok----
select * from Bijuterie
select * from Categorie
select * from BijuterieCategorie
exec AdaugaBijuterieCategorie 6442,'inel diamant',1.23,'ametist'
select* from LogActiuni
select * from Bijuterie
select * from Categorie
select * from BijuterieCategorie

--validare esuata---
select * from Bijuterie
select * from Categorie
select * from BijuterieCategorie
exec AdaugaBijuterieCategorie 9090,'',0,''
select* from LogActiuni
select * from Bijuterie
select * from Categorie
select* from BijuterieCategorie



