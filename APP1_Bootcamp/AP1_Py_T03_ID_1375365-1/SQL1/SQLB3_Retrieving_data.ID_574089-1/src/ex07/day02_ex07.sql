SELECT pz.name AS pizzeria_name
FROM person_visits AS pv
	JOIN person AS p ON pv.person_id = p.id
	JOIN pizzeria AS pz ON pv.pizzeria_id = pz.id
	JOIN menu AS m ON pz.id = m.pizzeria_id
WHERE p.name = 'Dmitriy' AND pv.visit_date = '2022-01-08' AND m.price < 800;