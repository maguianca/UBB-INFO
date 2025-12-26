use JewelryShop
GO
CREATE OR ALTER PROCEDURE DeadLock2
AS
BEGIN
	--SET DEADLOCK_PRIORITY LOW;
    BEGIN TRY
        WAITFOR DELAY '00:00:02';

        BEGIN TRANSACTION;

        PRINT 'LOCK id=2';
        UPDATE Angajati SET post = 'manager_deadlock2' WHERE id_angajat = 2;
		INSERT INTO LogActiuni(nume_tabel,tip_operatie,data) VALUES ('Angajati','UPDATE deadlock2',GETDATE())

        WAITFOR DELAY '00:00:10';

        PRINT 'LOCK id=1';
        UPDATE Angajati SET post = 'manager_deadlock2' WHERE id_angajat = 1;
		INSERT INTO LogActiuni(nume_tabel,tip_operatie,data) VALUES ('Angajati','UPDATE deadlock2',GETDATE())

        COMMIT;
    END TRY
    BEGIN CATCH
        PRINT 'Eroare detectata în DeadLock2. Se face ROLLBACK.';
        IF @@TRANCOUNT > 0
            ROLLBACK;
			INSERT INTO LogActiuni(nume_tabel, tip_operatie, data)
				VALUES ('Angajati deadlock2', 'Rollback', GETDATE());
        THROW;
    END CATCH
END;

exec DeadLock2
go
CREATE OR ALTER PROCEDURE DeadLock2Retry
AS
BEGIN
    DECLARE @RetryDone BIT = 0;
    DECLARE @Succeeded BIT = 0;

    WHILE @Succeeded = 0
    BEGIN
        BEGIN TRY
            WAITFOR DELAY '00:00:02'; 

            BEGIN TRANSACTION;

            PRINT 'LOCK id=2';
            UPDATE Angajati SET post = 'manager_deadlock2' WHERE id_angajat = 2;
            INSERT INTO LogActiuni(nume_tabel, tip_operatie, data)
            VALUES ('Angajati', 'UPDATE deadlock2', GETDATE());

            WAITFOR DELAY '00:00:10';

            PRINT 'LOCK id=1';
            UPDATE Angajati SET post = 'manager_deadlock2' WHERE id_angajat = 1;
            INSERT INTO LogActiuni(nume_tabel, tip_operatie, data)
            VALUES ('Angajati', 'UPDATE deadlock2', GETDATE());

            COMMIT;
            SET @Succeeded = 1;
            PRINT 'Tranzaction succeded';
        END TRY
        BEGIN CATCH
            PRINT 'Error detected, rollback.';
            IF @@TRANCOUNT > 0
                ROLLBACK;
				INSERT INTO LogActiuni(nume_tabel, tip_operatie, data)
				VALUES ('Angajati deadlock2', 'Rollback', GETDATE());

            IF ERROR_NUMBER() = 1205 AND @RetryDone = 0
            BEGIN
                PRINT 'Deadlock detected, retry';
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



exec DeadLock2Retry

