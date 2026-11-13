SELECT name, rating
FROM (SELECT pz.name, pz.rating, pv.visit_date
	FROM pizzeria AS pz
	LEFT JOIN person_visits AS pv
	ON pz.id = pv.pizzeria_id)
WHERE visit_date IS NULL;