(SELECT pz.name AS pizzeria_name
	FROM person_visits AS pv
		JOIN person AS p ON pv.person_id = p.id
		JOIN pizzeria AS pz ON pz.id = pv.pizzeria_id
	WHERE p.name = 'Andrey')
EXCEPT
(SELECT pz.name AS pizzeria_name
	FROM menu AS m
		JOIN pizzeria AS pz ON pz.id = m.pizzeria_id
	    JOIN person_order AS po ON po.menu_id = m.id
	    JOIN person AS p on po.person_id = p.id
	WHERE p.name = 'Andrey')
ORDER BY pizzeria_name;