use JewelryShop
GO

CREATE OR ALTER PROCEDURE DeadLock1
AS
BEGIN
    BEGIN TRY
        BEGIN TRANSACTION;

        PRINT 'LOCK id=1';
        UPDATE Angajati SET post = 'manager_deadlock1' WHERE id_angajat = 1;
		INSERT INTO LogActiuni(nume_tabel,tip_operatie,data) VALUES ('Angajati','UPDATE deadlock1',GETDATE())

        WAITFOR DELAY '00:00:10';

        PRINT 'LOCK id=2';
        UPDATE Angajati SET post = 'manager_deadlock1' WHERE id_angajat = 2;
		INSERT INTO LogActiuni(nume_tabel,tip_operatie,data) VALUES ('Angajati','UPDATE deadlock1',GETDATE())

        COMMIT;
    END TRY
    BEGIN CATCH
        PRINT 'Eroare detectata în DeadLock1. Se face ROLLBACK.';
        IF @@TRANCOUNT > 0
            ROLLBACK;
			INSERT INTO LogActiuni(nume_tabel, tip_operatie, data)
				VALUES ('Angajati deadlock1', 'Rollback', GETDATE());
        THROW;
    END CATCH
END;

exec DeadLock1
select * from Angajati
select * from LogActiuni

go
CREATE OR ALTER PROCEDURE DeadLock1Retry
AS
BEGIN
    DECLARE @RetryDone BIT = 0;
    DECLARE @Succeeded BIT = 0;

    WHILE @Succeeded = 0
    BEGIN
        BEGIN TRY
            BEGIN TRANSACTION;

            PRINT 'LOCK id=1';
            UPDATE Angajati SET post = 'manager_deadlock1' WHERE id_angajat = 1;
            INSERT INTO LogActiuni(nume_tabel, tip_operatie, data)
            VALUES ('Angajati', 'UPDATE deadlock1', GETDATE());

            WAITFOR DELAY '00:00:10';

            PRINT 'LOCK id=2';
            UPDATE Angajati SET post = 'manager_deadlock1' WHERE id_angajat = 2;
            INSERT INTO LogActiuni(nume_tabel, tip_operatie, data)
            VALUES ('Angajati', 'UPDATE deadlock1', GETDATE());

            COMMIT;
            SET @Succeeded = 1;
            PRINT 'Tranzaction succeded.';
        END TRY
        BEGIN CATCH
            IF @@TRANCOUNT > 0
                ROLLBACK;
				INSERT INTO LogActiuni(nume_tabel, tip_operatie, data)
				VALUES ('Angajati deadlock1', 'Rollback', GETDATE());

            IF ERROR_NUMBER() = 1205 AND @RetryDone = 0
            BEGIN
                PRINT 'Deadlock detected. Retry the transaction';
                SET @RetryDone = 1;
                WAITFOR DELAY '00:00:02';
                CONTINUE;
            END
            ELSE
            BEGIN
                PRINT 'Error: ' + ERROR_MESSAGE();
                SET @Succeeded = 1;
                THROW;
            END
        END CATCH
    END
END;

exec DeadLock1Retry