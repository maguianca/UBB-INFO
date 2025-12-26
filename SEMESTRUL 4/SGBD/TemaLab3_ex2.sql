USE JewelryShop
GO

----creare procedura -----------
GO
CREATE OR ALTER PROCEDURE dbo.AdaugaBijuterieCategorie2
	@pret_bij FLOAT,
	@descriere_bij VARCHAR(300),
	@gramaj_bij FLOAT,
	@descriere_cat VARCHAR(300)
AS
BEGIN
		DECLARE @id_bij_nou INT=NULL;
		DECLARE @id_categorie_nou INT=NULL;
		----------adaugare Bijuterie---------------
		------validare bijuterie----
		BEGIN TRY
			EXEC ValideazaBijuterie @pret_bij,@descriere_bij,@gramaj_bij
		END TRY
		BEGIN CATCH
			SELECT ERROR_MESSAGE() AS ErrorMessage;
			RETURN;
		END CATCH

		BEGIN TRY
		BEGIN TRAN
			INSERT INTO Bijuterie(pret_bij,descriere_bij,gramaj_bij)
			VALUES (@pret_bij,@descriere_bij,@gramaj_bij)
			SET @id_bij_nou=SCOPE_IDENTITY();
			COMMIT TRAN;

			INSERT INTO LogActiuni(tip_operatie,nume_tabel,data)
			VALUES('INSERT','Bijuterie',GETDATE())

			SELECT 'Bijuterie inserted' AS ResultBijuterie;
		END TRY
		BEGIN CATCH
			ROLLBACK TRAN

			INSERT INTO LogActiuni(tip_operatie,nume_tabel,data)
			VALUES('ROLLBACK','Bijuterie',GETDATE())

			SELECT 'Bijuterie rollbacked' AS ResultBijuterie;
		END CATCH
		-----------adaugare Categorie---------------------
		IF dbo.ValideazaDescriere(@descriere_cat) = 1
		BEGIN 
			SELECT 'Descriere Categorie incorecta' AS ErrorMessage
			RETURN;
		END

		BEGIN TRY
		BEGIN TRAN
			INSERT INTO Categorie(descriere)
			VALUES(@descriere_cat)
			SET @id_categorie_nou=SCOPE_IDENTITY();
			COMMIT TRAN;

			INSERT INTO LogActiuni(tip_operatie,nume_tabel,data)
			VALUES('INSERT','Categorie',GETDATE())

			SELECT 'Categorie inserted' AS ResultCategorie;
		END TRY
		BEGIN CATCH
			ROLLBACK TRAN;

			INSERT INTO LogActiuni(tip_operatie,nume_tabel,data)
			VALUES('ROLLBACK','Categorie',GETDATE())

			SELECT 'Categorie rollbacked' AS ResultCategorie;
		END CATCH

		-------adaugare BijuterieCategorie-------------
		IF @id_bij_nou is not NULL and @id_categorie_nou is not NULL
		BEGIN
			BEGIN TRY
			BEGIN TRAN
				INSERT INTO BijuterieCategorie(id_bij,id_categorie)
				VALUES(@id_bij_nou,@id_categorie_nou)
				COMMIT TRAN;

				INSERT INTO LogActiuni(tip_operatie,nume_tabel,data)
				VALUES('INSERT','BijuterieCategorie',GETDATE())

				SELECT 'BijuterieCategorie inserted' AS ResultBijuterieCategorie;
			END TRY
			BEGIN CATCH
				ROLLBACK TRAN;

				INSERT INTO LogActiuni(tip_operatie,nume_tabel,data)
				VALUES('ROLLBACK','BijuterieCategorie',GETDATE())

				SELECT 'BijuterieCategorie rollbacked' AS ResultBijuterieCategorie;
			END CATCH
		END
		ELSE
		BEGIN 
			SELECT 'Nu s-a adaugat in BijuterieCatgorie deoarece nu s-a reusit toate operatiile pana acum' AS ResultBijuterieCategorie;
		END
END
GO


----ok-------
select * from Bijuterie
select * from Categorie
exec AdaugaBijuterieCategorie2 20990,'colier diamant',11.5,'pietre'
select* from LogActiuni
select * from Bijuterie
select * from Categorie

---eroare Bijuterie---nu se adauga nimic
select * from Bijuterie
select * from Categorie
exec AdaugaBijuterieCategorie2 -010,'',0,''
select* from LogActiuni
select * from Bijuterie
select * from Categorie

