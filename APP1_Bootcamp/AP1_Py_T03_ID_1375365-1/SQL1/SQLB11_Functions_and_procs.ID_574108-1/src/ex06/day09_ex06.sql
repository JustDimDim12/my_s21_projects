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

select *  
from fnc_person_visits_and_eats_on_date(pprice := 800);

select *  
from fnc_person_visits_and_eats_on_date(pperson := 'Anna',pprice := 1300,pdate := '2022-01-01');