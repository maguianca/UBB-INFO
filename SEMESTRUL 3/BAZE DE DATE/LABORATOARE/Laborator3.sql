USE MagazinDeBijuterii;
GO 

SELECT * FROM Versiune;
SELECT * FROM Procent;

CREATE TABLE Versiune
(cod_v INT PRIMARY KEY IDENTITY,
 nr INT
 );
 INSERT INTO Versiune(nr)
 VALUES (0);

 CREATE PROCEDURE versiune1
 AS
 BEGIN 
	ALTER TABLE Procent
	ALTER COLUMN procent FLOAT ;
END;
GO


CREATE PROCEDURE versiune1undo
AS
BEGIN 
    ALTER TABLE Procent
	ALTER COLUMN procent DECIMAL(5,2);
END;
GO

CREATE PROCEDURE versiune2
AS 
BEGIN
	ALTER TABLE BorderouMarcare
	ADD CONSTRAINT pret_min DEFAULT 2 FOR pret_marcare;
    PRINT 'S-a adaugat o constrangere la coloana [pret_marcare] din [BorderouMarcare]'
END;
GO

CREATE PROCEDURE versiune2undo
AS 
BEGIN
	ALTER TABLE BorderouMarcare
	DROP CONSTRAINT pret_min
    PRINT 'S-a eliminat constrangerea pentru coloana [pret_marcare] din [BorderouMarcare]'
END;
GO


CREATE PROCEDURE versiune3
AS 
BEGIN
	CREATE TABLE Pietre(id int NOT NULL PRIMARY KEY, pret int NOT NULL,id_bijuterie VARCHAR(300))
	PRINT 'S-a creat un tabel nou [Pietre]'
END;
GO

CREATE PROCEDURE versiune3undo
AS 
BEGIN
	DROP TABLE Pietre
	PRINT 'S-a sters tabelul [Pietre]'
END;
GO

CREATE PROCEDURE versiune4
AS 
BEGIN
	ALTER TABLE Comanda
	ADD data_comanda date
	PRINT 'S-a adaugat un camp nou [data_comanda] la [Comenzi]'
END;
GO

CREATE PROCEDURE versiune4undo
AS
BEGIN
	ALTER TABLE Comanda
	DROP COLUMN data_comanda
	PRINT 'S-a eliminat campul [data-comanda] din [Comenzi]'
END;
GO

CREATE PROCEDURE versiune5
AS
BEGIN
	ALTER TABLE Pietre
	ADD CONSTRAINT tip_bijuterie FOREIGN KEY(id_bijuterie)REFERENCES Bijuterie(id_bij)
	PRINT 'S-a adaugat cheia straina [bijuterie] in tabelul [Pietre]'
END;
GO

CREATE PROCEDURE versiune5undo
AS
BEGIN
	ALTER TABLE Pietre 
	DROP CONSTRAINT tip_bijuterie
	PRINT 'S-a eliminat cheia straina [bijuterie] din tabelul [Pietre]'
END;
GO



CREATE OR ALTER PROCEDURE main @versiune INT
AS
BEGIN
		IF @versiune<0 OR @versiune>5
		BEGIN
			PRINT 'Versiunea este invalida'
			RETURN
		END
		DECLARE @versiune_cur AS INT
		SET @versiune_cur =(SELECT nr FROM Versiune)

		IF @versiune =@versiune_cur
		BEGIN
			PRINT 'Versiunea actuala este deja cea curenta!'
			RETURN
		END

		DECLARE @proc VARCHAR(30)
		DECLARE @proc_undo VARCHAR(30)

		DECLARE @ok AS INT
		SET @ok=0


		WHILE(@versiune_cur<@versiune)
		BEGIN
			SET @ok=@ok+1
			SET @versiune_cur=@versiune_cur+1
			SET @proc='versiune'+CAST(@versiune_cur AS VARCHAR(15))
			PRINT 'Se executa ' + @proc
			EXEC @proc
			IF (@@ERROR=0)
			BEGIN
				UPDATE Versiune
				SET nr=@versiune_cur
			END
			ELSE 
			BEGIN
				PRINT('Procedura are eroare')
				RETURN
			END

		END

		IF(@ok>0)
		BEGIN 
			RETURN 
		END

		WHILE(@versiune_cur>@versiune)
			BEGIN
				SET @proc_undo='versiune'+CAST(@versiune_cur AS VARCHAR(15))+'undo'
				PRINT 'Se executa '+@proc_undo
				EXEC @proc_undo
				SET @versiune_cur=@versiune_cur-1
				IF (@@ERROR=0)
				BEGIN
					UPDATE Versiune
					SET nr=@versiune_cur
				END
				ELSE 
				BEGIN
					PRINT('Procedura are eroare')
					RETURN
				END
			END
END
GO


EXEC versiune1;
EXEC versiune1undo;

EXEC versiune2;
EXEC versiune2undo;

EXEC versiune3;
EXEC versiune3undo;

EXEC versiune4;
EXEC versiune4undo;

EXEC versiune5;
EXEC versiune5undo;

EXEC main 0
EXEC main 1
EXEC main 2
EXEC main 3
EXEC main 4
EXEC main 5
EXEC main 10