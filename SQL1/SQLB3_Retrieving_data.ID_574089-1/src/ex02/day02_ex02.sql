SELECT COALESCE(p.name, '-') AS person_name, pv.visit_date, COALESCE(pz.name, '-') AS pizzeria_name
FROM (SELECT * FROM person_visits 
		WHERE visit_date BETWEEN '2022-01-01' AND '2022-01-03') AS pv
	FULL JOIN pizzeria AS pz ON pv.pizzeria_id = pz.id
	FULL JOIN person AS p ON pv.person_id = p.id
ORDER BY 1, 2, 3;