create table person
( id bigint primary key ,
  name varchar not null,
  age integer not null default 10,
  gender varchar default 'female' not null ,
  address varchar
  );

alter table person add constraint ch_gender check ( gender in ('female','male') );

insert into person values (1, 'Anna', 16, 'female', 'Moscow');
insert into person values (2, 'Andrey', 21, 'male', 'Moscow');
insert into person values (3, 'Kate', 33, 'female', 'Kazan');
insert into person values (4, 'Denis', 13, 'male', 'Kazan');
insert into person values (5, 'Elvira', 45, 'female', 'Kazan');
insert into person values (6, 'Irina', 21, 'female', 'Saint-Petersburg');
insert into person values (7, 'Peter', 24, 'male', 'Saint-Petersburg');
insert into person values (8, 'Nataly', 30, 'female', 'Novosibirsk');
insert into person values (9, 'Dmitriy', 18, 'male', 'Samara');


create table pizzeria
(id bigint primary key ,
 name varchar not null ,
 rating numeric not null default 0);

alter table pizzeria add constraint ch_rating check ( rating between 0 and 5);

insert into pizzeria values (1,'Pizza Hut', 4.6);
insert into pizzeria values (2,'Dominos', 4.3);
insert into pizzeria values (3,'DoDo Pizza', 3.2);
insert into pizzeria values (4,'Papa Johns', 4.9);
insert into pizzeria values (5,'Best Pizza', 2.3);
insert into pizzeria values (6,'DinoPizza', 4.2);


create table person_visits
(id bigint primary key ,
 person_id bigint not null ,
 pizzeria_id bigint not null ,
 visit_date date not null default current_date,
 constraint uk_person_visits unique (person_id, pizzeria_id, visit_date),
 constraint fk_person_visits_person_id foreign key  (person_id) references person(id),
 constraint fk_person_visits_pizzeria_id foreign key  (pizzeria_id) references pizzeria(id)
 );

insert into person_visits values (1, 1, 1, '2022-01-01');
insert into person_visits values (2, 2, 2, '2022-01-01');
insert into person_visits values (3, 2, 1, '2022-01-02');
insert into person_visits values (4, 3, 5, '2022-01-03');
insert into person_visits values (5, 3, 6, '2022-01-04');
insert into person_visits values (6, 4, 5, '2022-01-07');
insert into person_visits values (7, 4, 6, '2022-01-08');
insert into person_visits values (8, 5, 2, '2022-01-08');
insert into person_visits values (9, 5, 6, '2022-01-09');
insert into person_visits values (10, 6, 2, '2022-01-09');
insert into person_visits values (11, 6, 4, '2022-01-01');
insert into person_visits values (12, 7, 1, '2022-01-03');
insert into person_visits values (13, 7, 2, '2022-01-05');
insert into person_visits values (14, 8, 1, '2022-01-05');
insert into person_visits values (15, 8, 2, '2022-01-06');
insert into person_visits values (16, 8, 4, '2022-01-07');
insert into person_visits values (17, 9, 4, '2022-01-08');
insert into person_visits values (18, 9, 5, '2022-01-09');
insert into person_visits values (19, 9, 6, '2022-01-10');


create table menu
(id bigint primary key ,
 pizzeria_id bigint not null ,
 pizza_name varchar not null ,
 price numeric not null default 1,
 constraint fk_menu_pizzeria_id foreign key (pizzeria_id) references pizzeria(id));

insert into menu values (1,1,'cheese pizza', 900);
insert into menu values (2,1,'pepperoni pizza', 1200);
insert into menu values (3,1,'sausage pizza', 1200);
insert into menu values (4,1,'supreme pizza', 1200);

insert into menu values (5,6,'cheese pizza', 950);
insert into menu values (6,6,'pepperoni pizza', 800);
insert into menu values (7,6,'sausage pizza', 1000);

insert into menu values (8,2,'cheese pizza', 800);
insert into menu values (9,2,'mushroom pizza', 1100);

