-- CREATE VIEW v_persons_female AS
--    SELECT * FROM person
--    WHERE person.gender = 'female';

-- CREATE VIEW v_persons_male AS
--    SELECT * FROM person
--    WHERE person.gender = 'male';

CREATE OR REPLACE FUNCTION fnc_persons_female() RETURNS SETOF person AS $$
	SELECT * FROM v_persons_female;
$$ LANGUAGE sql;

CREATE OR REPLACE FUNCTION fnc_persons_male() RETURNS SETOF person AS $$
	SELECT * FROM v_persons_male;
$$ LANGUAGE sql;

SELECT *
FROM fnc_persons_male();

SELECT *
FROM fnc_persons_female();