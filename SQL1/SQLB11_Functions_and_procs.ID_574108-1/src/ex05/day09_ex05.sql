DROP FUNCTION IF EXISTS fnc_persons_female();
DROP FUNCTION IF EXISTS fnc_persons_male();

CREATE OR REPLACE FUNCTION fnc_persons(pgender VARCHAR DEFAULT 'female') RETURNS SETOF person AS $$
	SELECT * FROM v_persons_female WHERE pgender = 'female'
    UNION ALL
    SELECT * FROM v_persons_male WHERE pgender = 'male';
$$ LANGUAGE sql;

select *
from fnc_persons(pgender := 'male');

select *
from fnc_persons();