insert into menu values (10,3,'cheese pizza', 780);
insert into menu values (11,3,'supreme pizza', 850);

insert into menu values (12,4,'cheese pizza', 700);
insert into menu values (13,4,'mushroom pizza', 950);
insert into menu values (14,4,'pepperoni pizza', 1000);
insert into menu values (15,4,'sausage pizza', 950);

insert into menu values (16,5,'cheese pizza', 700);
insert into menu values (17,5,'pepperoni pizza', 800);
insert into menu values (18,5,'supreme pizza', 850);

create table person_order
(
    id bigint primary key ,
    person_id  bigint not null ,
    menu_id bigint not null ,
    order_date date not null default current_date,
    constraint fk_order_person_id foreign key (person_id) references person(id),
    constraint fk_order_menu_id foreign key (menu_id) references menu(id)
);

insert into person_order values (1,1, 1, '2022-01-01');
insert into person_order values (2,1, 2, '2022-01-01');

insert into person_order values (3,2, 8, '2022-01-01');
insert into person_order values (4,2, 9, '2022-01-01');

insert into person_order values (5,3, 16, '2022-01-04');

insert into person_order values (6,4, 16, '2022-01-07');
insert into person_order values (7,4, 17, '2022-01-07');
insert into person_order values (8,4, 18, '2022-01-07');
insert into person_order values (9,4, 6, '2022-01-08');
insert into person_order values (10,4, 7, '2022-01-08');

insert into person_order values (11,5, 6, '2022-01-09');
insert into person_order values (12,5, 7, '2022-01-09');

insert into person_order values (13,6, 13, '2022-01-01');

insert into person_order values (14,7, 3, '2022-01-03');
insert into person_order values (15,7, 9, '2022-01-05');
insert into person_order values (16,7, 4, '2022-01-05');

insert into person_order values (17,8, 8, '2022-01-06');
insert into person_order values (18,8, 14, '2022-01-07');

insert into person_order values (19,9, 18, '2022-01-09');
insert into person_order values (20,9, 6, '2022-01-10');

INSERT INTO menu (id, pizzeria_id, pizza_name, price)
VALUES (19, 2, 'greek pizza', 800);

INSERT INTO menu (id, pizzeria_id, pizza_name, price) 
	VALUES ((SELECT MAX(id)+1 FROM menu),
		(SELECT id FROM pizzeria WHERE name = 'Dominos'),
		'sicilian pizza', 900);

INSERT INTO person_visits (id, person_id, pizzeria_id, visit_date)
	VALUES ((SELECT MAX(id)+1 FROM person_visits),
		(SELECT id FROM person WHERE name = 'Denis'),
		(SELECT id FROM pizzeria WHERE name = 'Dominos'),
		'2022-02-24');

INSERT INTO person_visits (id, person_id, pizzeria_id, visit_date)
	VALUES ((SELECT MAX(id)+1 FROM person_visits),
		(SELECT id FROM person WHERE name = 'Irina'),
		(SELECT id FROM pizzeria WHERE name = 'Dominos'),
		'2022-02-24');

INSERT INTO person_order (id, person_id, menu_id, order_date)
	VALUES ((SELECT MAX(id)+1 FROM person_order),
		(SELECT id FROM person WHERE name = 'Denis'),
		(SELECT id FROM menu WHERE pizza_name = 'sicilian pizza'),
		'2022-02-24');

INSERT INTO person_order (id, person_id, menu_id, order_date)
	VALUES ((SELECT MAX(id)+1 FROM person_order),
		(SELECT id FROM person WHERE name = 'Irina'),
		(SELECT id FROM menu WHERE pizza_name = 'sicilian pizza'),
		'2022-02-24');

UPDATE menu
SET price = price - 0.1*price
WHERE pizza_name = 'greek pizza';