---eroare Categorie--se adauga bijuterie
select * from Bijuterie
select * from Categorie
exec AdaugaBijuterieCategorie2 80010,'colier',26.90,''
select* from LogActiuni
select * from Bijuterie
select * from Categorie
select * from BijuterieCategorie

go
CREATE OR ALTER PROCEDURE dbo.AdaugaBijuterieCategorie3
    @pret_bij FLOAT,
    @descriere_bij VARCHAR(300),
    @gramaj_bij FLOAT,
    @descriere_cat VARCHAR(300)
AS
BEGIN
    DECLARE @id_bij_nou INT = NULL;
    DECLARE @id_categorie_nou INT = NULL;

    --------------------- Bijuterie ---------------------
    BEGIN TRY
        BEGIN TRAN

        --validare
        EXEC ValideazaBijuterie @pret_bij, @descriere_bij, @gramaj_bij;

        INSERT INTO Bijuterie(pret_bij, descriere_bij, gramaj_bij)
        VALUES (@pret_bij, @descriere_bij, @gramaj_bij);
        SET @id_bij_nou = SCOPE_IDENTITY();

        COMMIT TRAN;

        INSERT INTO LogActiuni(tip_operatie, nume_tabel, data)
        VALUES('INSERT', 'Bijuterie', GETDATE());

        SELECT 'Bijuterie inserted' AS ResultBijuterie;
    END TRY
    BEGIN CATCH
        ROLLBACK TRAN;

        INSERT INTO LogActiuni(tip_operatie, nume_tabel, data)
        VALUES('ROLLBACK', 'Bijuterie', GETDATE());

        SELECT ERROR_MESSAGE() AS ResultBijuterie;
    END CATCH

    --------------------- Categorie ---------------------
    BEGIN TRY
        BEGIN TRAN

        --validare
        IF dbo.ValideazaDescriere(@descriere_cat) = 1
            RAISERROR('Descrierea categoriei nu este valida.', 16, 1);

        INSERT INTO Categorie(descriere)
        VALUES (@descriere_cat);
        SET @id_categorie_nou = SCOPE_IDENTITY();

        COMMIT TRAN;

        INSERT INTO LogActiuni(tip_operatie, nume_tabel, data)
        VALUES('INSERT', 'Categorie', GETDATE());

        SELECT 'Categorie inserted' AS ResultCategorie;
    END TRY
    BEGIN CATCH
        ROLLBACK TRAN;

        INSERT INTO LogActiuni(tip_operatie, nume_tabel, data)
        VALUES('ROLLBACK', 'Categorie', GETDATE());

        SELECT ERROR_MESSAGE() AS ResultCategorie;
    END CATCH

    --------------------- BijuterieCategorie ---------------------
    IF @id_bij_nou IS NOT NULL AND @id_categorie_nou IS NOT NULL
    BEGIN
        BEGIN TRY
            BEGIN TRAN

            INSERT INTO BijuterieCategorie(id_bij, id_categorie)
            VALUES(@id_bij_nou, @id_categorie_nou);

            COMMIT TRAN;

            INSERT INTO LogActiuni(tip_operatie, nume_tabel, data)
            VALUES('INSERT', 'BijuterieCategorie', GETDATE());

            SELECT 'BijuterieCategorie inserted' AS ResultBijuterieCategorie;
        END TRY
        BEGIN CATCH
            ROLLBACK TRAN;

            INSERT INTO LogActiuni(tip_operatie, nume_tabel, data)
            VALUES('ROLLBACK', 'BijuterieCategorie', GETDATE());

            SELECT ERROR_MESSAGE() AS ResultBijuterieCategorie;
        END CATCH
    END
    ELSE
    BEGIN
        SELECT 'BijuterieCategorie not inserted' AS ResultBijuterieCategorie;
    END
END
GO


----ok-------
select * from Bijuterie
select * from Categorie
select * from BijuterieCategorie
exec AdaugaBijuterieCategorie3 8840,'colier 2',81.5,'aur'
select* from LogActiuni
select * from Bijuterie
select * from Categorie
select * from BijuterieCategorie

---eroare Bijuterie---nu se adauga nimic
select * from Bijuterie
select * from Categorie
select * from BijuterieCategorie
exec AdaugaBijuterieCategorie3 -010,'',0,''
select* from LogActiuni
select * from Bijuterie
select * from Categorie
select * from BijuterieCategorie

---eroare Categorie--se adauga bijuterie
select * from Bijuterie
select * from Categorie
select * from BijuterieCategorie
exec AdaugaBijuterieCategorie3 18980,'bratara',26.90,''
select* from LogActiuni
select * from Bijuterie
select * from Categorie
select * from BijuterieCategorie