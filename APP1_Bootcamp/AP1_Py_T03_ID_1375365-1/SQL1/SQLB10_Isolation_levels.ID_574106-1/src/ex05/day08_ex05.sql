-- Session №1
BEGIN TRANSACTION ISOLATION LEVEL REPEATABLE READ;

-- Session №2
BEGIN TRANSACTION ISOLATION LEVEL REPEATABLE READ;

-- Session №1
SELECT SUM (rating) FROM pizzeria;

-- Session №2
INSERT INTO pizzeria (id, name, rating)
    VALUES(10, 'Kazan Pizza', 5);
COMMIT;

-- Session №1
SELECT SUM (rating) FROM pizzeria;
COMMIT;

SELECT SUM (rating) FROM pizzeria;

-- Session №2
SELECT SUM (rating) FROM pizzeria;