WITH menu_id AS (
    SELECT id FROM menu WHERE pizza_name = 'greek pizza'
),
max_id AS (
    SELECT MAX(id) AS max_id FROM person_order
),
new_ids AS (
    SELECT generate_series(
        (SELECT max_id + 1 FROM max_id),
        (SELECT max_id + (SELECT COUNT(*) FROM person) FROM max_id)
    ) AS id
)
INSERT INTO person_order (id, person_id, menu_id, order_date)
SELECT n.id, p.id, (SELECT id FROM menu_id), '2022-02-25'
FROM person p
CROSS JOIN new_ids n
WHERE n.id = (SELECT max_id + p.id FROM max_id);

DELETE FROM person_order WHERE order_date = '2022-02-25';

DELETE FROM menu WHERE pizza_name = 'greek pizza';

CREATE VIEW v_persons_female AS
    SELECT * FROM person
    WHERE person.gender = 'female';

CREATE VIEW v_persons_male AS
    SELECT * FROM person
    WHERE person.gender = 'male';

CREATE VIEW v_generated_dates AS
	SELECT generate_series('2022-01-01'::date, '2022-01-31'::date, '1 day')::date AS generated_date
	ORDER BY generated_date;

CREATE VIEW v_symmetric_union AS
	WITH R AS (SELECT * FROM person_visits WHERE visit_date = '2022-01-02'),
		S AS (SELECT * FROM person_visits WHERE visit_date = '2022-01-06')
	(SELECT person_id FROM R
	EXCEPT
	SELECT person_id FROM S)
	
	UNION
	
	(SELECT person_id FROM S
	EXCEPT
	SELECT person_id FROM R)
	ORDER BY person_id;

CREATE VIEW v_price_with_discount AS
	SELECT p.name, m.pizza_name, m.price, CAST(price - 0.1*price AS INTEGER) AS discount_price
	FROM person_order AS po
		JOIN person AS p ON po.person_id = p.id
		JOIN menu AS m ON po.menu_id = m.id
	ORDER BY name, pizza_name;

CREATE MATERIALIZED VIEW mv_dmitriy_visits_and_eats AS
	SELECT pz.name AS pizzeria_name
	FROM person_visits AS pv
		JOIN person AS p ON pv.person_id = p.id
		JOIN pizzeria AS pz ON pv.pizzeria_id = pz.id
		JOIN menu AS m ON pz.id = m.pizzeria_id
	WHERE p.name = 'Dmitriy' AND pv.visit_date = '2022-01-08' AND m.price < 800
WITH DATA;

INSERT INTO person_visits (id, person_id, pizzeria_id, visit_date)
	VALUES ((SELECT MAX(id)+1 FROM person_visits),
		(SELECT id FROM person WHERE name = 'Dmitriy'),
		(SELECT pz.id AS pizzeria_id
		FROM person_visits AS pv
			JOIN person AS p ON pv.person_id = p.id
			JOIN pizzeria AS pz ON pv.pizzeria_id = pz.id
			JOIN menu AS m ON pz.id = m.pizzeria_id
		WHERE m.price < 800
		EXCEPT
		SELECT pz.id AS pizzeria_id
		FROM person_visits AS pv
			JOIN person AS p ON pv.person_id = p.id
			JOIN pizzeria AS pz ON pv.pizzeria_id = pz.id
			JOIN menu AS m ON pz.id = m.pizzeria_id
		WHERE p.name = 'Dmitriy' AND pv.visit_date = '2022-01-08' AND m.price < 800),
		'2022-01-08');

REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;

DROP VIEW v_persons_female;
DROP VIEW v_persons_male;
DROP VIEW v_generated_dates;
DROP VIEW v_symmetric_union;
DROP VIEW v_price_with_discount;
DROP MATERIALIZED VIEW mv_dmitriy_visits_and_eats;

CREATE TABLE ways 
    (point1 VARCHAR,
    point2 VARCHAR,
    cost INT);

INSERT INTO ways (point1, point2, cost) VALUES
	('a', 'b', 10), ('b', 'a', 10),
	('a', 'd', 20), ('d', 'a', 20),
	('a', 'c', 15), ('c', 'a', 15),
	('b', 'c', 35), ('c', 'b', 35),
	('b', 'd', 25), ('d', 'b', 25),
	('c', 'd', 30), ('d', 'c', 30);

