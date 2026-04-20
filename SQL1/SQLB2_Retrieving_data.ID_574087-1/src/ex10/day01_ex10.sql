SELECT (SELECT name FROM person WHERE id = po.person_id) AS person_name, 
	(SELECT pizza_name FROM menu WHERE id = po.menu_id) AS pizza_name, 
	(SELECT name FROM pizzeria WHERE id = m.pizzeria_id) AS pizzeria_name
FROM person_order AS po
	JOIN menu AS m ON po.menu_id = m.id
	JOIN person ON person.id = po.person_id
ORDER BY person_name, pizza_name, pizzeria_name