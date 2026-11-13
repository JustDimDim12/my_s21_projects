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