WITH tours AS (
  SELECT w1.point1 as first,
    w1.point2 as second,
    w2.point2 as third, 
    w3.point2 as fourth,
    w4.point2 as last,
    (w1.cost + w2.cost + w3.cost + w4.cost) as total_cost
  FROM ways w1
    JOIN ways w2 ON w2.point1 = w1.point2 AND w2.point2 != 'a'
    JOIN ways w3 ON w3.point1 = w2.point2 AND w3.point2 != w2.point1 AND w3.point2 != 'a'
    JOIN ways w4 ON w4.point1 = w3.point2 AND w4.point2 = 'a'
  WHERE w1.point1 = 'a'
)
SELECT total_cost, 
  CONCAT('{', first, ',', second, ',', third, ',', fourth, ',', last, '}') AS tour
FROM tours
WHERE total_cost = (SELECT MIN(total_cost) FROM tours)
ORDER BY total_cost, tour;

WITH tours AS (
  SELECT w1.point1 as first,
    w1.point2 as second,
    w2.point2 as third, 
    w3.point2 as fourth,
    w4.point2 as last,
    (w1.cost + w2.cost + w3.cost + w4.cost) as total_cost
  FROM ways w1
    JOIN ways w2 ON w2.point1 = w1.point2 AND w2.point2 != 'a'
    JOIN ways w3 ON w3.point1 = w2.point2 AND w3.point2 != w2.point1 AND w3.point2 != 'a'
    JOIN ways w4 ON w4.point1 = w3.point2 AND w4.point2 = 'a'
  WHERE w1.point1 = 'a'
)
SELECT total_cost, 
  CONCAT('{', first, ',', second, ',', third, ',', fourth, ',', last, '}') AS tour
FROM tours
WHERE total_cost = (SELECT MIN(total_cost) FROM tours)
  OR total_cost = (SELECT MAX(total_cost) FROM tours)
ORDER BY total_cost, tour;

CREATE INDEX idx_menu_pizzeria_id ON menu(pizzeria_id);
CREATE INDEX idx_person_order_person_id ON person_order(person_id);
CREATE INDEX idx_person_order_menu_id ON person_order(menu_id);
CREATE INDEX idx_person_visits_person_id ON person_visits(person_id);
CREATE INDEX idx_person_visits_pizzeria_id ON person_visits(pizzeria_id);
CREATE INDEX idx_person_name ON person(name);
CREATE INDEX idx_person_order_multi ON person_order(person_id, menu_id, order_date);
CREATE UNIQUE INDEX idx_menu_unique ON menu(pizzeria_id, pizza_name);
CREATE UNIQUE INDEX idx_person_order_order_date ON person_order(person_id, menu_id)
WHERE order_date = '2022-01-01';

CREATE TABLE person_discounts (
	id BIGINT PRIMARY KEY,
	person_id BIGINT NOT NULL,
	pizzeria_id BIGINT NOT NULL,
	discount NUMERIC(5,2),

	CONSTRAINT fk_person_discounts_person_id 
        FOREIGN KEY (person_id) 
        REFERENCES person(id),
    
    CONSTRAINT fk_person_discounts_pizzeria_id 
        FOREIGN KEY (pizzeria_id) 
        REFERENCES pizzeria(id)
);

WITH m_pz_id AS (
	SELECT m.id AS menu_id, pizzeria_id
	FROM menu AS m JOIN pizzeria AS pz ON m.pizzeria_id = pz.id
	GROUP BY pizzeria_id, menu_id
)
INSERT INTO person_discounts (id, person_id, pizzeria_id, discount)
SELECT ROW_NUMBER() OVER() AS id, person_id, pizzeria_id,
	(CASE
		WHEN COUNT(po.person_id) = 1
		THEN 10.5
		WHEN COUNT(po.person_id) = 2
		THEN 22
		ELSE 30
	END)
