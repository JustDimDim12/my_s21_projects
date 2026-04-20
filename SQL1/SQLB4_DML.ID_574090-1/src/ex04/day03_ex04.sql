WITH gender_order AS (SELECT pz.name AS pizzeria_name,
		(CASE WHEN gender = 'female' THEN '+' END) AS is_female,
		(CASE WHEN gender = 'male' THEN '+'	END) AS is_male
	FROM menu AS m
	    JOIN pizzeria AS pz ON pz.id = m.pizzeria_id
	    JOIN person_order AS po ON po.menu_id = m.id
	    JOIN person AS p on po.person_id = p.id)
(SELECT pizzeria_name
	FROM gender_order
	GROUP BY pizzeria_name
	HAVING COUNT(is_female) = 0)
UNION ALL
(SELECT pizzeria_name
	FROM gender_order
	GROUP BY pizzeria_name
	HAVING COUNT(is_male) = 0)
ORDER BY pizzeria_name;