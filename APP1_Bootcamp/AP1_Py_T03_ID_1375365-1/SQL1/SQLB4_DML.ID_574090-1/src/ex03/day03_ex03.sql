WITH gender_visits AS (SELECT pz.name AS pizzeria_name,
	    (CASE WHEN gender = 'female' THEN '+' END) AS is_female,
	    (CASE WHEN gender = 'male' THEN '+' END) AS is_male
	FROM person_visits AS pv
		JOIN person AS p ON pv.person_id = p.id
		JOIN pizzeria AS pz ON pz.id = pv.pizzeria_id)
(SELECT pizzeria_name
	FROM gender_visits
	GROUP BY pizzeria_name
	HAVING COUNT(is_female) > COUNT(is_male))
UNION ALL
(SELECT pizzeria_name
	FROM gender_visits
	GROUP BY pizzeria_name
	HAVING COUNT(is_female) < COUNT(is_male))
ORDER BY pizzeria_name;