FROM person_order AS po
    JOIN m_pz_id AS mpz ON mpz.menu_id = po.menu_id
GROUP BY po.person_id, mpz.pizzeria_id
ORDER BY person_id;

CREATE UNIQUE INDEX idx_person_discounts_unique ON person_discounts(person_id, pizzeria_id);

ALTER TABLE person_discounts 
ADD CONSTRAINT ch_nn_person_id 
CHECK (person_id IS NOT NULL);

ALTER TABLE person_discounts 
ADD CONSTRAINT ch_nn_pizzeria_id 
CHECK (pizzeria_id IS NOT NULL);

ALTER TABLE person_discounts 
ADD CONSTRAINT ch_nn_discount 
CHECK (discount IS NOT NULL);

ALTER TABLE person_discounts 
ALTER COLUMN discount SET DEFAULT 0;

ALTER TABLE person_discounts 
ADD CONSTRAINT ch_range_discount 
CHECK (discount >= 0 AND discount <= 100);

COMMENT ON TABLE person_discounts IS
	'В данной таблице хранятся данные о том, какие скидки имеются для конкретных покупателей и в каких пиццериях';
COMMENT ON COLUMN person_discounts.id IS 'Уникальный идентификатор записи о скидке (первичный ключ)';
COMMENT ON COLUMN person_discounts.person_id IS 'Идентификатор конкретного покупателя';
COMMENT ON COLUMN person_discounts.pizzeria_id IS 'Идентификатор конкретной пиццерии';
COMMENT ON COLUMN person_discounts.discount IS
	'Идентификатор скидки, выдаваемой конкретному покупателю в конкретной пиццерии';

CREATE SEQUENCE seq_person_discounts START 1;

ALTER TABLE person_discounts 
ALTER COLUMN id SET DEFAULT nextval('seq_person_discounts');

SELECT setval('seq_person_discounts', (SELECT COUNT(*) + 1 FROM person_discounts));

UPDATE pizzeria SET rating = 3.0 WHERE name = 'Pizza Hut';
INSERT INTO pizzeria (id, name, rating)
    VALUES(10, 'Kazan Pizza', 5);
INSERT INTO pizzeria(id, name, rating) VALUES
    (11, 'Kazan Pizza 2', 4);
UPDATE pizzeria SET rating = 2.0 WHERE id = 1;
UPDATE pizzeria SET rating = 1.0 WHERE id = 2;

CREATE TABLE person_audit (
	created TIMESTAMP WITH TIME ZONE NOT NULL,
	type_event CHAR(1) default 'I' NOT NULL,
	row_id BIGINT NOT NULL,
	name VARCHAR,
	age INTEGER,
	gender VARCHAR,
	address VARCHAR,

	CONSTRAINT ch_type_event
	CHECK(type_event IN ('I', 'U', 'D'))
);

CREATE OR REPLACE FUNCTION fnc_trg_person_insert_audit() RETURNS trigger AS $person_audit$
    BEGIN
		IF (TG_OP = 'INSERT') THEN
            INSERT INTO person_audit
                    SELECT
                         current_timestamp,
                         'I',
                         new.id, new.name, new.age, new.gender, new.address;
        END IF;
        RETURN NULL;
    END;
$person_audit$ LANGUAGE plpgsql;

CREATE TRIGGER trg_person_insert_audit AFTER INSERT
    ON person
    FOR EACH ROW EXECUTE FUNCTION fnc_trg_person_insert_audit();

INSERT INTO person(id, name, age, gender, address)
VALUES (10,'Damir', 22, 'male', 'Irkutsk');

CREATE OR REPLACE FUNCTION fnc_trg_person_update_audit() RETURNS trigger AS $person_audit$
    BEGIN
		IF (TG_OP = 'UPDATE') THEN
            INSERT INTO person_audit
                    SELECT
                         current_timestamp,
                         'U',
                         new.id, new.name, new.age, new.gender, new.address;
        END IF;
        RETURN NULL;
    END;
$person_audit$ LANGUAGE plpgsql;

