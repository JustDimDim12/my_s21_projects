-- Session №1
BEGIN TRANSACTION ISOLATION LEVEL REPEATABLE READ;

-- Session №2
BEGIN TRANSACTION ISOLATION LEVEL REPEATABLE READ;

-- Session №1
UPDATE pizzeria SET rating = 2.0 WHERE id = 1;

-- Session №2
UPDATE pizzeria SET rating = 5.0 WHERE id = 2;

-- Session №1
UPDATE pizzeria SET rating = 1.0 WHERE id = 2;

-- Session №2
UPDATE pizzeria SET rating = 4.5 WHERE id = 1;

-- Session №2
COMMIT;

-- Session №2
COMMIT;