CREATE TRIGGER trg_person_update_audit AFTER UPDATE
    ON person
    FOR EACH ROW EXECUTE FUNCTION fnc_trg_person_update_audit();

UPDATE person SET name = 'Bulat' WHERE id = 10; 
UPDATE person SET name = 'Damir' WHERE id = 10;

CREATE OR REPLACE FUNCTION fnc_trg_person_delete_audit() RETURNS trigger AS $person_audit$
    BEGIN
		IF (TG_OP = 'DELETE') THEN
            INSERT INTO person_audit
                    SELECT
                         current_timestamp,
                         'D',
                         old.id, old.name, old.age, old.gender, old.address;
        END IF;
        RETURN NULL;
    END;
$person_audit$ LANGUAGE plpgsql;

CREATE TRIGGER trg_person_delete_audit AFTER DELETE
    ON person
    FOR EACH ROW EXECUTE FUNCTION fnc_trg_person_delete_audit();

DELETE FROM person WHERE id = 10;

CREATE OR REPLACE FUNCTION fnc_trg_person_audit() RETURNS trigger AS $person_audit$
    BEGIN
		IF (TG_OP = 'INSERT') THEN
            INSERT INTO person_audit
                    SELECT
                         now(),
                         'I',
                         new.id, new.name, new.age, new.gender, new.address;
		ELSIF (TG_OP = 'UPDATE') THEN
            INSERT INTO person_audit
                    SELECT
                         now(),
                         'U',
                         old.id, old.name, old.age, old.gender, old.address;
		ELSIF (TG_OP = 'DELETE') THEN
            INSERT INTO person_audit
                    SELECT
                         now(),
                         'D',
                         old.id, old.name, old.age, old.gender, old.address;
        END IF;
        RETURN NULL;
    END;
$person_audit$ LANGUAGE plpgsql;

CREATE TRIGGER trg_person_audit AFTER INSERT OR UPDATE OR DELETE
    ON person
    FOR EACH ROW EXECUTE FUNCTION fnc_trg_person_audit();

DELETE FROM person_audit;
DROP TRIGGER IF EXISTS trg_person_insert_audit ON person;
DROP TRIGGER IF EXISTS trg_person_update_audit ON person;
DROP TRIGGER IF EXISTS trg_person_delete_audit ON person;

INSERT INTO person(id, name, age, gender, address) VALUES (10,'Damir', 22, 'male', 'Irkutsk'); 
UPDATE person SET name = 'Bulat' WHERE id = 10; 
UPDATE person SET name = 'Damir' WHERE id = 10; 
DELETE FROM person WHERE id = 10;

CREATE VIEW v_persons_female AS
   SELECT * FROM person
   WHERE person.gender = 'female';

CREATE VIEW v_persons_male AS
   SELECT * FROM person
   WHERE person.gender = 'male';

CREATE OR REPLACE FUNCTION fnc_persons_female() RETURNS SETOF person AS $$
	SELECT * FROM v_persons_female;
$$ LANGUAGE sql;

CREATE OR REPLACE FUNCTION fnc_persons_male() RETURNS SETOF person AS $$
	SELECT * FROM v_persons_male;
$$ LANGUAGE sql;

DROP FUNCTION IF EXISTS fnc_persons_female();
DROP FUNCTION IF EXISTS fnc_persons_male();

CREATE OR REPLACE FUNCTION fnc_persons(pgender VARCHAR DEFAULT 'female') RETURNS SETOF person AS $$
	SELECT * FROM v_persons_female WHERE pgender = 'female'
    UNION ALL
    SELECT * FROM v_persons_male WHERE pgender = 'male';
$$ LANGUAGE sql;

CREATE OR REPLACE FUNCTION fnc_person_visits_and_eats_on_date(
	pperson VARCHAR DEFAULT 'Dmitriy',
	pprice NUMERIC DEFAULT 500,
	pdate DATE DEFAULT '2022-01-08'
)
RETURNS TABLE (name VARCHAR) AS $$
	BEGIN
		RETURN QUERY
			SELECT pz.name
			FROM person_order AS po
				JOIN person AS p ON po.person_id = p.id
				JOIN menu AS m ON po.menu_id = m.id
				JOIN pizzeria AS pz ON m.pizzeria_id = pz.id
			WHERE p.name = pperson AND m.price < pprice AND po.order_date = pdate;
    END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION func_minimum(VARIADIC arr NUMERIC[]) RETURNS NUMERIC AS $$
	BEGIN
		RETURN (SELECT MIN(val) FROM unnest(arr) AS val);
	END
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION fnc_fibonacci(pstop INTEGER DEFAULT 10) RETURNS TABLE(fibonacci BIGINT) AS $$
	DECLARE
		count INTEGER := 1;
		val BIGINT;
		past_val1 BIGINT := 1;
		past_val2 BIGINT := 0;
	BEGIN
		LOOP
	        EXIT WHEN past_val1 + past_val2 > pstop;
			IF count = 1 THEN
            	val := 0;
        	ELSIF count = 2 THEN
            	val := 1;
        	ELSE
            	val := past_val1 + past_val2;
        	END IF;

			fibonacci := val;
        	RETURN NEXT;
			
			past_val2 := past_val1;
        	past_val1 := val;
	        count := count + 1;
    	END LOOP;

		RETURN;	
	END;
$$ LANGUAGE plpgsql;

/*Стирание модели*/
DROP TRIGGER IF EXISTS trg_person_update_audit ON person;
DROP TRIGGER IF EXISTS trg_person_delete_audit ON person;
DROP TRIGGER IF EXISTS trg_person_audit ON person;
DROP FUNCTION IF EXISTS fnc_trg_person_insert_audit();
DROP FUNCTION IF EXISTS fnc_trg_person_update_audit();
DROP FUNCTION IF EXISTS fnc_trg_person_delete_audit();
DROP FUNCTION IF EXISTS fnc_trg_person_audit();
DROP FUNCTION IF EXISTS fnc_fibonacci(integer);
DROP FUNCTION IF EXISTS func_minimum(NUMERIC[]);
DROP FUNCTION IF EXISTS fnc_person_visits_and_eats_on_date(character varying,numeric,date);
DROP FUNCTION IF EXISTS fnc_persons(VARCHAR);
DROP FUNCTION IF EXISTS fnc_persons_female();
DROP FUNCTION IF EXISTS fnc_persons_male();
DROP FUNCTION IF EXISTS fnc_persons_male(character varying);
DROP VIEW IF EXISTS v_persons_female;
DROP VIEW IF EXISTS v_persons_male;
DROP VIEW IF EXISTS v_generated_dates;
DROP VIEW IF EXISTS v_symmetric_union;
DROP VIEW IF EXISTS v_price_with_discount;
DROP MATERIALIZED VIEW IF EXISTS mv_dmitriy_visits_and_eats;
DROP INDEX IF EXISTS idx_menu_pizzeria_id;
DROP INDEX IF EXISTS idx_person_order_person_id;
DROP INDEX IF EXISTS idx_person_order_menu_id;
DROP INDEX IF EXISTS idx_person_visits_person_id;
DROP INDEX IF EXISTS idx_person_visits_pizzeria_id;
DROP INDEX IF EXISTS idx_person_name;
DROP INDEX IF EXISTS idx_person_order_multi;
DROP INDEX IF EXISTS idx_menu_unique;
DROP INDEX IF EXISTS idx_person_order_order_date;
DROP INDEX IF EXISTS idx_person_discounts_unique;
DROP TABLE IF EXISTS person_audit;
DROP TABLE IF EXISTS ways;
DROP TABLE IF EXISTS person_discounts;
DROP SEQUENCE IF EXISTS seq_person_discounts;
DROP TABLE IF EXISTS person_order;
DROP TABLE IF EXISTS person_visits;
DROP TABLE IF EXISTS menu;
DROP TABLE IF EXISTS person;
DROP TABLE IF EXISTS pizzeria;